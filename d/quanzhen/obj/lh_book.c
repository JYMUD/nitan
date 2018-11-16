// Code of ShenZhou
//lh_book.c
//wsky
#include <ansi.h>
inherit ITEM;

int do_start(object me);


void create()
{
        set_name("��Ƥ����", ({ "ce zi", "book" }));
        set_weight(600);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", YEL"����һ����Ƥ���ӣ�������д�š�������������׭�֣����½�����д��ȫ�泤���ӡ�\n"NOR);
                set("material", "paper");
                set("no_drop","�������������뿪�㡣\n");
                set("no_get","�������������뿪�㡣\n");
                set("no_steal", 1);
                set("no_sell", 1);
                set("value", 300000);
        }
}

void init()
{
        add_action("do_lingwu","lingwu");
  
}
int do_lingwu(string arg)
{
        object me;
        int cost;
        me=this_player();
         if (me->is_busy())
            return notify_fail("����æ����!\n");
        
        if( arg != query("id", this_object()))return notify_fail("��Ҫ����ʲô?\n");
        
        if(me->query_skill("quanzhen-jian", 1) <100)
            return notify_fail("���ȫ�潣��������죬�޷�����Ҫ���еİ��\n");
            
        if(me->query_skill("taoism",1)<100)
                return notify_fail("��ĵ�ѧ��Ϊ������\n");
                
        if(me->query_skill("literate",1)<100)
                return notify_fail("����ѧˮƽ̫��������˲ᡣ\n");
        
        if( query("player_id", this_object()) != query("id", me) )
        {
                addn("max_neili", -10, me);
                return notify_fail(HIR"��һ��֮��ֻ���������ȣ��������ۣ�˵���������ܡ�\n"NOR);

        }

        if( query("can_perform/quanzhen-jian/lian", me) == 1 )
                    return notify_fail("���Ѿ�������������Ҫ��\n");
        
        if( query("neili", me)<1000 || query("jing", me)<200 )
                return notify_fail("�㾫�񲻼ѣ��޷������ķ��еİ��\n");
                
        cost=query("int", me);
        
        if(cost>=30)
                cost=5;
        else
                cost=35-cost;
        
        set_temp("lianhuan_cost", cost, me);
        
        message_vision(YEL"$N�ӻ�������һ��С����,ȫ���ע���Ķ��ţ���ʱ��������ıȻ���\n" NOR, me);
            me->start_busy((: do_start:));
        return 1;

}

int do_start(object me)
{

        if( query_temp("lianhuan_cost", me) <= 0 )
        {
                if( random(query("int", me))>15 || random(me->query_int())>35 )
                {
                        addn("lingwu_lianhuan", 1, me);
                        tell_object(me,HIY"�㾲�����ã��ƺ�����������������һ˿����\n"NOR);
                        
                        if( query("lingwu_lianhuan", me) >= 20 )
                        {
                                tell_object  (me,HIG"��ϲ������������������������ؾ��ľ�Ҫ��\n"NOR);
                                set("can_perform/quanzhen-jian/lian", 1, me);
                                delete("lingwu_lianhuan", me);
                                
                        }
                        set("neili", 0, me);
                        set("jingli", 0, me);
        
                }
                else
                {
                        
                        tell_object  (me,HIR"����˼����ʼ�ղ������򣬲��õ����д��\n"NOR);
                            addn("neili", -query("max_neili", me), me);
                            me->receive_damage("jing",query("max_jing", me));
                            
                            if( query("neili", me)<0 || query("jing", me)<0 )
                                    me->unconcious();
                                   
                }
        
                return 0;
        }
        addn_temp("lianhuan_cost", -1, me);
        
        return 1;
}