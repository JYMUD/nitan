inherit ROOM;

void create()
{
        set("short", "С��");
        set("long", @LONG
������һ���ּ�С���������������ѡ��������н��ɵ��������
�������߾��Ǵ�����ĵؽ��ˡ�
LONG );
        set("objects", ([
                __DIR__"obj/shikuai": 1,
        ]));

        set("outdoors", "foshan");
        set("exits", ([
	    "southwest" : "/d/dali/road5",
                "east"      : __DIR__"road2",
        ]));
	set("coor/x", -6670);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}