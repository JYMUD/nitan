// freezing.c

#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "yinyang12"; }

string chinese_name() { return "����֮����"; }

string update_msg_others()
{
        return HIW "$N" HIW "���ϳ��ֳ�ʹ��ı��飬��֫��ý�Ӳ��ȫ��̱����������\n" NOR;
}

string update_msg_self()
{
        return HIW "��ֻ��ȫ�������ޱȣ���ʹ����˿��������\n" NOR;
}

string die_msg_others()
{
        return HIW "$N" HIW "���ڵ��ϣ��鴤��һ����Ҳû�а�������ˡ�\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 6;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 5;
}

string die_reason()
{
        return "����֮������������������";
}


int dispel(object me, object ob, mapping cnd)
{
        if ((me->query_skill("jiuyang-shengong", 1) > 180 && 
             me->query_skill_mapped("force") == "jiuyang-shengong") ||
             (me->query_skill("jiuyin-shengong", 1) > 180 &&
              me->query_skill_mapped("force") == "jiuyin-shengong") || 
             (me->query_skill("yinyang-shiertian", 1) > 180 &&
              me->query_skill_mapped("force") == "yinyang-shiertian"))
        {
               me->add_temp("apply/dispel-poison", 1000);
               me->set_temp("add_dispel", 1); 
               call_out("clear_dispel", 2, me);
        }

        return ::dispel(me, ob, cnd);

}

void clear_dispel(object me)
{
       if (me->query_temp("apply/dispel-poison") && 
           me->query_temp("add_dispel"))
       {
                me->delete_temp("add_dispel");
                me->add_temp("apply/dispel-poison", -1000);
                return;
       }
               
}