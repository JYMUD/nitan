// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "����");
        set ("long", @LONG
�������������ؿ��˵�С���á��м�һ��СԲ��ľ���ϣ�������
һ����ϯ�����ſ����������ε��⣬���Կ�����԰�Ĵ�ɫ��
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "up"     : __DIR__"wan_beilou",
                "south"  : __DIR__"wan_zoulang",
                "north"  : __DIR__"wan_huayuan",
        ]));
        set("objects", ([
                __DIR__"obj/babao" : 1,
                __DIR__"obj/longfeng" : 1,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}