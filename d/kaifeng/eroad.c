inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
������ǿ��⸮�ڶ���������Ҫͨ������·�����˵��̸��ڲ��ϡ�
�������ƣ��۹�ģ�������ģ��ʽ���ģ��������׷��ѵģ�������
�ȡ��ϱ�һ��С�������ƺ��Ǹ�С��԰�ӡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"jiaomen",
                  "north" : __DIR__"eroad1",
                "east" : __DIR__"dongmen",
        ]));

        set("outdoors", "kaifeng");

	set("coor/x", -5030);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}