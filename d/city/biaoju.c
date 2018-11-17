// Room: /city/biaoju.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "福威鏢局");
        set("long", @LONG
你來到一座結構宏偉的建筑前，左右石壇上各插着一根兩丈多高
的旗杆，桿上青旗飄揚。右首旗子用金線綉着一頭張牙舞爪的獅子，
獅子上頭有一隻蝙蝠飛翔。左首旗子上寫着『福威鏢局』四個黑字，
銀鉤鐵劃，剛勁非凡。入口處排着兩條長凳，幾名鏢頭坐着把守。少
鏢頭正跟他們說笑。
LONG );

	set("exits", ([
		"south" : __DIR__"zhengting",
                "north" : __DIR__"xidajie3",
	]));
	set("objects", ([
		__DIR__"npc/biaotou" : 2,
	]));
//	set("no_clean_up", 0);
	set("coor/x", -30);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
	replace_program(ROOM);
}