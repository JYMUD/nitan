inherit DEMONROOM;

void create()
{
        set("short", "�߶���");
        set("long",@LONG
�����������߶��⣬��˵���ڶ��߱鲼������ס���߾���û���˽�ȥ��
���ٻ��ų�����
LONG);

        set("exits", ([
                "north"   : __DIR__"dong2.15",
                "enter"   : __DIR__"shedong1",

        ]));

                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 2);
                set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
