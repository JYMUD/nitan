// This program is a part of NITAN MudLIB
// ghost.c ��������
// Created by Lonely 04/05/2009

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIB "��������" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������ǧ��һ�������⾭���������������������\n"
                           "�˾�����Ӥ����������Ϊ��������ҽ�������䷨��\n"
                           "��������ز�ۡ�ӵ�˾������������ڹ����°빦����\n"
                           "������Ů������ֱ��������а�������ǿ���ħ����\n"
                           "���������Թ���ӵ�иü��ܵ����о��κο��Լ���\n"
                           "Ϊ�ڹ��ļ���ʱ���о�Ч�����50%�� ����������\n"
                           "Ҳ�����50%��\n");
}