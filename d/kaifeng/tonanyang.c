// /kaifeng/tonanyang.c
// Last modified by winder 2003.10.20

inherit ROOM;

void create()
{
        set("short", "�ٵ�");
        set("long", @LONG
���������ӿ��⸮���������Ĺٵ�����������·�ΰ��Ϻ�
����Ҳ���١�����ͨ�򿪷⣬����ͨ��������
LONG
        );
        set("exits", ([
                "west" : __DIR__"tokaifeng",
                "east" : "/d/nanyang/yidao3",
        ]));
        set("outdoors", "kaifeng");
        set("no_clean_up", 0);

	set("coor/x", -4990);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}