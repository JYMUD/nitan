// This program is a part of NITAN MudLIB
// musha.c ����ת��
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIR "����ת��" NOR; }

int perform(object me, string skill)
{
        return notify_fail("����ת��ʱ����������Ͷ̥ת������\n"
                           "ȡ�����Ǹ���ת����ӵ�г���û�е�\n"
                           "��ѧ����������ת����ӵ�иü��ܿ�\n"
                           "�����������ѧ�о��ٶȰٷ�֮��ʮ��\n"
                           "��ȡʵս����ٶ���߰ٷ�֮��ʮ��\n");
}