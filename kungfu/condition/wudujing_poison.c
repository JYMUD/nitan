#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "wudujing_poison"; }

string chinese_name() { return "�嶾��"; }

string update_msg_others()
{
       return HIW "$N�ؿ�һ�ȣ�Ѫ����ӿ�������赹��\n" NOR;
}

string update_msg_self()
{
        return HIM "ֻ�е��ؿ�һ�ȣ�Ѫ���͵���ӿ�������赹��\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 20;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 20;
}

