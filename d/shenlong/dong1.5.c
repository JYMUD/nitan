inherit DEMONROOM;

void create()
{
        set("short", "�������");
        set("long",@LONG
����һ��������������ס�
LONG);

	set("exits", ([
		"east"   : __DIR__"dong1.4",
		"west"   : __DIR__"dong1.6",

	]));

		set("n_time", 30); 
		set("n_npc", 3); 
		set("n_max_npc", 12);
		set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
