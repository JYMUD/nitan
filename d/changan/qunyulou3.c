//Room: qunyulou3.c

inherit ROOM;

void create()
{
        set("short", "Ⱥ��¥��¥");
        set("long", @LONG
Ⱥ��¥��¥������һ������ߵ�С¥��������ĳһλ�����ͬ��
������֮���������ѱ�Ⱥ��¥���ؽ����¡�ֻ��һ������ȭ�����
����Ů�˵Ľ�Ц����ʱ�Ĵӷ����д�����
LONG );
        set("exits", ([ /* sizeof() == 5 */
                "north" : "/d/changan/qunyuys5",
                "south" : "/d/changan/qunyuys6",
                "west"  : "/d/changan/qunyuys7",
                "east"  : "/d/changan/qunyuys8",
                "down"  : "/d/changan/qunyulou2",
        ]));

        set("coor/x", -10710);
	set("coor/y", 1950);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}