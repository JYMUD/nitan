// Code of JHSH
// Room: /d/mingjiao/luanshidui.c
// Zhangchi 3/00

#include <ansi.h>
inherit ROOM;

int start_wa(object me);
int check_busy(object me);

void create()
{
        set("short",HIR "����" NOR);
        set("long", @LONG
[1��37m������һ����ͺͺ��Сɽ������ʲô������ľҲû�С���ϸһ
��������ɽ����Χ��Щ������Ĵ�ʯͷ������ǹ�����ʢ�����ڽ���
��ʯ�����̽����õı������������ֿ�ʯ������ɣ���֮Ѱ��������
��ı�����Ϊ��̣�������[2��37��0m
LONG );
        set("exits", ([ /* sizeof() == 1 */
          "east" : __DIR__"rjqmenlou1",
        ]));

        set("invalid_startroom", 1);
        set("wa_times",15);
        setup();

}

void init()
{
        add_action("do_save", "save");
        add_action("do_wa", "excavate");
        add_action("do_wa", "dig");
}

int do_save(string arg)
{
        write("���ﲢ��һ��ط�,�����������¼��\n");
        return 1;
}

int do_wa(string arg)
{
        object qiao,me;

        me = this_player();

        if( me->is_busy() || query_temp("pending/job_busy", me) )
                return notify_fail("����æ���ء�\n");

        if( query("mingjiao/job", me) != "jin_caikuang")
                return notify_fail("���ﲻ��������ڣ�\n");

        if( present("wujin kuangshi", me) )
                return notify_fail("���Ѿ���һ���ʯ��ʵ�ڱ������ڶ����ˡ�\n");

        if( !objectp(qiao = present("tie qiao", me)) )
                 return notify_fail("��û�г��ֵĹ��ߣ��޷���������\n");

        if( query("jing", me) < 50 || query("qi", me) < 30 )
                return notify_fail("���Ѿ���ƣ�����ˣ�\n");

        if( query("wa_times") > 0 )
        {
                message_vision("$N�������������ϣ���׼��һ���������ڽ�����ʯ������������ȥ��\n",me);
                set_temp("pending/job_busy", 1, me);
                call_out("start_wa", 10, me);
                me->start_busy( (: check_busy :) );
        }
        else
                tell_object(me,"��ʯ�ƺ������ڹ��ˡ�\n");

        return 1;

}

int check_busy(object me)
{
        if (query_temp("pending/job_busy", me)) return 1;
        return 0;
}

int start_wa(object me)
{
        object kuangshi;

        if(query("jingli", me)>90 && random(3)==1)
        {
                message_vision("$N��һС��"+HIB"�ڽ��ʯ"NOR+"���˳����������ϡ�\n",me);
                addn("wa_times",-1);
                kuangshi=new(__DIR__"obj/kuangshi");
                if (! kuangshi->move(me))
                        kuangshi->move(environment(me));
                addn("jing",-20, me);
                addn("qi",-30, me);
        }
        else
        {
                tell_object(me,HIR"��ͻȻ�����������ã�����Ҳ�޷����ǿ��ʯ�ڳ���\n"NOR);
                addn("jing",-20, me);
                addn("qi",-30, me);
        }

        delete_temp("pending/job_busy", me);
        return 1;

}

int valid_leave(object me, string dir)
{
        object ob;

        if (dir == "northeast" && query_temp("job_busy", me) )
               return notify_fail("����æ���ڿ��أ�\n");

        return ::valid_leave(me, dir);
}