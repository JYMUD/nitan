//xym_guard.c 

inherit NPC; 

#include <ansi.h> 

int ask_xym(object me); 
void create() 
{ 
        set_name("����",({"shou wei","guard"}) ); 
        set("long","����һλ����Ӣ�˲����������ˡ�\n"); 
        set("title","�����˽���"); 
        set("gender","����"); 
        set("age",20); 
        set("combat_exp",100); 
        set("inquiry",([ 
                "������" : (: ask_xym :), 
        ]) ); 
        setup(); 
} 

int ask_xym(object me) 
{ 
        me = this_player(); 
     
        if( query("bunch/bunch_name", me) != "������" && query("shen", me) >= 0 )
        { 
                command("famours"+query("id", me));
                tell_object(me,"����Ц���еض���˵��������������������˰ɣ�����������\n"); 
                set_temp("good_xym", 1, me);
                return 1; 
        } 
        if( bad_bunch(me) || query("shen", me)<0 )
        { 
                command("say ��������аħ������Ҵ�ô��\n"); 
                return 1; 
        } 

        tell_object(me, "������������ֵ�����ͬΪ�����ֵܣ���γ����԰�����\n"); 
        return 1; 
} 
