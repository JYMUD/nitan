inherit DEMONROOM;

void create()
{
        set("short", "����ľ��");
        set("long",@LONG
����һƬ��ľ�֡���û���뵽����һ���µ��Ͼ���������һƬ��
ľ�֣����ɸе��ǳ��Ծ���
LONG);

	set("exits", ([
		"east"  : __DIR__"lin1.3", 
		"west"  : __DIR__"lin1.1",

	]));


		
		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 20);
		set("s_npc", "/clone/dream_npc/shenlongdao/snake/fushe");

        set("outdoors", "shenlong");
        setup();
}
