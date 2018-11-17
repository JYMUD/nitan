// Room: /d/shaolin/zoulang1.c
// Date: YZC 96/01/19

inherit ROOM;

string look_writing();

void create()
{
        set("short", "走廊");
        set("long", @LONG
這裡是禪房走廊。房頂一側支在南面的高牆上，另一側則與北邊
般若堂的屋頂相連。彩梁畫棟，連頂棚也用彩漆繪滿了各種飛天的圖
形，每幅畫似乎都在訴說一個娓娓動人的佛經故事。南邊牆上題着一
個字(writing)。往北通往般若堂。
LONG );
        set("exits", ([
                "east" : __DIR__"zoulang2",
                "north" : __DIR__"banruo1",
        ]));
        set("item_desc",([
                "writing"                :        (: look_writing :),
        ]));
        set("no_clean_up", 0);
        setup();
}

string look_writing()
{
        return
        "\n"
        "    塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵塵塵塵塵塵塵　　塵塵塵塵塵塵塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵塵塵　塵塵塵　　塵塵塵　塵塵塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵塵塵　塵塵塵　　塵塵塵　塵塵塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵塵　　塵塵塵　　塵塵塵　　塵塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵　　塵塵塵塵　　塵塵塵塵　　塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵　　塵塵塵塵　　塵塵塵塵　　塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵　　塵塵塵塵　　塵塵塵塵　　塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵塵　塵塵塵塵　　塵塵塵塵塵　塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵塵塵塵塵塵塵　　塵塵塵塵塵塵塵塵塵塵塵塵\n"
        "    塵塵塵塵　　　　　　　　　　　　　　　　　　塵塵塵塵\n"
        "    塵塵塵塵塵塵塵塵塵塵塵塵　　塵塵塵塵塵塵塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵塵塵塵塵塵塵　　塵塵塵塵塵塵塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵塵塵塵塵塵塵　　塵塵塵塵塵塵塵塵塵塵塵塵\n"
        "    塵塵塵塵塵塵塵塵塵塵塵塵　　塵塵塵塵塵塵塵塵塵塵塵塵\n"
        "    塵塵　　　　　　　　　　　　　　　　　　　　　　塵塵\n"
        "    塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵塵\n";
}
