#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(HIR"���赤"NOR, ({"huoqi dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "��");
                set("base_value", 80);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;
        int nl, mn;

        if( time()-query_temp("last_eat/dan(D, me)")<150 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();
        nl=query("neili", me)+800;
        mn=query("max_neili", me)*2;

        if (nl > mn)
        {
                write("������������Ϊ�������" + name() + "��\n");
                return 1;
        }

        set_temp("last_eat/dan(D)", time(), me);

        message_vision(HIR "$N����һ�����赤���е������������䡣\n" NOR, me);
        addn("neili", 800, me);

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}