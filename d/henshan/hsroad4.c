inherit ROOM;

void create()
{
        set("short", "����·");
        set("long", @LONG
������һ����������Ļ���·�ϣ�����������ɭɭ�����֡�����
��Զ���Ǻ����س��ˡ�����������һ�������
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "east"  : __DIR__"hengyang11",
                "west"  : __DIR__"hsroad5",
        ]));

	set("coor/x", -6920);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}