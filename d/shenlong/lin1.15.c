inherit DEMONROOM;

void create()
{
        set("short", "��������Σ�յش�");
        set("long",@LONG
����������ԭʼ�����������ǰ�߾���Σ�յش��ˣ�С�ġ�
LONG);

	set("exits", ([
		"east"  : __DIR__"lin1.16", 
		"west"  : __DIR__"lin1.14",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 1);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/qingshe");

        set("outdoors", "shenlong");
        setup();
}
