inherit DEMONROOM;

void create()
{
        set("short", "�������");
        set("long",@LONG
����һ��������������ס�
LONG);

        set("exits", ([
                "east"   : __DIR__"dong1.1",
                "west"   : __DIR__"dong1.3",

        ]));

                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 3);
                set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
