#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "����������" NOR, ({"baoming dan", "baoming", "dan"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", HIR "һ�ź�ɫ��ҩ�衣�ָ�ȫ����Ѫ�������Ѫ��\n" NOR);
                set("value", 100000);
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

        message_vision(HIR "$N" HIR "����һ��������������ֻ����̩֮����\n" NOR, me);

        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}