inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���������ݵı����š���������˲��١������м����ٱ����ڼ��
�����İ��ա��Ա߻�վ�ż������٣�ҫ��������վ�������ͣ��ָ��
���š�
LONG
        );

        set("exits", ([
                "south" : __DIR__"beidajie",
                "north" : "/d/beijing/road10",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
