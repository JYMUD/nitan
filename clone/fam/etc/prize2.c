#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "士章" NOR, ({ "chivalry medal", "chivalry", "medal" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "英女王的章，似乎可以好。\n" NOR);
                set("unit", "枚");
                set("value", 500000);
        }
        setup();
}