inherit DEMONROOM;

void create()
{
        set("short", "�����Ҷ����·��");
        set("long",@LONG
�������������ϲ��Ҷ������ڴ˴�·�治֪�ι��Ѿ����˱���
LONG);

        set("exits", ([
                "south"  : __DIR__"lin1.24", 
                "north"  : __DIR__"lin1.22",

        ]));

                set("n_time", 60); 
                set("n_npc", 1); 
                set("n_max_npc", 2);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/wangshe");

        set("outdoors", "shenlong");
        setup();
}
