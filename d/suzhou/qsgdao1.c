// Room: /d/suzhou/qsgdao1.c
// Last Modified by Winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "��ʯ�ٵ�");
        set("long",@long
������һ����ʯ����ϣ����������ǳ���æ����ʱ�������������
�Ҷ��������������һЩС��̯���ƺ���һ�����С�
long);
        set("outdoors", "suzhou");
        set("exits",([
                "south" : __DIR__"qsgdao",
                "north" : __DIR__"qsgdao2",
                "east"  : "/d/item/road1",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1110);
	set("coor/y", -1110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}