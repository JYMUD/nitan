//Edited by fandog, 02/18/2000

inherit ROOM;
void create()
{
        set("short", "����·");
        set("long", @LONG
����һ������·����ʱ�ɼ��������˱��Ű��������ŵ���������ȥ��
���������������ĺۼ���
LONG );
        set("exits", ([
                "south"     : __DIR__"tulu2",
                "north"     : __DIR__"jiangnan",
        ]));
        set("outdoors", "jingzhou");
        set("no_clean_up", 0);
        set("coor/x", -7100);
	set("coor/y", -2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}