
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIY "�콵�����¹�" NOR, ({ "lengyue guan", "lengyue", "guan" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "��˵���¹�����̺��ŷǷ�֮������\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 30);
                set("armor_prop/str", 30);
                set("armor_prop/con", 30);
                set("armor_prop/damage", 3000);
                set("armor_prop/blade", 100);
                set("special/desc", "��Ч�����ȼ����100����");
                set("limit", ([
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));
                
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}