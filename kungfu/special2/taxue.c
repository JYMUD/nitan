// taxue.c ̤ѩ�޺�
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIW "̤ѩ�޺�" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIW "��������������任���У��ܹ���ּ������ڵ�Ǳ����\n"
                               "ʹ������æ�ҵ�ʱ�������һ�����ʽ���æ��ʱ�䣬\n"
                               "�ۺ�Ч���������һ�����������ǶЧ�������ǿ��Ժ�\n"
                               "���һ�����������ǶЧ�����ݡ�\n"
                               "ͬʱ�����о��Ṧ�༼�ܵ�ʱ���ٶ�����50%��\n" NOR);

}