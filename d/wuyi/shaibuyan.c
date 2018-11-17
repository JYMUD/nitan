// Room: /d/wuyi/shaibuyan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "曬布岩");
        set("long", @LONG
曬布岩位於六曲溪畔，天游峰下。岩如刀切斧劈一般，直上直下，
闊大平坦，高近二百丈。每當夕陽西照，岩壁水刷痕迹愈發分明，宛若
仙人曬布。相傳挑擔大腳仙挑着織女的雲錦，貪圖武夷美景，結果雲錦
露濕，便在此曬布。不意到了中午，烈日晒化錦緞，連大仙接雲錦的手
印也留在岩壁上了。所以又名“仙掌峰”。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"jiesunfeng",
                "northeast" : __DIR__"chadong",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1360);
        set("coor/y", -4990);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
