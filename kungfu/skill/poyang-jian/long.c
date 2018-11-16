#include <ansi.h>
#include <combat.h>

#define LONG "��" HIC "��������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;
        int neili, hit_point, time;

        /*
        if( userp(me) && !query("can_perform/poyang-jian/long", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
        */

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(LONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" LONG "��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ����������ʩչ" LONG "��\n");

        if (me->query_skill("poyang-jian", 1) < 180)
                return notify_fail("���������⽣��Ϊ����������ʩչ" LONG "��\n");

        if ((int)me->query_skill("dodge") < 200)
                return notify_fail("����Ṧ��򲻹�������ʩչ" LONG "��\n"); 

        if( query("max_neili", me)<2700 )
                return notify_fail("���������Ϊ���㣬����ʩչ" LONG "��\n");

        if( query("neili", me)<350 )
                return notify_fail("�����������������ʩչ" LONG "��\n");

        if (me->query_skill_mapped("sword") != "poyang-jian")
                return notify_fail("��û�м���������⽣������ʩչ" LONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");
        
        if( !query("real_perform/poyang-jian/long", me) )
        {
                msg = HIY "\nֻ��$N" HIY "����" + weapon->name() + HIY
                      "��ɨ������ʩ�����С�" HIC "��������" HIY "����"
                      "�����ݺᣬ����һ���������Ѷ���������$n\n" HIY "��" NOR;
               
                neili = 220;
                hit_point = 55;
                time = 2 + random(2);
        }

        else
        {
                msg = HIW "\n����$N" HIW "����" + weapon->name() + HIW 
                      "�԰���к��������������ֱ������һ������һ�㣬��"
                      "��������⽣�ľ��衸" HIY "��������" HIW "����һ"
                      "��������$N" HIW "ʹ�������ߣ�����������Ȼ������$n\n" 
                      HIW "��" NOR;

                neili = 300;
                hit_point = 80;
                time = 3 + random(4);
        }
        message_sort(msg, me, target);

        ap = me->query_skill("sword");

        dp = target->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                addn("neili", -neili, me);
                me->start_busy(time);
                msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, hit_point,
                                           HIR "$n" HIR "�������������ͣ� �赲��"
                                           "���� ��ʱ��" + weapon->name() + HIR 
                                           "���ˣ��಻���ԡ�\n" NOR);
        } else
        {
                addn("neili", -150, me);
                me->start_busy(1 + random(2));
                msg = CYN "��ȴ��" CYN "$n" CYN "�͵İεض��𣬱ܿ���"
                      CYN "$N" CYN "�������͵�һ�С�\n" NOR;
        }
        message_vision(msg, me, target);

        return 1;
}