#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "���۱���");
        set("long", @LONG
�����������µĴ��۱�����й������������������Ҹ������⡢
����������һȺ����С���������ڷ���ǰ�ĵ����о���������������
��������һ�����ӷ����黨ǳЦ�����ݣ����˶�ʱ���𼸷�����֮
�С���߾�����һ�Ӷ�ɮ�������룬�������ֳֽ䵶���ƺ���Ѳ��
��ɮ�ˡ�
LONG );
        set("exits", ([
                "southdown" : __DIR__"guangchang2",
        ]));
        set("valid_startroom",1);
        set("book_count",1);
        set("objects",([
                CLASS_D("shaolin") + "/dao-zheng" : 1,
                CLASS_D("shaolin") + "/first" : 1,
                __DIR__"npc/xiang-ke" : 1,
        ]));
        setup();
        "/clone/board/bonze_b"->foo();
}

void init()
{
        set_temp("ketou_times", 50, this_player());
        add_action("do_ketou", "ketou");
}

int do_ketou()
{
        object me, ob;

        me = this_player();

        if( query("jing", me)<30 )
                return notify_fail("ͻȻ��е�һ���㱣����������Լ�����ͷ��\n");

        if( query_temp("ketou_times", me) == 0 )
        {
                message_vision(HIR "\n$N" HIR "��ͷ�ĵ����˹�ȥ��\n" NOR, me);
                set_temp("ketou_times", random(50), me);
                me->unconcious();
                return 1;
        }

        addn_temp("ketou_times", -1, me);

        message_vision(CYN "$N" CYN "�ϵع�������������������"
                       "ǰ��ͷ��\n" NOR, me);

        if (random(100) == 37 &&
            ! present("silk", me) &&
            query("book_count") >= 1)
        {
                addn("book_count", -1);
                ob=new("/clone/book/book-silk");
                ob->move("/d/shaolin/dxbdian");
                tell_object(me, HIM "\nͻȻ����ǰ��ž����һ����"
                                "��һ����Ƥ�ߴ������ı��\n" NOR);
        }

        if ((int)me->query_skill("force", 1) >= 30 &&
            (int)me->query_skill("force", 1) <= 100 &&
            present("silk", me) )
        {
                me->receive_damage("jing", 20);
                if (me->can_improve_skill("force"))
                        me->improve_skill("force",1+random(query("con", me)));
                if (random(5) == 0)
                tell_object(me, HIY "ڤڤ֮�У����ƺ����÷�����"
                                "�㲦�����ڹ���������ѡ�\n" NOR);
        }
        return 1;

}

int valid_leave(object me, string dir)
{
        if( query_temp("ketou_times", me) >= 0)delete_temp("ketou_times", me);

        return ::valid_leave();
}
