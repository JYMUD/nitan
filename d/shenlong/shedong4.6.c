inherit DEMONROOM;

void create()
{
        set("short", "��ͷ�߶�");
        set("long",@LONG
�����߶��ڵľ�ͷ�߶�����˵�������Ǿ�ͷ�߳�û�ĵط���
LONG);


	set("exits", ([
		"west"  : __DIR__"shedong4.5",		
		"east"   : __DIR__"shedong4.7",
	]));

		set("n_time", 30);
		set("n_npc",1); 
		set("n_max_npc", 2);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/jiutoushe");

        setup();
}
