// Room: /d/jiaxing/jiangpan3.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
һ���󽭺�ب����ǰ����ˮ�ƺƣ�����ҹҹ�������ݵر���󺣡�
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","jiaxing");

        set("exits", ([
                "west": __DIR__"jiangpan2",
                "east": __DIR__"haibin",
        ]) );

	set("coor/x", 1290);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}