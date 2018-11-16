#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "��ʥѪ��" NOR, ({ "god blood", "god", "blood" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "�@��һƿ��ʥѪ�壬�ƺ�������á�\n" NOR);
                set("unit", "ƿ");
                set("value", 300000);
        }
        setup();
}

void init()
{
        add_action("do_drink", "drink");
}

int do_drink(string arg)
{
        object me = this_player();

        string mapsk;
        string na, un;
        mapping my = me->query_entire_dbase();

        na = query("name");
        un = query("unit");

        if (! arg || ! id(arg))
                return notify_fail("��Ҫ��ʲô������\n");

        if (me->is_busy())
                return notify_fail("��ʲô��С�ı�ҭ���ˡ�\n");

        my = me->query_entire_dbase();

        if( time()-query_temp("last_eat/blood", me)<1800 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        set_temp("last_eat/blood", time(), me);


        message_vision(HIY "$N" HIY "һ��������һ��" + un + na +
                       HIY "���£���Ҳ�о������κ�ƣ����\n" NOR, me);

        my["jing"]     = my["max_jing"];
        my["qi"]       = my["max_qi"];
        my["eff_jing"] += my["max_jing"]/2;
        if( my["eff_jing"] > my["max_jing"] ) my["eff_jing"] = my["max_jing"];
        my["eff_qi"] += my["max_qi"]/2;
        if( my["eff_qi"] > my["max_qi"] ) my["eff_qi"] = my["max_qi"];
        my["neili"]    = my["max_neili"];
        my["jingli"]   = my["max_jingli"];

        me->start_busy(3);
        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
