inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���⸮���������Ҫ��ͨҪ�����ֵ����ߵ������������˳�����
��С�̷������ŵ�������ߺ�ȡ��˵��򶫾�������µķ����أ���
�򱱹�ȥ��Զ�����ܼ�������۵Ĵ����ˡ�
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"wroad",
                "west" : "/d/zhongzhou/eroad3",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5080);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}