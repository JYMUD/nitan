//xym_guard.c 

inherit NPC; 

#include <ansi.h> 

int ask_xym(object me, object ob); 
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

int ask_xym(object me, object ob) 
{ 
     me=this_player(); 
     ob=this_object(); 
     if( query("bunch/bunch_name", me) != "������" && query("shen", me) >= 0 )
     { 
           command("famours"+query("id", me));
           tell_object(me,"����Ц���еض���˵��������������������˰ɣ�����������\n"); 
           set_temp("good_xym1", 1, me);
           return 1; 
     } 
     if( bad_bunch(me) || query("shen", me)<0 )
     { 
           ob->command("say ��������аħ������Ҵ�ô��\n"); 
           return 1; 
     } 

     tell_object(me,"������������ֵ�����ͬΪ�����ֵܣ���γ����԰�����\n"); 
     return 1; 
} 
