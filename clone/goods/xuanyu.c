#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIG "�ŵء�����" NOR, ({"jiudi xuanyu", "jiudi", "xuanyu"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIG "һ����ɫ�ľŵ�����ӵ����ҽ�ز������ܶ�\n"
                            "ɱ����һ������������ŵ������ഫ��ũ��\n"
                            "������ũ�߾�������ö�ŵ����������ɡ���\n"
                            "������Ѿ�ͨ�顣\n" NOR);
                set("value", 10000000);
                set("unit", "��");
                set("can_be_enchased", 1);
                set("magic/type", "earth");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_earth" : 50,
                "add_skill" : 30,
        ]));
        setup();
}

int query_autoload() { return 1; }
