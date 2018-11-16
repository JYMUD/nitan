

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

string name() { return HIW "���λ�λ" NOR; }

int perform(object me, string skill)
{
        int heal;
        int ap, dp;
        object target;

        if (me->query("jing") < 100)
                return notify_fail("��ľ��񲻼ã�����ʩչ���λ�λ��\n");

        me->clean_up_enemy();
        target = me->select_opponent();

        if (! me->is_fighting())
                return notify_fail("���ֲ����ڴ�ܣ�û�����������ʲô��\n");

        message_vision(HIM "$N" HIM "�鼱���ǣ�����$n" HIM
                       "���ϲ������Ҵ�һͨ���������컨��׹�������ɼ䣬����ʩչ�����Ȱ������֮زز��\n",
                       me, target);

        me->receive_damage("jing", 30 + random(20));

        message_vision(HIM "$n" HIM "�������κ������ƼٷǼ٣��������ޣ���֪���ԣ�"
                           "��ֻ�ǻ���һ����$N" HIM "���Ѿ����ߡ�\n" NOR,
                            me, target);
        me->set_temp("success_flee", HIG "��ɹ��������ˣ�\n" NOR);
        GO_CMD->do_flee(me);

        return 1;
}
