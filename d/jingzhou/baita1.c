inherit ROOM;

void create()
{
        set("short", "������¥");
        set("long", @LONG
�����Ǳ������ĵڶ�¥���ഫ��ǰ��һλ״Ԫ�ɿ�ȡ��������
����ĸ���޽��ı�����������������Ƹߣ������̲�סҪ�Ǹ�������
LONG );
        set("exits", ([  
                  "up" : __DIR__"baita2",
                  "down" : __DIR__"baita",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -7090);
	set("coor/y", -2040);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}