inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
���������Ŷ�������֪���д����˵����ڡ����а���һ��ɼľԲ����
�������ӣ�������һ�׾��µ����˴�����ǽ�Ϲ���һ�����ã��������ͻ�
��ɽ������֪�����ֱʡ�
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "north" : __DIR__"yamen",
        ]));

	set("coor/x", -6970);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}