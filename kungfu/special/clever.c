// clever.c �츳��ӱ
// Created by Vin 26/8/2001

#include <ansi.h>

inherit F_CLEAN_UP;

string name() { return HIM "�츳��ӱ" NOR; }

int perform(object me, string skill)
{
        //return notify_fail("������ܹ�ʹ����������֪ʶ������Ҫ���á�\n");
        return notify_fail("������ܹ�ʹ������ѧϰ���ܺ��о����ܡ�\n"
                       HIC "�����ÿ��ѧϰ��������50�Σ����ÿ���о���������50�Ρ�\n" NOR);
}

