inherit ROOM;

void create()
{
          set ("short", "����·��");
        set("long", @LONG
��·���˷�Ϊ��·��һ��·�򱱾��ǿ���ǣ��������������֡�
����������С���������������·ͨ��Ұ���֡�
LONG );

          set("outdoors", "kaifeng");
          set("exits", ([
                  "southwest" : __DIR__"dadao2",
                  "southeast" : __DIR__"shulin",
                  "north" : __DIR__"dadao",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2110);
	set("coor/z", 10);
	setup();
          replace_program(ROOM);
}