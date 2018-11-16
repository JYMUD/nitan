// /clone/quest/questjianxi.c
//last modified by sega 13/4/2000
// Modified by Zeratul Jan 5 2001

//�޸ĳɲ��ܰ�æɱ
#include <dbase.h>
#include <login.h>
#include <ansi.h>

inherit NPC;
inherit F_CLEAN_UP;
inherit F_UNIQUE;
int ask_me(object who);
string * name_msg = ({
        "��å",
        "�����",
        "����",
        "�Ҷ�",
        "�ٱ�",
        "��������",
        "������",
        "С��",
        "����",
        "����",
        "�η�����",
        "��������",
});

string * long_id = ({
        "liu mang",
        "jinxiang ke",
        "tiao fu",
        "jia ding",
        "guan bing",
        "flower girl",
        "tangzi shou",
        "xiao fan",
        "dao ke",
        "jian ke",
        "seng ren",
        "jianghu haoke",
});

void create()
{
        int i;
        i = random(sizeof(name_msg));
        set_name(name_msg[i], ({ long_id[i]}) );
        set("gender", random(2)>0 ? "Ů��" : "����" );
        set("attitude", "friendly");
        set("chat_chance", 30);
        set("chat_msg", ({
          (:call_out,"random_move",0:),
                }) );
               set("inquiry", ([
                "��ϸ"    : (: ask_me :),
                "jian xi" : (: ask_me :),
                "jianxi"  : (: ask_me :),
        ]) );
        set("no_steal", 1);
//      set("ask_time", 0);
        set( "jianxi", 1 );
        setup();
        carry_object("/d/city/npc/obj/tiejia")->wear();
//        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/food/jiudai");
  if (clonep())
   call_out("dest_me",1200,this_object());
}
int ask_me(object who)
{
        object ob = this_object(), me = this_player();
        mapping map_status;
        string*        mname;
        int i,j;
        mixed perform_actions = ({});
        mixed combat_actions = ({});
        mixed msg =({});

        if( query("owner", this_object()) == query("id", me) )
        {
                message_vision(HIY"$N����ͻȻ���������Ŀ�⣬˫��ð������$n������������"+RANK_D->query_self_rude(ob)+"����"+query("fname", ob)+"��"+RANK_D->query_rude(me)+"���������ɣ�\n"NOR,ob,me);
                me->start_busy(1);        
    ob->fight_ob(me);         
//                me->fight_ob(ob);        
                if( query_temp("asked", ob))return 1;
                if( query("combat_exp", me)>10000000 )
                        addn_temp("apply/dodge", 250, ob);
    else if( query("combat_exp", me)>5000000 )
      addn_temp("apply/dodge", 200, ob);
    else if( query("combat_exp", me)>3000000 )
      addn_temp("apply/dodge", 150, ob);
    else if( query("combat_exp", me)>1000000 )
      addn_temp("apply/dodge", 100, ob);
    else 
      addn_temp("apply/dodge", 50, ob);
                set("title",query("family_name",  ob)+"��ϸ", ob);
                set("name",query("fname",  ob), ob);
                if ( mapp(map_status = ob->query_skill_map()) ) {
                        mname  = keys(map_status);
        
                        for(i=0; i<sizeof(map_status); i++) {
                                perform_actions = get_dir( SKILL_D(map_status[mname[i]]) + "/" );
                                for ( j = 0; j < sizeof( perform_actions ); j++ )
                                {
                                        sscanf( perform_actions[j], "%s.c", perform_actions[j] );
                                        if ( mname[i] == "force" )
                                                msg = ({ (: exert_function, perform_actions[j] :) });
                                        else
                                                msg = ({ (: perform_action, mname[i] + "." + perform_actions[j] :) });
                                        combat_actions += msg;
                                }
                        }
                }
                set( "chat_chance_combat", 60);                
                set( "chat_msg_combat", combat_actions );                
    set_temp("asked", 1, ob);
        }
        else
                message_vision(HIY"$N���к���һ���������ֱ��ĮȻ�ˣ�ֻ����ֵؿ���$n��\n"NOR, ob, me);
        return 1;
}

int random_move()
{
        mapping exits;
        string *dirs, dir, dest;

        if( !mapp(exits=query("exits", environment())))return 0;
        dirs = keys(exits);
        dir = dirs[random(sizeof(dirs))];
        dest = exits[dir];
        if( query("no_fight", find_object(dest)))return 0;
        if( this_object()->is_fighting() ) return 0;
        command("go " + dir);
        return 1;
}

void init()
{
         add_action("do_halt","halt");
         add_action("do_halt","go");
         add_action("do_halt","surrender");
}
int accept_hit(object me)
{
        notify_fail(HIW"������Ҫץ���ˣ���ʲô���֣�\n"NOR);
        if( query("owner", this_object()) == query("id", me )
         && query_temp("asked", this_object()) )
        {
                me->kill_ob(this_object());
                return 1;
        }
        return 0;
}
int accept_fight(object who)        {return accept_hit(who);}
int accept_kill(object who)                {return accept_hit(who);}
int accept_ansuan(object who) {return accept_hit(who);}
int accept_touxi(object who)        {return accept_hit(who);}

int do_halt()
{
        object me = this_player();
        object ob = this_object();
        
        if ( me->is_fighting(ob)  )
        {
                tell_object( me, HIR"��ϸδ������������������\n"NOR );
                return 1;
        }
        return 0;
}

void dest_me(object ob)
{
        message_vision("ֻ��$N��Ȼ��ת���У�������������У�ת�۾��ټ����ޡ�\n",ob);
        destruct(ob);
}