// This program is a part of NITAN MudLIB
// monster.c ��������
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "��������" NOR; }

int perform(object me, string skill)
{
        return notify_fail("����������ת�������в��������������\n"
                           "��֮����������ʱ��ʹ����֮��ʹ����\n"
                           "Ҳͬ���ܵ��˺���\n");
}