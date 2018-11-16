// /d/shenlong/shulin3.c
// Last Modified by winder on Jul. 12 2002

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "С����");
        set("long", @LONG
�����һƬС���֣������м���һС��յء��յ��ϳ��˿���
���⻹����һЩ��ͬ��С��ʯ�飬��Щʯ����涼�ȽϹ⻬�ƺ���
������Ϊ����һ̧ͷ���ֿյ����ܵ������϶�û����Ƥ��
LONG );

        set("exits", ([
                "southeast" : __DIR__"luanshi",
        ]));
        set("outdoors", "shenlong");
        set("no_clean_up", 0);
        setup();
}

void init()
{
        add_action("do_kick", "kick");
        add_action("do_kick", "ti");
        add_action("do_pick", "take");
        add_action("do_pick", "pick");
}

int do_pick(string arg)
{
        object me = this_player();

        if( !arg || !(arg == "shikuai" || arg == "shitou") )
                return notify_fail("ʲô��\n");

        if( query_temp("sg/leg", me)>1 )
                return notify_fail("�����ϰ�����ô��ʯ�顣\n");

        addn("qi", 200/(1+me->query_str()), me);
        if( random(query_temp("sg/shikuai", me))<3 )
        {
                message_vision("$N����һ��ʯͷ�����˵������ҡ��ҡͷ�������ڵ��ϡ�\n", me);
                addn_temp("sg/shikuai", 1, me);
                return 1;
        }
        delete_temp("sg/shikuai", me);
        if( !query_temp("sg/leg", me) )
        {
                message_vision("$N����һ��ʯͷ�����˵��������������������ϡ�\n", me);
                addn_temp("sg/leg", 1, me);
                addn_temp("apply/dodge", -10, me);
                return 1;
        }
        if( query_temp("sg/leg", me)>0 )
        {
                message_vision("$N����һ��ʯͷ�����˵��������������������ϡ�\n", me);
                addn_temp("apply/dodge", -10, me);
                addn_temp("sg/leg", 1, me);
        }
        return 1;
}

int do_kick(string arg)
{
        object me = this_player();

        if( !arg || !(arg == "tree" || arg == "shu") )
                return notify_fail("ʲô��\n");

        message_vision("$N�ڿն���˫��������Χ���ɡ�\n", me);

        me->receive_damage("jing", 15, "�����ʴ�����");
        me->receive_damage("qi", 25, "��������");
//        me->improve_skill("kick", random(me->query_int()));

        if( query_temp("sg/leg", me) == 2 )
        {
                me->receive_damage("jing", 10, "�����ʴ�����");
                me->receive_damage("qi", 20, "��������");
                me->improve_skill("dodge", random(me->query_int()));
                return 1;
        }
        if( query_temp("sg/leg", me) == 1 )
        {
                me->receive_damage("jing", 8, "�����ʴ�����");
                me->receive_damage("qi", 16, "��������");
                me->improve_skill("dodge", random(me->query_int() / 2));
                return 1;
        }
        me->improve_skill("dodge", random(me->query_int() / 5));
        return 1;
}

int valid_leave(object me, string dir)
{
        if( query_temp("sg/leg", me) )
        {
                addn_temp("apply/dodge",query_temp("sg/leg",  me)*10, me);
                message_vision("$N���˰󣬽����ϵ�ʯ������һ�ߡ�\n", me);
                delete_temp("sg/leg", me);
                me->start_busy(1);
        }

        return ::valid_leave(me, dir);
}

