inherit ROOM;

void create()
{
        set("short", "��ʸ����");
        set("long", @LONG
��¥�д�ɨ�û���ɾ���������ʿ�Ƕ���������Ȼ�������⣬��
��ʻ���ͦ���صġ��˵ع�������𺺰������ʴ��������ϸ�壬
�ƿ����������ܿ��������Ŀ���־���
LONG );
        set("objects", ([
                  __DIR__"npc/obj/yudixiang" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "down" : __DIR__"yuhuang",
        ]));

	set("coor/x", -5100);
	set("coor/y", 2240);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}