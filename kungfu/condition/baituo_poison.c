// baituo_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "baituo_poison"; }

string chinese_name() { return "�����߶�"; }

string update_msg_others()
{
        return HIR "$N" HIR "һ���Һ���ȫ�������������ɣ�ʹ�಻����\n" NOR;
}

string update_msg_self()
{
        return HIR "��ֻ��ȫ����ʹ�ޱȣ��������ܡ�\n" NOR;
}

string die_msg_others()
{
        return HIR "$N" HIR "���ݵ������ڵ��������˼��£�����û"
               "��㶯���ˡ�\n" NOR;
}

string die_reason()
{
        return "�������߶����Ķ���";
}