// This program is a part of NITAN MudLIB
// capture.c ��Ӱ����
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "��Ӱ����" NOR; }

int perform(object me, string skill)
{
        if (me->query_skillo("count", 1) < 800)
                me->set_skill("count", 800);

        if (me->query_skillo("mathematics", 1) < 800)
                me->set_skill("mathematics", 800);

        return notify_fail("����ת���������ݹ����󣬲����������������\n"
                           "���أ�������̬�����۵ס��˺����ܵ�����ж��\n"                          
                           "֮�����Ի�ת����ɵõ��������Լ������˰ټ���\n"
                           "ͬʱ��ӵ�иü����߿�ͬʱʩչ���һ���֮������\n"
                           "���ܵ��������Ե����ơ�    \n");
}