// xiangcha.c ���
// By Marz 03/29/96

inherit ITEM;

void create()
{
        set_name("���",({"tea", "cha", "xiang cha"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "һ���Ȳ裬���Ƶ�ð������������\n");
                set("unit", "��");
                set("value", 1);
                set("remaining", 2);
                set("drink_supply", 25);
                set("only_do_effect", 1);
                set("can_drink", 1);
        }
        
        setup();
}

int do_effect(object me)
{
        int heal, recover, jing, e_jing, m_jing;
        recover = 5;

        if( query("water", me) >= me->max_water_capacity() )
                return notify_fail("���Ѿ���̫���ˣ���Ҳ�಻��һ��ˮ�ˡ�\n");

        set("value", 0);
        addn("water", query("drink_supply"), me);
        jing=query("jing", this_player());
        e_jing=query("eff_jing", this_player());
        m_jing=query("max_jing", this_player());

        if (me->is_fighting())
                me->start_busy(2);
        addn("remaining", -1);
        if (query("remaining"))
        {
                message_vision("$N������裬������ζ��Ʒ�˼��ڡ�\n"+
                               "һ������ֱ����Ƣ��$N���þ���ö��ˡ�\n", me);
        } else 
        { 
                message_vision("$N�����С������ʣ�µ����һ��������\n" +
                               "һ������ֱ����Ƣ��$N���þ���ö��ˡ�\n", me);
                destruct(this_object());
        }
        return 1;
}
