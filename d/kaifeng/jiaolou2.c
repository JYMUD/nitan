inherit ROOM;

void create()
{
        set("short", "����¥");
        set("long", @LONG
����¥��ƽʱפ���������ĵط���һ��ֻ��¥�Ķ��˹��˸�����
��ơ���ҹ����ֵ�ء��Ӵ�����������ȸ�ţ������Ƕ���֣�����Ŀ
Զ����������¥�����Ǵ�ý�ɽ��
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "westdown" : __DIR__"zhuque",
                  "eastdown" : __DIR__"eroad2",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5040);
	set("coor/y", 2240);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}