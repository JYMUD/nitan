// lwchang3.c
// By haiyan

inherit ROOM;

void create()
{
        set("short", "練武場");
        set("long", @LONG
這裡是日月神教的練武場，場上立着幾個木人，教中眾弟子常在
此處修鍊邪功，四周充滿着詭秘色彩。
LONG );
        set("exits", ([
            "south"    : __DIR__"midao02",
        ]));
        set("objects", ([
            "/clone/npc/mu-ren" : 4,
        ]));

        setup();
        replace_program(ROOM);
}
