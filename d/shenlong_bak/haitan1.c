inherit DEMONROOM;

void create()
{
        set("short", "ɳ��");
        set("long",@LONG
����������������һƬɳ�ء�
LONG);

        set("exits", ([
                "west"  : __DIR__"lin1.16", 
                "east"  : __DIR__"haitan2",

        ]));

                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 3);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/jinshewang");

        set("outdoors", "shenlong");
        setup();
}
