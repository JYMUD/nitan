inherit DEMONROOM;

void create()
{
        set("short", "����");
        set("long",@LONG
���������������ذ����ߡ�
LONG);

        set("exits", ([
                "west"  : __DIR__"haitan10", 
                "east"  : __DIR__"haitan12",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 7);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/shuishe");

        set("outdoors", "shenlong");
        setup();
}
