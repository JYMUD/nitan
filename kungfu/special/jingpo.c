
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "Ǭ������" NOR; }

int perform(object me, string skill)
{
        return notify_fail("��������һ����ӵ�и��ߵľ�����Ϊ�������������ֵ30%������Ҫ���á�\n");
}

