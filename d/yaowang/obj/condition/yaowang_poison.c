#include <ansi.h>
#include <condition.h>

inherit F_CLEAN_UP;
inherit POISON;

string name() { return "yaowang_poison"; }

string chinese_name() { return HIW "ҩ���ȶ��Ŷ�ҩ" NOR; }

string update_msg_others()
{
       return HIW "$N��ɫ���ϣ�ȫ��ס�Ĳ��������ظ�����졣\n" NOR;
}

string update_msg_self()
{
        return HIW "���ҩ���ȶ���֮�������ˣ�\n" NOR;
}

int jing_damage(object me, mapping cnd)
{
        return cnd["level"] / 3;
}

int qi_damage(object me, mapping cnd)
{
        return cnd["level"]/ 2;
}

int dispel(object me, object ob, mapping cnd)
{

        if (me == ob)
        {
                if ((me->query_skill("shennong-xinjing", 1) > 180 && 
                        me->query_skill_mapped("force") == "shennong-xinjing") ||
                        (me->query_skill("yaogu-xinfa", 1) > 250 &&
                        me->query_skill_mapped("force") == "yaogu-xinfa")||
                        (me->query_skill("yaowang-shenxin", 1) > 180 &&
                        me->query_skill_mapped("poison") == "yaowang-shenxin"))
                {                                           
                        return ::dispel(me, ob, cnd);
                }
                                        
                tell_object(me, "����ͼ�˹�����ҩ����֮����ͻȻһ�е�"
                                "��˺���ѷε���ʹ���������ʡ�\n");
                return -1;
        }
        else
        {
                if ((me->query_skill("shennong-xinjing", 1) > 180 && 
                        me->query_skill_mapped("force") == "shennong-xinjing") ||
                        (me->query_skill("yaogu-xinfa", 1) > 250 &&
                        me->query_skill_mapped("force") == "yaogu-xinfa")||
                        (me->query_skill("yaowang-shenxin", 1) > 180 &&
                        me->query_skill_mapped("poison") == "yaowang-shenxin"))
                {                                           
               addn_temp("apply/dispel-poison", -50, me);
               set_temp("add_dispel", 1, me);
               call_out("clear_dispel", 2, me);
                return ::dispel(me, ob, cnd);
                }


        tell_object(me, "�㽫��������" + ob->name() + "���У�ȴ����"
                        "������ת�쳣���죬������⣬\nͻȻ��" + ob->name() +
                        "�������£���æס�֡�\n");
        tell_object(ob, "�����" + me->name() + "�����������������"
                        "��������Ȼһ��˺���ѷεľ�ʹ��\n��ʤҩ���ȶ���֮"
                        "��������ʱ�����㼸�����ʡ�\n");
        return -1;
        }
        
}

void clear_dispel(object me)
{
       if( query_temp("apply/dispel-poison", me) && 
           query_temp("add_dispel", me) )
       {
                delete_temp("add_dispel", me);
                addn_temp("apply/dispel-poison", 50, me);
                return;
       }
               
}