//  Room:  /d/luoyang/road2.c

inherit  ROOM;

void  create  ()
{
        set("short",  "��ٵ�");
        set("long",  @LONG
����һ��������ֱ�Ĺٵ�������ݵ���ʮ���ۡ�·�߻�����Щ��
������ĵ������һ����֪���������ǵ�Ͻ�ء��������ͨ�����ݵĴ��
�����������������������ǣ�����������������������ʤ�أ������¡�
���������οͺܶ࣬·�߲ݵ��Ѿ����ȵ��൱ƽ�ˡ�
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "east"      :  __DIR__"hulaoguan",
                "westup"    :  __DIR__"ebridge",
                "south"     :  __DIR__"road7",
                "northeast" :  __DIR__"baimasi",
                "southeast" :  __DIR__"road0",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6910);
	set("coor/y", 2150);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}