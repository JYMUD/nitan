//Room: huiwenge.c

#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "���ĸ�");
        set("long", @LONG
����һ����֡����������һ���ŵ�����������������ط�
��һЩ���ᣬ���ڻ������ż��軨���ݲݣ�������䣬�������£���
��������Ŀ�������Ϳ��Կ���һ����ң�[1��34m         ��ɽ�о���Ϊ· 
        ѧ�����Ŀ�����[2��37��0m
LONG );

        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/yongtai-dadao3",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/shuchi" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10750);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}