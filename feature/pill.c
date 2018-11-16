// pill.c

#include <name.h>

void init()
{
        add_action("do_eat", "eat");
}

int do_eat(string arg)
{
        string healwhat;

        if( !this_object()->id(arg) ) return 0;
        if( this_player()->is_busy() )
                return notify_fail("����æ���ء�\n");

        if (!(healwhat = query("heal")))
                return notify_fail("���������������ˡ�\n");


        if( !query("food_remaining") )
                return notify_fail( name() + "�Ѿ�ûʲô�óԵ��ˡ�\n");
        if( (int)query("food", this_player()) >= (int)this_player()->max_food_capacity() )
                return notify_fail("���Ѿ���̫���ˣ���Ҳ�������κζ����ˡ�\n");

        addn("food", query("food_supply"), this_player());
        if( this_player()->is_fighting() ) this_player()->start_busy(2);

        // This allows customization of drinking effect.
        if( query("eat_func") ) return 1;

        set("value", 0);
        addn("food_remaining", -1);
        if( !query("food_remaining") ) {
                message_vision("$N��ʣ�µ�" + name() + "�Եøɸɾ�����\n", this_player());
                if( !this_object()->finish_eat() )
                        destruct(this_object());
        } else
                message_vision("$N����" + name() + "ҧ�˼��ڡ�\n", this_player());

        return 1;
}
