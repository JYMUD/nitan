// bian.c ��

#include <weapon.h>
inherit WHIP;

void create()
{
        set_name("����", ({ "chang bian", "bian","whip" }));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ����ͨ�ĳ��ޣ������ֲڡ�\n");
                set("wield_msg", "$N��ৡ���һ����������һ��$n�������С�\n");
                set("unwield_msg", "$N�����е�$n�������\n");
        }
        init_whip(5);
        setup();
}
