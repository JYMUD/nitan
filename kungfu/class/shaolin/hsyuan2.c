// Room: /d/shaolin/hsyuan2.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "和尚院二部");
        set("long", @LONG
這裡是僧眾們飲食起居的地方。靠牆一溜擺着幾張木床，床
上鋪的是篾席。床頭疊着床薄被，冬天想必很冷，僧侶們全靠扎
實的內功根基禦寒。地上整齊的放着幾個蒲團和木魚。
LONG
        );
        set("sleep_room",1);

        set("exits", ([
                "east" : __DIR__"zhulin2",
                "south" : __DIR__"hsyuan1",
                "north" : __DIR__"hsyuan3",
        ]));

        set("objects",([
                CLASS_D("shaolin") + "/hui-xiu" : 1,
        ]));
        setup();
        replace_program(ROOM);
}


