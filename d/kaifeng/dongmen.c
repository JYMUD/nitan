inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���⸮�ڶ������Ҫ��ͨҪ�����ֵ����ߵ������������˳�����
��С�̷������ŵ�������ߺ�ȡ������򶫱����ǻ����ˣ�������
���ݳǡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"eroad",
                "east" : __DIR__"guandao1",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5020);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}