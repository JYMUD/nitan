inherit DEMONROOM;

void create()
{
        set("short", "�������");
        set("long",@LONG
����һ��������������ס�
LONG);

        set("exits", ([
                "east"   : __DIR__"dong3.1",
                "west"   : __DIR__"lin1.25",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 6);
                set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
