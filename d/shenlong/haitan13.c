inherit DEMONROOM;

void create()
{
        set("short", "ǳ̲");
        set("long",@LONG
���������������ذ�ǳ̲�������������ˮ�С�
LONG);

	set("exits", ([
		"west"  : __DIR__"haitan12", 
		//"east"  : __DIR__"haitan14",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 10);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/shuishe");

        set("outdoors", "shenlong");
        setup();
}
