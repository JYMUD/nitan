inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
������ԭ��һ�������ݸ����Ľ��⡣��������ݲ�Զ����
��Ҳ��˵�ù�ȥ�������������Ƿ��򣬶���ͨ�����ݸ���
LONG);
        set("exits", ([
                //"west" : __DIR__"wroad1",
               "west" : "/d/luoyang/hulaoguan",
                  "east" : __DIR__"chenglou",
        ]));
        set("outdoors", "zhongzhou");
        set("no_clean_up", 0);

        set("coor/x", -9090);
	set("coor/y", -1000);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}