// zhuha.c �����Ե
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "�����Ե" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������ʱ���Ե�ɺϣ����ɷ���������\n"
                           "���ç����򣬴Ӵ�֮��ٶ����֡�\n");
}