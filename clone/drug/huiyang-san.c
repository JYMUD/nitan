// Code of ShenZhou
//huiyang-san.c ��������ɢ
//kane 1998.6
#include <ansi.h>
inherit PILL;

void setup()
{}

int cure_ob(string);
void create()
{
        set_name(HIY"��������ɢ"NOR, ({"huiyang san","san"}));
        set_weight(50);
        if (clonep())
            set_default_object(__FILE__);
    else
    {
                set("unit", "��");
        set("long", 
"����ɳ��õ�������ҩ����ĩ΢ϸ��ɫ�󵭻ƣ�΢�������̱ǵ�ζ��\n
����ˮ���Ч���ȼѡ�\n");
                set("value", 10000);
                set("medicine", 1);
                set("no_sell", 1);
    }
        setup();
}

int cure_ob(object me)
{
        if (me->query_condition("hot_drug") > 0)
        {
                if( query("jingli", me)>500 )
                        addn("jingli", -500, me);
                else
                        addn("jingli", -(query("jingli", me)), me);

                message_vision(BLU"$N����һ��"+query("name")+BLU"�������ؿ����ƣ���֫������ԭ����ʳ̫��\n̫�࣬ҩЧ�ʵ��䷴��\n" NOR, me);
                destruct(this_object());
                return 1;
        }
           
        message_vision(HIY"$N����һ��"+query("name")+HIY"��ֻ��ͨ����̩��������������ƴ��к�ת��\n"NOR, me);
        me->receive_heal("qi", 100+random(200));
        addn("jingli", 100+random(200), me);
        me->apply_condition("hot_drug", 30);

        if ((int)me->query_condition("snake_poison") > 0)         
                    me->apply_condition("snake_poison",0);
          destruct(this_object());
           return 1;
}

void init()
{
        add_action("do_pour", "pour");
}

int effect_in_liquid(object ob)
{

        tell_object(this_player(),HIG"��ֻ��������һ��ů����������Ϊ���á�\n"NOR);
        this_player()->receive_heal("qi",10+random(20));
       return 0;
}

