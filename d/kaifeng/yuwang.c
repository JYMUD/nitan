inherit ROOM;

void create()
{
        set("short", "����̨");
        set("long", @LONG
����̨������Сɽ��֮�ϣ�����羰�������������ţ��Թ�����
���������δ��Ǹߵ�ʤ�ء��ഫ����ʱ�ڣ�����ä����ʦ�����ڴ˴�
����֣���������̨����
LONG );
        set("objects", ([
                  __DIR__"npc/woman" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"shulin",
                  "eastup" : __DIR__"yuwangmiao",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5020);
	set("coor/y", 2100);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}