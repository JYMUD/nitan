// Room: /d/luoyang/road10.c
// Last modified by winder 2002.11.11

inherit ROOM;

void create()
{
        set("short", "��ٵ�");
        set("long", @LONG
����һ��������ֱ�Ĺٵ�������ݵ���ʮ���ۡ���·���ߣ���һ
���Ÿ���������֮�⣬����һƬƬ��ũ���ˡ�����ﴫ��ũ�˵ĺ��ţ�
��ͷ��ţ���е�ſ���š�
LONG);
        set("exits", ([  /*  sizeof()  ==  2  */
                "east" : __DIR__"road9",
                "west" : __DIR__"road11",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6880);
	set("coor/y", 2140);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}