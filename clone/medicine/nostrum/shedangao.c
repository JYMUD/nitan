// shedangao.c
inherit ITEM;
void init()
{
        add_action("do_eat", "eat");
        add_action("do_eat", "fu");
}

void create()
{
        set_name("�ߵ���", ({"shedan gao", "gao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "�������Ʒ���ߵ��ࡻ��\n");
                set("value", 100);
        }
        set("pour_type", "1");
        setup();
}

int do_eat(string arg)
{
        object me = this_player();

        if(!id(arg)) return notify_fail("��Ҫ��ʲô��\n");
        if(!present(this_object(), me))
                return notify_fail("��Ҫ��ʲô��\n");
        if( me->is_busy() )
                return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");

        if( (query("max_jing", me) >= 110) || (query("max_qi", me) >= 200) )
                return notify_fail("��ԡ��ߵ��ࡻ����Ч�ã�\n");
        if( query("max_jing", me)<105 )
        {
                addn("max_jing", 2, me);
                addn("eff_jing", 2, me);
                addn("jing", 4, me);
                addn("max_qi", 5, me);
                addn("eff_qi", 5, me);
                addn("qi", 10, me);
        }
        else
        {
                addn("max_jing", 1, me);
                addn("eff_jing", 1, me);
                addn("jing", 2, me);
                addn("max_qi", 3, me);
                addn("eff_qi", 3, me);
                addn("qi", 5, me);
        }
        message_vision("$N����һ���ߵ��࣬�پ�һ�ɺƵ�����ֱӿ����������������...\n" , me);
        destruct(this_object());
        return 1;
}