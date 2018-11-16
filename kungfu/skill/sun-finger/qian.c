#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "һָǬ��" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("sun-finger", 1) < 100)
                return notify_fail("��һ��ָ��������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 160)
                return notify_fail("��Ծ���ѧ�˽ⲻ��������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("��û�м���һ��ָ��������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("��û��׼��һ��ָ��������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "��Ȼʹ����" HIR "һָǬ��" HIY "����������ָ��"
              "��$n" HIY "̴��ҪѨ����ʽ�仯����֮����\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force") + me->query_skill("qiantian-zhi", 1);
        dp = defense_power(target, "parry") + me->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        damage += damage*n*15/100;
                        msg += HIM"$N"HIM"����������ת�ĸ�����ʹ��һָǬ���˺���ǿ��\n"NOR;
                }
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                           HIR "$n" HIR "ֻ���ؿ�һ�飬�ѱ�$N" HIR
                                           "һָ���У���ʱ��Ѫ��ӿ�����������Ѫ"
                                           "��\n" NOR);
                addn("neili", -100, me);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "����$n" CYN "������$N" CYN "����"
                       "�����������򵲿�����һָ��\n" NOR;
                me->start_busy(3);
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        return 1;
}
