// Room: /d/suzhou/lingyansi.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "靈岩寺");
        set("long",@long
爬上山頂，就是靈岩寺。靈岩寺原系吳王館娃宮遺址，為“東南著
名叢林”，佛教凈土宗道場。始建於南朝，原名綉峰寺。唐代改稱靈岩
寺，信奉律宗。
long);
        set("objects",([
                __DIR__"npc/ke" : 2,
        ]));
        set("exits",([
                "northdown" : __DIR__"shiyuan",
                "west"      : __DIR__"zhonglou",
                "east"      : __DIR__"lingyanta",
                "enter"     : __DIR__"dxbdian",
        ]));
        set("outdoors","suzhou");
	set("coor/x", 1120);
	set("coor/y", -1160);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}