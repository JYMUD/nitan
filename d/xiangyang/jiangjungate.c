// Room: /d/xiangyang/jiangjungate.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "����������");
        set("long", @LONG
���ǽ������Ĵ��ţ��Ű岻֪����ʲô�����Ƴɣ�����ȥ���һ
Ƭ���ƺ���Ϊ���أ��������������þ�����ͭ�����ڴ��ŵ���������
������һ���ߴ��ľ�Ʒ������顸���������������֣��ּ�����Ʈ�ݣ�
ֻ����Щģ���ˣ�������������µĺۼ���������һ���ϰأ����ò�
��ͦ�Σ�֦Ҷï�ܡ���ǰ�������߸���������������󵶵��α���
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "south" : __DIR__"eastjie1",
                "north" : __DIR__"jiangjunyuan",
        ]));
        set("objects", ([
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7810);
	set("coor/y", -760);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "north" &&
                objectp(present("song bing", environment(me))))
           return notify_fail("�α�����ȵ���ʲô�˵����ô��ر������ţ�\n");

        return ::valid_leave(me, dir);
}