inherit ROOM;

void create()
{
        set("short", "�������");
        set("long", @LONG
�������������ݣ�������å������ڶ�Ǯ�������и�С
�ţ������Ϊ�����·�����ʱ��Ľ���ͨ����
LONG);
        set("exits", ([
                "out" : __DIR__"eba",
                "south" : __DIR__"hutong2",     
        ]));

        set("coor/x", -9010);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}