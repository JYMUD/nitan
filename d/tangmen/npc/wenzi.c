// wenzi.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("����", ({ "wen zi" }) );
        set("long",     "һֻ�����С����Ц�����Ŀ����㡣\n");

        set("race", "Ұ��");
        set("age", 1);
        set("attitude", "peaceful");

        set("max_jingli", 80);
        set("max_qi", 80);

        set("str", 10);
        set("cor", 50);

        set("limbs", ({ "ͷ��", "����", "���" }) );
        set("verbs", ({ "bite" }) );

        set_temp("apply/attack", 10);
        set_temp("apply/damage", 10);
        set_temp("apply/armor", 10);

        set("combat_exp", 1000);
        setup();
}

void init()
{
        object me,ob;
        
        ::init();
        if (interactive(me = this_player())&& !is_fighting())
        {
        if( query_temp("lianyl", me) )
               {
               remove_call_out("telling");
               call_out("telling", 1, me);
                }
        }
        add_action("do_zha", "zhua");
}

int telling(object me)
{   
    if (!me || environment(me) != environment()) return 1; 
    if( query("tangmen/yanli", me) >= 50 )
       return notify_fail("��λ���ŵ��Ӻ������������Ͱ���\n");
       return notify_fail("�����벻�������벻�����������̫ˮ�˰ɣ�ҪŬ������\n");
}

int do_zha(string arg)
{       
        object ob;
        object obb = this_object();
        int jing_drop;
        mapping myfam;
        
        ob = this_player();
        myfam=query("family", ob);
        jing_drop = random(40);
        
        if ( myfam["family_name"] != "��������" )
           {
           message_vision(HIR"$N���Ϸ���Ӱ���\n"NOR,ob);
           return 1;
           }          
        if ( !arg||(arg != "wenzi" && arg != "wen zi"))
           return notify_fail("����ץʲô��? \n");
        
        if( query_temp("find_wz", ob) )
           return notify_fail("�Ĳ�Ҫ̫�ڣ���Ҫ��ֻ����\n");
        
        if( query_temp("minchen", ob) != query("short") )
           return notify_fail("�㲻Ҫ�������Ӿ�ץ����\n");   
           
/*
        if( query("jingli", ob)<20 )
           return notify_fail("������Ҫ����Ҫ������Ϣ����\n");
*/
         
        if( query("d3name") != query("id", ob) )
           return notify_fail("�����������֣�����֣�\n");   
           
        if( query_temp("lianyl", ob) )
          {   
        message_vision(YEL"$N�����۾�����С������Ŀ������ӣ��͵�һ��......\n"NOR, ob);
                 if( random(query("tangmen/yanli", ob)/3+10+query("dex", ob)/3)>random(50) )
                    {
                        message_vision(HIG"$N����һЦ������һ���������ѱ�$Nץס�ˣ����в��ɵ�һ����⡣\n"NOR,ob);
                        tell_object(ob,HIR"����һ�����������������ˣ���Ҫ�ˡ���ȥ����ɣ�\n"NOR);
                        delete_temp("lianyl", ob);
                        set_temp("find_wz", 1, ob);
                        delete_temp("started", ob);
                        set_temp("jobok", 1, ob);
                        ob->clear_condition("tmjob");
                        obb->die();
                        return 1;
                     }
                 else 
                  {   
                  switch( random(3))
                   {case 0:
                     say("�������˵ķɿ��ˡ����������\n");
                    break;
                    case 1:
                     say(HIY"һ��С�������˸������࣬��������\n"NOR);
                    break;
                    case 2:   
                     say(HIC"������һ������ſ��\n"NOR);
                    break;
                   }
                  return 1; 
                  } 
           }     
       return notify_fail(HIR"����һ��û���������ˣ�\n"NOR);
}                     
                  
                     
