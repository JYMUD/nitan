
#include <weapon.h>
#include <ansi.h>
inherit STAFF;

void create()
{
        set_name(NOR + YEL "��ͭ��" NOR, ({ "qingtong zhang","qingtong","zhang" }));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", NOR + YEL "����һ����ͭ������ȣ����ֳ����ģ��ƺ��൱��ʵ��\n" NOR);
                set("material", "qingtong");
                set("value", 100000);
        }
        init_staff(300);
        setup();
}

int query_autoload()
{
        return 1;
}
