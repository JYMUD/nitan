#include <ansi.h>
inherit CLASS_D("generate") + "/boss";

void random_move();
void sp_attack();
void set_from_me(object me);
void create()
{
        string *names = ({ "陶俑將領" });

        ::create();
        set_name( names[random(sizeof(names))], ({ "jiang ling", "jiang"}));
        set("long", @LONG
這是一個沉睡在皇陵千年陶俑將領，身高八尺有餘，由陶土燒制而成，看起來十分堅
硬。他手持一柄青銅長劍，神情頗為威武。在機關消息的作用下，他的四肢可以活動，
攻守進退也有模有樣，但總歸不算非常靈活。
LONG);
        set("title", YEL "皇陵二品侍衛" NOR);

        set("str", 120);
        set("con", 120);
        set("dex", 120);
        set("int", 120);
        set("max_qi", 2000000);
        set("max_jing", 1000000);
        set("neili", 2500000);
        set("max_neili", 2500000);
        set("max_jingli", 500000);
        set("attitude", "killer");
        set("auto_perfrom", 1);
        /*
        set("chat_chance", 30);
        set("chat_msg", ({
                (: random_move :)
        }) );
        */
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: sp_attack :),
        }) );
        set("combat_exp", 100000000);
        set("death_msg",YEL"\n$N化成了一堆黃土。\n\n"NOR);

        set("rewards", ([
                "exp" : 400,
                "pot" : 80,
                "mar" : 10,
        ]));
        set_temp("apply/attack", 8000);
        set_temp("apply/parry", 8000);
        set_temp("apply/damage", 8000);
        set_temp("apply/unarmed_damage", 8000);
        set_temp("apply/armor", 8000);
        setup();
}

void init()
{
        object me;

        ::init();
        if( !interactive(me = this_player()) ||
            this_object()->is_fighting())
                return;

        set_from_me(me);
        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

void set_from_me(object me)
{
        mapping my;

        NPC_D->init_npc_skill(this_object(), NPC_D->check_level(me));
        my = query_entire_dbase();
        my["eff_jing"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        my["eff_qi"] = my["max_qi"];
        my["qi"] = my["max_qi"];
        set("jiali", query_skill("force") / 2);
}
void sp_attack()
{
        object *enemies,enemy;
        string msg;

        enemies = query_enemy();
        if( !enemies || sizeof(enemies)==0 )
                return;
        enemy = enemies[random(sizeof(enemies))];
        msg = RED"$N"RED"一聲嚎叫，口中吐出黃沙，狂風呼嘯，那尖利的嘯聲如刀，如劍，越來越尖... 越來越急...！！\n"
              RED"$n"RED"全身頓時千創百孔，鮮血直涌而出。\n"NOR;
        message_vision(msg, this_object(), enemy);
        enemy->receive_damage("qi",3000+random(3000),this_object());
        COMBAT_D->report_status(enemy);
        if( !enemy->is_busy() )
                enemy->start_busy(2);
        return;
}

int random_move()
{
        mapping exits;
        string *dirs, direction, to_go_place, my_birth_place;
        object env;
        string userid,mazeobj;
        int x,y;

        if( !mapp(exits=query("exits", environment())))return 0;

        dirs = keys (exits);
        direction = dirs[random(sizeof(dirs))];
        env = environment(this_object());
        to_go_place=query("exits/"+direction, env);
        //my_birth_place = file_name(this_object());

        //ccommand("say "+to_go_place);
        if( sscanf(to_go_place,"/f/mausoleum/%s/%s/%d/%d",userid,mazeobj,x,y)!=4 )
                return 1;
        command("go " + direction);
        addn_temp("random_move", 1);
        return 1;
}
