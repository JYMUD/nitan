inherit DEMONROOM;

void create()
{
        set("short", "��������");
        set("long",@LONG
����һƬԭʼ���֣����ر����ܸ��ʵ���ľ�ڱΣ��쳣������
LONG);

        set("exits", ([
                "east"  : __DIR__"lin1.10", 
                "west"  : __DIR__"lin1.8",

        ]));


                
                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 6);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/mangshe");

        set("outdoors", "shenlong");
        setup();
}
