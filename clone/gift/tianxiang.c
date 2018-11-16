// tianxiang.c ������¶

#include <ansi.h>

#include "gift.h"

void create()
{
        set_name(HIG "������¶" NOR, ({"magic water", "yvlu", "lu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "Щ");
                set("base_unit", "��");
                set("long", HIG "���Ǹ�������֥�ϵ�һ�ξ�Ө��͸����¶����˵����\n"
                                "��ɽ��ǧ��������֥Ϊĸ�����ϵ���ȡ���վ��»���\n"
                                "�������ޱ�����Ĺ�Ч��\n");
                set("base_value", 100000); 
                set("base_weight", 200);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        string force;
        int neili_limit;

        neili_limit = me->query_current_neili_limit();
        message_vision(HIG "$N" HIG "С������Ľ���¶�������У���ʱ����"
                       "��̨һ�������������\n��ƮƮ���ɣ�һʱ�侹�в���"
                       "�����ĸо���\n" NOR,
                       me);

        if( query("max_neili", me)<neili_limit )
        {
                addn("max_neili", 120+random(150), me);
                if( query("max_neili", me)>neili_limit )
                        set("max_neili", neili_limit, me);
                set("neili",query("max_neili",  me), me);

        }

        if( query("gift/tianxiang", me) <= 200 )
        {
        force = me->query_skill_mapped("force");
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 40000);
        if (stringp(force) && me->can_improve_skill(force))
                me->improve_skill(force, 40000);
        }

        addn("gift/tianxiang", 1, me);
        // me->start_busy(random(5) + 5);
        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());
        
        return 1;
}
