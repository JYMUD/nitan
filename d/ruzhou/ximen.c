inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���������ݵ������š���������˲��١������м����ٱ����ڼ��
�����İ��ա��Ա߻�վ�ż������٣�ҫ��������վ�������ͣ��ָ��
���š�
LONG
        );

        set("exits", ([
                "east" : __DIR__"xidajie",
                "west" : "/d/songshan/taishique",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6780);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
