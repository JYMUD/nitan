// Code of ShenZhou
// yulu-wan.c �Ż���¶��

#include <ansi.h>

inherit PILL;

void create()
{
        set_name(GRN "�Ż���¶��" NOR, ({"yulu wan", "wan"}));
        set_weight(90);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ���Ż���¶�裬����һ����������Ƣ��������\n");
                set("no_drop","�Ż���¶��������ף��������ӣ� \n");
                set("value", 10000);
                set("no_sell", 1);
                set("medicine", 1);
        }

        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("cool_drug") > 0){
        addn("max_neili", -1, me);
        message_vision(HIR "$N����һ���Ż���¶�裬ֻ����ͷ�ؽ��ᣬҡҡ������ԭ����ʳ̫��̫�࣬ҩЧ�ʵ��䷴��\n" NOR, me);
        destruct(this_object());
        return 1;
        }
        set("eff_jing",query("max_jing",  me), me);
        addn("jing", 200, me);
        addn("jingli", 200, me);
        set("eff_qi",query("max_qi",  me), me);
        addn("qi", 200, me);
//        if (random(3)==1) me->add("max_neili", 3);
//        me->set("neili", (int)me->query("max_neili"));
        
        message_vision(HIG 
"$N����һ���Ż���¶�裬һ������֮��ֱ͸���ֻ���þ���������Ѫ��ӯ����������ԴԴ��������ƣ��һɨ����! \n" NOR, me);

        me->apply_condition("cool_drug", 30);
        destruct(this_object());
        return 1;
}

void init()
{
        add_action("do_pour", "drop");
}

int effect_in_liquid(object ob)
{
        tell_object(this_player(),
                GRN"��ֻ������������ԴԴ�������������ơ�\n"NOR);
        
        addn("neili", (random(1000)+1000)/query("max_liquid", ob), this_player());
        
        if( query("neili", this_player())>query("max_neili", this_player())*3/2 )
            set("neili",query("max_neili",  this_player())*3/2, this_player());

    return 0;
}