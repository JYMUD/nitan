inherit ROOM;

void create()
{
        set("short", "�ص���");
        set("long", @LONG
�ص���ǰһ���ϴ������¯����Ϊ����ү�������š�����������
����Э����Ҫ��һ�¹ص�ү�����ϣ����������е�ʤ���ˣ�Ҳ��Ҫ
�����������㡣�Ͼ��ص��ֱ���Ϊ��ʥ��
LONG );
        set("objects", ([
                  __DIR__"npc/obj/guanyu" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"paifang",
        ]));

	set("coor/x", -5000);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}