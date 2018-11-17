#include <ansi.h>

inherit __DIR__"skpaper";

void create()
{
        set_name(NOR + WHT "杖譜殘篇" NOR, ({ "zhangpu canpian", "zhangpu", "canpian" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是一張殘缺不全的書頁。\n" NOR);
                set("value", 30);
                set("no_sell", "什麼世道，就一張破紙頭也拿來賣錢？");
                set("material", "paper");
                set("skill_name", "基本杖法");
                set("skill_type", "staff");
                set("power_point", 30000);
                set("need_exp", 300000);
                set("min_lvl", 100);
                set("max_lvl", 300);
        }
        setup();
}