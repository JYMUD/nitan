inherit ROOM;

void create()
{
        set("short", "��·");
        set("long", @LONG
������һ����������Ļ���·�ϣ�����������ɭɭ�����֡�����
��Զ���Ǻ����س��ˡ�
LONG );
        set("outdoors", "hengyang");

        set("exits", ([
                "northeast": __DIR__"hsroad2",
                "west"     : __DIR__"hengyang2",
        ]));

	set("coor/x", -6870);
	set("coor/y", -5700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}