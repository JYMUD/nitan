inherit DEMONROOM;

void create()
{
        set("short", "�����ƴ���");
        set("long",@LONG
��������������һƬ�����ƴ��֣������Ĵ�����һ�˸ߵ������ơ�
LONG);

        set("exits", ([
                "west"  : __DIR__"haitan5", 
                "east"  : __DIR__"haitan7",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 4);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/xiangweishe");

        set("outdoors", "shenlong");
        setup();
}
