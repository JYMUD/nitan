#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "������" NOR, ({"xuming wan", "xuming", "wan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "һ�ź�ɫ��ҩ�衣�ָ�2000����Ѫ�������Ѫ��\n" NOR);
                set("value", 50000);
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        if( time()-query_temp("last_eat", me)<2 )
        {
                write("��ճԹ�ҩ��ҩ����û����ȫ���ա�\n");
                return 1;
        }
        set_temp("last_eat", time(), me);

        message_vision(HIR "$N" HIR "����һ�������裬ֻ����̩֮����\n" NOR, me);

        if( query("max_qi", me)-query("eff_qi", me) <= 2000 )
        {
                 set("eff_qi",query("max_qi",  me), me);
                 if( query("max_qi", me)-query("qi", me) <= 2000 )
                        set("qi",query("max_qi",  me), me);
                 
                 else 
                        addn("qi", 2000, me);
        }

        else 
        {
                addn("eff_qi", 2000, me);
                addn("qi", 2000, me);
        }

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}