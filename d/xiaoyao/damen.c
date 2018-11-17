// damen.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
        set("short", "石室大門");
        set("long", @LONG
穿多岩洞，突然之間，手碰到一個冷冰冰的圓物，原來是個門環，
門環的後面象是一扇銅鐵鑄成的大門，十分沉重。即使是臂力很好的人，
推它也覺得甚為吃力。
LONG );
        set("exits", ([
                "north" : __DIR__"shidong",
                "south" : __DIR__"yandong",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50020);
        set("coor/y", -21050);
        set("coor/z", -40);
        setup();
        replace_program(ROOM);
}