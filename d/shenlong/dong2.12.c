inherit DEMONROOM;

void create()
{
        set("short", "�������");
        set("long",@LONG
����һ��������������ס�
LONG);

	set("exits", ([
		"north"   : __DIR__"dong2.11",
		"south"   : __DIR__"dong2.13",

	]));

		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 12);
		set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
