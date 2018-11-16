// This program is a part of NITAN MudLIB
// feilong.c ��ɽ�����������������ɽ���

#include <ansi.h>
#include <combat.h>

string name() { return HIM "�����������ɽ�" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, fp, pp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�\n");

        if( query_temp("perform", me) == 1 ||
            query_temp("perform2", me) == 1 ||
            query_temp("perform3", me) == 1 )
                return notify_fail("�����������š���â���ء�\n");


        if ((int)me->query_skill("huashan-sword", 1) < 160)
                return notify_fail("�㻪ɽ����������죬�޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("dodge", 1) < 160)
                return notify_fail("���Ṧ��Ϊ�������޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "huashan-sword")
                return notify_fail("��û�м�����ɽ�������޷�ʹ��" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -280, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        fp = defense_power(target, "force");
        pp = defense_power(target, "parry");
        damage = damage_power(me, "sword");

        message_combatd(HIW "\n$N" HIW "��Хһ��������" + weapon->name() + HIW "�漴��ͣת������ӿ��\n"
                        "�������ǻ�ɽ���ھ�����" HIM "�����������ɽ�" HIW "��������" + weapon->name() + HIW
                        "\n����ͻ�䣬һ����ʱ��Ϊ������Ϯ��$n" HIW "����\n" NOR, me, target);

        msg = HIM "$N" HIM "������ȫ���˵��˽��ϣ�����һ������ͷֱ����\n" NOR;
        if (ap / 2 + random(ap) < dp)
                msg += CYN "$n" CYN "б��������\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40 + random(20),
                                           HIR "$n" HIR "��æ���ˣ���Ȼ��ܲ�������$N"
                                           HIR "��һ����ÿ�����Ѫ���������ˡ�\n" NOR);
        }

        msg += HIM "\n$N" HIM "Ȧת" + weapon->name() + HIM "���������������ƻֺ룬�����ݺᣬ���˷�����˼��\n" NOR;
        if (ap / 2 + random(ap) < fp)
                msg += CYN "$n" CYN "����ӽ���Խ����\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 40 + random(20),
                                           HIR "�������Ƶ���켰��$n" HIR "�������ü���"
                                           "���мܣ�ֻ��$N" HIR "����������$n"
                                           HIR "������ʱ��Ѫ���죡\n" NOR);
        }

        msg += HIM "\n$N" HIM "�������ã�����$p" HIM "���ģ�����֮�죬��λ֮׼����������δ�š�\n" NOR;
        if (ap / 2 + random(ap) < pp)
                msg += CYN "$n" CYN "���ڿ��У��������У�ֻ�ܻӳ�һ�У�������$N"
                       CYN "���ϣ���һ������ƮȻ��ȥ��\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50 + random(20),
                                           HIR "$n" HIR "���ڿ��У��������ü����У�ֻ��$N"
                                           HIR "�˽��ӹ���$n" HIR "�����Һ�����Ѫ���·ɽ���\n" NOR);
        }

        me->start_busy(4);
        message_combatd(msg, me, target);
        return 1;
}
