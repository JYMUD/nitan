inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
������ǿ��⸮�ڶ���������Ҫͨ������·�����˵��̸��ڲ��ϡ�
�������ƣ��۹�ģ�������ģ��ʽ���ģ��������׷��ѵģ��ϱ߲�
Զ����ɽ�¸ʻ�ݡ������ǿ������������������������µĺ컨���
�ܶ����ڡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"eroad2",
                  "west" : __DIR__"tieta",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5030);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}