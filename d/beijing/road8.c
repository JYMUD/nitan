inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
������һ����������Ĵ�����ϡ����Ͼ��Ǳ����ǡ������ӵġ�
���̵ġ����Ŵ󳵵�����Ͼ��Ͽ��������������������ǳ����֡�
��ʱ����������������߷ɳ۶���������һ·�����������и�С̯��
�����������ЪϢ��
LONG );
        set("exits", ([
                "north" : "/d/beijing/road4",
                "south" : "/d/beijing/road9",
                "west" : "/d/beijing/xiaotan"                
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2770);
	set("coor/y", 7570);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}