
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "��תǬ��" NOR; }

int perform(object me, string skill)
{
        return notify_fail("�������ܵ������������ӵ����תǬ��֮�������߱���������������\n"
                           "����������+10%\n"
                           "�о�������+10 ��\n"
                           "�������ޣ�+500\n"
                           "�������ޣ�+500\n"
                           "������Ч������[�ɷ����]���ܿ��ٶ��������о�����10��\n"
                           "����Ҫ���á�\n");
}

