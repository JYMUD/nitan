// zhuque.c ��ȸ����
// Created by rcwiz for yhonline

#include <ansi.h>

inherit F_CLEAN_UP;

int is_scborn() { return 1; }

string name() { return HIR "��ȸ����" NOR; }

int perform(object me, string skill)
{
        return notify_fail(HIR "����һ��˰�����ǣ� ��������40%���ʲ���ʧ��\n"
                           "�ܲ������ε���ʱ����50% ���ʻ������Ǳ����˲�䱬����\n"
                           "��Ѫ��������˲���Զ��ָ�60%������ε����ر���ս����\n"
                           "�ɽ�����Ϊ�ε��������Ŀ��ܡ������ͨ�������غ�������\n"
                           "��ʧ���ܵļ��ʽ������������ص�Ч���ۻ���\n" NOR);
}