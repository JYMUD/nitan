inherit ROOM;

void create()
{
        set("short", "�ٵ�");
        set("long", @LONG
���������ӿ��⸮�����ݸ��Ĺٵ�����������·�ΰ��Ϻ�
����Ҳ���١�����ͨ�򿪷⣬���������ݸ���
LONG);
        set("exits", ([
                "west" : __DIR__"dongmeng",
                "east" : __DIR__"eroad2",
        ]));
        set("outdoors", "zhongzhou");
        set("no_clean_up", 0);

        set("coor/x", -8990);
	set("coor/y", -1010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}