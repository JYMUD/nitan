// Code of ShenZhou
//yangrong-wan.c �˲�������
//kane 1998.6
#include <ansi.h>
inherit PILL;

void setup()
{}

int cure_ob(string);
void create()
{
        set_name(HIW"�˲�������"NOR, ({"yangrong wan","wan"}));
        set_weight(50);
        if (clonep())
            set_default_object(__FILE__);
    else
    {
                set("unit", "��");
        set("long",
"һ�Ž�׹����ҩ�裬���˲εȴ�ҩ�����ƶ��ɣ������������飬\n��Ԫ�̱���������֮�˸��е���֮Ч��\n");
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
           
        message_vision(HIW"$N����һ��"+query("name")+HIW"��ֻ��ȫ��ů���ڵģ�˵���������ã�����\n��Ȼ������\n"NOR, me);
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
            set("jingli",query("max_jingli",  me), me);
            set("eff_qi",query("max_qi",  me), me);
            set("qi",query("max_qi",  me), me);
        me->apply_condition("hot_drug",10);
        destruct(this_object());
        return 1;                
}

