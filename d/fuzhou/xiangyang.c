// Room: /d/fuzhou/xiangyang.c
// Date: May 12 1998 Java

inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�����Ǹ��ݳ��������������һ���ưܵ�լ�ӡ�������һ���ӻ�
�̣�ר��Ů�˼��õĶ��������˲����Խ�ȥ��
LONG );

        set("exits", ([
                "east"  : __DIR__"shiqiao",
                "north" : __DIR__"laozhai",
                "west"  : __DIR__"zahuopu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "fuzhou");
	set("coor/x", -100);
	set("coor/y", -6200);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if( dir == "west" && (query("gender", me) == "����") && !wizardp(me) )
                return notify_fail("�������ү�Ƕ�ȥ�Ǹ����\n");
        return 1;
}