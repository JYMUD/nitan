
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "�����Ȼ" NOR; }

int perform(object me, string skill)
{
        return notify_fail("�������ܣ�����Ҫʩչ���ܴ��������������޺ͼ�"
                           "�����ޣ���������ָ��ٶȡ�\n");
}