// Room: /d/huanggong/huangjidian.c

inherit ROOM;

void create()
{
        set("short", "�ʼ���");
        set("long", @LONG
�����ǹ��н���������԰��Ǭ¡��԰�����ġ��ʼ���ǰ�������ţ�
��ͨ���ٹ��������׳ơ��ⶫ·����̫�ϻ��������Դ���
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([
                "north"     : __DIR__"ningshougong",
                "south"     : __DIR__"ningshoumen",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2790);
	set("coor/y", 7761);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}