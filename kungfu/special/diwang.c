// diwang.c ����֮��
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "����֮��" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIM "��������ӵ�е���֮�������������Կ����ø�����\n"
                               "�㡣ͬʱ���������޺;������޸�����20%�� ��Ѫ��\n"
                               "���ٶ�����30%��\n" NOR);

}