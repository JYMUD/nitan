inherit ROOM;

void create()
{
        set("short", "�ϳ���");
        set("long", @LONG
���������ݵ��ϳ��š���������ͨ������ȥ�ıؾ�Ҫ����һ����
�󰸷�������ս���������������ڴ��迨�̲飬ƽʱ���ٱ�Ҳ���ù�
�����£�������һƬ̫ƽʢ������
LONG
        );

        set("exits", ([
                "south" : __DIR__"xiaozheng",
                "north" : __DIR__"nandajie",
        ]));

        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 3,
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1840);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
