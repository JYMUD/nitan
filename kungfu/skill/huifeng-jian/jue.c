// jue.c  �ط����������������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "����" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        string wname;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("����ʹ�õ��������ԣ��޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "huifeng-jian")
                return notify_fail("��û�м����ط�����������޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("huifeng-jian", 1) < 120)
                return notify_fail("��ط��������������죬�޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("���ڹ���򲻹����޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wname = weapon->name();

        damage = damage_power(me, "sword");

        // ��һ��
        ap = attack_power(me, "sword") + me->query_str();
        dp = defense_power(target, "parry") + target->query_str();
        msg = HIC "$N" HIC "һ�����ȣ����е�" + wname + HIC "��׼$n" HIC "ֱ����"
              "�£����ǻط��������" NOR + HIW "����" NOR + HIC "��������\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$p" HIR "�����ֵ���ȴ�����мܵ�ס����$P"
                                           HIR "��һ�����£���ʱ��Ѫ������\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "�ٵ�һ����Ӳ������$P"
                       CYN "��һ���ܿ���˿������\n" NOR;
        }

        // �ڶ���
        ap = attack_power(me, "sword") + me->query_int();
        dp = defense_power(target, "parry") + target->query_int();
        msg += "\n" HIC "$N" HIC "�漴һ����Ц�����е�" + wname +
               HIC "�����������������£����Ī�⣬��㽣������$n" HIC "��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           HIR "$p" HIR "��󲻽⣬һʱ���Կ�͸��"
                                           "�а��һ�����˼��У�����������\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "����һЦ����Ȼ����$P"
                CYN "����������������У����⽫֮�ܿ���\n" NOR;
        }

        // ������
        ap = attack_power(me, "sword") + me->query_con();
        dp = defense_power(target, "force") + target->query_con();
        msg += "\n" HIC "$N" HIC "��������һ���������е�" + wname +
               HIC "�û���һ��ǳǳ�Ĺ�â���˽���һ����$n" HIC "��ȥ��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 55,
                                           HIR "$p" HIR "�����ֵ���ֻ����һ��͸������"
                                           "Ϯ��������һ�����裬�������̱�ÿտյ�����\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "һ�����Ե�������������$P"
                CYN "���彣â��Ȼ������ȴδ����$p" CYN "�ֺ���\n" NOR;
        }

        // ������
        ap = attack_power(me, "sword") + me->query_dex();
        dp = defense_power(target, "dodge") + target->query_dex();
        msg += "\n" HIC "$N" HIC "�Ų�һ�Σ���Ȼ��������������죬���е�" + wname +
               HIC "Ӧ�����𣬴���$n" HIC "��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                           HIR "$p" HIR "ֻ������һ������ʱ��$P"
                                           HIR "��һ�����˸����У���Ѫ�Ĵ����䣡\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "��ȴ�Ǹ��죬ֻ��һ�ˣ���$P"
                CYN "��һ�п���������Ч��\n" NOR;
        }

        // ������
        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");
        msg += "\n" HIC "$N" HIC "һ����̾�������ú������飬" + wname +
               HIC "���ƶ�ת��������������˵����Ĳ���֮�⡣\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 65,
                                           HIR "$p" HIR "ֻ������ԡ�ڷ���һ�㣬�����о�Ȼ���޿ɵֵ�����"
                                           HIR "�������˸�Ѫ��ģ����\n" NOR);
        } else
        {
                msg += CYN "$p" CYN "�侲�Ƿ���˿����Ϊ����õ�����"
                       "����������ֵ�����©���������\n" NOR;
        }

        me->start_busy(3 + random(5));
        addn("neili", -400-random(100), me);
        message_combatd(msg, me, target);
        return 1;
}
