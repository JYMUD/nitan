// zhuha.c �����Ե
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "����ת��" NOR; }

int perform(object me, string skill)
{
        return notify_fail("����ת��ʱ����������Ͷ̥ת���������\n"
                                                   "�������������ȡ�����Ǹ���ת����ӵ��\n"
                                                   "����û�е���ѧ����������ת����ӵ�и�\n"
                                                   "���ܿ������������ѧ�о��ٶȰٷ�֮ʮ��\n"
                                                   "���Ҵ����������ٶ���߰ٷ�֮��ʮ����\n"
                                                   "ȡʵս����ٶ���߰ٷ�֮��ʮ��\n");

}