//  Room:  /d/luoyang/wangzhangfang.c

inherit  ROOM;

void  create  ()
{
        set("short",  "�ʷ�");
        set("long",  @LONG
���������ҵ��˷������ıڶ����ʲ��ܣ������˳������ʣ�����һ
Щ�ʲ����ڵ��¡�һ��ʦүһ��������������ʰ�����ʡ�
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south"  :  __DIR__"wangxiangfang",
                "east"   :  __DIR__"wangdatang",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/yi" : 1,
        ]));
	set("coor/x", -7031);
	set("coor/y", 2159);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}