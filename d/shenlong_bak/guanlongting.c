inherit ROOM;

void create()
{
        set("short", "����ͤ");
        set("long",@LONG
����һ���žɵ�ͤ�ӣ���֪��ʲô���Ϊ˭������
LONG);

        set("exits", ([
                "north"  : __DIR__"xiaoxi2",
        ]));

        set("objects", ([
                __DIR__"npc/yufu" : 1, 
        ]));
        //set("no_fight", 1);
        set("outdoors", "shenlong");
        setup();
}
