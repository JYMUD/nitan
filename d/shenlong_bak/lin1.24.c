inherit DEMONROOM;

void create()
{
        set("short", "�����Ҷ�����");
        set("long",@LONG
�������������ϲ��Ҷ����һ�����ѣ������쳣���䡣
LONG);

        set("exits", ([
                "south"  : __DIR__"lin1.25", 
                "north"  : __DIR__"lin1.23",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 6);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/xuanmang");

        setup();
}
