inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
���⸮���������Ҫ��ͨҪ�����ֵ����ߵ������������˳�����
���̷���ߺ�ȣ�������С�����ּۻ��������ޱȡ������������ۣ�
��������ϵ���¥��
LONG );
        set("objects", ([
                  __DIR__"npc/qigai" : 1,
        ]));
        set("outdoors", "kaifeng");
        set("exits", ([
                  "eastup" : __DIR__"jiaolou",
                  "west" : __DIR__"yanqing",
                  "north" : __DIR__"wroad3",
                  "south" : __DIR__"wroad1",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -5070);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}