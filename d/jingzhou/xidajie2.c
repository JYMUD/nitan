inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
����һ����������ʯ��ֵ���������ͷ���졣�������ﲻ����
�����ǵ��������Ĺ�ʥ��������һ�����ֵĹ㳡��
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"xidajie1",
                "west" : __DIR__"jzximen",
                "north" : __DIR__"guanmiao",
                "south" : __DIR__"lydao1",
        ]));
        set("objects", ([
                "/d/beijing/npc/hunhun" : 1,
        ]));
        set("coor/x", -7120);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}