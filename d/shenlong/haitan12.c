inherit DEMONROOM;

void create()
{
        set("short", "����");
        set("long",@LONG
���������������ذ����ߡ�
LONG);

	set("exits", ([
		"west"  : __DIR__"haitan11", 
		"east"  : __DIR__"haitan13",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 8);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/shuishe");

        set("outdoors", "shenlong");
        setup();
}
