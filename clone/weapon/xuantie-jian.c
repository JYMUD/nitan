#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(NOR + WHT "�����ؽ�" NOR, ({ "xuantie jian", "xuantie", "jian" }));
        set_weight(5000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ����ɽ��������Ĵ󽣣����ֳ����ޱȣ�����ȴ�������÷�����\n");
                set("value", 2000);
                set("material", "steel");
                set("wield_msg", "$N��ৡ���һ�����һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n��ؽ��ʡ�\n");
        }
        init_sword(500);
        setup();
}
