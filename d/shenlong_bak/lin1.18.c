inherit DEMONROOM;

void create()
{
        set("short", "神秘岩洞");
        set("long",@LONG
这是神龙岛东部的一个岩洞，这里阴暗潮湿，令人觉得毛骨悚然。
LONG);

        set("exits", ([
                "south"  : __DIR__"lin1.19", 
                "north"  : __DIR__"lin1.17",

        ]));

                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 10);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/jinshewang");

        set("outdoors", "shenlong");
        setup();
}
