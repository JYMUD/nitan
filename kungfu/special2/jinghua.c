// jinghua.c ����ݼ��
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "��������" NOR; }

int perform(object me, string skill)
{
        return notify_fail("��ת���Ĺ��������ܵ�����������ľ�����\n"
                           "ת�������������õ��˼������������\n"
                           "��ܿ���ʹ����������ԡ����ǡ�����\n"
                           "�Լ��������Ƹ��������㡣\n");

}