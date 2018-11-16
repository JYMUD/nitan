// xiaohuayuan.c

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short",HIG "С��԰" NOR);
        set("long", @LONG
����һ��С��԰������ķ�������ʮ���ʺϸ��ֻ����������ر�
��һЩʮ������Ļ��֣�����Ҳ��������������������ֻ�(zhonghua)��
����������򵽻������ӡ�
LONG
        );

        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "south"  : __DIR__"huadian",
        ]));

        set("no_fight", 1);
	set("coor/x", 30);
	set("coor/y", 20);
	set("coor/z", 0);
	setup();
}

void init()
{
        add_action("do_jiaoshui", "jiaoshui");
        add_action("do_peiyu", "peiyu");
}

int do_peiyu()
{
        object ob,me;
        me = this_player();

        if( !query_temp("zhonghua", me) )
        {
                tell_object(me, HIR "�����Ӷ�û�У������ֻ���\n" NOR);
                return 1;
        }

        if( query_temp("jiaoshui", me) == 1 )
        {
                tell_object(me,HIR "���Ѿ��������������������ڿ��Խ�ˮ(jiaoshui)��\n" NOR);
                return 1;
        }

        if( query("combat_exp", me)>150000 || query("combat_exp", me)<10000 )
        {
                tell_object(me,HIR "�������ݴ�Ų��ʺ���С��԰�ֻ��ɣ�\n" NOR);
                return 1;
        }

        if( query("jing", me)<70 )
        {
                message_vision(HIR "$Nһ���������������ӣ���ô���ֻ��أ�\n" NOR,me);
                return 1;
        }

        message_vision("$N��������Χ�úõ�������һ�£�ʹ���������ʺϻ���������\n", me);
        set_temp("peiyu", 1, me);
        set_temp("jiaoshui", 1, me);
        me->start_busy(1 + random(3));
        return 1;
}

int do_jiaoshui()
{
        object me,ob;

        me = this_player();

        if( query("jing", me)<70 )
        {
                tell_object(me,HIR "����ɫ���ã�������Ϣ��Ϣ�ɡ�\n" NOR);
                return 1;
        }

        if (me->is_busy())
        {
                tell_object(me, HIR "����æ���أ����ż���\n" NOR);
                return 1;
        }

        if( !query_temp("peiyu", me) == 1 )
        {
                tell_object(me,HIR "������������û�¸ɽ�ʲôˮ����\n" NOR);
                return 1;
        }

        if( query_temp("peiyu", me) == 2 )
        {
                if (random(14) == 1)
                {
                        switch (random(5))
                        {
                                case 1 : ob = new("/d/changan/npc/obj/hmeigui"); break;
                                case 2 : ob = new("/d/changan/npc/obj/zi-luolan"); break;
                                case 3 : ob = new("/d/changan/npc/obj/bai-chahua"); break;
                                case 4 : ob = new("/d/changan/npc/obj/huang-meigui"); break;
                                case 0 : ob = new("/d/changan/npc/obj/lan-tiane"); break;
                        }

                        if (random(15) == 1)
                        {
                                if (random(10000) == 1)
                                {
                                        ob = new("/d/shenlong/obj/hua4");
                                        CHANNEL_D->do_channel(this_object(), "rumor",
                                                              query("name", me)+"��С��԰�ֳ�һ���������");
                                        message_vision(HIR "$N" HIR "�õ����������\n" NOR,me);
                                        ob->move(me, 1);
                                        delete_temp("jiaoshui", me);
                                        delete_temp("zhonghua", me);
                                        delete_temp("peiyu", me);
                                        addn("combat_exp", 500, me);
                                        me->improve_potential(100 + random(100));
                                        return 1;
                                }

                                ob = new("/d/shenlong/obj/hua2");
                                addn("combat_exp", 20+random(10), me);
                                me->improve_potential(20 + random(10));
                                CHANNEL_D->do_channel(this_object(), "rumor",
                                                      query("name", me)+"��С��԰�ֳ�һ����������");
                                return 1;
                        }

                        message_vision(HIC "$N" HIC "ʮ��С�ĵĸ�С���ｽ��һЩˮ��ͻȻ" +
                                       query("long", ob)+"�ӿ���ð�˳�����\n"NOR,me);
                        message_vision(HIR "$N" HIR "����ժ���������������\n" NOR,me);
                        ob->move(me, 1);
                        delete_temp("jiaoshui", me);
                        delete_temp("peiyu", me);
                        delete_temp("zhonghua", me);
                        addn("combat_exp", 20+random(10), me);
                        me->improve_potential(10 + random(10));
                        return 1;
                }

                message_vision(HIR "$N" HIR "���ֱ��ŵ�����ˮ����С���ｽˮ�����ˮ"
                               "����̫��ѻ������ˡ�\n",me);
                delete_temp("jiaoshui", me);
                delete_temp("zhonghua", me);
                delete_temp("peiyu", me);
                addn("jing", -50, me);
                addn("combat_exp", 3, me);
                me->improve_potential(2);
                return 1;
        }

        if( query_temp("jiaoshui", me) == 1 )
        {
                message_vision("$N����ˮ����С�ӽ���һЩˮ��\n",me);
                addn("jing", -70, me);
                set_temp("peiyu", 2, me);
                me->start_busy(1 + random(2));
                return 1;
        }
}