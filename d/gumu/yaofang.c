// Roo: /d/guu/yaofang.c
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"ҩ��"NOR);
        set("long", @LONG
������һ��ʯ�ң���Χ�Ļ�ѽ�ʯ���յĵƻ�ͨ����ʯ���������
�˺ܶ�ƿƿ�޹ޣ����涼�����˱�ǩ��һƿƿ��佬����Ĺ�����Ƴɺ�
���ڴ˴������ܿ���������Ĺ��������æµ�ĸɻ
LONG        );
        set("exits", ([
                "north" : __DIR__"mudao10",
        ]));
        set("objects", ([
                __DIR__"obj/yaolu" : 1,
                __DIR__"npc/baiyi_yaofang" : 1,
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3220);
        set("coor/y", -30);
        set("coor/z", 90);
        setup();
}

//void init()
//{
//        add_action("do_make","make");
//        add_action("do_make","huo");
//}

int do_make(string arg)
{
        object ob, name1, me = this_player();
        int exp,pot,score;

        ob= present("feng mi", me);
        name1=query("id", me);
        if (me->is_busy() || me->is_fighting())
                return notify_fail("����æ���ء�\n");
        if ( arg =="jiang")
        {
                if( !query_temp("gm_job1", me) )
                        return notify_fail("�㻹ûȥ�����أ���ô������佬��\n");
                if (!objectp(present("feng mi", me)))
                        return notify_fail("����ʲô���Ƴ���佬��\n");
                if( query_temp("gm/make", ob) != name1 )
                        return notify_fail("����ۺ�����������İɣ�\n");
                message_vision(HIY"$N��ϸ�ؽ����۵��;��ȣ��Ƴ���佬�����ڼ��ϡ�\n"NOR,me);
                delete_temp("gm_job1", me);
                exp=40+random(20);
                addn("combat_exp", exp, me);
                pot= 10+random(10);
                addn("potential", pot, me);
                score=2+random(5);
                addn("score", score, me);
                call_out("destroying", 1, ob);
                tell_object(me,HIW"��Ϊ�������������ˣ�" + chinese_number(exp) + "��ʵս����" + chinese_number(pot) + "��Ǳ��" + chinese_number(score) + "�㽭��������\n"NOR);
                return 1;
        }
        return notify_fail("����ѷ����Ƴ�ʲô����\n");
}

void destroying(object ob)
{
        destruct(ob);
        return;
}
