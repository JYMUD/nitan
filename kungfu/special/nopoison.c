// This program is a part of NITAN MudLIB
// nopoison.c Ⱥа����
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "Ⱥа����" NOR; }

int perform(object me, string skill)
{
        return notify_fail("��ת��ʱ�Զ�����ֻغ���ӵ�е����ʣ��Ӵ�֮��\n"
                           "�ٶ����֣����Ⱦ�������ܽ����Ǻ��ġ��ϳ���\n"
                           "�Լ������Ķ��������Σ����������Ǵ󷨡�Ǭ����\n"
                           "Ų��֮���񹦵ķ���Ҳ�����׻��⡣��ӵ�д�����\n"
                           "������о��ͼ�ȡʱ����Ч��50%��\n");
}