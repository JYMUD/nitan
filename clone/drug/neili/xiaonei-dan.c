#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "С�ڵ�" NOR, ({"xiaonei dan", "xiaonei", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 2000);
                set("only_do_effect", 1);
                set("long", HIY "һ����ɫ��ҩ�衣�ָ�500��������\n" NOR);
        }
        setup();
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if( time()-query_temp("last_eat", me)<2 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        set_temp("last_eat", time(), me);

        message_vision(HIW "$N����һ��С�ڵ����е������������䡣\n" NOR, me);

        if( query("max_neili", me)-query("neili", me)<500 )
                  set("neili",query("max_neili",  me), me);
        else
                  addn("neili", 500, me);


        destruct(this_object());

        return 1;
}

int query_autoload()
{
        return 1;
}