//  Room:  /d/luoyang/wanghuating.c

inherit  ROOM;

void  create  ()
{
        set("short",  "����");
        set("long",  @LONG
���߽����һ���������ᵽ�������������Ž�����̺죬ʲô����
�д�ɫ�ޱߡ������У�СС�����ݺ����ѣ���ɫ���ڡ����������Ǹ�ʯ
ͤ�������������������������֮����
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"  :  __DIR__"wangdatang",
                "south"  :  __DIR__"wanglianwu",
                "west"   :  __DIR__"wangxiangfang",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/wangzhongqiang" : 1,
        ]));
        set("outdoors", "luoyang");
	set("coor/x", -7021);
	set("coor/y", 2149);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}