// Room: /d/huanggong/dao9.c

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ͻ�����Ǽ�Ĺ���. ƽ����һЩ��������ڹ�, ��������·
��. �⹬����ÿ�ն��д�����������Ѳ��, �����ҪС��. �������߸�
�ߵĺ�ǽ, ����Ϊ���������ָ��ֵ�.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 2 */
                "south" : __DIR__"jiao4",
                "north" : __DIR__"xihuamen",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2840);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}