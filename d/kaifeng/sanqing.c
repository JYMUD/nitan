inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
����������������񣬲������⸮�ڵľ����ൽ�������
ȥ���㻹Ը�ˣ��������𲢲���������Ҳ��ͷ����������ᡣ����
ȥ�����߸ߵĸ�¥��������ʸ�
LONG );
        set("objects", ([
                  __DIR__"npc/obj/sanqingxiang" : 1,
                  __DIR__"npc/xianghuo" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"yanqing",
                  "west" : __DIR__"yuhuang",
        ]));

	set("coor/x", -5090);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}