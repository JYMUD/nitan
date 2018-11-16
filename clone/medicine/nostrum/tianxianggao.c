// tianxianggao.c ���������

inherit ITEM;
#include <ansi.h>

void init()
{
        add_action("do_fu", "fu");
}

void create()
{
        set_name(HIY"���������"NOR, ({"tianxiang duanxugao", "gao"}));
        set("unit", "��");
        set("vegetable", 25);
        set("nostrum", 13);
        set("level", 50);
        set("long", "����һ����������࣬�Ǻ�ɽ�ɵ�����ʥҩ������֮����ʱ��(fu)ҩ����������֮����\n");
        set("pour_type", "1");
        setup();
}

int do_fu(string arg)
{
        object me=this_player();

        if(!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if(!present(this_object(), me))
                return notify_fail("��Ҫ��ʲô��\n");
        if( me->is_busy() )
                return notify_fail("�𼱣�������С�ı�����ˡ�\n");

        if( query("eff_jing", me) >= query("max_jing", me) && 
                query("eff_qi", me) >= query("max_qi", me) && 
                query("neili", me) >= query("max_neili", me) )
        {
                message_vision("$Nû��Ҫ����������ࡣ\n",me);
        }
        else
        {
                set("eff_jing",query("max_jing",  me), me);
                set("jing",query("eff_jing",  me), me);
                set("eff_qi",query("max_qi",  me), me);
                set("qi",query("eff_qi",  me), me);
                addn("neili",query("max_neili",  me), me);
                message_vision("$N�ó�һ����������࣬���������Ⱥ󣬡�ž����һ�������ڴ����ϡ�\n",me);
                destruct(this_object());
        }
        return 1;
}