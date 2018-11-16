#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "���ݺ�" NOR; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ" + name() + "��\n");

        skill = me->query_skill("six-finger", 1);

        if (skill < 260)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" + name() + "��\n");

        if (me->query_skill("force") < 480)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<5500 )
                return notify_fail("���������Ϊ����,�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<850 )
                return notify_fail("������������������޷�ʩչ" + name() + "��\n");

        if( query_temp("weapon", me) )
                return notify_fail("������ǿ��ֲ���ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        msg = HIM "$N" HIM "һ����Х��ʮָ�׵����پ�����������ӿ����ͷ������"
              "�˷������಻������ʱ�����籼�������޾������������Ȼ����$n" HIM
              "��\n" NOR;

        ap = attack_power(me, "finger") + me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");

        if (target->query_skill("martial-cognize", 1) >= 800
            && random (100) == 1 )
        {
                addn("neili", -600, me);
                me->start_busy(3);
                msg += HIY "����$n" HIY "����һЦ��������䣬���׵Ķ����һ�У�\n"NOR;
        } else
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        damage += damage*n*15/100;
                        msg += HIM"$N"HIM"����������ת�ĸ�����ʹ�����ݺ��˺���ǿ��\n"NOR;
                }
                addn("neili", -800, me);
                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 100,
                                           HIR "ֻ��$n" HIR "һ���ҽУ����������"
                                           "͸��������˿ڴ���Ѫ��ʱ��ӿ��ʹ���ѵ���\n" NOR);
                me->start_busy(2);
        } else
        {
                addn("neili", -400, me);
                me->start_busy(3);
                msg += CYN "$n" CYN "��$N" CYN "������ӿ����������"
                       "�мܣ���æ����Ծ����\n" NOR;
        }
        message_sort(msg, me, target);

        return 1;
}

