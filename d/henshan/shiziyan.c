inherit ROOM;

void create()
{
        set("short", "ʨ����");
        set("long", @LONG
ʨ���Ҳ������ι�״����ʯ��ϸ�������ʨ�ӣ���Ծ���𣬸�Ф
���ࡣ��ʨ���ң�ף�ڷ��Ѿ������ˡ�
LONG );
        set("exits", ([ 
               "southwest"  : __DIR__"nantian",
               "northup"    : __DIR__"wangritai",
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6930);
	set("coor/y", -5510);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}