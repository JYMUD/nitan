inherit ROOM;

void create()
{
        set("short", "花園");
        set("long", @LONG
這裡是一個小花園，雖比不上富豪大院里的萬紫千紅，但
卻也布置得精緻可人。丐幫里顯然不乏高雅之士。春天裡桃花
盛開，夏日池塘里荷花田田，秋天裡菊花爭艷，冬天則是一片
香雪海。花園旁站着一位老丐，也不知道在幹什麼。
LONG);
        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "west"  : __DIR__"ma_xiaojing",
        ]));
        set("objects", ([
                CLASS_D("gaibang") + "/bai-shijing" : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", 50);
	set("coor/y", -70);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}