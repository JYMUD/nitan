//  Room:  /d/lanzhou/southgate.c

inherit  ROOM;

void  create  ()
{
        set("short",  "����");
        set("long",  @LONG
�����������ţ���ǽ���������Ե�������ΰ�����������Ǿ�������
��˹ٱ��Ƕ�����ʮ���־������������ˡ�һ����ֱ�Ĺٵ����ϱ���
�����졣
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"road2",
                "south" : __DIR__"road1",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/city/npc/wujiang": 1,
                "/d/city/npc/bing": 2,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "lanzhou");
	set("coor/x", -15750);
	set("coor/y", 3790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}