#include <ansi.h>
#include <weapon.h>
inherit CLUB;

void create()
{
        set_name(HIG "��ľ��" NOR, ({ "tiemu gun", "gun" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIG "����һ����ǧ����ľ������Ĺ��ӣ������Ƿ���\n" NOR);
                set("material", "wood");
                set("value", 600000);
                set("wield_msg", "$N���һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n������䡣\n");
        }
        init_club(500);
        setup();
}

int query_autoload()
{
        return 1;
}
