inherit DEMONROOM;

void create()
{
        set("short", "�Ĺ�");
        set("long",@LONG
���а�����9��18�±�����������ʿ��Ϊ���ǵ�Ӣ�۱���ɣ�
LONG);

	set("exits", ([
		"north"   : __DIR__"japan4",
		"east"   : __DIR__"siguo2",
		"west"  : __DIR__"siguo3",
	    "south"  : __DIR__"siguo4",

	]));

		set("n_time", 30); 
		set("n_npc", 5); 
		set("n_max_npc", 15);
		set("s_npc", "/clone/dream_npc/japangame/japannpc01");

        setup();
}
