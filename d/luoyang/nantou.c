inherit ROOM;

void create()
{
        set("short", "�ϳǸ�");
        set("long", @LONG
�����������ڳ���ǽ�š��������壬����û���˻�����������ǰ
���˸ߴ�ĳ�ǽ�����صĳ������Ӳݾ�ʲôҲû���ˡ�
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"suishi4",
                  "northeast" : __DIR__"dongtou",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -6950);
	set("coor/y", 2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}