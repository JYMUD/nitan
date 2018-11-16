// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
#include <ansi.h>

inherit ROOM;

int do_pigua();

void create()
{
        set("short", "������");
        set("long", @LONG
�˶����ϱ�������֮������С���������겻�����⡣����ֵ��Ƕ���
ʮ�ָ��Ҳû��ʲô����������(wall)����һЩģģ���������Σ�����
����֮״�������һ�����һЩ������ѧͼ�⡣
LONG );
        set("item_desc", ([
                "wall" : " ������ʮ�������Σ����ݸ߷��ͣ����ƴ�����ÿһ�������Ų�ָͬ������Ϊ�鶯��\n"
                         "�ƺ����һ�����һ��������ѧ���������ʽ��\n",
        ]));
         set("exits", ([
                "out" : __DIR__"tzfeng",
        ]));

        set("coor/x", 9030);
        set("coor/y", -2970);
        set("coor/z", 20);
        setup();
//        replace_program(ROOM);
}

void init()
{
        add_action("do_tanzhi", "tanzhi");
        add_action("do_use", "use");
}

int do_use(string arg)
{
        object me = this_player();

        if (! arg || arg == "") 
                return 0;
        if (! present("fire", me))  
                return 0;
        if (arg == "fire") 
        {
                tell_object(me, "���Ż��ӳ�գ����������ȥ��\n");
                     me->move(__DIR__"neidong");
        }
        return 1;
}

int do_tanzhi()                
{
        object me, ob, *inv; 
        int check, i;

        me = this_player();

        ob = present("tie bagua", me);
        if( (ob) && (query("tanzhi", ob)<1) )
        {
                message_vision(CYN "����ָ���������ϵ�����ȥ��\n" NOR, me);
                message_vision(HIW "�����ԡ����ꡱһ�������ˣ�\n" NOR, me);
                if (ob->query_amount() > 1) 
                {
                        ob->add_amount(-1);
                        set("tanzhi", 200, ob);
                } else    
                        destruct(ob);
                return 1;
        }

        if ((int)me->query_skill("finger", 1) >= 30
        &&  (int)me->query_skill("finger", 1) <= 100 
        &&  present("bagua", me))
        {
                check = (int)me->query_skill("finger", 1) *
                        (int)me->query_skill("finger", 1) *
                        (int)me->query_skill("finger", 1);
                        
                if( check<query("combat_exp", me)*10 && query("jing", me)>50 )
                {
                             me->receive_damage("jing", random(40));
                              me->improve_skill("finger",query("int", me)*2);
                              tell_object(me, CYN "����ָ���������ϵ�����ȥ��\n" NOR);
                        tell_object(me, "�������˻���ָ������ļ������ѡ�\n");
                             addn("tanzhi", -1, ob);
                } else 
                if( check<query("combat_exp", me)*10 && query("jing", me)<30 )
                {
                              tell_object(me, "�㾫���޷����С�\n");
                } else 
                {
                        tell_object(me, "��ʵս���鲻�㣬�޷��������ָ����\n");
                }        
        } else 
        if ((int)me->query_skill("finger", 1) > 120) 
        {
                tell_object(me, HIC "ֻ�������һ���������Է���һ������\n" NOR);
        } else 
        {
                tell_object(me, "ʲô��\n");
        } 
         
        return 1;
}    
