inherit DEMONROOM;

void create()
{
        set("short", "�����Ҷ�");
        set("long",@LONG
����������������һ���Ҷ�������������ʪ�����˾���ë���Ȼ��
LONG);

	set("exits", ([
		"south"  : __DIR__"lin1.20", 
		"north"  : __DIR__"lin1.18",

	]));

		set("n_time", 30); 
		set("n_npc", 2); 
		set("n_max_npc", 10);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/jinshewang");

        set("outdoors", "shenlong");
        setup();
}
