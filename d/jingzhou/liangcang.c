inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������Ǿ��������ˣ����϶��������������װ���ǰ��ȴ���
֮�����ʳ��
LONG );
        set("exits", ([
                "west" : __DIR__"lcmen",
        ]));

        set("coor/x", -7080);
	set("coor/y", -2070);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}