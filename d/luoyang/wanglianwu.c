//  Room:  /d/luoyang/wanglianwu.c

inherit  ROOM;

void  create  ()
{
        set("short",  "������");
        set("long",  @LONG
��˵����������ԥ�����书��������������������������ġ�����
������Ҳֻ������һ����Ѱ�������Ӷ��ѣ�Ψһͻ���ģ������Ƕ�ǽ��
������һ�ڵ������ˡ�
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north"  :  __DIR__"wanghuating",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -7021);
	set("coor/y", 2139);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}