inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
�������ڵĳ��������˵�Ƚϼ򵥣����е�ǽ����д�Ÿ�����
�����֡���������һ�Ŵ�ϯ�ӣ�һ�Ű����ͷ���ϯ���м䡣������
�������档�ڿ�����ĵط����и����ţ������Ǹ�Сľ�㣬��˵����
��ʦÿ��ֻ�����Ƭ�̾;������档
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"xiaoyuan",
        ]));
        set("objects", ([
                  __DIR__"npc/zhiqing" : 1,
        ]));

	set("coor/x", -5020);
	set("coor/y", 2230);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}