#include <room.h>

inherit ROOM;
void create()
{
        set("short", "��������");
        set("long", @LONG
���������ţ��������Ϸ����ż����������֡���ǽ�����ż��Źٸ�
��ʾ��һ��·����ͨ�������ڤ�塣
LONG );
        set("exits", ([
                "west"      : "/d/xuanminggu/xiaolu1",
                "southeast" : __DIR__"xidajie",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6295);
        set("coor/y", 2935);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

