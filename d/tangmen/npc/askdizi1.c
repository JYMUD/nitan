inherit NPC;
#include <ansi.h>;

void create()
{       
        string *order = ({"��", "��", "��", "��", "��", "��", "֣", "��", "��",
                "��", "��", "��", "��", "��", "��", "κ", "��", "��", "��", "��"});
        string *orderr = ({"����", "����", "�Թ�", "СС", "����",
                "����", "ѻѻ", "����", "èè","����","����","�ɷ�"});
        set_name(order[random(20)]+orderr[random(8)], ({ "boy","nanhai" }) );
        set("title", "��֪�к�");
        set("gender", "����" );
        set("age",5+random(3));
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("no_get", "1");
        set("max_qi",100);
        set("max_jingli",100);
        /*
        set("chat_chance", 30);
        set("chat_msg", ({
                // (: random_move :)
        }) );
        */
             

        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        add_action("do_dating","xunwen");
}       

int do_dating(string arg)
{
        object me = this_player();
        object ob = this_object();
        string str=query("id", me);
       
        if (!arg || arg != "wenzi")
             return notify_fail("�������ʲô���㵹��˵����\n");
        
        if( query("dname") != query("id", me) )
             return notify_fail("�Ҳ���˵���㲻Ҫ�ʣ�����Ҳ���ʣ�\n");     
         
        if( !(query_temp("started", me)) )
             return notify_fail("����������⣬��Ҫ����һ�£��������ǲ��Ǿ����е��Ȱ���\n");
        
        if( !(query_temp("asked", me)) )
           {
             command("ah");
             command("say ���ң������Ҷ��ˣ�������˵�ɣ��Ҹձ����Ӷ�������˵�һ᲻��֪������\n");
             
             switch(random(2))
             {
                case 0 : command("joke");break;
                case 1 : set_temp("asked",1,me);tell_object(me,HIC"�������䣬һ������û��Ӱ�ˣ�\n"NOR); 
             destruct(ob);delete_temp("started", me);break;
                default: return 1;
             }
            return 1;                       
            }  
        tell_object(me,"����û˵�꣬������������������\n");       
        tell_object(me,HIG"һ�����ˡ�����һȺ���Ӵ�����߷ɹ���\n"NOR);
        tell_object(me,HIR"��Ҫ��ԥ�ˣ���ȥ׷����\n"NOR);
        return 1;
                
}
