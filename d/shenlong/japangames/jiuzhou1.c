inherit DEMONROOM;

void create()
{
        set("short", "����");
        set("long",@LONG
���а�����9��18�±�����������ʿ��Ϊ���ǵ�Ӣ�۱���ɣ�
LONG);

	set("exits", ([
		"south"   : __DIR__"changqi2",
		"east"   : __DIR__"jiuzhou2",
		"north"  : __DIR__"jiuzhou3",
	    "west"  : __DIR__"jiuzhou4",

	]));

		set("n_time", 30); 
		set("n_npc", 5); 
		set("n_max_npc", 15);
		set("s_npc", "/clone/dream_npc/japangame/japannpc01");

        setup();
}
