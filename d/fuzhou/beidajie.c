// Room: /d/fuzhou/beidajie.c
// may. 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
�ֵ����࣬��ľ���졣����ʢ�Ŀ��ȣ���ֲ����������ˬ��������
�ųǡ���������һ����·�ڣ����Ͼ�����ɽ��
LONG );
        set("exits", ([
                "south"   : __DIR__"dongjiekou",
                "northup" : __DIR__"pingshan",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -80);
	set("coor/y", -6170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}