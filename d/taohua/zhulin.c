// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����ȫ������ɫ���񹹳ɣ�����������֦��ɵ���ͤ��ͤ�Ϻ��д��
������ͤ�����֡�ͤ��������ȫ�Ƕ���֮��õ����ˣ��ֳ������ƹ⡣
��֮ͤ�ಢ���������ô�����֦����̣�ֻ������������Ĺ����������
�������ޱȡ�
LONG );
         set("exits", ([
                "south" : __DIR__"tuqiu",
                "north" : __DIR__"zhulin2",
        ]));

        set("objects", ([
                 __DIR__"npc/yapu" : 2,
        ]));

        set("cost", 2);
        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2980);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}