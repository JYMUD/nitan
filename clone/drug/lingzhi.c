// Code of ShenZhou
//lingzhi.c

#include <ansi.h>

inherit ITEM;

int cure_ob(string);
void init();

void create()
{
        set_name(HIW "��֥" NOR, ({"ling zhi", "zhi"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "ö");
                set("long", HIW"����һö��֥����Լ�Ĵ磬��ɡ״��ͨ�徧�ס�\n"NOR);
                set("value", 20000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("cool_drug") > 0){
        addn("max_jingli", -1, me);
        addn("eff_jingli", -1, me);
        message_vision(HIR "$N����һö��֥��ֻ����ͷ�ؽ��ᣬҡҡ������ԭ����ʳ̫��̫�࣬ҩЧ�ʵ��䷴��\n" NOR, me);
        destruct(this_object());
        return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("jingli",query("max_jingli",  me), me);
        set("qi",query("max_qi",  me), me);
        set("neili",query("max_neili",  me), me);
        
        message_vision(HIG "$N����һö��֥��ֻ���þ���������Ѫ��ӯ����������ԴԴ�������������ٸе������ɿ�! \n" NOR, me);

        me->apply_condition("cool_drug", 30);
        destruct(this_object());
        return 1;
}