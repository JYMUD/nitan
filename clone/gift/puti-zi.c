// puti-zi.c ������

#include <ansi.h>
#include "gift.h"

void create()
{
        set_name(HIG "������" NOR, ({"puti zi", "zi"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "����һ�ž�Ө����������ӣ�������ɽ������"
                            "ǰ����ϡ�ޱȣ�\n������������֮ʵ�����ܻ��ٽ�"
                            "����ǧ�֣������ͬ�١�\n");
                set("base_value", 50000);
                set("base_weight", 100);
                set("base_unit", "��");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int neili_limit;

        neili_limit = me->query_current_neili_limit();
        if ((int)me->query_condition("putizi_drug") > 0)
        {
                write("�����������Ϣδ���������������ܸе������嵴����"
                      "��óȻ��ʳ��\n");
                return 1;
        } else
        if( query("max_neili", me)<neili_limit )
        {
                addn("max_neili", 100+random(30), me);
                if( query("max_neili", me)>neili_limit )
                        set("max_neili", neili_limit, me);
                set("neili",query("max_neili",  me), me);

                message_vision(HIY "$N" HIY "����һ�������ӣ���Ȼ��ֻ��һ�ɺ�"
                               "���ޱȵ�����ֱ�嶥�ţ���æ�˹����ɡ�\n" NOR,
                               me);
                // me->apply_condition("putizi_drug", 50);
        } else
        {
                message_vision(HIY "$N" HIY "һ������������һ�������ӡ�\n" NOR,
                               me);
                tell_object(me, "�����ûɶ�о������绨���óԡ�\n");
        }

        // me->start_busy(random(5) + 5);
        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());
                
        return 1;
}

