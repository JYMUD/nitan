inherit ROOM;

void create()
{
        set("short", "����ͤ");
        set("long", @LONG
����Ϊ�����������ʯ���������ɣ�ʯ���������������ǧ���
��ʯ���ϣ�������ϸ�壬��Ϊ������
LONG );
        set("exits", ([ 
               "south"  : __DIR__"zhengchuan",
               "north"  : __DIR__"jiayingmen",
        ]));

        set("no_clean_up", 0);

	set("coor/x", -6890);
	set("coor/y", -5660);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}