// This program is a part of NT MudLIB
#include <ansi.h>

inherit ROOM;
void create()
{
        set("short", "�ݵ�");
        set("long",@LONG
����һƬ�տ��Ĳݵأ����ܳ������Ӳݣ��ƺ������Ѿ��ܾ�û��
�������ˣ�������Ұ�ĵط���������в��ɵ�����һ˿���⡣����
���߾���һ������׵ľ����ˡ�
LONG
);
        set("outdoors","changan");
        set("exits", ([
                "west" :__DIR__"boshulin10",
                "east" :__DIR__"jueya",
        ]));
        set("item_desc", ([
                "�ݵ�" : "����Ƭ�ݵص��м䣬���ƺ��е�һЩ������\n",
        ]));
        set("coor/x", -10620);
	set("coor/y", 1980);
	set("coor/z", 0);
	setup();
}

void init()
{
        if (interactive(this_player()))
                add_action("do_kill","kill");
}

void check(object me,object ob)
{
        if (!me || !ob)
                return;

        if (!present(me,this_object())
        ||  !present(ob,this_object()))
                return;

        if( query("jiali", ob) != (ob->query_skill("force")/2 )
         || query("jiali", me) != (me->query_skill("force")/2) )
                return;

        if( query("max_neili", me)<100000
         || query("max_neili", ob)<100000 )
                return;

        if( query("max_neili", ob)<query("max_neili", me) )
        {
                message_vision("$n��$N����һ�����±ߵ�����ȥ��\n",me,ob);
                ob->move(__DIR__"qinhuang/gudi.c");
                set_temp("killer", 1, ob);
                ob->unconcious();
        }
        else
        {
                message_vision("$N��$n����һ�����±ߵ�����ȥ��\n",me,ob);
                me->move(__DIR__"qinhuang/gudi.c");
                set_temp("killer", 1, me);
                me->unconcious();
        }
}

int do_kill(string arg)
{
        object ob, me=this_player();

        if (!arg || arg=="")   return 0;
        if (ob=present(arg, this_object()))
        {
                message_vision( HIY "$N��$nһ���棬������ɱ��������\n" NOR ,me,ob);
                if (userp(ob) &&
                    query("jiali", ob) == (ob->query_skill("force")/2) && 
                    query("jiali", me) == (me->query_skill("force")/2) )
                {
                        remove_call_out("check");
                        call_out("check",random(20)+5,me,ob);
                }
        }
        return 0;
}

