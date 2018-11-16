// yellowyao.c

// inherit F_CLEAN_UP;
inherit COMBINED_ITEM;
#include <ansi.h>

void create()
{
        set_name(HIY"黄色药粉"NOR, ({ "yellow yao","yao"}) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "这是一包五毒教精炼的毒药。\n你可以用(ypour)命令试试。\n" );
                set("unit", "些");
                set("base_value", 200);
                set("base_unit", "包");
                set("base_weight", 30);
                set("pour_type", "wugong_poison");
                set("value", 200);
        }
        set_amount(1);
}

void init()
{
        add_action("do_ypour", "ypour");
        add_action("do_tu", "tu");
}

int do_ypour(string arg)
{
        string what;
        object ob,me,who,victim;
//        object *inv;
        function f;
        me = this_player();
        if( !arg || sscanf(arg, "%s in %s", who, what)!=2 || victim == me)
                return notify_fail("命令格式: ypour <人物> in <物品>。\n");
        victim = present(who, environment(me));
        if( !victim || victim==me) return notify_fail("没有你想下毒的人哦。\n");
        if( query("family/family_name", me) != "五毒教" )
                return notify_fail("下毒！！你怎么能干这么卑鄙的事哦？\n");
        if ((int)me->query_skill("five-poison",1) < 50)
                return notify_fail("才这么点本事就想害人？别弱了我五毒教的威名啊！\n");
        ob = present(what, victim);
        if( !ob )
                return notify_fail("对方身上没有" + what + "这样东西。\n");
//        if( me->query_temp("being_toudu") )
//                return notify_fail("你已经在找机会下手了！\n");
        if( query("max_liquid", ob) )
        {
                int myskill=(me->query_skill("five_poison",1))*10+query("neili", me);
                int skill=query("neili", victim);
                if( query("liquid/remaining", ob)<1 )
                return notify_fail("那个容器是空的，不能用来溶解毒粉！\n");
                if (random(myskill)<random(skill))
                {
                        tell_object(me, HIR "糟糕！你失手了！\n\n" NOR);
                        message_vision("$N一回头，正好发现$n正想向$P身上的" + ob->name() + "下毒！\n\n" + "$N喝道：「干什么！」\n\n", victim, me);
                        if( userp(victim) )
                        {
                                victim->fight_ob(me);
                                me->fight_ob(victim);
                        }
                        else
                        {
                                victim->kill_ob(me);
                                me->kill_ob(victim);
                        }
                        me->start_busy(3);
                        return 1;
                }
                f = (: call_other, __FILE__, "drink_drug" :);
                set("liquid/drink_func", bind(f,ob), ob);
                addn("liquid/slumber_effect", 100, ob);
                message("vision","你与" + victim->name() + "擦身而过，偷偷将《" + name() + "》洒进他的" + ob->name()+ "里面。\n", this_player());
                add_amount(-1);
                me->start_busy(2);
                if( random(myskill) < skill/2 )
                        message("vision","你看到"+me->name()+"鬼鬼祟祟地在"+victim->name()+"身上的一"+query("unit", ob)+ob->name()+"里洒入了一些"+name()+"！\n",environment(me),({me,victim}));
                return 1;
        }
        else return notify_fail("毒只能下在饮水里面！\n");
        return 1;
}

int drink_drug(object ob)
{
        this_player()->apply_condition("wugong_poison",this_player()->query_condition("wugong_poison")+query("liquid/slumber_effect", ob));
        return 0;
}

#include "poison2.h";
