
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIY "��ͷ��" NOR, ({ "huang toujin2", "huang", "toujin2" }) );
        set_weight(300);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "cloth");
                set("unit", "��");
                set("long", HIY "����һ����ͷ���ഫ�����ƽ�����������\n" NOR);
                set("value", 100000);
                set("armor_prop/armor", 100);
                set("armor_prop/str", 12);
        }
        setup();
}

int query_autoload()
{
        return 1;
}