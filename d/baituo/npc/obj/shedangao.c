//
inherit ITEM;
void init()
{
        add_action("do_eat", "eat");
}

void create()
{
        set_name("�ߵ���", ({"shedan gao", "gao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("long", "�������Ʒ���ߵ��ࡻ��\n");
                set("value", 1000);
        }
        setup();
}

int do_eat(string arg)
{
        object me = this_player();
        if (!id(arg))
                return notify_fail("��Ҫ��ʲô��\n");
        if( (query("max_jing", me) >= 200) || (query("max_qi", me) >= 200) )
                return notify_fail("��ԡ��ߵ��ࡻ����Ч�ã�\n");
        if( query("max_jing", me)<180 )
           {
            addn("max_jing", 10, me);
            addn("jing", 10, me);
            addn("max_qi", 10, me);
            addn("qi", 10, me);
           }
        else
           {
            addn("max_jing", 2, me);
            addn("jing", 2, me);
            addn("max_qi", 2, me);
            addn("qi", 2, me);
            }
        message_vision( "$N����һ���ߵ��࣬�پ�һ�ɺƵ�����ֱӿ������
����������...\n" , me);
        destruct(this_object());
        return 1;
}
