//  Room:  /d/luoyang/wangxiangfang.c

inherit  ROOM;

void  create  ()
{
        set("short",  "�᷿");
        set("long",  @LONG
���������ҵ��᷿�����Ŵ���һ�ȵ��ţ��������οյ���������
�£�һ����ǧ���ߵ���������Ҿ�����һ���Ƕ���ɽ�ϻ��ң�Ҳ�Ǹ�
��������ĳ��档����һ�Ŵ󴲣�������ϯ�����Ǿ��ࡣ����С���ϰ�
�Ų�ߣ����Ϲ���һ�ڵ�����
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"  :  __DIR__"wangzhangfang",
                "east"   :  __DIR__"wanghuating",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                __DIR__"npc/wangjiajun" : 1,
        ]));
	set("coor/x", -7031);
	set("coor/y", 2149);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}