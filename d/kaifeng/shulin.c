inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
һƬ�����֣���Ҷ�������أ��߲���֦Ҷ��¶�����������顣��
ɫ��С�ݾʹ���֮��Ŀ�϶�����������е��Ķ�����ɫ��С·����
���ֲ�Զ��������̨�����������ݷ���
LONG );
        set("no_clean_up", 0);

        set("exits", ([
                "northwest" : __DIR__"dadao1",
                "east" : __DIR__"yuwang",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5030);
	set("coor/y", 2100);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}