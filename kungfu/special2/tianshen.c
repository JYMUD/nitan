// tianshen.c ��������
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIY "��������" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIY "�׵ۡ��Ƶۡ����ͬ����������֮��ӵ�о��춯��\n"
                               "�������������������ڵ�ϵ���ˡ���ô˼�������Ϊ\n"
                               "���������ӡ������ʦ��������ȡ��������ֵ����\n"
                               "���10%����Ϊ����ɷ���ǡ���ڤ˼�������10%��\n"
                               "ͬʱ��ӵ�иü����߿ɲ��������ƣ���ͬʱӵ������\n"
                               "���Ӽ���ɷ�����������ԡ�\n" NOR);


}