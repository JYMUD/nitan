// baigu.c �׹�ɭȻ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "�׹�ɭȻ"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int damage;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("���ֻ���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹����޷�ʩչ�����ơ�\n");

        if ((int)me->query_skill("huagu-mianzhang", 1) < 100)
                return notify_fail("��Ļ������ƻ�������죬���ữ���ơ�\n");

        if( query("neili", me)<300 )
                return notify_fail("����������������ܻ��ǡ�\n");

        if (me->query_skill_mapped("strike") != "huagu-mianzhang")
                return notify_fail("��û�м����������ƣ��޷�ʩչ�����ơ�\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -100, me);

        msg = BLU "$N"BLU"���ޱ��飬��Ȼ������ϣ�����$n"BLU"��ת��Ȧ���͵�����һ����ת��$n"BLU"��ǰ��\n"
              "���ֻ���һ����Ȧ����$n"BLU"����ӡ����ȥ��\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");

        if( ap / 2 + random(ap) > dp )
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(random(3));
                damage=query("neili", target)/2;
                if (damage < 300) damage = 300;

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                          CYN"$n"CYN"��æ����ȴ�Ѳ�����ֻ�����������Ѿۣ�������������̱����\n"NOR);
        } else
        {
                me->start_busy(2);
                msg += HIY"����$pҲ��������бԾ���ܿ��˵���Ҫ����\n"NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}
