#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�Ƕ���");
        set("long", @LONG
���Ÿ߿��������Ǻ�֮�ϣ����ƷǷ���վ��������������ȥ��һ����
������Ļ��Ǻӽ�������Χ�ڵ��У������Ժ�������ͣ��������ֺܼ�̡�
���ϳ�ˮ������������Ϣ�����µĻ��Ǻ�ˮ�峺���ף�ʱ������Ծ��
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"dongdoor",
                //"eastdown" : __DIR__"guandaoe1",
                "eastdown" : __DIR__"road2",
        ]));

	set("coor/x", -6920);
	set("coor/y", 2150);
	set("coor/z", 0);
	setup();
        //replace_program(ROOM);
}

void init()
{
        object me;
        object ob;

        if( interactive(me = this_player()) && !me->is_fighting() )
        {
                if( query_temp("juxianzhuang_step", me) == 11 )
                {
                        ob = new("/maze/juxianzhuang/npc/qiaofeng");
                        ob->move(environment(me));
                        message_vision(HIW "$N���˹������������һ������\n", ob);
                }
        }
}