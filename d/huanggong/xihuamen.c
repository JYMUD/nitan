// Room: /d/huanggong/xihuamen.c

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�������ǻʵۺͺ�����ȥ����Է�󼰻ع�ʱ����ʹ�֮��. ������
������ʯ, ����: ��Ա�˵���������. ����ٹٵ���˵�, �Ĺٱ���
�½�, ��ٱ�������, ����Υ��.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 4 */
                "west"  : __DIR__"humen",
                "east"  : __DIR__"wuying",
                "north" : __DIR__"dao8",
                "south" : __DIR__"dao9",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2840);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}