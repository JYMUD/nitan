inherit ROOM;

void create()
{
        set("short", "ԭʼɭ��");
        set("long", @LONG
���߽�ԭʼɭ�֣�ֻ����Χ����ããȫ�ǲ������������
���գ����ܹ��ߺܰ����ֲ��嶫������������˭������������
��ȥ�ˡ��Һõ�����������ʱ��������һ��·�����򣬾���
�������޳Ե�������ҲҪ�����ζ�����
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "west" : __DIR__"yunnan3", 
                "north"  :__DIR__"yunnan1",
        ]));
        set("objects", ([
                "/clone/worm/huabanzhu" : 1,
                "/clone/npc/walker"  : 1,
        ]));
	set("coor/x", -16760);
	set("coor/y", -7170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}