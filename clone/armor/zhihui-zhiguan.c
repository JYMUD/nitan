
#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIR "�ǻ�֮��" NOR, ({ "zhihui guan", "zhihui", "guan" }) );
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("material", "gold");
                set("unit", "��");
                set("long", HIR "����һ�������ǻ�֮���ͷ�ڣ�������ʹڤ˼�����ӱ���\n" NOR);
                set("value", 350000);
                set("armor_prop/int", 6);
                set("armor_prop/reflect2", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}