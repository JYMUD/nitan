// zhuguo.c
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "���" NOR, ({"zhu guo", "guo"}));
        set_weight(20);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "����һ�������ͨ���ʺ죬һ����֪�ǲ�"
                            "�ɶ�õ���Ʒ��\n");
                set("value", 10000);
                set("no_sell", "���С�춹Ҳ����������\n");
                set("only_do_effect", 1);
        }

        setup();
}

int do_effect(object me)
{
        set("qi",query("eff_qi",  me), me);
        set("neili",query("max_neili",  me), me);
        message_vision(HIR "$N" HIR "����һ�������ֻ������ȫ����һ��"
                       "ů���ӵ���ֱ��������\n"NOR,me);

        destruct(this_object());
        return 1;
}
