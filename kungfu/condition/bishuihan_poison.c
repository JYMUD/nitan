#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "bishuihan_poison"; }

string chinese_name() { return "��ˮ����"; }

string update_msg_others()
{
       return HIW "$N" HIW "��ɫ�԰ף�ͻȻ�ɰ�תΪ��ɫ������������ɫתΪ��ɫ��ȫ��ס�Ĳ������ƺ��ǳ�ʹ�ࡣ\n" NOR;
}

string update_msg_self()
{
        return HIW "��ֻ�е�һ�ɴ�δ�й����溮֮����������Ȼ����������ȫ�������Ѩ�������Ǳ�ˮ���������ˣ�\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
                me->add("neili", -1 * cnd["level"] / 6);
                if (random(3) == 1)me->start_busy(2 + random(3));
                else me->start_busy(1);

        return 1;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"] / 6;
}

int dispel(object me, object ob, mapping cnd)
{

        if ((me->query_skill("jiuyang-shengong", 1) > 380 && 
             me->query_skill_mapped("force") == "jiuyang-shengong") ||
             (me->query_skill("yinyang-shiertian", 1) > 380 &&
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