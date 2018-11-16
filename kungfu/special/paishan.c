
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "��ɽ����" NOR; }

int perform(object me, string skill, string arg)
{
        int add_dam;     

        if (me->query_temp("special/paishan"))
                return notify_fail("��ɽ���������Ѿ���ʩչ���ˡ�\n");

        if (me->is_busy())return notify_fail("����æ����˵�ɣ�\n");

        message_vision(HIW "$N" HIW "˫ȭ���գ�ɱ�����ˣ������޷�����һ������������ɽ�������ӿ�� ����\n" NOR, me);
 
        me->start_busy(1);

        if (me->query_temp("weapon"))
                add_dam = 1 + me->query_temp("apply/damage") / 20;
        else
                add_dam = 1 + (me->query_temp("apply/damage") + me->query_temp("apply/unarmed_damage")) / 20;

        me->set_temp("special/paishan", 1);
        me->add_temp("apply/damage", add_dam);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, add_dam :), 180);
        return 1;
}

void remove_effect(object me, int add_dam)
{
        if ((int)me->query_temp("special/paishan"))
        {
                me->add_temp("apply/damage", -1 * add_dam);
                me->delete_temp("special/paishan");
                tell_object(me, "����ɽ�����ؼ�ʩչ��ϡ�\n");
        }
}

