// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
����ԼĪ���ɼ�����һ���ʯ�ݣ�ǽ�ڶ���һ���ֲڵĴ�ʯ������
����Ҳ�Ǵ�ʯ���̳ɣ�ǽ���������һֻ��Ͱ�������ŵ��ľ��ǳ�����
ù�����η���ȴ������������ૣ������ﴦ��ȥ��ֻ��һ�����ӽ��ɽ�
Զ������ʮ�����¥�ϵĴ����ӹ�����ɴ�������ع��ţ�������ȴ����
����һ���ʻ�������������õ�壬�����Ƕ��㡢���ɡ�������ǽ�ϵ�
С����ȥ�����Լ������ָ���һ�ǡ�
LONG );

        set("exits", ([
                "west" : __DIR__"ymzhengting",
        ]));
        set("objects", ([
                __DIR__"npc/dingdian" : 1,
        ]));

        create_door("west", "����", "east", DOOR_CLOSED);
        set("cost", 0);
        set("coor/x", -7100);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
}