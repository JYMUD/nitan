inherit DEMONROOM;

void create()
{
        set("short", "�����Ҷ����ѷֲ��");
        set("long",@LONG
�������������ϲ��Ҷ����һ�����ѣ������쳣���䡣
LONG);

	set("exits", ([
		"north"  : __DIR__"lin1.24",
		"east"   : __DIR__"dong3",
		"west"   : __DIR__"dong1",
		"south"  : __DIR__"dong2",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 2);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/xuanmang");

        setup();
}
