// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// heiyu.c

#include <ansi.h>
inherit ITEM;

void init()
{
        add_action("do_eat", "fu");
}

void create()
{
        set_name(HIW "���������" NOR, ({"heiyu duanxugao", "gao", "heiyu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "��");
                set("heiyu", 3);
                set("long", "һ������ʥҩ��������࣬�������ʵ��ѩ�ס�\n");
                set("value", 100000);
        }
        setup();
}

int do_eat(string arg)
{
        object me, ob;
      
        me = this_player();
        ob = this_object();

        if (! id(arg))
                return notify_fail("��Ҫ��ʲô��\n");
                
        if (this_player()->is_busy() || this_player()->is_fighting())
                return notify_fail("����æ���ء�\n");
                
        if( query("eff_qi", this_player()) == 
            this_player(query("max_qi", )) )
                return notify_fail("�����ڲ���Ҫ�ú�������ࡣ\n");

        if( query("heiyu", ob)>0 )
        {      
                me->receive_curing("qi",query("max_qi", me));
                me->receive_curing("jing",query("max_jing", me)/2);
                addn("neili",query("max_neili",  me)/10, me);
                set("food", me->max_food_capacity(), me);
                set("water", me->max_water_capacity(), me);
                message_vision(HIW"$N�Ѻ��������Ϳ���˿��ϣ�ֻ�����ƴ�Ϊ��ת��\n"NOR, me);
                addn("heiyu", -1, ob);
                this_player()->start_busy(3);      
                return 1;
        }
        
        if( query("heiyu", ob)<1 )
        {
                write("���еĺ���������Ѿ���ʣ�޼��ˡ�\n");
                set("long", "һ������ʢ����ʥҩ����������ľ�С�\n", ob);
                set("value", 5000, ob);
                return 1;
        }
}
