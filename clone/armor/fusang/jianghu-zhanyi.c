

#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIG "����ս��" NOR, ({ "jianghu zhanyi", "jianghu", "zhanyi" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIG "��ɣ����������ս�£��˵´����������У�ս���Ͼ����С��´�����������\n" NOR);
                set("material", "steel");
                set("value", 800000);
                set("armor_prop/armor", 600);

        }
        setup();
}

int query_autoload()
{
        return 1;
}
