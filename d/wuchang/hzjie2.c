//Edited by fandog, 01/31/2000

inherit ROOM;

void create ()
{
        set ("short", "������");
        set ("long", @LONG
�����人����Ľֵ����Ӵ��ϱ����ĸ�ɫ�˵ȣ�����������Ħ
����ࡣ������һ��С�Ե꣬�ſڵ�������д�š���ͨ�ǡ��������֡�
������һ����ͷ������ϸ��������������ˮ�Ĵ򽭰���������
LONG);
        set("outdoors", "wuchang");
        set("exits", ([
                "east" : __DIR__"matou1",
                "west" : __DIR__"laotc",
                "south": __DIR__"zhongxin",
                "north": __DIR__"hzjie1",
        ]));

        set("no_clean_up", 0);
	set("coor/x", -5090);
	set("coor/y", -1870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}