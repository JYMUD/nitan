inherit ROOM;

void create()
{
        set("short", "��ʯ·");
        set("long", @LONG
����һ������ʯ�̳ɵ�·����Ȼ��Щ������ȴ�ܿ�������ȥ����
�����ˡ�����ǰ��һƬ��ʯ����ס��ȥ·����˵�ǵ��������Ϊ����
ֹ���׷�϶���ġ�
LONG );
        set("objects", ([
                __DIR__"npc/boy" : 1,
                __DIR__"npc/girl" : 1,
        ]));
        set("exits", ([
                "north" : __DIR__"nanshilu",
                "south" : __DIR__"jiangbei",
        ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -7100);
	set("coor/y", -2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}