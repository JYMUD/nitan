//  Room:  /d/luoyang/wangdatang.c

inherit  ROOM;

void  create  ()
{
        set("short",  "����");
        set("long",  @LONG
һ�������ţ�ֻ����������һ�������ң�д�š�������Ϊ���ĸ�
���֣���������Ǻ���ʡ��Ѳ��ĳ�ˡ��������ҵ�������ֻ�书�ϵ���
�������ġ�����Ҳ������ӭ������ĵط����������ߣ���װ�ε�ʮ�ֻ�
��
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south"  :  __DIR__"wanghuating",
                "north"  :  __DIR__"wangdayuan",
                "west"   :  __DIR__"wangzhangfang",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/wang" : 1,
        ]));
	set("coor/x", -7021);
	set("coor/y", 2159);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}