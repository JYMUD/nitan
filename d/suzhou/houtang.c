#include <room.h>
inherit ROOM;

void create()
{
        set("short", "����");
        set("long", @long
�������鳡�ĺ��ã�������һ�����Ӻ�һ�Ű�����ǽ�ϵĴ�������
�ţ�ǽ�Ϲ���һ���껭(picture)��
long);
        set("item_desc", ([
                "picture" : "��һ��Ѱ��ũ�ҹ���ʱ�����껭��\n",
        ]));
        set("exits", ([
                "out" : __DIR__"shuchang",
        ]));
        create_door("out", "С��", "enter", DOOR_CLOSED);
	set("coor/x", 1089);
	set("coor/y", -1051);
	set("coor/z", -1);
	setup();
}
void init()
{
        add_action("do_jie","jie");
        add_action("do_jump","jump");
}
        
int do_jie(string arg)
{
        object me=this_player();
        
        if (!arg) return 0;
        if (arg !="picture") return 0;
        if (arg=="picture")
        {
                write("��ҿ��껭������ǽ���и�����ǡ��������һ���ˣ����̲�ס����(jump)��ȥ��\n");
                set_temp("marks/��1", 1, me);
                return 1;
        }
}
int do_jump(string arg)
{
        object me;
        me=this_player();
        if( query_temp("marks/��1", me) )
        {
                message("vision", me->name() + "�����ǽ�ϵĶ���������ȥ��ֻ���ġ�ƹ����һ���졣\n", environment(me), ({me}) );
                me->move(__DIR__"szyunhe");
                message("vision", me->name() + "ͻȻ�������ˤ��������\n", environment(me), ({me}) );
                delete_temp("marks/��1", me);
                return 1;
        }
}