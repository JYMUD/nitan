#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
        set_name(WHT "���ߵ�" NOR, ({"guiling dan", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("base_unit", "��");
                set("no_drop", "�������������뿪�㡣\n"); 
                set("no_sell", "�������������뿪�㡣\n"); 
                set("no_put", "�����������ܷ����Ƕ���\n"); 
                set("no_get", "�������������뿪�Ƕ���\n"); 
                set("no_steal", "�������������뿪�Ƕ���\n"); 
                set("no_beg", "�������������뿪�Ƕ���\n"); 
                set("base_value", 0);
                set("only_do_effect", 2);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/dan(M, me)")<400 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }

        my = me->query_entire_dbase();

//        me->set_temp("last_eat/dan(M)", time());

        if (me->improve_neili(2))
                message_vision(WHT "$N" WHT "����һ�����ߵ����е��������ۺ���һЩ��\n" NOR, me);
        else
                message_vision(WHT "$N" WHT "����һ�����ߵ����о�����ûʲôЧ����\n" NOR, me);

//        me->start_busy(6);
        me->start_busy(1);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}

void owner_is_killed() 
{
        destruct(this_object()); 
}