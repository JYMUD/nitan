
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "��ǹ�ལ" NOR; }

int perform(object me, string skill)
{
        return notify_fail("��ӵ������֮�ڲţ��ܹ������Ƿǣ��ߵ��ڰס����׻ƺڵꡢ��ͨNPC�̵깺��\n"
                           "��Ʒ�ɻ���м�9�۵��Żݡ�ͬʱ���߱���������������Ч������Ҫ���á�\n");
}

