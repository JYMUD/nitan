inherit ROOM;

void create()
{
        set("short", "��¥");
        set("long", @LONG
����һ�Ҽ�Ϊ��ͨ�ľ�¥��ƽ�������Щ�׾ƣ����ӣ���
������������˶��������㶫�������ˣ�Ҳ��Щ�˽е㻨��
�ף��е���ţ�����������ѵġ�
LONG);
        set("exits", ([
                "west" : __DIR__"nandajie1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
	set("coor/x", -16830);
	set("coor/y", -7220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}