#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "˳����" NOR, ({"shunqi wan", "shunqi", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("value", 30000);
                set("only_do_effect", 1);
                set("long", HIY "һ����ɫ��ҩ�衣�ָ�1000��������\n" NOR);
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

        message_vision(HIW "$N����һ��˳���裬�е������������䡣\n" NOR, me);

        if( query("max_neili", me)-query("neili", me)<1000 )
                  set("neili",query("max_neili",  me), me);
        else
                  addn("neili", 1000, me);


        destruct(this_object());

        return 1;
}

int query_autoload()
{
        return 1;
}