inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����������������ĵ�������Ժ�����������ڵ��ʥ�����
���¥�
LONG );
        set("exits", ([ 
               "south"  : __DIR__"kuixingge",
               "north"  : __DIR__"yubeiting",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}