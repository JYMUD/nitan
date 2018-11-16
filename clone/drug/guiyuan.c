// Code of ShenZhou
// guiyuan.c 归元丹
// Ryu
// Modified by xQin to forbid the abuse of gyd

inherit PILL;
#include <ansi.h>
void setup()
{}
void init();
void wear(int);

int worn;

int cure_ob(string);
void create()
{
        set_name("归元丹", ({"guiyuan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "颗");
                set("long", "这是一颗莹白溜圆的归元丹。\n");
                set("value", 5000);
                set("no_sell", 1);
                set("medicine", 1);
        }
        setup();
}

int cure_ob(object me)
{
        addn("neili", -200, this_player());
        message_vision(HIR "$N吃下一棵归元丹，只觉得头重脚轻，火气翻腾，原来服食过猛，药效适得其反！\n" NOR, this_player());
        this_player()->apply_condition("bonze_drug",
                this_player()->query_condition("bonze_drug")+10);
        destruct(this_object());
        return 1;
}

void init()
{
        worn = 0;
        call_out("wear", 1200, 1);

        add_action("do_pour", "drop");
}



void wear(int phase)
{
        worn = phase;
        switch(phase) {
        case 1:
                set("long", "这是一粒搁了很长时间的归元丹。\n");
                call_out("wear", 300, phase+1);
                break;
        case 2:
                set("long", "这是一粒已经不太成形的归元丹，快被风化了。\n");
                call_out("wear", 100, phase+1);
                break;
        case 3:
                destruct(this_object());
                break;
        }
}
int effect_in_liquid(object ob)
{
        object me = this_player();
        if (this_player()->query_condition("bonze_drug" ) > 0 )
        {        
        addn("neili", -50, me);
        message_vision(HIR "$N喝下一口药酒，发现原来体内药性过猛，适得其反。\n" NOR, this_player());
        this_player()->apply_condition("bonze_drug",
        this_player()->query_condition("bonze_drug")+10);
        return 1;
        }
        
        if( query("neili", this_player())>query("max_neili", this_player())*2 )
        set("neili",query("max_neili",  this_player())*2-1, this_player());
        if( query("liquid/type", ob) == "alcohol" && !query("zuixian", ob)){
        tell_object(this_player(), HIG"你只觉得体内真力源源滋生，不绝如缕。\n"NOR);
        addn("neili", random(10)+10*query("liquid/drunk_apply", ob), this_player());
        me->apply_condition("bonze_drug", 30);
        return 1;
        }
}