// Room: /d/suzhou/road2.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
        set("short", "��ʯ���");
        set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ�������������
�Ҷ��������������һЩС��̯���ƺ���һ�����С���������Ǻų���
�õ����ݳ��ˡ���Ȼ�ǳ��⣬���Ǿ�ɫ���ˣ�������һ����ס����
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "west"  : __DIR__"road3",
                "east"  : __DIR__"ximen",
        ]));
	set("coor/x", 1070);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
}
