// literateb4.c 論語
#include <ansi.h>
inherit ITEM;
void create()
{
        set_name(YEL"論語"NOR, ({ "literateb4", "shu4", "book4"}));
        set_weight(300);
        if( clonep() )
            set_default_object(__FILE__);
        else {
            set("unit", "本");
            set("long","一本孔夫子的《論語》。\n");
            set("value", 400);
            set("material", "paper");
            set("skill", ([
                "name": "literate",    // name of the skill
                "exp_required": 10,    // minimum combat experience required
                "jing_cost":    40,    // jing cost every time study this
                "difficulty":   45,    // the base int to learn this skill
                "max_skill":   120,    // the maximum level you can learn to
                "min_skill":   110,    // minimun level required
            ]) );
        }
}
int query_autoload()
{
        return 1;
}