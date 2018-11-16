#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "�������" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("�������ֲ���ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����Ϊ�������޷�ʩչ" + name() + "��\n");

        if (me->query_skill("piaoxue-zhang", 1) < 180)
                return notify_fail("���Ʈѩ��������Ϊ�������޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 || query("max_neili", me)<3500 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        /*
        if (me->query_skill_mapped("force") != "emei-jiuyang" &&
            me->query_skill_mapped("force") != "wudang-jiuyang" &&
            me->query_skill_mapped("force") != "shaolin-jiuyang" &&
            me->query_skill_mapped("force") != "jiuyang-shengong")
                return notify_fail("��û�м����ڹ�Ϊ�����񹦣��޷�ʩչ" + name() + "��\n");
        */

        if (me->query_skill_mapped("strike") != "piaoxue-zhang")
                return notify_fail("��û�м���Ʈѩ�����ƣ��޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "piaoxue-zhang")
                return notify_fail("��û��׼��Ʈѩ�����ƣ��޷�ʩչ" + name() + "��\n");

        if( !query_temp("powerup", me) )
                return notify_fail("����뽫ȫ���������������ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "����ȫ��������ʱ�����ŷ���ȫ�������ž��"
              "�죬��Ȼһ����$n" HIY "\nȫ���ĳ�������һ���еУ�����һ"
              "�С�������ա���\n" NOR;

        ap = attack_power(me, "strike") +
             me->query_skill("force") +
             query("str", me)*10;

        dp = defense_power(target, "dodge") +
             target->query_skill("force") +
             query("con", me)*10;

        if (target->query_skill_mapped("force") == "jiuyang-shengong")
        {
                addn("neili", -800, me);
                me->start_busy(5);
                msg += HIW "ֻ����Ȼһ�����죬$n" HIW "�ѱ�һ�����У���$N"
                       HIW "ֻ��ȫ���������罭����\n��������ˮ�齻�ڣ���"
                       "ʱ��ʧ����Ӱ���١�\n" NOR;
        } else
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike") + me->query_skill("mahayana", 1);
                addn("neili", -800, me);
                me->start_busy(3);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                           HIR "ֻ����Ȼһ�����죬$n" HIR "��$N"
                                           HIR "һ�����У����ӱ��絾�ݰ�ƽƽ�ɳ�"
                                           "����\n��ˤ�ڵ��£�Ż��һ�����Ѫ����"
                                           "Ҳ������\n" NOR);
        } else
        {
                addn("neili", -500, me);
                me->start_busy(4);
                msg += CYN "����$p" CYN "������񣬼�ʱ������"
                       CYN "$P" CYN "������ǣ�����㿪����һ����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
