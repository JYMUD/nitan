#include <ansi.h>
#include <weapon.h>
inherit WHIP;

void create()
{
        set_name(HIY "��β����", ({ "longwei bian", "bian","longwei" }));
        set_weight(300);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIY "����һ���������صĳ��ޣ���˵������β�������������ơ�\n" NOR);
                set("wield_msg", "$N��ৡ���һ����������һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n�������\n");
                set("value", 100000);
        }
        init_whip(300);
        setup();
}

int query_autoload()
{
        return 1;
}

