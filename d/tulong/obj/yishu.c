#include <ansi.h>; 
inherit ITEM;

void init()
{
        add_action("do_du", "du");
        add_action("do_du", "study");
}

int query_autoload() { return 1; }
void create()
{
        set_name(CYN"武穆遗书"NOR, ({ "wumu yishu", "book", "yishu"}));
        set_weight(500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("material", "paper");
                set("no_sell", "这样东西不能卖。\n");
                set("long", "一本薄薄的绢帛，乃抗金大将岳飞灌注毕生心血所编撰而成。\n", );
        }
        setup();
}

int do_du(string arg)
{
        object me = this_player();
        object where = environment(me);
        object ob;
        mapping skill;
        int pxlevel, arlevel; 

        if (!(arg=="wumu yishu" || arg == "book" || arg == "yishu" ))
        return 0;
        if (me->is_busy()) {
                write("你现在正忙着呢。\n");
                return 1;
        }
        if( me->is_fighting() ) {
                write("你无法在战斗中专心下来研读新知！\n");
                return 1;
        }
        if (!id(arg)) { 
                write("你要读什么？\n");
                return 1;
        }
        if( !me->query_skill("literate", 1) ){
                write("你是个文盲，先学点文化(literate)吧。\n");
                return 1;
        }
        message("vision", me->name() + "正专心地研读武穆遗书。\n", environment(me), me);
        if( query("jing", me)<80){
                write("你现在过于疲倦，无法专心下来研读新知。\n");
                return 1;
        }
        if( query("qi", me)<80){
                write("你现在过于疲倦，无法专心下来研读新知。\n");
                return 1;
        }
        pxlevel = me->query_skill("craft-cognize", 1);
        arlevel = me->query_skill("array-cognize", 1);
        if( query("combat_exp", me)<100000){
                write("你的实战经验不足，无法看懂武穆遗书中的内容。\n");
                return 1;
        }
        if( query("combat_exp", me)<pxlevel*pxlevel/10*pxlevel){
                write("你的实战经验不足，无法看懂武穆遗书中的内容。\n");
                return 1;
        }
        if( me->query_skill("craft-cognize", 1) > 399 &&
            me->query_skill("array-cognize", 1) > 399){
                write("你发现对于武穆遗书上的兵法和阵法要诣已经了然于胸，完全掌握了。\n");
                return 1;
        }
        me->receive_damage("qi", 50);
        me->receive_damage("jing", 50);
        if( pxlevel < 400 )
                me->improve_skill("craft-cognize", (int)me->query_skill("literate", 1)/5+1);
        if( arlevel < 400 )
                me->improve_skill("array-cognize", (int)me->query_skill("literate", 1)/5+1);
        write("你仔细研读武穆遗书中兵法和阵法，颇有心得。\n");
        return 1;
}
