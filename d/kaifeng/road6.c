inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @LONG
�����Ǻ�Ὺ�����Ҫ�ֵ���Ҳ�ǻ��ϳ�Ѳ��Ҫ�����ֵ����ߵ�
��̨ͤ���ϣ�С����������������������������һ�ɷ���������һ��
�ߵ��������������Ŀ���������
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"jieying",
                  "south" : __DIR__"road5",
                  "north" : __DIR__"xuandemen",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5060);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}