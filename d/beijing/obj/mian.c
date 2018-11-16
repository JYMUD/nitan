// mian.c

inherit ITEM;

void create()
{
        set_name("��", ({ "mian" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "һ���������ڵ����档\n");
                set("unit", "��");
                set("value", 100);
                set("remaining", 2);
                set("food_supply", 25);
                set("water_supply", 10);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if( query("food", me) >= me->max_food_capacity() )
                return notify_fail("���Ѿ���̫���ˣ���Ҳ�Բ����ˡ�\n");

        set("value", 0);
        addn("food", query("food_supply"), me);
        if( query("water", me)<me->max_water_capacity()-query("water_supply") )
                addn("water", query("water_supply"), me);

        if (me->is_fighting())
                me->start_busy(2);

        addn("remaining", -1);
        if (query("remaining"))
                message_vision("$N�������棬���̻��ʵس�������\n", me);
        else 
        { 
                message_vision("$N������������ʣ�µ����������ˡ�\n"
                               "$N��������һ�ӣ�Ĩ��Ĩ�죬�޵������㣡\n", me);
                destruct(this_object());
        }

        return 1;
}
