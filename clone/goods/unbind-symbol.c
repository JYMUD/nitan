#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "����󶨷�" NOR, ({ "unbind symbol", "unbind", "symbol" }));
        set_weight(3000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", YEL "�÷��Ŀ��Խ��(unbind)��Ʒ�İ����ԡ�\n" NOR);
                set("unit", "��");
                set("value", 500000);
        }
        setup();
}

void init()
{
        add_action("do_unbind", "unbind");
}

int do_unbind(string arg)
{
        object me;
        object ob;

        if (! arg || arg == "")
                return notify_fail("��Ҫ��ʲô������ʹ�ø������\n");

        me = this_player();
        if (! objectp(ob = present(arg, me)) &&
            ! objectp(ob = present(arg, environment(me))))
                return notify_fail("�����Ϻ͸���û���������߰���\n");

        if (ob == this_object() || ob->is_character())
                return notify_fail("����Ҫ��ʲô?\n");

        if (!query("bindable", ob))
                return notify_fail("�����Ʒû�а󶨹����������󶨣�\n");

        delete("bindable", ob);
        delete("bind_owner", ob);
        set("set_data", 1, ob);
        set("auto_load", 1, ob);

        tell_object(me, "���" + name() + "����" + ob->name() + "�ϣ�Ȼ����������дʣ�"
                        "ֻ��ʥ������һ��������" + ob->name() + "���ڣ�\n");

        tell_object(me, HIC "�����" + ob->name() + HIC"�Ѿ�����˰󶨡�\n" NOR);

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}


