inherit DEMONROOM;

void create()
{
        set("short", "�����Ҷ�");
        set("long",@LONG
�������������ϲ���һ���Ҷ�������������ʪ�����˾���ë���Ȼ��
LONG);

        set("exits", ([
                "south"  : __DIR__"lin1.22", 
                "north"  : __DIR__"lin1.20",

        ]));

                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 5);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        set("outdoors", "shenlong");
        setup();
}
