//houzhai.c                �������ҡ�����

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��լ");
        set("long",
"���������Ƹ��լ���������򱱾������ŵĴ�������̫̫�����Ҿ���\n"
"����Ҫ��������̫̫�Ʊȵ��컹�ѣ�����������һ��񷿣�������ͨ��\n"
"��Ժ��С·��\n"
);
        set("exits", ([
                        "north" : __DIR__"nzlang2",
                        "south" : __DIR__"dating",
                        "southwest" : __DIR__"chaifang",
        ]));
        create_door("southwest","ľ��","northeast",DOOR_CLOSED);
        set("objects", ([
                __DIR__"npc/tangkan" : 1,
        ]));
        set("area", "tangmen");
        setup();
//        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if( (dir == "north") && (query("family/family_name", me) != "��������") )
                return notify_fail("�㲻���������ˣ���������ǰ���ˣ�\n");

        return ::valid_leave(me, dir);
}