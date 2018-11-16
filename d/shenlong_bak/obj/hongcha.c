// hongcha.c ���
// Last Modified by winder on Jul. 12 2002

inherit ITEM;

void create()
{
        set_name("���",({"tea", "cha", "hong cha"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "һ����裬���Ƶ�ð������������\n");
                set("unit", "��");
                set("value", 300);
                set("remaining", 2);
                set("drink_supply", 25);
        }
        setup();
}

void init()
{
        add_action("do_drink", "drink");
}

int do_drink(string arg)
{

        int heal, recover, jing, e_jing, m_jing;

        recover = 5;
        if( !this_object()->id(arg) ) return 0;
        if( this_player()->is_busy() )
                return notify_fail("����һ��������û����ɡ�\n");
        if( query("water", this_player()) >= 
                (int)this_player()->max_water_capacity() )
                return notify_fail("���Ѿ���̫���ˣ���Ҳ�಻��һ��ˮ�ˡ�\n");

        set("value", 0);
        addn("water", query("drink_supply"), this_player());
        jing=query("jing", this_player());
        e_jing=query("eff_jing", this_player());
        m_jing=query("max_jing", this_player());

        if (jing < e_jing )
        {
                if ( (jing + recover) >= e_jing )
                {
                        set("jing", e_jing, this_player());
                }
                else
                {
                        set("jing", jing+recover, this_player());
                }
        }
        if( this_player()->is_fighting() ) this_player()->start_busy(2);
        addn("remaining", -1);
        if ( query("remaining") )
        {
                 message_vision( "$N���𱭺�裬������ζ��Ʒ�˼��ڡ�\nһ������ֱ����Ƣ��$N���þ���ö��ˡ�\n", this_player());
        }
        else
        {
                 message_vision( "$N�����С������ʣ�µĺ��һ��������\nһ������ֱ����Ƣ��$N���þ���ö��ˡ�\n", this_player());
                destruct(this_object());
        }
        return 1;
}