inherit ROOM;

void create()
{
        set("short", "���ɽ·");
        set("long", @LONG
����һ�����ѵ�����С·����ͨ���ɽ��Ψһ�ĵ�·��·
���Կ�����֪����Ұ����������Ʈ��������һƬ��������԰
��⡣������ɽ��Խ��Խ�ߣ�·Ҳ��������������
LONG);
        set("exits", ([
                "west" : __DIR__"houcun-road",
                "east" : __DIR__"luanshigang",
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("objects", ([
                "/clone/quarry/tu" : 20+random(20),
        ]));
        setup();

        replace_program(ROOM);
}