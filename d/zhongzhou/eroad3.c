inherit ROOM;

void create()
{
        set("short", "�ٵ�");
        set("long", @LONG
�˴�������Զ�ǿ��⣬�����ɵ����ݣ���������˳������·���档
LONG);
        set("exits", ([
                "east": "/d/kaifeng/ximen",
                "west" : __DIR__"eroad2",
        ]));
        set("outdoors", "zhongzhou");

        set("coor/x", -8970);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}