#include <ansi.h>
#include "pill.h"

void create()
{
        set_name(HIY "����" NOR, ({ "haotian guo", "haotian", "guo" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "����һö���ɫ�Ĺ�ʵ�����ú��������˵���ۡ�\n" NOR);
                set("base_unit", "ö");
                set("base_value", 6000);
                set("base_weight", 80);
                set("only_do_effect", 1);

        }
        setup();
}

int do_effect(object me)
{
        int na, un;

        na = query("name");
        un = query("base_unit");

        if( time()-query_temp("last_eat/dan(linghui, me)")<100 )
        {
                write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
                return 1;
        }
        set_temp("last_eat/dan(linghui)", time(), me);

        message_vision(HIY "$N" HIY "һ������������һ" + un + na +
                       HIY "��\n" NOR, me);
        addn("magic_points", 5+random(6), me);

        me->start_busy(3);
        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}