inherit DEMONROOM;

void create()
{
        set("short", "���߿�");
        set("long",@LONG
�����߶��ڵĶ��߿ߣ�ֻ���������Ƕ��ߣ��ֲ��ǳ���
LONG);


        set("exits", ([
                "north"  : __DIR__"shedong1",                
                "south"  : __DIR__"shedong4.1",
        ]));

                set("n_time", 60);
                set("n_npc", 3); 
                set("n_max_npc", 5);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/xuanmang");

        setup();
}
