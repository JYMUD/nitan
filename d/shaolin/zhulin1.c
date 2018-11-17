// Room: /d/shaolin/zhulin1.c
// Date: YZC 96/01/19

inherit ROOM;

void create()
{
        set("short", "竹林小道");
        set("long", @LONG
這是一條卵石鋪成的小道，曲曲折折地通向前方。兩邊是密密的
竹林。這裡人跡罕至，惟聞足底叩擊路面，有僧敲木魚聲；微風吹拂
竹葉，又如簌簌禪唱。令人塵心為之一滌，真是絕佳的禪修所在。
LONG );
        set("exits", ([
                "west" : __DIR__"hsyuan1",
                "north" : __DIR__"zhulin2",
                "south" : __DIR__"zoulang8",
        ]));
        set("outdoors", "shaolin");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
