inherit ROOM;

void create()
{
        set("short", "���");
        set("long", @LONG
�������ٽ�ɳĮ�ĸ��̲���������̡�������һ���޼ʵĴ�ɳĮ��
���������Կ���һ��С��
LONG );
        set("outdoors", "baituo");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : "/d/xingxiu/shamo4",
                "northwest" : __DIR__"dongjie",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("coor/x", -40000);
        set("coor/y", 20000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}