// you.c ��ڤһ��
 
#include <ansi.h>
#include <combat.h>
 
inherit F_SSERVER;
 
int perform(object me, object target)
{
        string msg;
        int ap, dp, bs;
        int damage;
        object weapon;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if( query("gender", me) != "����" && !query("tianmo_jieti", me) )
                return notify_fail("����Ա��������ڹ���⣬�޷�ʹ�ô˾��У�\n");  

        if( userp(me) && !query("can_perform/pixie-jian/you", me) )
                return notify_fail("�㻹����ʹ�á���ڤһ������\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ڤһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("��û��װ��������������һ�С�\n");

        if( me->query_skill_mapped("sword") != "pixie-jian") 
                return notify_fail("�㲢û��ʹ�ñ�а�������޷�ʹ�ô˾��У�\n"); 

        if (me->query_skill("pixie-jian", 1) < 400)
                return notify_fail("��ı�а������������죬����ʹ����ڤһ����\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������ʹ����ڤһ����\n");
 
        msg = HIR "$N" HIR "��������ǰȥ����ʱ��ƽ�$n" HIR
              "������" + weapon->name() + HIR "��Ȼ����$p��Ҫ����\n" NOR;
 
        ap=me->query_skill("pixie-jian",1)*3/2+query("dex", me)*20+
             me->query_skill("martial-cognize", 1);
        dp=target->query_skill("parry")+query("dex", target)*20+
             target->query_skill("martial-cognize", 1);

        me->start_busy(2);
        addn("neili", -40, me);

        if (ap * 2 / 3 + random(ap) < dp || !living(target))
        {
                msg += HIG "Ȼ��$n" HIG "�ֵ��÷�����$N" HIG
                       "�Ĺ���һһ���⡣\n" NOR;
        } else
        {
                target->start_busy(1);
                addn("neili", -60, me);
                damage = ap / 4 + random(ap / 4) - random(80);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40,
                                           HIR "$n" HIR "��æ���ˣ�������ң��������$N"
                                           HIR "���У���Ѫ����һ�أ�\n" NOR);
        }

        message_combatd(msg, me, target);
        return 1;
}
