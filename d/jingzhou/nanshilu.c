inherit ROOM;
void create()
{
        set("short", "��ʯ·" );
        set("long", @LONG
����һ������ʯ�̳ɵ�·����Ȼ��Щ������ȴ�ܿ�����������ȥ
���ǳ����ˡ�
LONG );
        set("exits", ([
                  "north" :__DIR__"jznanmen",
                  "south" :__DIR__"nanshilu1",
                "west" : __DIR__"qingshilu1",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -7100);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}