//  Room:  /d/luoyang/wanggate.c

inherit  ROOM;

void  create  ()
{
        set("short",  "����");
        set("long",  @LONG
�����Ǵ������������������ҡ���������ʮ�ָߴ������Ĵ�
�ţ�����������ͭ�������þ���ѩ���������������Ϳ�͵ġ��𵶡���
�֣�����׳�������ڴ������̺�
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "enter"  :  __DIR__"wangdayuan",
                "north"  :  __DIR__"wroad3",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/zhuanghan" : 2,
        ]));
        set("outdoors", "luoyang");
	set("coor/x", -7020);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if ( objectp(present("zhuang han", environment(me))) && dir == "enter")
           return notify_fail("׳����ס��˵����������������Ұ�����ȥ��\n");
        return ::valid_leave(me, dir);
}