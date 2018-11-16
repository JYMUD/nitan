// shulin1.c
#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
       set("short","ɽ��");
       set("long", @LONG
���߽�ɽ�ȣ�������ľï�ܣ������ɾ���ֻ����ɽ֮������һ��СϪ����
�峺��Ϫˮ����ű߾������ʹ����ڿʵ������ÿ�����(drink)������
LONG);
        set("resource/water", 1);
        set("exits", ([
                "southeast" : __DIR__"shulin",
                "north" : "/d/gaochang/road",
        ]));
        set("outdoors", "hasake");
        set("no_quest",1);
        setup();
}


int do_drink(string arg)
{
        int current_water;
        int max_water;
        object me;
        me = this_player();
        current_water=query("water", me);
        max_water=query("str", me)*10+100;
        if (current_water<max_water) {
            set("water", current_water+30, me);
            message("vision", me->name()+"����������ˮ���˼��ڡ�\n", environment(me), ({me}));
            write("��ֻ��Ϫˮ΢����ζ�����������ɿڡ�\n");
            }
        else write("��Ȳ����ˡ�\n");
        return 1;
}
void init()
{
/*        object ob = this_player();        
        if( interactive(ob) && query_temp("li_meet", ob) == 2){
             addn_temp("li_meet", 1, ob);
             new(__DIR__"obj/shoujuan2")->move(ob);
             write("
�㷢����֦����һ�����������µİ��־ԭ�������ε������������������
�����ҿ��˿�����������������뿪�ˣ��������������Ī�Ǿ��ǡ�������\n");
        }        
*/        add_action("do_drink", "drink");
}