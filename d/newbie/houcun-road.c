inherit ROOM;

void create()
{
        set("short", "���С·");
        set("long", @LONG
����һ�����ѵ���ʯ�̾͵�С·����ͨ���ɽ��Ψһ�ĵ�
·��·���Կ�����֪����Ұ����������Ʈ��������һƬ����
����԰��⡣
LONG);
        set("exits", ([
                "west" :  __DIR__"lianwuchang",
                "east" : __DIR__"houcun-shanlu",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("objects", ([
                "/clone/quarry/tu" : 20 + random(20),
        ]));
        setup();

        replace_program(ROOM);
}
