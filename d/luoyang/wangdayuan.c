//  Room:  /d/luoyang/wangdayuan.c

inherit  ROOM;

void  create  ()
{
        set("short",  "��Ժ");
        set("long",  @LONG
���߽����Ҵ�Ժ��Ժ�����ż�����÷��֦������򰾢��Ժ������С
ͥԺ�ڣ��ٲ������������ı�־������ͦ�����ĵ����Ժ����ͣ�˲���
����ÿһƥ���ڶ��ǰ����������������ҡ������������ƹ��ǲ�����
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "south"  :  __DIR__"wangdatang",
                "west"   :  __DIR__"wangxiaoyuan",
                "out"    :  __DIR__"wanggate",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -7021);
	set("coor/y", 2169);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}