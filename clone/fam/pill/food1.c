#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(HIC "������" NOR, ({ "yangsheng dan", "yangsheng", "dan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "������ҩ�ľ������ɣ����Ǹ������Ĺ��\n" NOR);
                set("base_unit", "��");
                set("base_value", 10000);
                set("base_weight", 55);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int na, un, limit1, limit2;

        na = query("name");
        un = query("base_unit");

        limit1 = me->max_food_capacity();
        limit2 = me->max_water_capacity();

        message_vision(HIC "$N" HIC "һ������������һ" + un + na + HIW "��\n" NOR, me);

        if( query("food", me)<limit1*3 || query("water", me)<limit2*3 )
        {
                       tell_object(me, HIY "��ֻ��ƣ��һɨ���գ���Ҳ�����ü�����\n" NOR);

                if( query("food", me)<limit1*3 )
                        set("food", limit1*3, me);

                if( query("water", me)<limit2*3 )
                        set("water", limit2*3, me);
        } else
        {
                       tell_object(me, HIR "��ֻ�����ӡ����������и���ͣ�������˸����"
                                "�ޱȵ�ƨ��\n" NOR);

                if( query("food", me)>limit1/10 )
                        set("food", limit1/10, me);

                if( query("water", me)>limit2/10 )
                        set("water", limit2/10, me);
        }
        me->start_busy(random(1) + 1);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}