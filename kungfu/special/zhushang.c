// zhushang.c ����֮��
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "����֮��" NOR; }

int perform(object me, string skill)
{
        return notify_fail("����������ת�������в��������������\n"
                           "��֮����������ʱ��ʹ����֮��ʹ����\n"
                           "Ҳͬ���ܵ��˺���\n");
}