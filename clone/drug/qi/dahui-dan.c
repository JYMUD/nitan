#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "��ص�" NOR, ({"dahui dan", "dahui", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "һ�ź�ɫ��ҩ�衣�ָ�600����Ѫ�������Ѫ��\n" NOR);
                set("value", 10000);
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

        message_vision(HIR "$N" HIR "����һ�Ŵ�ص���ֻ����̩֮����\n" NOR, me);

        if( query("max_qi", me)-query("eff_qi", me) <= 600 )
        {
                 set("eff_qi",query("max_qi",  me), me);
                 if( query("max_qi", me)-query("qi", me) <= 600 )
                        set("qi",query("max_qi",  me), me);
                 
                 else 
                        addn("qi", 600, me);
        }


        else 
        {
                addn("eff_qi", 600, me);
                addn("qi", 600, me);
        }

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}