#include <ansi.h>
#include <combat.h>

#define SHENG "��" HIW "������" NOR "��"

inherit F_SSERVER;
 
int perform(object me, object target)
{
        object weapon;
        string msg;
                int i;
 
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHENG "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
              query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" SHENG "��\n");

        if (me->query_skill("tianjian", 1) < 20)
                return notify_fail("����콣��Ϊ������Ҫ���콣��ʮ����������ʩչ" SHENG "��\n");

        if (me->query_skill_mapped("sword") != "tianjian")
                return notify_fail("��û�м����콣������ʩչ" SHENG "��\n");

        if( query("neili", me)<15 )
                return notify_fail("������������Ҫ��15������������������ʩչ" SHENG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��Է������������ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "�����죬����" + weapon->name() +
              HIY "��ת��ͻȻ��ৣ�ৣ�����������������$n" HIY "��\n" NOR;

        message_combatd(msg, me, target);

                addn("neili", -10, me);

        me->start_busy(1 + random(2));
                addn_temp("apply/attack", me->query_skill("sword"), me);

                for (i = 0; i < 4; i++)
                {
                        if (! me->is_fighting(target))break;

                        if (random(2))target->start_busy(1);
                        
                        COMBAT_D->do_attack(me, target, weapon, 0);
                }

                addn_temp("apply/attack", -1*me->query_skill("sword"), me);

                if( query("newbie_quest/leixing", me) == "perform" )
                {
                                set("newbie_quest/completed", 1, me);
                                me->save();
                                tell_object(me, HIG "���Ѿ�ѧ�������ʩչ���У����ȥ���ϴ峤��ȡ�����ɣ�\n" NOR);
                }

        return 1;
}
