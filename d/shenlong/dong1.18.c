inherit DEMONROOM;

void create()
{
        set("short", "��������");
        set("long",@LONG
������������һ�����صĶ�Ѩ���˴��Ծ����䣬��˵���ڲ��и��ֹ��ޣ�
��˵һֻ�޴�ı�����ס���ⶴ�ڣ�����û�˼�������
LONG);

	set("exits", ([
		"east"   : __DIR__"dong1.17",
                //"enter"   : __DIR__"bingdong1",

	]));

		set("n_time", 30); 
		set("n_npc", 1); 
		set("n_max_npc", 3);
		set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
