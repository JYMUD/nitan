// This program is a part of NT MudLIB

inherit ROOM;

void create ()
{
        set ("short", "����");
        set ("long", @LONG
�������Ϊ��ף��ү����ʮ���ٲ��õĴ�����ǰ�����ٵĿ�����½
������������Ѿ��������æ�Ŷ˲���ˮ��������һ�����ο����������
�ں��ڱ���������
LONG);
        set("region", "jingzhou");
        set("exits", ([
                "south"  : __DIR__"wan_damen",
                "north"  : __DIR__"wan_zoulang",
                "east"   : __DIR__"wan_donglou",
                "west"   : __DIR__"wan_xilou",
        ]));
        set("objects", ([
                __DIR__"npc/wanzhenshan" : 1,
                __DIR__"npc/lvtong"      : 1,
                __DIR__"npc/lukun"       : 1,
                __DIR__"npc/zhouqi"      : 1,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}