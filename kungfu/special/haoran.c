
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIW "��Ȼ����" NOR; }

int perform(object me, string skill, string arg)
{
        int joblv, damage_up;
      
        joblv = me->query_joblv();

        if (me->query_temp("special2/haoran"))
                return notify_fail("���Ѿ����˹����ˡ�\n");

                if (me->query("yhjob/job") != "����")
                                return notify_fail("���ְҵ�����޷�ʩչ��\n");

                if (me->query("neili") < 600)
                                return notify_fail("����������㣬�޷�ʩչ��\n");

                if (joblv < 20)
                                return notify_fail("���ְҵ�ȼ����㣬�޷�ʩչ��\n");                

        if (me->is_busy())return notify_fail("����æ����˵�ɣ�\n");

        message_vision(HIM "$N" HIM "ʩչ����Ȼ��������ʱȫ��������֣�\n" NOR, me);
 
        me->add("neili", -600);
        me->start_busy(1);

        // �ֻص���������
        joblv = joblv + me->query("lhpoint/special/haoran") * 8;

        me->set_temp("special2/haoran", joblv);
        me->add_temp("apply/damage", joblv * 100);
        me->add_temp("apply/unarmed_damage", joblv * 100);
        // �˺���������15%
        damage_up = me->query_temp("apply/damage") * 9 / 20;
        me->add_temp("apply/damage", damage_up);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, joblv, damage_up :), joblv * 10);
        return 1;
}

void remove_effect(object me, int joblv, int damage_up)
{
        if ((int)me->query_temp("special2/haoran"))
        {
                me->add_temp("apply/damage", -1 * joblv * 100);
                me->add_temp("apply/unarmed_damage", -1 * joblv * 100);
                me->add_temp("apply/damage", -1 * damage_up);
                me->delete_temp("special2/haoran");
                tell_object(me, "���Ȼ�����˹���ϡ�\n");
        }
}

