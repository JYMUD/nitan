inherit ROOM;

void create()
{
        set("short", "С·");
        set("long", @LONG
һ��бб��С·������ȥ��Զ��Ƭ���֣�����ȥ�ں������ԴӲ�
��ǰ�����г���Ұ�����˺��������������ߡ�ֻ��̰ͼ·�����˻�
����������
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "southwest" : __DIR__"yezhulin",
                  "northeast" : __DIR__"dadao1",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5050);
	set("coor/y", 2100);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}