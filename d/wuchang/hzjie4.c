//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "������");
        set ("long", @LONG
�����人����Ľֵ����Ӵ��ϱ����ĸ�ɫ�˵ȣ�����������Ħ
����ࡣ������һ�ҿ�ջ����������ҩ�ĵĵ��̣��ƺ�������������ҩ��
����һ������ʯ�ʵ�������
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"zhongxin",
                "west" : __DIR__"ximen",
                "south": __DIR__"kedian",
                "north": __DIR__"yaocaidian",
        ]));

        set("no_clean_up", 0);
	set("coor/x", -5100);
	set("coor/y", -1880);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}