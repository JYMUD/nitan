inherit ROOM;

void create()
{
          set ("short", "���");
        set("long", @LONG
��ƽԭ֮�ϵ�һ����·�������˺ܶ࣬·�������Զ���и�Сͤ
�ӹ�����Ъ�ţ���ȥ���ǿ���ǡ����治Զ�Ǹ�����·�ڡ�
LONG );
          set("outdoors", "kaifeng");

          set("exits", ([
                  "south" : __DIR__"dadao1",
                  "north" : __DIR__"nanying",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2120);
	set("coor/z", 10);
	setup();
          replace_program(ROOM);
}