inherit ROOM;

void create()
{
        set("short", "���ϴ�ϷԺ");
        set("long", @LONG
ϷԺ����һ���߸ߵ�Ϸ̨��̨��һЩ�����Ϲ�ױ���ˣ�����Ϸ������
�ŵ��ߣ��������㵸������ѽѽ�ĳ����й��Ĺ��⾩�磬̨���кü�����
�ӣ�������Ϸ�ԣ�Ʊ�ѣ������²����Ŀ���̨�ϵı��ݣ������������
��סվ���������һ�����á���
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"houtai",
                  "west" : __DIR__"sroad4",
        ]));
        set("objects", ([
                "/d/beijing/npc/guanzhong" : 4,
                "/d/beijing/npc/xizi2" : 1,
                "/d/beijing/npc/xizi3" : 1,
        ]));
	set("coor/x", -6980);
	set("coor/y", 2140);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}