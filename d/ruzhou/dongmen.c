inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
���������ݵĶ����š���������ͨ����ɽȥ�ıؾ�Ҫ����һ����
�󰸷�������ս���������������ڴ��迨�̲飬ƽʱ���ٱ�Ҳ���ù�
�����¡�
LONG
        );

        set("exits", ([
                "west" : __DIR__"dongdajie",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6740);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
