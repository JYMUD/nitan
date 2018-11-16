// This program is a part of NITAN MudLIB

#include <ansi.h>

string name() { return HIR "��������" NOR; }

int perform(object me, object target)
{
        string force;

        if (! target)
                return notify_fail("��Ҫ������Ϊ˭���ˣ�\n");

        if (target == me)
                return notify_fail(name() + "ֻ�ܶԱ���ʩչ��\n");

        if (me->is_fighting() || target->is_fighting())
                return notify_fail("ս�����޷��˹����ˡ�\n");

        if( query("not_living", target) )
                return notify_fail("���޷���" + target->name() + "���ˡ�\n");

        if ((int)me->query_skill("sun-finger", 1) < 100)
                return notify_fail("���һ��ָ��������죬����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("jingluo-xue", 1) < 100)
                return notify_fail("��Ծ���ѧ���˽ⲻ��������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("finger") != "sun-finger")
                return notify_fail("��û�м���һ��ָ������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "sun-finger")
                return notify_fail("��û��׼��һ��ָ������ʩչ" + name() + "��\n");

        if (! (force = me->query_skill_mapped("force")))
                return notify_fail("����뼤��һ���ڹ�����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ̫ǳ������ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if( query("jing", me)<100 )
                return notify_fail("�����ڵ�״̬���ѣ�����ʩչ" + name() + "��\n");

        if( query("eff_qi", target) >= query("max_qi", target) &&
            query("eff_jing", target) >= query("max_jing", target) )
                return notify_fail("�Է�û�����ˣ�����Ҫ�������ơ�\n");

        message_sort(HIY "\nֻ��$N" HIY "ĬĬ��ת" + to_chinese(force) +
                     HIY "����������һ������ͷ������ð��������Ȼʩչ��"
                     "һ��ָ�����Դ���ָ��˲ʱ�����$n" HIY "ȫ����ʮ��"
                     "����Ѩ������һ�ᣬ�����$n" HIY "���ۡ���һ���³�"
                     "������Ѫ����ɫ��ʱ������������ˡ�\n" NOR, me, target);

        addn("neili", -800, me);
        me->receive_damage("qi", 100);
        me->receive_damage("jing", 50);

        target->receive_curing("qi", 100 + (int)me->query_skill("force") +
                                     (int)me->query_skill("sun-finger", 1) * 3);

        if( query("qi", target) <= 0 )
                set("qi", 1, target);

        target->receive_curing("jing", 100 + (int)me->query_skill("force") / 3 +
                                       (int)me->query_skill("sun-finger", 1));

        if( query("jing", target) <= 0 )
                set("jing", 1, target);

        if ((int)target->query_condition("tiezhang_yin")
           || (int)target->query_condition("tiezhang_yang"))
        {
                target->clear_condition("tiezhang_yin");
                target->clear_condition("tiezhang_yang");
                tell_object(target, HIC "\n��ֻ�����ڲд�������ƾ�����"
                                    "���ˣ��о��ö��ˡ�\n" NOR);
        }

        if ((int)target->query_condition("freezing"))
        {
                target->clear_condition("freezing");
                tell_object(target, HIC "\n��ֻ��������תů����������֮������ʧ����Ӱ���١�\n" NOR);
        }

        if (! living(target))
                target->revive();

        if (! target->is_busy())
                target->stary_busy(2);

        message_vision("\n$N��Ŀڤ������ʼ�˹���Ϣ��\n", me);
        me->start_busy(10);
        return 1;
}
