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
                "west"  : __DIR__"zhulin2",
                "north" : __DIR__"tingyu",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -2970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}