#include <ansi.h>
#include <getconfig.h>
inherit NPC;
string ask_me();

void create()
{
        set_name(HIR+LOCAL_MUD_NAME()+NOR, ({ "shizhe" }) );
        set("nickname", HIR"��ս����"NOR);
        set("gender", "����" );
        set("age", 18);
        set("long", YEL"��λ�ǡ�"+LOCAL_MUD_NAME()+"����ʹ�ߣ��������������������������벻���ľ�ϲ��\n"NOR);
        set("shen_type", 1);
        set("combat_exp", 1000000);
        set("str", 30);
        set("dex", 30);
        set("con", 30);
        set("int", 30);
        set("per", 30);
        set("attitude", "friendly");
        set("max_qi", 100000);
        set("neili", 100000);
        set("max_neili", 100000);
        set("score", 100000);

        set("inquiry", ([
                         "����" : (: ask_me :)
        ]));
        setup();
}

void init()
{
        object ob;
        ob = this_player();     
        ::init();
        if( interactive(ob) && !is_fighting() )
               {
                        remove_call_out("greeting");
                        call_out("greeting", 1, ob);
                }
}

void greeting(object ob)
{
   if( !ob || environment(ob) != environment() ) return;
   command("whisper"+query("id", ob)+""HIW"��ӭ����"+HIR+"(askshizheabout����)"+NOR+HIW+"��С���������߽�����"NOR);
   command("es " + HIR"��"+HIY+LOCAL_MUD_NAME()+HIR+"��"NOR+WHT"��ӭ���Ĺ���,"+HIR"ip:"NOR+WHT+RELEASE_SERVER()+NOR+HIR"port:"NOR+WHT+LOCAL_PORT()+NOR);
}

string ask_me()
{
        object me = this_player();
        mapping fam; 
        
         if( query("comeworld", me) )
                return "�Ǻǡ���������Ĳ����ˣ�С���Ѿ�����ʩ�������ˣ�";
         else{
                set("comeworld", 1, me);
                addn("potential", 1000, me);
                addn("food", 10000, me);
                addn("water", 10000, me);
                return "�����嵥: Ǳ��: 1000,ʳ�����ˮ��: 10000��" ;
             }
}
