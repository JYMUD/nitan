inherit ROOM;

void create()
{
        set("short", "�ٵ�" );
        set("long", @LONG
������һ����ٵ��ϣ����Բ�ʱ���˴�������߹������Էֱ��
�м����ǽ������ˡ�������Լ���Կ������ݣ�������ͨ������ǡ�
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                  "east" : __DIR__"guandao1",
                  "west" : __DIR__"guandao3",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7050);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}