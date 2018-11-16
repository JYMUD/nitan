//Cracked by Kafei

inherit ITEM;
#include <ansi.h>
void init();
void do_eat();

void create()
{
        set_name(HIM"��������"NOR,({"guihua geng", "soup", "geng"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "һ����Ĺ𻨸������Ƶ�ð������������\n");
                set("unit", "��");
                set("value", 120);
        set("remaining", 3);
        set("drink_supply", 80);
        set("food_supply", 30);
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
    if( query("water", this_player() )
       >= (int)this_player()->max_water_capacity() )
     return notify_fail("���Ѿ���̫���ˣ���Ҳ�಻��һ��ˮ�ˡ�\n");

        set("value", 0);
    addn("water", query("drink_supply"), this_player());
    addn("food", query("food_supply"), this_player());
    jing=query("jing", this_player());
    e_jing=query("eff_jing", this_player());
    m_jing=query("max_jing", this_player());

// No heal effect for ���
/***

    if ( e_jing < m_jing )
        {         
                if ( (e_jing + heal) >= m_jing )
                {
                        set("eff_jing", m_jing, this_player());
                } else
                {        
                        set("eff_jing", e_jing+heal, this_player());
                }        
        } 
***/

        if (jing < e_jing )
        {
        if ( (jing + recover) >= e_jing )
        {
            set("jing", e_jing, this_player());
        } else
        {   
            set("jing", jing+recover, this_player());
        }   
        }

    if( this_player()->is_fighting() ) this_player()->start_busy(2);

    addn("remaining", -1);
        if ( query("remaining") )
        {
                    message_vision("$N���������������������ζ��Ʒ�˼��ڡ�\n"+
                      "һ�ɹ���ֱ����Ƣ��$N���þ���ö��ˡ�\n", this_player());
        } else 
        { 
                    message_vision("$N�����룬��ʣ�µĹ�������һ��������\n"+
                      "һ�ɹ���ֱ����Ƣ��$N���þ���ö��ˡ�\n", this_player());
                
                destruct(this_object());
        }

        return 1;
}