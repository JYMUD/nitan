#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
        set_name(HIY "����֮Դ" NOR, ({ "tianlai zhiyuan", "tianlai", "zhiyuan" }));
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "����ͨ�巺���߲�֮�⣬ҫ�۶�Ŀ�������µ�һ�١��Ͽ̡�" HIC "����֮Դ" HIY "����\n" NOR);
                set("value", 5000000);
                set("material", "gold");
        }
        setup();
}

void init()
{
        add_action("play_qin", "play");
}
