// This program is a part of NITAN MudLIB
// yi.c ��Ų��

#include <ansi.h>

inherit F_SSERVER;

string name() { return "��Ų��"; }

int perform(object me, object target)
{
        object weapon;
        object *obs;
        object der;
        string msg;
        int ap, dp;
        int damage;
        int level;
        int i;

        me->clean_up_enemy();
        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("����Ų�ơ�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((level = (int)me->query_skill("qiankun-danuoyi", 1)) < 50)
                return notify_fail("���Ǭ����Ų�ƻ�û���������ڶ��㣬�޷�ʩչ��Ų�ơ�\n");

        if (query("neili", me) < 400)
                return notify_fail("�����������������޷�ʹ�á���Ų�ơ���\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIM "$N" HIM "������Ȼ��һ�䣬ġ�������������Ĵ�������������ǣ����$n"
              HIM "����ʽ��\n";

        ap = attack_power(me, "parry");
        dp = defense_power(target, "dodge");

        if (level >= 300)
        {
                // layer 7 force
                ap += level;
        }

        if (ultrap(target))
                dp += target->query_skill("matrial-cognize", 1);

        der = 0;
        me->start_busy(2);
        addn("neili", -350, me);
        if (ap / 2 + random(ap / 2) > dp)
        {
                // Success to make the target attack hiself
                msg += HIR "���$p" HIR "һ�л��������ô����Լ���"
                       "Ҫ���ϣ�����һ���ҽУ�ˤ����ȥ��\n" NOR;
                // damage = target->query("max_qi");
                damage = damage_power(me, "parry");
                damage+= query("jiali", me);
                damage *= 2;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage / 2, me);
        } else
        if (ap / 2 + random(ap) < dp)
        {
                // The enemy has defense
                msg += CYN "Ȼ��$p" CYN "�ڹ���񣬲�û�б�$P"
                       CYN "������ľ�����������\n" CYN;
        } else
        if (sizeof(obs = me->query_enemy() - ({ target })) == 0)
        {
                // No other enemy
                msg += HIC "���$p" HIC "����ʽĪ������ı�"
                       "�˷��򣬾�Ȼ���Ʋ�ס���Һ����û�б�"
                       "�ˣ�û����ɴ����\n" NOR;
        } else
        {
                string pname;
                // Sucess to make the target attack my enemy
                der = obs[random(sizeof(obs))];
                pname = der->name();
                if (pname == target->name()) pname = "��һ��" + pname;
                msg += HIG "���$p" HIG "��������ʽ��������"
                       "�ı��˷���ͻȻ����" + pname + HIG "��������" +
                       pname + HIG "���һ�����мܲ�����" NOR;
        }

        message_combatd(msg, me, target);

        if (der)
        {
                // Target attack my enemy
                for (i = 0; i < 2 + random(3); i++)
                {
                        if (! der->is_busy()) der->start_busy(2);
                        COMBAT_D->do_attack(target, der, query_temp("weapon", target));
                }
        }

        return 1;
}
