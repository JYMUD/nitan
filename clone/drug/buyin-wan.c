// Code of ShenZhou
//wzfeng 99 11/29
#include <ansi.h>
inherit ITEM;

void setup()
{}
void init()
{
        add_action("do_eat", "eat");
}
void create()
{
        set_name(HIW"������"NOR, ({"buyin wan","wan"}));
        set_weight(5);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("unit", "��");
                set("long","����һ�������裬�̲�����֮������Ч���������˷�ʳ�����쳣 ��\n");
                set("value", 0);
                set("no_sell", 1);
                set("no_drop","�������������뿪�㡣\n");
                set("value", 2000);
                set("medicine", 1);

        }
        setup();
}
 
int do_eat(string arg)
{

        object me;
        int skill;
        me=this_player();
        skill=me->query_skill("pixie-jian", 1);

        if (!id(arg))
        return notify_fail("��Ҫ��ʲô��\n");
        if(skill<200)
        {
        message_vision(HIR"$N����һ�������裬ֻ���û���һ�������һ������֮��֮���ﴮ��ȫ����ɲ�Ǽ�����ʧ�ף���������!\n"NOR, this_player());
        if( query("max_jingli", me)>50 )
        {
        addn("eff_jingli", -20, me);
        addn("max_jingli", -20, me);
        }
        me->unconcious();
        }
        else
        {
                if( query("drug_list/1", me) == query("drug_list/1" )
                         && query("drug_list/2", me) == query("drug_list/2" )
                         && query("drug_list/3", me) == query("drug_list/3" )
                         && query("drug_list/4", me) == query("drug_list/4" )
                         && query("drug_list/5", me) == query("drug_list/5" )
                        )
                
                
                {

                        if( query("pixie/buyin-wan/lvl", me) >= skill && query("pixie/buyin-wan/lvl", me)>0 )

                        {
                                message_vision(HIG"$N����һ�������裬ֻ���û���һ�������һ������֮��֮���ﴮ��ȫ����ɲ�Ǽ��������������������\n"NOR, this_player());
                                message_vision(HIR"������ǰ��ҩ���ƺ���δ��ʧ����������Ч���ʵ��䷴��$Nɲ�Ǽ�����ʧ�ף���������\n"NOR, this_player());
        if( query("max_jingli", me)>50 )
        {
        addn("eff_jingli", -20, me);
        addn("max_jingli", -20, me);
        }

                        }
                        else
                        {
                        
                                message_vision(HIG"$N����һ�������裬ֻ���û���һ�������һ������֮��֮���ﴮ��ȫ����ɲ�Ǽ��������������������\n"NOR, this_player());
                                addn("eff_jingli", 5+random(2), me);
                                addn("max_jingli", 5+random(2), me);
                                set("pixie/buyin-wan/lvl", skill, me);
                        }
                
                }
                else
                {
                message_vision(HIG"$N����һ�������裬ֻ���û���һ�������һ������֮��֮���ﴮ��ȫ����ɲ�Ǽ��������������������\n"NOR, this_player());
                message_vision(HIR"���ϴ�ҩ�����������岻����ɲ�Ǽ�$N����ʧ�ף���������\n"NOR, this_player());
                addn("max_jingli", -20, me);
                me->unconcious();
        
                }

        }
        
        
        destruct(this_object());
        return 1;
}