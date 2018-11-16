#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "冲穴铜人·手阳明脉·手三里穴" NOR, ({ "tongren r15", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "个");
                set("long", NOR + YEL "这是一个冲穴铜人，上面绘制了一些经络穴位图案，以及冲穴使用方法。\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "手阳明脉");
        set("xuewei_name", "手三里穴");
        set("chongxue_xiaoguo", "FOOD:40:ADDPOT:1000000");
        set("neili_cost", "8000");
        setup();
}

