inherit ROOM;

void create()
{
        set("short", "馬庄宴廳");
        set("long", @LONG
這裡是馬庄的正廳，布置的頗為優雅，絲毫沒有正廳上的
嚴肅氣氛。一張紅木大桌邊上有個書櫃，櫃里擺了各式各樣的
書。幾個丐幫的乞丐圍聚在這裡。
LONG);
        set("region", "yangzhou");
        set("exits", ([
                "east"  : __DIR__"ma_zhengting",
        ]));
        set("objects", ([
                "/d/gaibang/npc/2dai" : 1,
                "/d/gaibang/npc/3dai" : 1,
                "/d/gaibang/npc/4dai" : 1,
        ]));
        set("no_clean_up", 0);
	set("coor/x", 20);
	set("coor/y", -40);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}