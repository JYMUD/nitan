inherit ROOM;

void create()
{
        set("short", "�ּ��");
        set("long", @LONG
������һ���ּ�С���������������ѡ��������Ȫ�ݳǵ����ŵ�
�ţ������Ͽɴ����Ϲ㶫��
LONG );
        set("objects", ([
                __DIR__"obj/hua3": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                "east"      : "/d/quanzhou/westbridge",
                "southwest" : __DIR__"road13",
        ]));
	set("coor/x", -6480);
	set("coor/y", -9720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}