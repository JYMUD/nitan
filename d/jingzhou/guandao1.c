inherit ROOM;

void create()
{
        set("short", "�ٵ�" );
        set("long", @LONG
������һ����ٵ��ϣ����Բ�ʱ���˴�������߹�������ͨ��
�ݣ�����������ǵ����š�
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : "/d/wuchang/ximen",
                  "west" : __DIR__"guandao2",
        ]));

        set("no_clean_up", 0);

        set("coor/x", -7040);
	set("coor/y", -2050);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}