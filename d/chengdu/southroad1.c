// Room: southroad1.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "�ϴ��");
        set("long", @LONG
�������ϴ���ϣ����ż�ʵ����ʯ����档�����Ե����ֶ��ˡ�
���������Ƕ���֣�����һֱ�߶����ϴ�֡����Ϸ������������֣�
�����и��͵꣬���������� �����䡣
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
            "northeast"  : __DIR__"eastroad3",
            "southeast"  : __DIR__"kedian",
            "west"       : __DIR__"southroad2",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -15210);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}