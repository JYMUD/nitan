// Room: wuguanxiao.c
// Date: Feb.14 1998 by Java

inherit ROOM;
void create()
{
        set("short", "��ţ�������");
        set("long", @LONG
�����ǡ���ţ��ݡ�����������ʦ�����ɽ������¼��ܣ�������
���������ڹ��������мܣ�����ָ��������������
LONG );
        set("objects", ([
                __DIR__"npc/xiaofei" : 1,
        ]));
        set("no_fight",0);
        set("no_steal",1);
        set("no_beg",1);
        set("no_clean_up", 0);
        set("exits", ([
                "east" : __DIR__"wuguan",
        ]));
        set("coor/x", -15210);
	set("coor/y", -1800);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}