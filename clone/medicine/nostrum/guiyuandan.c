// guiyuandan.c
#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW"��Ԫ��"NOR, ({"guiyuan dan", "dan"}));
        if (clonep())
        {
                set_default_object(__FILE__);
        }
        else {
                set("unit", "��");
                set("long", "��Ԫ���Ƕ��ҵ���һ��Ѫ����������ޱȣ�������
���֮����Ϊ����������\n");
                set("value", 0);
        }
        set("pour_type", "1");
        seteuid(query("id", this_player()));
        setup();
}

int init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

int do_eat(string arg)
{
        object me = this_player();

        if( !query("dietime", me) || time()-query("dietime", me)>480 )
                return notify_fail("�����ڲ��˳Թ�Ԫ���ˡ�\n");
        if(!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if (!present(this_object(), this_player()))
                return notify_fail("��Ҫ��ʲô��\n");
        if( me->query_skill("linji-zhuang", 1) < 180 )
                return notify_fail("��δ���޳���ڤׯ�����³Բ��ô˵���\n");
        if( me->is_busy() )
                return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");
        message_vision("$N����һ��" + name() + "��\n", me);
        log_file("eat_dan", sprintf("[%s] %s eat guiyuan \n", ctime(time()), geteuid(me)));
        delete("dietime", me);
        me->reincarnate();
        addn("combat_exp",query("combat_exp",  me)/49, me);
//        me->add("potential", 50);
        addn("max_neili", 2, me);
        me->skillreincarnate();
        me->start_busy(2);
        destruct(this_object());
        return 1;
}
