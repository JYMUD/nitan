inherit ROOM;

void create()
{
        set("short", "С�ﾡͷ");
        set("long", @LONG
����һ�������ֺڵ����ӣ�ɢ����һ������ˮ��ζ����ʳ�﷢ù
��ζ���������ֳ���
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "north" : __DIR__"xxiang",
                "south" : __DIR__"yuanmiaoguan",
        ]));
        set("objects", ([
                "/d/kaifeng/npc/qigai" : 2,
                "/d/beijing/npc/dipi" : 1,
        ]));
        set("coor/x", -7080);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}