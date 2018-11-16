#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(CYN"��Ȫ��"NOR, ({"suoquan dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "��");
                set("base_value", 70);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;
        int jl, mj;

        if( time()-query_temp("last_eat/dan(C, me)")<60 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();
        jl=query("jingli", me)+220;
        mj=query("max_jingli", me)*2;

        if (jl > mj)
        {
                write("�����ھ�����Ϊ�������" + name() + "��\n");
                return 1;
        }

        set_temp("last_eat/dan(C)", time(), me);

        message_vision(CYN "$N����һ����Ȫ����������֮һ�𣬾���������ߡ�\n" NOR, me);
        addn("jingli", 220, me);

        me->start_busy(2);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}