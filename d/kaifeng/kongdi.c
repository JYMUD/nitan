inherit ROOM;

void create()
{
        set("short", "�յ�");
        set("long", @LONG
����԰�Ĳ˵��м��һƬ�յأ���������Ϊԭ���Ĳ˵ر���ƽ��
ɮ�˲��ͷ����ֶ��������ġ����ص��м�һס�ϻ���֦Ҷ�����ģ���
�����ѻ��ʱ���С��ϱ��Ǹ�С��ѣ������м�С�ü䡣
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"caidi5",
                  "south" : __DIR__"fenjiao",
                  "east" : __DIR__"tangjian",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -4980);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}