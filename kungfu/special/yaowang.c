
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIG "����ҩ��" NOR; }

int perform(object me, string skill)
{
        return notify_fail("�������ҩ���������ó����뻯�������๥�����֣���ʹ�����ж��̶ȼ���20%��\n"
                           "ͬʱ�����б���֪ʶ���ܵ���Ч����Ч������10%������Ҫ���á�\n");
}

