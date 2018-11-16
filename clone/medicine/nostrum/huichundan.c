// huichundan.c �ش���
// Last Modified by Winder on Mar. 5 2001

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIG"�ش���"NOR, ({"huichun dan", "dan"}));
        set("unit", "��");
        set("vegetable", 0);
        set("nostrum", 0);
        set("level", 300);
        set("long", "����һ��������͸�Ļش�����\n");
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        object me=this_player();

        if (!present(this_object(), me))
                return notify_fail("��Ҫ��ʲô��\n");
        if (!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if( me->is_busy() )
                return notify_fail("�𼱣������ȣ�С�ı�Ǻ���ˡ�\n");

        if( query("age", me) <= 39 )
        {
                message_vision("$Nû��Ҫ�Իش�����\n",me);
        }
        else
        {
                addn("mud_age", -86400, me);
                addn("vegetable/huichun", 1, me);
                delete("last_slp", me);
                delete("jingzuo_time", me);
                message_vision("$N����һ���ش��������˸��������������ӹ��������ࡣ\n",me);
                destruct(this_object());
        }
        return 1;
}