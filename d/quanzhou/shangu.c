// Room: /d/quanzhou/shangu.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "ɽ��");
        set("long", @LONG
������������ɽ����ˬ��ɽ���У�������һ����Ժ����ǰ�Ķ���д
�ţ�

              ��������ʤ������ؼž���������

����һ��ʯ���������С�����硣��Χ���ɴ�أ��������־��¡���
����Ħ��̵����ڡ�Ħ����ǲ�˹��Ħ�ᴴ�����ڽ̣��ֳ�Ϊ�����̡���
Ħ���ͽ��Ҫʳ�أ������˴�Ϊ��ʳ����ħ������֮Ϊ��ħ�̡���
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "enter" : __DIR__"caoan",
                "north" : __DIR__"shisun",
        ]));
	set("coor/x", -930);
	set("coor/y", -7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}