inherit ROOM;

void create()
{
        set("short", "���⹱Ժ");
        set("long", @LONG
�������ţ��ֵ���һ������Ĵ�Ժ�������ʯʨ�������������
����Ժ�����������ɫ��ÿ����Ѯ���˴������о��˵Ŀ������ű�ǽ
�������Ÿ�ʾ��
LONG );
        set("objects", ([
                  __DIR__"npc/zhukao3" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"road2",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}