// Room : /d/dali/huanggs.c �ƹ����ٲ�

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "�ƹ����ٲ�");
        set("long", @LONG
����Ǵ������������µĻƹ����ٲ��������ݺύ���ٲ���Ⱥ��
��Ѩ�ɴ������͵��䣬ֲ�����أ����ֳ���ηḻ�Ŀ�˹��ɽˮ��
��⡣
LONG );
        set("outdoors", "dali");

        set("exits", ([
                "east" : __DIR__"feilihusouth",
        ]));
	set("coor/x", -19140);
	set("coor/y", -6970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}