inherit ROOM;

void create()
{
        set("short", "����ɽ��");
        set("long", @LONG
�����������һ��ɽ�ڡ�������Ƿ�ɽ�ˣ������Ǻ�ب���Ϲ㶫
�����롣��������ǳ����ȣ����������쳤������Ҳ����Զ����ԭ�ˡ�
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "northup" : "/d/henshan/hsroad9",
                "southwest" : "/d/yaowang/lcd01",
                "south"   : __DIR__"northgate",
        ]));
	set("coor/x", -6570);
	set("coor/y", -9730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}