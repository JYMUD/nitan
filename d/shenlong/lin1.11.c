inherit DEMONROOM;

void create()
{
        set("short", "��������");
        set("long",@LONG
����һƬԭʼ���֣����ر����ܸ��ʵ���ľ�ڱΣ��쳣������
LONG);

	set("exits", ([
		"east"  : __DIR__"lin1.12", 
		"west"  : __DIR__"lin1.10",

	]));


		
		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 6);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/yanjingshe");

        set("outdoors", "shenlong");
        setup();
}
