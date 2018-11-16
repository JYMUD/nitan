// /d/xueshan/obj/jitan.c
// jitan.c 法坛
// Ryu
// kane

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY"般阳法坛"NOR, ({ "fa tan", "altar", "tan" }) );
        set_weight(300000);
        set_max_encumbrance(5000000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", "这是一个极其庞大的铜制祭坛，高约三丈，方圆约有五丈，乃是当年吐番国王亲\n"
                            "自指挥铸造的，耗倾国之力，十年方成。\n");
                set("value", 1000);
                set("material", "wood");
                set("no_get",1);
        }
        setup();
}

int is_container() { return 1; }

void init()
{
        add_action("do_put", "put");
        add_action("do_light", "light");
        add_action("do_spray", "peng");
        add_action("do_dazuo", "dazuo");
        add_action("do_wave", "wave");
        add_action("do_spray", "spray");
}

int do_put(string arg)
{
        object me, obj;
        string item, target; 
        int amount;

        me = this_player();

        if (me->is_busy()
         || query_temp("pending/exercising", me )
         || query_temp("exit_blocked", me) )
                return notify_fail("你现在正忙着呢。\n");

        if( !arg || sscanf(arg, "%s in %s", item, target) != 2 )
                return notify_fail("你要将什么东西放进哪里？\n");
                
        if( item == "all" ) {
                write("还是一样一样来吧。\n");
                return 1;
        }
                                                                
        sscanf(item, "%d %s", amount, item);
        
        if( !objectp(obj = present(item, me)) )
                return notify_fail("你要给谁什么东西？\n");

        if( query("id", obj) != "corpse"){
                write("你不能往祭坛里放这样东西。\n");
                return 1;
        }

}
int do_light(string arg)
{
        object  me = this_player();

        if (!present("fire", me))
                return notify_fail("你要用什么点火？\n");
        if (!query("in_use"))
                return notify_fail("你要点燃什么？\n");
        if (!id(arg))
                return notify_fail("你要点燃什么？\n");
        if( query("pending", this_object()) != query("name", me) )
                return notify_fail("又不是你超度，瞎积极什么？\n");
        message_vision(HIR"$N点燃了祭坛中的木柴与酥油，熊熊烈火冲天而起。\n"NOR, me);
        set("burning", 1);
        set("pending",query("name", me));
        set("long", query("long") + HIR"里面燃着熊熊的火焰。\n"NOR);
        set("in_use", 0);
        log_file("job/xueshan",query("name", me)+"("+
            query("id", me)+")开始烧人"+ctime(time())+"\n");
        remove_call_out("burning");
        call_out("burning",20+random(20), me);
        return 1;
}
void burning(object me)
{
        int point, butter;
                object room, gang, suyou;

        // add to involve the butter stuff ***************
                butter = 0;
            if(!( room = find_object("/d/xueshan/dumudian")) )
                   room = load_object("/d/xueshan/dumudian");
            if ( objectp(gang = present("tong gang", room)) ) {
                if( gang->query_current_liquid() >= 30) {
                                // if less than 30 then can't deduct, shouldn't happen
                    if ( objectp(suyou = present("su you", gang)) ) {
                   if( (query("liquid/status", suyou) == 1) && (suyou->query_amount() >= 30)){
                                          // take 30 for each burn
                                          butter=gang->query_current_liquid();
                                          suyou->add_amount(-15);
                                      gang->add_current_liquid(-15);
                                   }
                                }
                }
            }
                // butter bonus = butter level / 200
                // for max 50000 / 200 = 250 bonus
                // for gang started at 3000 / 200 = 15 bonus
                butter = butter/200;
                // ***********************************************

        point=query_temp("award_pot", me)*10/query("combat_exp", me);
        point = point * me->query_skill("lamaism")/20;
                
        if( query("combat_exp", me)<150000)point=point/2;
        message_vision(BLU"一丝魂魄升出祭坛，冉冉而起。魂魄受$N佛法感召，徘徊不去。\n"NOR, me);
/************ add butter bonus ******/
                point += butter;
/************************************/
        if( query_temp("award_pot", me) )
        addn("potential", point+random(point), me);
        if( query_temp("award_doubling", me) )
                set("potential", me->query_potential_limit(), me);
        if( query("potential", me)>me->query_potential_limit() )
                set("potential", me->query_potential_limit(), me);
        set("wait_for_spray", 1);
}
int do_spray(string arg)
{
        object  ob, me = this_player();
        ob = (present("lubo", me));
        
        if (!present("lubo", me))
                return 0;
        if( query("name", me) != query("pending") )
                return notify_fail("你跟这儿凑什么热闹？\n");
        if (!query("wait_for_spray"))
                return notify_fail("时辰未到！\n");
        if (!id(arg))
                return notify_fail("你想往哪儿喷？\n");
        if( query("liquid/remaining", ob)<1 )
                return notify_fail("颅钵里面的水已经所剩无几了。\n");

        message_vision(HIW"$N端起颅钵吸进一口水，「噗」的一声猛地朝那熊熊火焰喷将过去。\n"NOR, me);
        addn("liquid/remaining", -1, ob);
        set("wait_for_spray", 0);
        set("time_to_dazuo", 1);
        return 1;
}
int do_dazuo()      
{
        object me = this_player();

        if (me->is_busy()
         || query_temp("pending/exercising", me )
         || query_temp("exit_blocked", me) )
                return notify_fail("你现在正忙着呢。\n");
        
        if( query("name", me) != query("pending") )
                return notify_fail("你凑什么热闹？\n");
        if( query("neili", me)<600 )
                return notify_fail("你内力不够！\n");
        if (!query("time_to_dazuo"))
                return notify_fail("这不是你打坐的时候。\n");

        message_vision(HIY"$N盘腿打坐，神光内蕴，口中念念有辞，渐渐有一丝魂魄在$N面前凝聚成形。\n"NOR, me);
        me->start_busy(20);
        remove_call_out("rise");
        call_out("rise",20+random(20), me);
        return 1;
}
void rise(object me)
{
        message_vision(BLU"魂魄越聚越多，竟然呈出人形！ $N手指人形，口念真言，指引往生之路。\n"NOR, me);
        addn("neili", -600, me);
        if( query_temp("award_pending", me)*10/query("combat_exp", me) >= 16){
        addn("max_neili", me->query_skill("lamaism",1)/100, me);
        log_file("job/xueshan",query("name", me)+"("+query("id", me)+")得到"+me->query_skill("lamaism",1)/100+"点最大内力值"+ctime(time())+"\n");
        }

        if( query_temp("award_doubling", me)){
        addn("max_neili", me->query_skill("lamaism",1)/20, me);
        log_file("job/xueshan",query("name", me)+"("+query("id", me)+")得到"+me->query_skill("lamaism",1)/100+"点最大内力值"+ctime(time())+"\n");
        }
        set("time_to_dazuo", 0);
        set("time_to_wave", 1);
}
int do_wave(string arg)
{
        object weapon, me = this_player();

        if (!arg && arg != "ling" && arg != "fa ling")
                return notify_fail("你要摇什么？\n");
                
        if (!present("fa ling", me))
                return notify_fail("你要摇什么？\n");

        if( query("name", me) != query("pending") )
                return notify_fail("你跟这儿凑什么热闹？\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || (query_temp("weapon",query("name",  me))) != "法铃" )
                return notify_fail("你手中没有这样东西。\n");
        
        if (!query("time_to_wave"))
                return notify_fail("时辰未到！\n");

        message_vision(CYN"$N手持法铃，边走边摇，高声诵读密传经咒。突然大喝一声。声似雷霆。\n"NOR, me);
        set("time_to_wave", 0);
        remove_call_out("close_up");
        call_out("close_up",20+random(20), me);
        me->start_busy(20);
        return 1;
}
void close_up(object me)
{
        object *inv, ob, room, gang, suyou;
        int gaining, butter, i;
    int expG, potG;
        ob = this_object();


        // add to involve the butter stuff ***************
                butter = 0;
            if(!( room = find_object("/d/xueshan/dumudian")) )
                   room = load_object("/d/xueshan/dumudian");
            if ( objectp(gang = present("tong gang", room)) ) {
                if( gang->query_current_liquid() >= 15) {
                                // if less than 15 then can't deduct, shouldn't happen
                    if ( objectp(suyou = present("su you", gang)) ) {
                   if( (query("liquid/status", suyou) == 1) && (suyou->query_amount() >= 15)){
                                          // take 30 for each burn
                                          butter=gang->query_current_liquid();
                                          suyou->add_amount(-15);
                                      gang->add_current_liquid(-15);
                                   }
                                }
                }
            }
                // butter bonus = butter level / 50
                // for max 50000 / 50 = 1000 bonus
                // for gang started at 3000 / 50 = 60 bonus
                butter = butter/50;
                // ***********************************************

        gaining=query_temp("award_pending", me)*10/query("combat_exp", me);
        gaining = 12 * gaining;
        if (gaining > 300) gaining = 300;       

        if( query("combat_exp", me)<80000 )
        gaining = gaining/3;

        if( query("combat_exp", me)>80000 && query("combat_exp", me)<100000 )
        gaining = gaining/2;

//*********** add butter bonus *******
        gaining = gaining + butter;
//************************************

        message_vision(HIW"大院里光茫四起，一声巨响过后，又恢复了平静。超度完毕。\n"NOR, me);
        set("long", "这是一个极其庞大的铜制祭坛，高约三丈，方圆约有五丈，乃是当年吐番国王亲\n"
                    "自指挥铸造的，耗倾国之力，十年方成。\n");
        set("long", query("long") + RED"里面燃着的火焰快熄灭了。\n"NOR);
        me->improve_skill("lamaism",query("int", me));
        addn("jingli", -300, me);
        set("burning", 0);
       //expG = gaining + random(gaining/2);
        expG = gaining*2 + random(gaining);
         // if (me->query_temp("award_pending"))
            addn("combat_exp", expG, me);
            addn("potential", expG/5, me);
        log_file("job/xueshan",query("name", me)+"("+query("id", me)+")烧人获得"+
            expG + " 点经验和 "+ expG / 5 + " 点浅能 "+ctime(time())+"\n");

       // if (me->query_temp("award_doubling"))
        //me->addn("combat_exp", (int)me->query_temp("award_pending")/50);       
        delete_temp("award_pending", me);
        delete_temp("award_doubling", me);
        delete_temp("award_pot", me);
        delete_temp("marks/葛", me);

        //clean all stuff in fatan after finish  // by maco
        inv = all_inventory(ob);
        for (i=0; i < sizeof(inv); i++) 
                {
                        destruct(inv[i]);
                }

        if( random(query("potential", me)-query("learned_points", me))>me->query_con()*10 )
        me->unconcious();

        remove_call_out("renewing");
        call_out("renewing", 50 + random(100), ob);
}

void renewing(object ob)
{
        set("last_burner",query("pending",  ob), ob);
        set("pending", 0, ob);
        ob->set("long","这是一个极其庞大的铜制祭坛，高约三丈，方圆约有五丈，乃是当年吐番国王亲\n"
                        "自指挥铸造的，耗倾国之力，十年方成。\n");
}                                
