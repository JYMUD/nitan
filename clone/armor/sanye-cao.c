
#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIG "��Ҷ��" NOR, ({ "sanye cao", "sanye", "cao" }) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "Ƭ");
                set("long", HIG "����һƬ����ƬҶ�ӵ���ݣ��˷�ɣ�����˲ݡ�\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/qy", 3);

        }
        setup();
}

int query_autoload()
{
        return 1;
}