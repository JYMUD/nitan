

#include <weapon.h>
inherit STAFF;

void create()
{
        set_name("��ľ��", ({ "taomu zhang" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ���������������ȡ�\n");
                set("value", 2000);
                set("rigidity", 100);
                set("material", "wood");
                set("wield_msg", "$N���һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
          init_staff(100);
        setup();
}
