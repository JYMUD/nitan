inherit ROOM;

void create()
{
        set("short", "��ʯ·" );
        set("long", @LONG
һ����ʯ�̳ɵ�·��ƽ̹������·�����档����������������
���˶�������ȥ�˳�����ЪЪ�ţ�һЩС��Ҳ�˻����������Ժȵ�
���������������Ͽ�ȥ����Լ���Կ������ڵĳ�����
LONG );
        set("exits", ([
                "south" : __DIR__"xiaowu",
                "east" : __DIR__"qingshilu1",
                "southwest" : __DIR__"shandao",
           ]));

        set("no_clean_up", 0);
        set("outdoors", "jingzhou");
        set("objects", ([
                "/d/beijing/npc/girl2" : 1,
        ]));
        set("coor/x", -7120);
	set("coor/y", -2090);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}