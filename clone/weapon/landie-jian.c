#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(HIC "��������" NOR, ({ "landie jian", "landie", "jian" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIC "����һ��������˵�ı�������������ɾ����������ӵ������������ɰ����������������̲��ž޴��������\n" NOR);
                set("value", 2000);
                set("limit", ([
                         "exp" : 2088888888,
                         //"thborn" : 1,
                         "str" : 700,
                         "dex" : 700,
                         "int" : 700,
                         "con" : 700,
                ]));
                set("material", "steel");
                set("wield_msg", "һ����ɫ�Ľ�â������ֻ����â����һֱ��ɫ�ĺ�������â��ȥ$N" HIC "����ȴ����һ�ѱ�����\n");
                set("unwield_msg", HIC "$N" HIC "һ����̾��$n����һ����ɫ������ʧ�ˡ�\n" NOR);
        }
        init_sword(5000);
        setup();
}
