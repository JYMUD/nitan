inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
�����ں�ɽɽ·�ϣ�����ɽ����䣬�������ϪȪ���٣�����
���ƣ��������ش�졣һֱ������ͨ��ĥ��̨�������塣 
LONG );
        set("exits", ([ 
                "southeast"  : __DIR__"banshan",
                "west"       : __DIR__"shanlu001",    
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6920);
	set("coor/y", -5540);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}