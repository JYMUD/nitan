#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "��԰");
        set("long", @LONG
�����������������������Ļ��һ���������ң������������滨
��ݺǻ������У���Ȼ�����и������ĵ����ֻ����ĵ����ģ��׵ģ���
�ģ��ϵģ��Ƶģ���ɫ���������涷�ޣ��������Σ������Ͱ�����һ���
Ϊ����������������Ҳ�����������ֻ���
LONG);
        set("outdoors", "luoyang");
        set("no_fight",1);
        set("no_clean_up", 0);
        set("exits", ([
                "west" : __DIR__"miaopu",
        ]));

	set("coor/x", -6970);
	set("coor/y", 2110);
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
        object ob, me;
        me = this_player();

        if( !query_temp("zhonghua", me) )
        {
                tell_object(me, "�����Ӷ�û�У������ֻ���\n"); 
                return 1;
        }

        if( query_temp("jiaoshui", me) == 1 )
        {
                tell_object(me, "���Ѿ��������������������ڿ��Խ�ˮ"
                                HIY "(jiaoshui)" NOR "��\n");
                return 1;
        }

        if( query("combat_exp", me)<8000 )
        {
                tell_object(me, "��ľ�����ǳ�������ȵ������߶��߶��ɡ�\n");
                return 1;
        }

        if( query("combat_exp", me)>30000 )
        {
                tell_object(me, "�������ݴ�Ų��ʺ��ֻ��˰ɡ�\n");
                return 1;
        }

        if( query("jing", me)<70 )
        {
                tell_object(me, "���Ѿ���ƣ���ˣ���Ϣһ���ٽ����ְɡ�\n");
                return 1;
        }

        message_vision(HIC "$N" HIC "��������Χ�úõ�������һ�£�ʹ��������"
                       "�ʺϻ���������\n" NOR, me); 
        set_temp("peiyu", 1, me);
        set_temp("jiaoshui", 1, me);
        me->start_busy(1 + random(3));
        return 1;
}

int do_jiaoshui()
{
        object me, ob;
        int exp, pot;

        me = this_player();

        if( query("jing", me)<70 )
        {
                tell_object(me, "���Ѿ���ƣ���ˣ���Ϣһ���ٽ����ְɡ�\n");
                return 1;
        }
        if (me->is_busy())
        {
                tell_object(me, "����æ���أ����ż���\n");
                return 1;
        }
        if( !query_temp("peiyu", me) == 1 )
        {
                tell_object(me, "��û�¸ɽ�ʲôˮ����\n");
                return 1;
        }
        if( query_temp("peiyu", me) == 2 )
        {
                if (random(14) < 4)
                {
                        switch (random(5))
                        {
                                case 1 : ob = new("/clone/megazine/obj/hmeigui"); break;
                                case 2 : ob = new("/d/changan/npc/obj/zi-luolan"); break;
                                case 3 : ob = new("/d/changan/npc/obj/bai-chahua"); break;
                                case 4 : ob = new("/d/changan/npc/obj/huang-meigui"); break;
                                case 0 : ob = new("/d/changan/npc/obj/lan-tiane"); break;
                        }

                        if (random(15) == 1)
                        {
                                if (random(10000) == 8)
                                {
                                        ob = new("/d/shenlong/obj/hua4");
                                        message_vision(HIY "$N" HIY "�ֳ���һ���������\n"
                                                       NOR, me);
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
                                message_vision(HIY "$N" HIY "�ֳ���һ����������\n" NOR,me);
                                return 1;
                        }
                        message_vision(HIC "$N" HIC "ʮ��С�ĵĸ�С���ｽ��һЩ"
                                       "ˮ��ͻȻһ��"+query("name", ob)+HIC
                                       "�ӿ���ð�˳�����\n" NOR, me);   
                        message_vision(HIY "$N" HIY "����ժ���������������\n" NOR, me);
                        ob->move(me, 1);
                        delete_temp("jiaoshui", me);
                        delete_temp("peiyu", me);
                        delete_temp("zhonghua", me);

                        exp = 10 + random(10);
                        pot = 2 + random(3);

                        if( query("potential", me)>me->query_potential_limit() )
                                pot = 1;

                        addn("combat_exp", exp, me);
                        me->improve_potential(pot);

                        tell_object(me, HIC "ͨ�����ѵ����������" + chinese_number(exp)
                                        + "�㾭���" + chinese_number(pot) + "��Ǳ�ܡ�\n"
                                        NOR);
                        return 1; 
                }
                message_vision(HIR "$N" HIR "���ֱ��ŵ�����ˮ����С���ｽˮ����"
                               "��ˮ����̫��ѻ������ˡ�\n", me); 
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
                message_vision(HIC "$N" HIC "����ˮ����С�ӽ���һЩˮ��\n" NOR, me); 
                addn("jing", -70, me);
                set_temp("peiyu", 2, me);
                me->start_busy(1 + random(2)); 
                return 1;
        }
}