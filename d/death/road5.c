#include <ansi.h>
inherit ROOM;
 
void create()
{
        set("short", HIR "�����Ŵ����" NOR);
       set("long", HIR @LONG

                    ��     ��     ��     ��

    ������һ����ɭɭ��·�ϣ�ŨŨ��������������ܣ�������Զ��
����ɢȥ�Ƶģ�����·ǰ��ֻ�������ǵļ�յ��������


LONG NOR );
        set("exits", ([
                "north" : "/d/death/road6",
                "south" : "/d/death/road4",
        ]));

        set("no_fight", 1);
        set("no_sleep_room", 1);

        setup();
}

int valid_leave(object me, string dir)
{
        int i;
        if (dir == "north") {
                i=query_temp("long_road", me);
                i = i + 1;
                if (i == 35) {
                delete_temp("long_road", me);
                return 1;
                }
                else {
                        set_temp("long_road", i, me);
                        return notify_fail( HIB "\n���������������������ܾ�ɫ��Ȼ��û�б䡭��\n" NOR);
                }
        }
        else {
        if (dir == "south") {
                delete_temp("long_road", me);
                return 1;
                }
        return 1;
        }
}
