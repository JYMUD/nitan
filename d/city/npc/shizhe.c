#include <ansi.h>
#include <getconfig.h>
inherit NPC;
string ask_me();

void create()
{
        set_name(HIR+LOCAL_MUD_NAME()+NOR, ({ "shizhe" }) );
        set("nickname", HIR"挑戰極限"NOR);
        set("gender", "男性" );
        set("age", 18);
        set("long", YEL"這位是〖"+LOCAL_MUD_NAME()+"〗的使者，向他打聽“禮物”，他會帶給您想不到的驚喜。\n"NOR);
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
                         "禮物" : (: ask_me :)
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
   command("whisper"+query("id", ob)+""HIW"歡迎光臨"+HIR+"(askshizheabout禮物)"+NOR+HIW+"，小的助您行走江湖．"NOR);
   command("es " + HIR"『"+HIY+LOCAL_MUD_NAME()+HIR+"』"NOR+WHT"歡迎您的光臨,"+HIR"ip:"NOR+WHT+RELEASE_SERVER()+NOR+HIR"port:"NOR+WHT+LOCAL_PORT()+NOR);
}

string ask_me()
{
        object me = this_player();
        mapping fam; 
        
         if( query("comeworld", me) )
                return "呵呵～這就是您的不是了！小的已經對您施過法力了！";
         else{
                set("comeworld", 1, me);
                addn("potential", 1000, me);
                addn("food", 10000, me);
                addn("water", 10000, me);
                return "禮物清單: 潛能: 1000,食物和飲水各: 10000。" ;
             }
}
