inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
����������������ʷ�ˡ����ⶰ¥����ںڵ���������ܿ���
�������������ʳ�ͻ���ͦ�ࡣ�����������ˡ�¥�ϵ�Ȼ����������
����Ҫ��һ����ݵ�λ���˲����ϡ�
LONG );
        set("exits", ([
                "up" : __DIR__"daoxiang2",
                "west" : __DIR__"road2",
                "east" : __DIR__"majiu",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

	set("coor/x", -5040);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}