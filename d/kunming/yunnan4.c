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
                "north" : __DIR__"yunnan3", 
                "south"  :__DIR__"xiaolu",
        ]));
	set("coor/x", -16770);
	set("coor/y", -7180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}