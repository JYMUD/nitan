// Room: /city/biaoju.c

inherit ROOM;

void create()
{
        set("short", "�����ھ�");
        set("long", @LONG
��������ϲ豭��С��ͭ���������⣬�Ŷ��Ҷ�д�š������ھ֡�
�ĸ�������֣�������顰�ܺš�����С�֡����Ŵ����ų��ʣ�������
����װ���ӣ����������ͦ���Գ�һ��Ӣ��֮����
LONG );

        set("exits", ([
                "south" : __DIR__"xidajie",
                "enter" : __DIR__"biaojudy",
        ]));
        set("objects", ([
                __DIR__"npc/chenqi" : 1,
                __DIR__"npc/baier" : 1,
        ]));
	set("coor/x", -100);
	set("coor/y", -6170);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}