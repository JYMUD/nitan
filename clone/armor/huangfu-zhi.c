
#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(NOR + YEL "�Ʒ�ֽ" NOR, ({ "huangfu zhi", "huangfu", "zhi" }) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "��");
                set("long", NOR + YEL "һ�ŷ��Ƶķ�ֽ�������ú�ɫ�����ϻ��Ÿ�����ֵķ��š�\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/qy", 5);

        }
        setup();
}

int query_autoload()
{
        return 1;
}