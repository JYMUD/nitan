inherit DEMONROOM;

void create()
{
        set("short", "����ľ���");
        set("long",@LONG
����һƬ��ľ�֡���û���뵽����һ���µ��Ͼ���������һƬ��
ľ�֣����ɸе��ǳ��Ծ���
LONG);

        set("exits", ([
                "east"  : __DIR__"lin1.8", 
                "west"  : __DIR__"lin1.6",

        ]));


                
                set("n_time", 60); 
                set("n_npc", 2); 
                set("n_max_npc", 15);
                set("s_npc", "/clone/dream_npc/shenlongdao/snake/qingshe");

        set("outdoors", "shenlong");
        setup();
}
