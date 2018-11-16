// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short", "����");
        set ("long", @LONG
�ߵ����һ�������ûʵĴ�լԺ�����������ǰ����ͷ�ߴ��
ʯʨ����ס�˴������࣬���������������������Ϲ�������������
д�š������򸮡��ĸ�������֡�ֻ��������������������վ�ڴ���
���࣬�����ע�������ˡ�
LONG);
        set("outdoors", "jingzhou");
        set("region", "jingzhou");
        set("exits", ([
                "north"  : __DIR__"wan_dating",
                "south"  : __DIR__"xidajie1",
        ]));

        set("objects", ([
                "/d/shaolin/npc/shang2" : 2,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -7110);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        if( dir == "north" &&
           objectp(present("jia ding", environment(me))) )
                return notify_fail(CYN "�Ҷ���ס�������ʲô��������Ȼ����"
                                   "��ү�ĸ�ۡ�����Ҵ���\n" NOR);
        return ::valid_leave(me, dir);
}