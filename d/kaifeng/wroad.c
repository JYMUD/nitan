inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
���⸮���������Ҫ��ͨҪ�����ֵ����ߵ������������˳�����
��С�̷������ŵ�������ߺ�ȡ��˵��򶫾�������µķ����أ���
�򱱹�ȥ��Զ�����ܼ�������۵Ĵ����ˡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"wroad1",
                  "eastup" : __DIR__"fangsheng",
                "west" : __DIR__"ximen",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5070);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}