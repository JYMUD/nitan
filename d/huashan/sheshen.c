// sheshenya.c

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����һ�μ�խ���յ�ɽ�£�����������ƣ�����Ԩ���޵ס��粻
С�ģ�һʧ�����ȥ��ֻ������ͷ���Ҳ����������и�Сɽ��(dong)��
LONG );
        set("exits", ([ /* sizeof() == 1 */
                "eastdown" : __DIR__"canglong",
        ]));
        set("item_desc", ([
                "dong" : "����������ʯ�ڵ�С�����ں����Ĳ�֪�ж��\n",
        ]));
        set("outdoors", "huashan" );

        setup();
}

void init()
{
        object me = this_player();
        add_action("do_enter", "enter");
        add_action("do_enter", "zuan");
        if( query_temp("xunshan", me) )
                set_temp("xunshan/sheshen", 1, me);
        return;
}

int do_enter(string arg)
{
        object me;
        mapping fam;

        me = this_player();
        if( !arg || arg=="" ) return 0;
        if( arg=="dong" )
        {
                if( (fam=query("family", me)) && fam["family_name"] == "ؤ��" )
                {
                        message("vision",
                                me->name() + "����ؤ�����ǹ���һ�������������˽�ȥ��",
                                environment(me), ({me}) );
                        me->move("/d/gaibang/undertre");
                        message("vision",
                                me->name() + "�Ӷ������˽�����\n",
                                environment(me), ({me}) );
                                return 1;
                } else  
                        return notify_fail("��ôС�Ķ�������ý�ȥ��\n");
        }
}

