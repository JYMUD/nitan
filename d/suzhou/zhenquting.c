// Room: /d/suzhou/zhenquting.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "��Ȥͤ");
        set("long", @LONG
��Ȥͤ�ڸ߸�����������д�ġ���Ȥ����һ�顣ͤ��װ�ξ��½��
�Ի͡����ܡ�Χ����ȹ���ϵ�̵��������ͼ��Ω��ΩФ���ڴ˿���
����ȫ԰��ɫ��
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"wenmeige",
                "northwest" : __DIR__"yanyutang",
        ]));
        set("objects", ([
                "/clone/npc/walker"  : 1,
        ]));
	set("coor/x", 1140);
	set("coor/y", -1080);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}