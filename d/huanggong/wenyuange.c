// Room: /d/huanggong/wenyuange.c

inherit ROOM;

void create()
{
        set("short", "��Ԩ��");
        set("long", @LONG
����������ͼ���. �ղ��ˣ����ִ�䣾, ���Ŀ�ȫ�飾, ���Ž�
ͼ�鼯�ɣ�, ����Ӣ��������飾 �Ⱥ���.
LONG
        );
        set("exits", ([
                "north"      : __DIR__"wenhua",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2790);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}