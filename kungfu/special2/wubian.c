
#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "�����ޱ�" NOR; }

int perform(object me, string skill)
{
        return notify_fail("��������ת���Ĺ����и�Ӧ�����µ������ǻۣ�ʹ���ѧϰ���������ߡ�\n"
                       HIY "�����ÿ��ѧϰ��������100�Σ����ÿ���о���������100�Ρ�\n" NOR);
}