// Room: /d/luoyang/road8.c
// Last modified by winder 2002.11.11

inherit ROOM;

void create()
{
        set("short", "��ٵ�");
        set("long", @LONG
����һ��������ֱ�Ĺٵ�������ݵ���ʮ���ۡ����ڳ��공��
�ۣ�·����������ĳ��ޡ���ѩ��������Ţ������������ͷ���ַ۳���
��������ͨ��֬��֮�������ݣ�����������ͨ�������ǡ�
LONG);
        set("exits", ([  /*  sizeof()  ==  2  */
                "east"      : "/d/city/ximenroad",
                "northwest" : __DIR__"road9",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6860);
	set("coor/y", 2130);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}