
#include <armor.h>
#include <ansi.h>

inherit MYHEART;

void create()
{
        set_name(HIM "������β" NOR, ({ "xianshu lingwei", "xianshu", "lingwei" }) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "��");
                set("long", HIM "��Ԫ��������괺�ڣ��������ɵ���������նɱ����������õ���β���쳣���������ء�\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   1000000,
                ]));                
                set("armor_prop/qy", 3);
                set("armor_prop/fy", 3);
                set("armor_prop/damage", 200);
                set("armor_prop/str", 4);
                set("armor_prop/int", 4);
                set("armor_prop/dex", 4);
                set("armor_prop/con", 4);
                set("special/desc", HIR "���������������ɱ�ֽ���1%���Ҽ������������ƶ�æ��ʱ�䡣" NOR);
                set("armor_prop/xianshu-lingwei", 1);

        }
        setup();
}

int query_autoload()
{
        return 1;
}