#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIC "���ġ��ɻ�" NOR, ({"dixin shihun", "dixin", "shihun"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIC "һ����ɫ�ĵ����ɻ꣬ӵ�м������򶾼�а��\n"
                            "��һ����������������ɻ꣬�ഫΪа��֮��\n"
                            "��ɲ������֮�ף�������걻Ů����������\n"
                            "���ǣ��Ե��Ķ��������ɡ��Ϲ�����Ѿ�\n"
                            "ͨ�顣\n" NOR);
                set("value", 10000000);
                set("unit", "��");
                set("can_be_enchased", 1);
                set("magic/type", "fire");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_fire"  : 50,
                "add_skill" : 30,
        ]));
        setup();
}

int query_autoload() { return 1; }
