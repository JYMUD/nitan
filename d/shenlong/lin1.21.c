inherit DEMONROOM;

void create()
{
        set("short", "神秘岩洞");
        set("long",@LONG
這是神龍島東南部的一個岩洞，這裡陰暗潮濕，令人覺得毛骨悚然。
LONG);

	set("exits", ([
		"south"  : __DIR__"lin1.22", 
		"north"  : __DIR__"lin1.20",

	]));

		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 5);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        set("outdoors", "shenlong");
        setup();
}
