inherit DEMONROOM;

void create()
{
        set("short", "�������");
        set("long",@LONG
����һ��������������ס�
LONG);

        set("exits", ([
                "east"   : __DIR__"dong1.14",
                "west"   : __DIR__"dong1.16",

        ]));

                set("n_time", 60); 
                set("n_npc", 4); 
                set("n_max_npc", 6);
                set("s_npc", "/clone/dream_npc/shenlongdao/xixue-bianfu");

        setup();
}
