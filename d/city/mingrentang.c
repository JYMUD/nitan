// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
#include <room.h>

inherit BUILD_ROOM;
string look_shu();

void create()
{
        set("short", HIY "������" NOR);
        set("long", @LONG
���������̶�������á������﹩����д�����Ҳ��ħͷ��Ҳ��
���Ǵ�������ħͷ����ҡ���������һλ�������ھ�һʱ������һ��
���������Ķ��ǵĹ��£�ÿһ�����¶�������Զ��Ӱ����һ��������
������ҡ���Ȼ���Ƕ�����������������������ķ��꣬�������
��Ҳ�����ڽ��������ˡ����Ƕ��Ѿ��˳������������ǵ���Ӱħ�ٺ�
��ʱ���Ժ�����һ����˵��
LONG );

        set("no_fight", "1");
        set("no_steal", "1");
        set("no_beg", "1");
        set("no_sleep_room", "1");
        set("no_clean_up", 0);

        set("exits", ([
                "down" : __DIR__"wumiao2",
        ]));
        set("objects", ([
                // __DIR__"npc/mingren/gzf" : 1,
        ]));
	set("coor/x", -10);
	set("coor/y", 20);
	set("coor/z", 20);
	setup();
}