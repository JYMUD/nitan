// wushuang.c ��ʿ��˫
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "��ʿ��˫" NOR; }

int perform(object me, string skill)
{
        return notify_fail("�������߳Ǹ�������������Լ������ԣ�\n"
                           "���˴�Ħ��͸������������������������\n"
                           "�������������书�й������Ե����ơ�\n");
}