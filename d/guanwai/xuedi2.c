// /guanwai/xuedi2.c

inherit ROOM;

#include "gwxuedi.h"

void create()
{
        set("short", "ѩ��");
        set("long", @LONG
������һƬ��ãã��ѩ�أ�һ���������߼ʡ�����һ����ӰҲû�У���
��Ļ�ѩ������������֨�����������������һ���¶��Ľ�ӡ������ı���
��Х��������������ʹ��������̫����������ߣ��Ե���ô�԰ס�
LONG );
        set("exits", ([
                "east"       : __DIR__"xuedi3",
                "southwest"  : __DIR__"xuedi1",
        ]));
        set("outdoors", "guanwai");
        set("coor/x", 4020);
	set("coor/y", 9250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}