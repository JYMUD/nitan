#include <weapon.h>
inherit CLUB;

void create()
{
        set_name("��ü��", ({ "qimei gun", "gun" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ����ľ���������ٿ���ü�����غ��ˡ�\n");
                set("material", "wood");
                set("wield_msg", "$N���һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
                set("shaolin",1);
        }
        init_club(5);
        setup();
}
