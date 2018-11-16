// Code of ShenZhou
// renshen-guo.c �˲ι�

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIG "�˲ι�" NOR, ({"renshen guo", "guo"}));
        set_weight(90);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long", "����һö�˲ι�������ȥ����һ���װ����ֵ�С���ޡ�\n");
                set("value", 20000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("cool_drug") > 0){
        addn("max_neili", -1, me);
        message_vision(HIR "$N����һö�˲ι���ֻ����ͷ�ؽ��ᣬҡҡ������
ԭ����ʳ̫��̫�࣬ҩЧ�ʵ��䷴��\n" NOR, me);
        destruct(this_object());
        return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        if (random(2)==1) addn("max_neili", 2, me);
        set("neili",query("max_neili",  me), me);
        set("food", me->max_food_capacity(), me);
        set("water", me->max_water_capacity(), me);
        
        message_vision(HIG "$N����һö�˲ι���ֻ���þ���������Ѫ��ӯ����������ԴԴ��������ƣ������һɨ����! \n" NOR, me);
        me->apply_condition("cool_drug", 30);
        destruct(this_object());
        return 1;
}
