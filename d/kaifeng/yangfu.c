inherit ROOM;

void create()
{
        set("short", "�첨�︮");
        set("long", @LONG
�첨�︮�ǿ���������ҵ�ĸ�ۡ���Դ���ҵȥ��֮�󣬸���ֻʣ
��һЩŮ�Ӿ�ס����ǰ�����������ԣ������ʯ�⻬�쳣�����ǵ���
���͡��Ĺٹ������ţ���ٹ�������
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"road3",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5070);
	set("coor/y", 2220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}