inherit ROOM;

void create()
{
        set("short", "����·");
        set("long", @LONG
������·�������������һ����·���ֵ������ɾ�������������·
�汻��ˮ��ù����羵����·������߷��ߴ����ΰ���������Ǿ޸�լԺ��
˫�˺ϱ�������ʮ��һ�꣬������������ߡ������Ǿ�����ų�ȥ֮����
�����������ǿƿ��Գ� ��
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"wenmiao",
                  "north" : __DIR__"nroad4",
                  "west" : __DIR__"kaoshi",
                  "south" : __DIR__"nroad2",
        ]));
        set("objects", ([
                "/d/beijing/npc/shusheng2" : 1,
        ]));
	set("coor/x", -6990);
	set("coor/y", 2210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}