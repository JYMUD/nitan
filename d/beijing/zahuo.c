inherit ROOM;

void create()
{
        set("short", "�ӻ���");
        set("long", @LONG
�����Ǳ����Ƕ���������ߵ�һ���ӻ��̣��ӻ��̲�����ǰ
�߸ߵĹ���һ�����������д�š��ϱ������������֣����ֽ���Ѿ�
���ƣ�������ҵ����������Ѿ���һ����ʷ�ˡ����������С�����
��һ�أ�����һЩ��ͨ���ճ���Ʒ�������ƹ������������һֻ����
�ϣ��к��Ź������ˡ�
LONG );
        set("exits", ([
                "west" : "/d/beijing/caroad_e2",
        ]));
        set("objects", ([
                "/d/beijing/npc/hu": 1,
        ]));

	set("coor/x", -2760);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}