
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "�������" NOR; }

int perform(object me, string skill)
{
        return notify_fail("��ӵ��������ǿ���˺ͱƶ������������������Ƹ�����5%������Ҫ���á�\n");
}

