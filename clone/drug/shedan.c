// Code of ShenZhou
//  poison: shedan.c
// Jay 3/18/96
// ryu added effect_in_liquid

inherit PILL;
#include <ansi.h>;
int cure_ob(string);


void create()
{
        set_name("���ߵ�", ({"shedan", "dan"}));
        set("unit", "��");
        set("long", "����һֻ��ӨӨ�Ķ��ߵ���\n");
        set("value", 200);
                set("no_sell", 1);
        set("medicine", 1);
        setup();
}

/*
int do_eat(string arg)
{
        if (!id(arg))
                return notify_fail("��Ҫ��ʲô��\n");
        return notify_fail("����������\n");
}
*/


void init()
{
        add_action("do_pour", "drop");
}
int cure_ob(object me)
{
   message_vision("$N����һ��" + name() + "��\n", me);
   if ((int)me->query_condition("snake_poison") > 7) {
      me->apply_condition("snake_poison", (int)me->query_condition("snake_poison") - 5);
   }

   destruct(this_object());
   return 1;
}
int effect_in_liquid(object ob)
{
        if( query("liquid/type", ob) == "alcohol"){
        addn("qi", 10*query("liquid/drunk_apply", ob), this_player());
        tell_object(this_player(), MAG"��е�һ����������ע�뵤���������ů���ġ�\n"NOR);
        }
        return 0;
}