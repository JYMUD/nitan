inherit ROOM;

void create()
{
        set("short", "��¥����");
        set("long", @LONG
�������¥�±Ƚϰ����������������ţ���������£�����Ҳ������
�������շ�Ҳ����΢�ĸ���ôһ�㣬������Ҫ�������������������͵�˵
��������˵��һ�ζ�������Ȥ��������ʤ�Ĺ��£�����һЩ������͵���
�������������˸�����������
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "down" : __DIR__"chalou",
                  "west" : __DIR__"shuoshu",
        ]));
        set("objects", ([
                "/d/beijing/npc/chake" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2160);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}