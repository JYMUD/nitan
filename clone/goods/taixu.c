#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIY "�Ϲš�̫��" NOR, ({"tai xu", "tai", "xu"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIY "һ����ɫ��̫�飬ӵ������仯��ħ������\n"
                            "���Ǵ�˵�е����������Ϲ�̫�飬�ഫΪ�Ϲ�\n"
                            "ʱ�����Ƶ۵þ�����Ů�����ϱ��������ƶ��ɡ�\n"
                            "�Ϲ�����Ѿ�ͨ�顣\n" NOR);
                set("value", 10000000);
                set("unit", "��");
                set("can_be_enchased", 1);
                set("magic/type", "metal");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_metal" : 50,
                "add_skill" : 30,
        ]));
        setup();
}

int query_autoload() { return 1; }
