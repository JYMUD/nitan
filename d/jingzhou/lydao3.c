inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
����һ���������������������������ֹ�������ɫ��ʯ�ӣ���
������ͷ���졣������һ�����������ֱͨ�ϴ�֡����ߺ�����һ��
��Ȫ��
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                "east" : __DIR__"lydao4",
                "westdown" : __DIR__"wenquan",
        ]));
        set("coor/x", -7120);
	set("coor/y", -2070);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}