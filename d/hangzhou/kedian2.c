// kedian2.c
// Date: Nov.1997 by Venus
inherit ROOM;

void create()
{
        set("short", "������͵��¥");
        set("long", @LONG
��������������͵��¥�������ϣ����������ӿͷ��ﲻʱ�غ���
�Ĵ�����һ��߹�һ�󡣲�ʱ��˯�����ʵ��ÿͽ�����������¥�µ�
�ƹ񴦸���Ǯ������˯����
LONG );
        set("exits", ([
                "down"  : __DIR__"kedian",
                "enter" : __DIR__"kedian3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 840);
	set("coor/y", -2070);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}