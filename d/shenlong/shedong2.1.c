inherit DEMONROOM;

void create()
{
        set("short", "���߿�");
        set("long",@LONG
�����߶��ڵĶ��߿ߣ�ֻ���������Ƕ��ߣ��ֲ��ǳ���
LONG);

	set("exits", ([
		"east"  : __DIR__"shedong2", 
	]));

		set("n_time", 15); 
		set("n_npc", 3); 
		set("n_max_npc", 8);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        setup();
}
