inherit DEMONROOM;

void create()
{
        set("short", "�������");
        set("long",@LONG
����һ��������������ס�
LONG);

	set("exits", ([
		"east"   : __DIR__"dong1.15",
		"west"   : __DIR__"dong1.17",

	]));

		set("n_time", 30); 
		set("n_npc", 4); 
		set("n_max_npc", 20);
		set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        set("outdoors", "shenlong");
        setup();
}
