
#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "�ɷ����" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������ܹ�ʹ������ѧϰ���ܺ��о����ܡ�\n"
                       HIC "�����ÿ��ѧϰ��������50�Σ����ÿ���о���������50�Ρ�\n" NOR);
}

