// Room: /d/luoyang/hulaoguan.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "���ι�");
        set("long",  @LONG
���ι��ֳ���ˮ�ء��ɸ޹أ������������ڴ��λ���������������
�����޲��ڴ�������������������������ƺӣ�ɽ�뽻���Գ����ա�
����һ�򵱹أ����Ī��֮�ƣ�Ϊ�������ұ���֮�أ�������Ӣս����
��ʹ����������
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "west" : __DIR__"road2",
                "east" : "/d/zhongzhou/xijiao",
        ]));
        set("objects",  ([  /*  sizeof()  ==  2  */
                "/d/city/npc/bing" : 2,
        ]));
        set("outdoors", "luoyang");
	set("coor/x", -6900);
	set("coor/y", 2150);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}