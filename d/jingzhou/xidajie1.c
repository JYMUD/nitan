inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
����һ����������ʯ��ֵ���������ͷ���졣��������ϡ�٣�
�����ĵغ������塣������һ�����ֵĹ㳡���ϱ��Ǿ��ݸ��á�����
��һ��������Ժ���Ǿ����������ˡ�
LONG );
        set("outdoors", "jingzhou");

        set("exits", ([
                "east" : __DIR__"guangchang",
                "south" : __DIR__"jzyamen",
                "west" : __DIR__"xidajie2",
                "north" : __DIR__"wan_damen",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
        ]));
        set("coor/x", -7110);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}