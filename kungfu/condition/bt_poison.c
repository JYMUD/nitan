//ice_poison.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "bt_poison"; }

string chinese_name() { return "�����涾"; }

string update_msg_others()
{
       return HIB "$N������ͻȻ�������Σ��Եú�ʹ������ӡ�\n" NOR;
}

string update_msg_self()
{
        return HIB "��Ȼһ���ʹ����о�����������������������壡\n" NOR;
}