inherit ROOM;

void create()
{
        set("short", "���䳡");
        set("long", @LONG
���ǹŴ�����䳡��һ��¶��ĳ���������������õ�ɳ����
ľ�ˣ���������С������һλ���ߵ�֪���º�������ػӶ���ȭ�š�
LONG);
        set("exits", ([
                "north" : __DIR__"bingqishi",
                "south" : __DIR__"xiuxishi",
                "west" : __DIR__"road2",
                "east" : __DIR__"houcun-road",
        ]));

        set("objects", ([
                __DIR__"npc/wubo" : 1,
        ]));
        set("xinshoucun", 1);
        set("outdoors", "newbie");

        set("no_fight", 1);
        set("no_fight", 1);
        setup();

        replace_program(ROOM);
}
