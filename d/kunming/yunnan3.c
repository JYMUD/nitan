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
                "east" : __DIR__"yunnan2", 
                "south"  :__DIR__"yunnan4",
        ]));
	set("coor/x", -16770);
	set("coor/y", -7170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}