#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIY"С��"NOR, ({"gold dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "��");
                set("base_value", 50);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if( time()-query_temp("last_eat/dan(D, me)")<10 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();
        nl=query("neili", me)+100;
        mn=query("max_neili", me)*2;

        if (nl > mn)
        {
                write("������������Ϊ�������" + name() + "��\n");
                return 1;
        }

        set_temp("last_eat/dan(D)", time(), me);

        message_vision(HIY "$N����һ��С�𵤣��е������������䡣\n" NOR, me);
        addn("neili", 100, me);

        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}