
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "�����޼�" NOR; }

int perform(object me, string skill)
{
        return notify_fail("���������б�����磬���ʦ������ɻ�ö����5%�Ľ���������Ҫ���á�\n");
}

