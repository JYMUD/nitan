// Room:  /d/luoyang/road7.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "��·");
        set("long",  @LONG
���������ǽ���һ��é����·����������֮�أ�ƽԭԶ����ʼ䣬
�����ɼ�Ⱥɽ���ơ�
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"road2",
                "south" : __DIR__"dukang",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6910);
	set("coor/y", 2140);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}