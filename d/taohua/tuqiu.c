// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "С����");
        set("long", @LONG
�ߵ�������Ʋ��Լ����������֮����Ȼû��ʲô�ߴ���ľ������
�����𣬼�����һЩ�滨��ݣ�ɢ�������������ķε����㣬���˾���Ϊ
֮һ�񡣾Ӹ����³�������ȥ�ƺ���һƬСС���֡�
LONG );
         set("exits", ([
                "south" : __DIR__"xiaojing",
                "north" : __DIR__"zhulin",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}