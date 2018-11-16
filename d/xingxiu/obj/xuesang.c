// Code of ShenZhou
// xuesang.c  
// By Haowen 1/14/98

#include <ansi.h>

inherit ITEM;


void create()
{
        set_name("ѩɣ",({"xue sang","sang"}));
        set_weight(900000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "����һ����ɽ���е�������ѩ���ѩɣ����
��˵��һ��ѩ����ϲ����������ѩɣ֮�ϣ�����������Ѱ��(xunzhao)� \n");
                set("unit", "��");
                set("value", 8);
                set("no_get", 1);
                set("leaves",20);
       }
       
        setup();
}

void init()
{
        add_action("do_search", "search");
        add_action("do_search", "xunzhao");
        add_action("do_feed", "fed");
        add_action("do_look", "look");
        add_action("do_look", "l");
}

int do_search()
{
object obj=this_object(),me=this_player();

if( query_temp("find_can", me) )
        return notify_fail("ѩ���Ѿ���ѩɣ���ˣ��㻹��ʲôѽ��\n");

if( random(query("kar", me))>15 )
        {
        tell_object(me,HIG"����ϸ�ķ���ѩɣҶ������Ѱ��������\n" NOR);
        if(random(10)>5)
                {
                tell_object(me,HIR"���Ȼ��ǰһ����һ����Өѩ�׵�ѩ��(can)������һƬѩɣҶ�ϣ�\n"NOR);
                set_temp("find_can", 1, me);
                }
        addn("neili", -10, me);
        return 1;
        }
else    {
        addn("neili", -10, me);
        return notify_fail("�����˰���ʲôҲû�ҵ���\n");
        }
}

int do_feed(string arg)
{
object ob,obj=this_object(),me=this_player();
string what;

//message_vision(arg);
if (!arg || sscanf(arg,"%s",what)!=1)
        return notify_fail("��Ҫιʲô��\n");

if (what!="can")
        return notify_fail("�����ѩɣҶֻ����ɽѩ�ϰ��ԣ�\n");

if( !query_temp("find_can", me) )
        return notify_fail("��ѩɣ��ʲôҲû�У���Ҫιʲô��\n");

if( query_temp("get_si", me) )
        return notify_fail("ѩ�ϸ��¹�˿���������ڲ��������ˣ�\n");

if( query("leaves", obj)>1 )
        {
        tell_object(me,HIY "��ժ��һƬѩɣҶι��ѩ�ϳԡ�ѩ����ϸ�ĳ���������\n" NOR);
        set("leaves",query("leaves",  obj)-1, obj);
                if (random(10)>5)
                        {
                        tell_object(me,HIY "ѩ�ϳ�����ɣҶ��ͷһ�����³�һ����˿����Ͻ����ֽ�ס��\n" NOR);
                        set_temp("get_si", 1, me);
                        ob=new("/d/xingxiu/obj/xuecan-si");
                        ob->move(me);
                        }
        return 1;}
else 
        {
        call_out("grow",200,obj);
        return notify_fail("ѩɣ�ϵ�Ҷ�Ӷ�ժ���ˣ�����������������ι�ɣ�\n");
        }
}

int do_look(string arg)
{
        object ob,me=this_player();
        string what;
        ob=this_object();
 
        if( !arg || arg == "" || sscanf(arg,"%s",what)!=1) return 0;

        
        if(what=="sang" || what=="xue sang")
                {        
                if( query_temp("find_can", me) )
                        tell_object(me,query("long", ob)+"����������һֻѩ��(can)���������ڵ���ι(fed)����\n");
                else tell_object(me,query("long", ob));
                return 1;
                }

return 0;

}

int grow(object ob)
{
        message_vision(HIG "ѩɣ�ϵ�ɣҶ�ֳ������ˣ�\n");
        set("leaves", 20, ob);
}