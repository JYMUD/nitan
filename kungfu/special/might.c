// might.c ����ȭ
// Created by Vin 25/5/2002

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIW "��֮��" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������Զ�����������һ��ϡ��Ѫ�����ִ�����Ҳ���������޼�����\n"
                           "��ӵ�д�Ѫ����������ǿ��׳���������ӵ�п�Ѫ��֮�ˣ�����\n"
                           "ʹ��ļ����������20%��\n");
}

