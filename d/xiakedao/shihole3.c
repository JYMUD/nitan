// /d/xiakedao/shihole3.c 俠客島 石洞3

inherit ROOM;

int do_learn(string arg);
void create()
{
        set("short", "石洞");
        set("long", @LONG
迎面可見四個行書大字「水銀瀉地」，極具神韻。洞中陳設奢華，
潔白的大理石磚，漢白玉欄杆。幾個香爐煙霧繚繞，白衣婢女垂手侍
立，依稀是豪門內宅一般。
LONG );
        set("exits", ([
                "out"   : __DIR__"shihole2",
                "enter" : __DIR__"shihole4",
                "north" : __DIR__"shiroom09",
                "south" : __DIR__"shiroom10",
                "east"  : __DIR__"shiroom11",
                "west"  : __DIR__"shiroom12",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3090);
        set("coor/y", -25300);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}