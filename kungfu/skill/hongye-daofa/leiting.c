//gladiator

#include <ansi.h>
#include <combat.h>

#define LEITING "��" HIR "��������" NOR "��" 

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        int extra;
        object weapon;
        int damage;

        if( userp(me) && !query("can_perform/hongye-daofa/leiting", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n"); 


        if(me->is_busy())
                return notify_fail("������û�գ���\n");

        if( (int)me->query_skill("hongye-daofa",1) < 150)
                return notify_fail("��Ŀǰ������ʹ����" LEITING "��\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "blade" )
                        return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query("neili", me)<500 )
                 return notify_fail("�������������\n");

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail(LEITING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
  if (! living(target)) 
         return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n"); 

        weapon=query_temp("weapon", me);
        damage = me->query_skill("hongye-daofa", 1) + random((int)me->query_skill("dodge")) / 2;
        extra = me->query_skill("hongye-daofa",1) / 10;

        addn_temp("apply/attack", extra, me);
        addn_temp("apply/damage", extra, me);

        msg = HIR  "\n$N���е�"+ weapon->name() +HIR"�ó����쵶�ƣ�" + 
                   weapon->name() + 
              HIR  "���Ƶ��ƣ�����������Ļ���$n��\n" NOR;
        message_vision(msg, me, target);

        if (random(10) > 5)
        {
                msg = COMBAT_D->do_damage(me,target, WEAPON_ATTACK, damage, 10,
                       HIC  "\n$N�������Ʊ���ǰ����һ�㣬�����Ŵ̶��ļ�����ֱ��$n��ȥ��\n" NOR);
                message_combatd(msg, me, target);
        } else
        {
                message_combatd(HIC  "\n$n���˷�������$N�ӵ�֮ǰ�Ƶ�����ʹ��$N���ò��ջ����߳ɵ�������\n" NOR, me, target);
                COMBAT_D->do_attack(me,target, weapon, TYPE_REGULAR, msg);
        }

        addn_temp("apply/attack", -extra, me);
        addn_temp("apply/damage", -extra, me);

        me->start_busy(1);
        return 1;
}