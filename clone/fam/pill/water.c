#include <ansi.h>
inherit ITEM;

inherit F_LIQUID;

void create()
{
        set_name(NOR + YEL "ţƤˮ��" NOR, ({ "shui dai", "shui", "dai" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "����һ֧�ش�ŵ�ţƤˮ��������"
                            "�൱��������������������ԽɳĮ��\n" NOR);
                set("unit", "֧");
                set("value", 5000);
                set("max_liquid", 30000);
                set("can_drink", 1);
                set("only_do_effect", 1);
        }
        set("liquid", ([
                "type"         : "water",
                "name"         : "��ˮ",
                "remaining"    : 30000,
                "drunk_supply" : 3000,
        ]));
}

int do_effect(object me)
{
        int remain;

        if ((remain = query("liquid/remaining")) < 1)
        {
                write(name() + "���" + query("liquid/name") + "�Ѿ����ȵ�һ��Ҳ��ʣ�ˡ�\n"); 
        if( query("env/auto_drinkout", me) && environment(this_object()) != environment(me) )
           {
                message_vision("$N����һ��$n��\n", me, this_object());  
                this_object()->move(environment(me));  
           }
                return 1;
        }
        
        if( query("water", me) >= me->max_water_capacity() )
        {
                write("���Ѿ���̫���ˣ���Ҳ�಻��һ��ˮ�ˡ�\n"); 
                return 1;
        }

        message_vision("$N����" + name() + "������غ��˼����" + query("liquid/name") + "��\n" NOR, me);
        
        if (remain < 3000)
        {
                addn("water", remain, me);
                set("liquid/remaining", 0);
        } else
        {
                addn("water", 3000, me);
                addn("liquid/remaining", -3000);
        }

        if (query("liquid/remaining") < 1 &&
            query("env/auto_drinkout", me) && 
            environment(this_object()) != environment(me)) 
        {
                message_vision("$N����һ��$n��\n", me, this_object()); 
                this_object()->move(environment(me)); 
        }
        
        return 1;
}
