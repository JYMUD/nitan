//Edited by fandog, 01/31/2000

inherit ROOM;
void create ()
{
        set("short", "������");
        set("long", @LONG
����һ�Ҽ�ª�Ĵ����̣����İ���һ����¯��¯��������յ�һƬ
ͨ�죬��һ�߽�ȥ�͸е�������ȡ�ǽ�Ƕ��������깤��δ�깤�Ĳ˵���
������������ذ�ס����׵��һλ������ͷ�󺹻�����������ר����
־���ڴ�����
LONG );
        set("exits", ([
                "south" : __DIR__"dongdajie",
        ]));
        set("objects", ([
                __DIR__"npc/smith": 1,
        ]));
	set("coor/x", -6750);
	set("coor/y", 1870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}