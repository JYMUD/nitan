// guimai.c ��������
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIM "��������" NOR; }

int perform(object me, string skill)
{
        return notify_fail("������ǧ��һ�������⾭��������������\n"
                           "�������˾�����Ӥ����������Ϊ������\n"
                           "��ҽ�������䷨����������ز�ۡ�����\n"
                           "������겻���ߣ��˺����������ڹ�����\n"
                           "�빦������������Ϊ�ȳ��˸��ߡ�������\n"
						   "Ů������ֱ��������а�������ǿ���ħ����\n"
						   "���������Թ���\n"
						   "ע��ӵ�иü��ܵ����о��κο��Լ���Ϊ\n"
						   "�ڹ��ļ���ʱ���о��ٶ����10%��������\n"
						   "����Ҳ�����30%��\n");
}