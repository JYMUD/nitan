// Room: /d/luoyang/road9.c
// Last modified by winder 2002.11.11

inherit ROOM;

void create()
{
        set("short", "��ٵ�");
        set("long", @LONG
����һ��������ֱ�Ĺٵ�������ݵ���ʮ���ۡ�·�ϳ������
�����ߵ�����Ⱦ��һ��ƻҡ��������ͨ��֬��֮�������ݣ���������
��ͨ�������ǡ�
LONG);
        set("exits", ([  /*  sizeof()  ==  2  */
                "west"      : __DIR__"road10",
                "southeast" : __DIR__"road8",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6870);
	set("coor/y", 2140);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}