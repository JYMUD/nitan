// Room: /d/huangshan/zuishi.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        set("short", "��ʯ");
        set("long", @LONG
�������������ߵ���ʯ��ʯ��һ������ϡ�ɼ���������״ǡ�ƾ�
��������ʯ������ʯ���֣������پ������������Ʒ�һ��������������
�ֽ��ڴ˴�������ʯ�������б����Խ�ʯ��
LONG
        );
        set("exits", ([ 
                "west"      : __DIR__"shijian",
                "eastup"    : __DIR__"banshan",
                "northdown" : __DIR__"sandie",
                "southeast" : __DIR__"qingluan",
        ]));
        set("objects", ([
                __DIR__"obj/stone2" : 1,
        ]) );
        set("outdoors", "huangshan");
        set("coor/x", -605);
        set("coor/y", -1080);
        set("coor/z", -30);
        setup();
        replace_program(ROOM);
}