inherit DEMONROOM;

void create()
{
        set("short", "��������Σ�յش�");
        set("long",@LONG
����������ԭʼ�����������ǰ�߾���Σ�յش��ˣ�С�ġ�
LONG);

        set("exits", ([
                "enter"  : __DIR__"lin1.17", 
                "west"  : __DIR__"lin1.15",
                "south" : __DIR__"xiaoxi1",
                "east" : __DIR__"haitan1",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 1);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/qingshe");

        set("outdoors", "shenlong");
        setup();
}
