inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������һƬ�Դ�����֣���紵������Ӱҡ�����������������
������
LONG);
        set("exits", ([
                "east" : __DIR__"shulin",
                "south" : __DIR__"luanshigang",
        ]));

        set("objects", ([
                 "/clone/quarry/tu" : 30 + random(20),
        ]));

        set("xinshoucun", 1);
        set("outdoors", "newbie");

        setup();
}

void init()
{
        object me = this_player();

        if( query("newbie_quest/leixing", me) == "move" )
        set("newbie_quest/completed", 1,  me);
                
}