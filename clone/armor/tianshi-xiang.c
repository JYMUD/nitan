#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIY "��ʦ��" NOR, ({ "tianshi xiang", "tianshi", "xiang" }) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "��");
                set("long", HIY "һ�����ư��С��ͭ��ϸ��֮�£���Ȼ�м������졣\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/kar", 5);

        }
        setup();
}

int query_autoload()
{
        return 1;
}
