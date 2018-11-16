inherit ROOM;

void create()
{
        set("short", "民居");
        set("long", @LONG
这是一户普通的农家，屋里没有什么象样的摆设。墙边摆放着一
些农具，除此只外四壁皆空，看来并不富裕。 
LONG);

        set("exits", ([
                "south" : __DIR__"cun4",
                "west" : __DIR__"minju8",
        ]));
        set("objects", ([
                __DIR__"npc/cuilan": 1,
        ]));

        setup();
        replace_program(ROOM);
}