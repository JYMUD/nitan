inherit ROOM;

void create()
{
        set("short", "�˱�������");
        set("long", @LONG
�����������ڴ��۵���˵ҪС�ö࣬��ȴ���Եø��������ޱȣ�
�������������������̵ģ������ǽ���϶��ο��˷𾭹��£�����
�����շ����ûƽ���䣬��ʯ�������װ�γư˱�����
LONG );
        set("objects", ([
                __DIR__"npc/jiansi" : 1,
                __DIR__"npc/obj/milexiang" : 1,
        ]));

        set("exits", ([
                "south" : __DIR__"houyuan",
                "northdown" : __DIR__"gongmen",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -5040);
	set("coor/y", 2230);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}