inherit ROOM;

void create()
{
        set("short", "�����ջ");
        set("long", @LONG
����������������һ�ҿ�ջ�������������ģ�����������ʤ������
��������Ի�������ջ�������ڼ۸񹫵�����˵����������޵Ŀ��˴���
Ϣ�����ﲻ�������⼰����¡�������ڰ����߰������ӣ���С��������ȥ
�Ӵ��Ŵ�����˷����Ŀ��ˡ���¥������������ջ��������ǡ�
LONG);
        set("no_fight", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"majiu",
                "up" : __DIR__"kezhan2",
                "west" : __DIR__"sroad1",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}