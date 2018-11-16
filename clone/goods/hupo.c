#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIB "�Ϲš�����" NOR, ({"tiger soul", "tiger", "soul"}));
        set_weight(50);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", HIB "\nһ����ɫ�Ļ��ǣ���Ͼ�ı������ǳ���õĹ�\n"
                            "�����з·��̲��������ħ��������Ǵ�˵\n"
                            "�е�����������֮�׵ġ����ϹŻ��ǣ��ഫΪ\n"
                            "�Ϲ�ʱ������������������ƶ��ɡ��Ϲ����\n"
                            "�Ѿ�ͨ�顣\n" NOR);
                set("value", 10000000);
                set("unit", "��");
                set("can_be_enchased", 1);
                set("magic/type", "wood");
                set("magic/power", 1000);
        }
        set("enchase/SN", 5 + random(5));
        set("enchase/type", "all");
        set("enchase/weapon_prop", ([
                "add_wood"  : 50,
                "add_skill" : 30,
        ]));
        setup();
}

int query_autoload() { return 1; }
