// qijin.c ������
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIG "������" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIG "�������������������棬�˰���������������š�\n"
                               "ӵ�д˼����߿�ʹ�о����ܴ������Ƽӱ����������\n"
                               "Ŀǰÿ�ο����о�300�Σ� ��ӵ�иü��ܺ��ÿ����\n"
                               "��600�Ρ�ͬʱ�� ӵ�иü��������о�����ʱ������\n"
                               "��Ǳ�ܼ���10%����������о�600�������ĵ�Ǳ��ԭ\n"
                               "Ϊ600�㣬���ʱΪ540�㡣���о�����С��10����\n"
                               "��������Ǳ������10%��Ч����\n" NOR);

}