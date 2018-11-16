#include <ansi.h>
#include <combat.h>

#define HUI "��" HIR "�����л�" NOR "��"
#define HUIP "��" HIR "�����л�" HIW "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;

        if( userp(me) && !query("can_perform/xianglong-zhang/hui", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HUI "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 380)
                return notify_fail("���ڹ���Ϊ����������ʩչ" HUI "��\n");

        if( query("max_neili", me)<6000 )
                return notify_fail("��������Ϊ����������ʩչ" HUI "��\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 250)
                return notify_fail("�㽵��ʮ���ƻ�򲻹�������ʩչ" HUI "��\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("��û�м�������ʮ���ƣ�����ʩչ" HUI "��\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("��û��׼������ʮ���ƣ�����ʩչ" HUI "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("��������������������ʩչ" HUI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        // ��һ��
        ap=me->query_skill("strike")+query("str", me)*5;
        dp=target->query_skill("dodge")+query("dex", target)*5;

        message_sort(HIW "\n��Ȼ$N" HIW "���μ���������һ�������ֺ���һ��"
                     "����$n" HIW "�����ǽ���ʮ����" HUIP "����������֮��"
                     "˵���㵽������ɽ����֮����$n" HIW "��ӿ��ȥ������ʯ"
                     "���쾪�������ޱȡ�\n" NOR, me, target);

        if (ap * 3 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 60 + random(10),
                                          HIR "$P����һ�������ѻ���$p��ǰ��$p��"
                                          "���������ٱ��������С�\n" NOR);
        } else
        {
                msg = HIC "ȴ��$p����˫�ۣ�����Ӧ�ԣ�$P��"
                      "������ţ�뺣������жȥ��\n" NOR;
        }
        message_vision(msg, me, target);

        // �ڶ���
        ap=me->query_skill("strike")+query("str", me)*5;
        dp=target->query_skill("parry")+query("int", target)*5;

        message_sort(HIW "\n$N" HIW "һ�Ƽȳ���������Ȼ������$n" HIW "��"
                     "����֮�⣬������ǰ�������������ϲ�������һ��" HUIP
                     "��������������ŭ����ӿ���Ʋ��ɵ�����ʱ$p�����Ϣ��"
                     "�ͣ����㲻�ȡ�\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70 + random(10),
                                          HIR "$pһ���Һ�����$P��һ�ƻ�����ǰ��"
                                          "���꿦����˼����߹ǡ�\n" NOR);
        } else
        {
                msg = HIC "����$pȫ���ֵ��мܣ�����������"
                      "�࣬��$P������ж�����Ρ�\n" NOR;
        }
        message_vision(msg, me, target);

        // ������
        ap=me->query_skill("strike")+query("str", me)*5;
        dp=target->query_skill("force")+query("con", target)*5;

        message_sort(HIW "\n������$N" HIW "����б�ӣ�ǰ������δ����������"
                     "���ֵ�����Ȼ�ֹ���һ��" HUIP "���Ƽз��ƣ���������"
                     "����һ��������ǽ����ǰ�����ȥ��$n" HIW "ֻ����Ѫ��"
                     "ӿ����Ϣ���ǡ�\n" NOR, me, target);

        if (ap *11 / 20 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIR "���$p����������$P�ƾ���ʱ���ض�"
                                          "������ʱ������Ѫ���硣\n" NOR);
        } else
        {
                msg = HIC "$p�ۼ��������ͣ����μ��ˣ�˲��"
                      "Ʈ�����ɣ��ѳ�����֮�⡣\n" NOR;
        }
        message_vision(msg, me, target);
        me->start_busy(3 + random(4));
        addn("neili", -400-random(600), me);
        return 1;
}