inherit ROOM;

void create()
{
        set("short", "����·");
        set("long", @LONG
�����ƹ��ԭ��������Ϊ�˺�ɫ��������ø����£�����
��ȥ��ֻ����Χ�������ԭʼɭ�ֲ����߼ʣ����ʱ�����ĸ�
־Զ��һ�ɺ���ӿ����������Ҫ��һ������ҵ��
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south" : __DIR__"yunnan2", 
               "northeast"  : "/d/jingzhou/tulu2",
                "west" : __DIR__"zhaoze",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -16760);
	set("coor/y", -7160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}