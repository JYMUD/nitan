// Room: /d/yanziwu/dong4.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "潮聲洞");
        set("long", @LONG
洞里伸手不見五指。隱隱聽到湖浪衝擊巨岩，延綿不絕。你在洞里
摸索前行，聽着潮聲引導，試圖找到出洞的方向。
LONG );
        set("exits", ([
                "south"  : __DIR__"dong3",
                "north"  : __DIR__"dong2",
                "east"   : __DIR__"dong4",
                "west"   : __DIR__"dong5",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1210);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}