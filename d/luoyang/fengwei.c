inherit ROOM;

void create()
{
        set("short", "��ζС��");
        set("long", @LONG
�����ǰͻȻ������һ��С�Ե꣬���������һ�����ӣ�������д��
����ζС�ԡ��ĸ��֣���С�Ե������Զ����������ﲻ��������ҵ�����
�ܳԵ�ȫ�����صķ�ζС�ԣ������С�������Ĺ�������ӣ������Ŀ�
Ѽ�����˵����㶹��֣�ݵ�����ȵȣ�����Ʒ��һ�°ɣ�
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                "north" : __DIR__"zashua",
                "east" : __DIR__"wanju",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
	set("coor/x", -6960);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}