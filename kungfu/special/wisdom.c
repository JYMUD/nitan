// This program is a part of NITAN MudLIB
// wisdom.c ��������
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIY "��������" NOR; }

int perform(object me, string skill)
{
        return notify_fail("��������ת���Ĺ����и�Ӧ������������ǻۣ�ʹ\n"
                           "���ѧϰ���������ߡ�ӵ�иü����ߣ������ÿ\n"
                           "��ѧϰ����ϰ���о��������ް˰ٴΣ�ѧϰ����ϰ\n"
                           "���о�Ч������50%�� \n");
}
