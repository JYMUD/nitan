inherit DEMONROOM;

void create()
{
        set("short", "�������");
        set("long",@LONG
����һ��������������ס�
LONG);

        set("exits", ([
                "north"   : __DIR__"lin1.25",
                "south"   : __DIR__"dong2.1",

        ]));

                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 8);
                set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
