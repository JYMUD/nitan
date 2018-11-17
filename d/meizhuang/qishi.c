inherit ROOM;

void create()
{
        set("short", "棋室");
        set("long", @LONG
這裡便是二莊主黑白子的棋室了，棋室里兩張石凳，一張石几，
石几上用黑白子的指力刻着縱橫九九八十一道，這裡除了簡單的放着
兩盒用玉做成的棋子外，什麼都沒有，顯是怕雙方對弈時分心。只不
過現在二莊主不知道到那裡去了，只剩下一副棋盤棋子在這裡。
LONG );
        set("exits", ([
                "east" : __DIR__"zoulang2",
        ]));

        set("objects", ([
                __DIR__"obj/qizi" : 1,
                __DIR__"obj/qipan" : 1,
        ]));

        setup();
        replace_program(ROOM);
}