inherit ROOM;

void create()
{
        set("short",  "��ʯ·" );
        set("long", @LONG
һ����ʯ�������ʯ�̳ɣ�ƽ̹������̧ͷһ����ǰ���
���������ɼ���
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "west" : __DIR__"dongmen", 
                "east"  :__DIR__"qingshilu1",
        ]));
	set("coor/x", -16810);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}