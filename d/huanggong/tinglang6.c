// Room: /d/huanggong/tinglang6.c

inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���ܵ���������. ������ϲ�˵Ļ���, վ�����, ��Լ���õ���
��������Ů����Ц������, �����������������, �Եþ�������, ����
����Ĺ��ͦ�ϵ�.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([ /* sizeof() == 3 */
                "west"  : __DIR__"gong11",
                "east"  : __DIR__"gong12",
                "north" : __DIR__"tinglang5",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -2790);
	set("coor/y", 7761);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}