// This program is a part of NITAN MudLIB
// sophistry.c �����ѧ
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIC "�����ѧ" NOR; }

int perform(object me, string skill)
{
        return notify_fail("��ͨ���Ӱټҵĸ���˼��ѧ˵���ڱ�����������\n"
                           "ɧ���ô˷��߿������Ƿǣ���ʯ�ɽ�ָ¹Ϊ��Ҳ\n"
                           "�����档������������������һ����ӵ�и��ؼ���\n"
                           "�����ȡ��ʦ������ʱ����ǰ�����������㣬��ȡ\n"
                           "�����񲻽��ͽ������������������\n");
}
