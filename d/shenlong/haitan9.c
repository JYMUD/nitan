inherit DEMONROOM;

void create()
{
        set("short", "�����ƴ���");
        set("long",@LONG
��������������һƬ�����ƴ��֣������Ĵ�����һ�˸ߵ������ơ�
LONG);

	set("exits", ([
		"west"  : __DIR__"haitan8", 
		"east"  : __DIR__"haitan10",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/xiangweishe");

        set("outdoors", "shenlong");
        setup();
}
