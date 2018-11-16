// Room: /d/gumu/chucangshi.c
// Last Modifyed by Winder on Jan. 14 2002

#include <room.h>
inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", HIC"������"NOR);
        set("long", @LONG
��Ĺ����������࣬�����Ҷ���Щ�ճ���Ʒ������������ѷ���ǽ
�ǣ����������й�Ĺ����ǰ����ɨ������������
LONG        );

        set("exits", ([
                "east" : __DIR__"mudao22",
        ]));
        set("fire_count", 2);
        set("no_clean_up", 0);
        set("coor/x", -3240);
        set("coor/y", -20);
        set("coor/z", 90);
        setup();
}

void init()
{
        add_action("do_search", ({"search", "zhao"}));
}

int do_search(string arg)
{
        object ob, me = this_player();

        if ( arg == "qiangjiao" || arg == "ǽ��")
        {
                if( query_temp("fire", me)<3 )
                {
                        if(objectp(ob = present("fire", me)))
                                return notify_fail("���Ѿ����˻����ˣ���ô��ô̰�ģ�\n");
                        addn_temp("fire", 1, me);
                        message_vision(YEL "$N��ǽ�ŵ���Ʒ���﷭����ȥʲôҲû���š�\n"NOR, me);
                        return 1;
                }
                message_vision("$N��ǽ�ŵ���Ʒ���﷭����ȥ�ҳ�һ�ѻ��ۡ�\n",me);
                delete_temp("fire", me);
                new("/clone/misc/fire")->move(me);
                return 1;
        }
        return notify_fail("��Ҫ��ʲô��\n");         
}