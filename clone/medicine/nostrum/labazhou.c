// labazou.c ������

#include <ansi.h>
inherit ITEM;

void setup()
{}

void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name(GRN"������"NOR, ({"laba zhou", "zhou", "laba"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long","����һ�����࣬����������ð��أ����һ�������ݴ���׳彫������һ���ྡ������֮ɫ������ȥ˵�����Ĺ��졣����ҩ���̱ǣ��䶾��֪��\n");
                set("value", 50000);
        }
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        int force_limit, neili_limit;
        object me = this_player();

        force_limit = me->query_skill("force")*10;
        neili_limit=query("max_neili", me);

        if(!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if(!present(this_object(), me))
                return notify_fail("��Ҫ��ʲô��\n");
        if( me->is_busy() )
                return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");

        if ( (int)me->query_condition("labazhou_drug" ) > 0 )
        {
                addn("max_neili", -100, me);
                message_vision(HIR "$N�ֺ���һ��"GRN"������"HIR"��ֻ���øγ���ϣ��������ѣ�ԭ���ȵ�̫��̫�࣬ҩЧ�ʵ��䷴��\n" NOR, me);
        }
                        
        else if ( neili_limit <= force_limit  )
        {
                addn("max_neili", 50, me);
                addn("neili", 50, me);
                message_vision(HIY "$N����һ��"GRN"������"HIY"����Ȼ��ֻ��һ�ɺƵ��ޱȵ�����ֱ�嶥��...\n" NOR, this_player());
                me->apply_condition("labazhou_drug", 500);
        }
        me->start_busy(50);
        destruct(this_object());
        return 1;
}
