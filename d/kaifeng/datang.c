inherit ROOM;

void create()
{
        set("short", "���⸮����");
        set("long", @LONG
���ŵ�����վ�����ߣ����Ա�����ͷ����ͷ����ͷ����ա������
���ķ������˺�ëֱ����̨����߹ҡ��������������Ҷ���˴��ã�
����Ҳ�����������ȥ���ǽֵ���
LONG );
        set("objects", ([
                __DIR__"npc/baozheng" : 1,
        ]));

        set("exits", ([
                  "east" : __DIR__"kaifeng",
        ]));

	set("coor/x", -5060);
	set("coor/y", 2150);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}