inherit ROOM;

void create()
{
        set("short", "�����");
        set("long", @LONG
����һ����������ʯ�ֵ������ϱ���ͷ���졣�����Ǳ�����ͨ��
���⡣�ϱ��Եúܷ�æ��������һ��С���ݣ��Ŷ���д�š����Ϸ�ׯ
�������֣����������������㴹�����Ρ�������һ��ҩ�ꡣ
LONG );
        set("outdoors", "jingzhou");
        set("exits", ([
                //"east" : __DIR__"libailou",
                "east" : __DIR__"shupu",
                "south" : __DIR__"beidajie1",
                "west" : __DIR__"yaopu",
                "north" : __DIR__"jzbeimen",
        ]));
        set("objects", ([
                "/d/beijing/npc/liumang" : 1,
        ]));
        set("coor/x", -7100);
	set("coor/y", -2030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}