// search.c

// ��һ��ROOM��Ѱ����Ʒ
// ����SCORE�Ĳ�ͬ��Ѱ�ҵĶ���ͼ���Ҳ��ͬ��
// ROOM�������û���������search_objects����������ָ��������
// �������е�ĳЩ��Ʒ���������ʡ�Ҳ��������no_search ָ����
// ����������С��ĳһ��ֵ�Ͳ����ҵ��������ֵΪ�㣬��ô����
// ���ĸ��˵Ľ��������������Ʒ�����Բ������ҵ�������������
// �����������÷��ݵ���ʽ����Ҳ��������ʱ���������Ǳ�����ʾ
// ���ݵĻ�������ʱ������ʾ�Ƿ�����ʱ����Ѱ��Ϣ��

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object env;

        seteuid(getuid());

        env = environment(me);

        if (me->is_busy())
                return notify_fail("����æ������ͷ���������Ұɣ�\n");

        if (me->is_fighting())
                return notify_fail("һ�ߴ��һ���Ҷ�����ֻ�������ó�����\n");

        if( query("no_search", env) == "all" )
                return notify_fail("��ط������Ҳ���ʲô����...\n");

        set_temp("pending/searching", 1, me);
        me->set_short_desc("���ڶ���������");
        message("vision", me->name() + "���������������ʲô�أ�\n",
                environment(me), ({ me }));
        tell_object(me, "�㿪ʼ����������������û��ʲôֵǮ�Ķ�����\n");
        me->start_busy(bind((:call_other, __FILE__, "searching" :), me),
                       bind((:call_other, __FILE__, "halt_searching" :), me));
        return 1;
}

mapping query_default_objects(object me)
{
        int score=query("score", me);

        if( !query("outdoors", environment(me)) )
                return ([ ]);

        if (score < 100)
                return ([
                  "/clone/money/coin"       : 100000,
                  "/clone/money/silver"     : 20000,
                  "/clone/misc/jinchuang"   : 20000,
                  "/clone/weapon/dagger"    : 20000,
                  "/d/city/npc/obj/jiudai"  : 10000,
                  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
        if (score < 400)
                return ([
                  "/clone/money/coin"       : 10000,
                  "/clone/money/silver"     : 15000,
                  "/clone/misc/jinchuang"   : 15000,
                  "/clone/weapon/dagger"    : 8000,
                  "/d/city/npc/obj/jiudai"  : 8000,
                  "/clone/weapon/duanjian"  : 3000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
        if (score < 2000)
                return ([
                  "/clone/money/coin"       : 5000,
                  "/clone/money/silver"     : 10000,
                  "/clone/misc/jinchuang"   : 25000,
                  "/clone/weapon/dagger"    : 20000,
                  "/d/city/npc/obj/jiudai"  : 10000,
                  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
        if (score < 10000)
                return ([
                  "/clone/money/silver"     : 10000,
                  "/clone/misc/jinchuang"   : 20000,
                  "/clone/weapon/dagger"    : 10000,
                  "/d/city/npc/obj/jiudai"  : 5000,
                  "/clone/weapon/duanjian"  : 6000,
                  "/clone/weapon/changjian" : 4000,
                  "/clone/weapon/blade"     : 4000,
                  "/clone/weapon/gangzhang" : 4000,
                  "/clone/cloth/tiejia"     : 3500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
        else
                return ([
                  "/clone/weapon/changjian" : 8000,
                  "/clone/weapon/blade"     : 8000,
                  "/clone/weapon/gangzhang" : 8000,
                  "/clone/cloth/tiejia"     : 2500,
                  "/d/item/obj/chanhs"      : 1000,
                  "/d/item/obj/jingtie"     : 1000, ]);
}

//object found(object me, object env)
mixed found(object me, object env)
{
        mixed  *st;
        mapping cs, ns;
        mapping os;
        object  ob, task_ob;
        mixed   sob;
        int sum;
        int i;

        os = query_default_objects(me);
        if( mapp(cs=query_temp("search_objects", env)) )
                os += cs;

        if( mapp(cs=query("search_objects", env)) )
                os += cs;

        sum=query("score", me)>>7;
        if( mapp(ns=query_temp("no_search", env)) )
        {
                st = keys(ns);
                for (i = 0; i < sizeof(st); i++)
                {
                        if (! ns[st[i]] || sum < ns[st[i]])
                                // can not search this object or
                                // need score
                                map_delete(os, st[i]);
                }
        }

        if( mapp(ns=query("no_search", env)) )
        {
                st = keys(ns);
                for (i = 0; i < sizeof(st); i++)
                {
                        if (! ns[st[i]] || sum < ns[st[i]])
                                // can not search this object or
                                // need score
                                map_delete(os, st[i]);
                }
        }

        if (sum > 30) sum = 30;
        if( query_temp("been/searched", env)>0 )
                sum-=query_temp("been/searched", env);
        if (random(sum + 100) < 93)
                return 0;

        st = keys(os);
        sum = 0;
        for (i = 0; i < sizeof(st); i++)
        {
                if (! intp(os[st[i]]))
                        os[st[i]] = 0;
                sum += os[st[i]];
        }

        if (! sum) return 0;
        sum = random(sum);
        for (i = 0; i < sizeof(st); i++)
        {
                if (sum < os[st[i]])
                {
                        if (stringp(st[i]))
                        {
                                if (objectp(task_ob = get_object(st[i])) &&
                                    sscanf(st[i], "/task/obj/%*s"))
                                {
                                        object boss;

                                        if( !random(5) )
                                                ob = task_ob;
                                        else {
                                                FUBEN_D->enter_fuben(me, "ultra");
                                                boss = new("/maze/ultra/npc/yaowang");
                                                boss->move(get_object("/f/ultra/"+query("id", me)+"/maze/exit"));
                                                task_ob->move(boss);
                                                get_object("/f/ultra/"+query("id", me)+"/maze")->set_display_map(1);
                                                get_object("/f/ultra/"+query("id", me)+"/maze")->set_maze_boss(boss);
                                                tell_object(me, "�ף���������и����ε��Թ�����˺�·��������Թ����š�\n");
                                                delete_temp("search_objects", env); 
                                                return 1;
                                        }
                                        delete_temp("search_objects", env);
                                }
                                else
                                        ob = new(st[i]);
                        }
                        else
                        if (objectp(st[i]))
                                ob = st[i];
                        else
                        if (functionp(st[i]))
                                ob = evaluate(st[i], me, env);

                        if (! objectp(ob))
                                return 0;

                        addn_temp("been/searched", 15, env);
                        return ob;
                }
                sum -= os[st[i]];
        }

        return 0;
}

int searching(object me)
{
        object env;
        mixed ob;

        env = environment(me);
        if( me->add_temp("pending/searching",1)>6 )
        {
                tell_object(me, "���˰��죬�㻹��һ������ֻ���ȷ����ˡ�\n");
                message("vision", me->name() + "̾�˿��������˷�����\n", env, ({ me }));
                me->set_short_desc(0);
                return 0;
        }

        if( query("qi", me)<30 || 
            query("jing", me)<30 )
        {
                tell_object(me, "��ʵ��̫ƣ���ˣ�ֻ�÷�����Ѱ�ҡ�\n");
                message("vision", me->name() + "̾�˿�����һ�����ݡ�\n",
                        env, ({ me }));
                me->set_short_desc(0);
                return 0;
        }

        me->receive_damage("qi", 30);
        me->receive_damage("jing", 30);

        ob = found(me, env);
        if (intp(ob) && ob > 0)
        {
                me->set_short_desc(0);
                return 0;
        }
        if (objectp(ob))
        {
                if( query("base_unit", ob) )
                        ob->set_amount(random(5) + 1);
                tell_object(me,HIC"��ͻȻ������һ"+query("unit", ob)+
                                ob->name() + HIC "��\n");
                message("visoin", me->name() + "ͻȻ����������֪���ӵ�"
                        "�ϼ�����ʲô������ü����Ц�ġ�\n", env, ({ me }));
                if (! ob->move(me, 1))
                {
                        tell_object(me, "��ϧ" + ob->name() + "������"
                                    "˵̫���ˣ���ֻ���ȷ��ڵ��ϡ�\n");
                }
                delete_temp("pending/searching", me);
                addn("score", 1, me);
                me->set_short_desc(0);
                return 0;
        } else
        {
                message_vision(random(2) ? "$N�������������ĵ�����\n"
                                         : "$Nʱ���������ڵ��ϲ���ʲô������\n",
                               me);
                return 1;
        }
}

int halt_searching(object me)
{
        object env;

        env = environment(me);
        delete_temp("pending/searching", me);
        tell_object(me, "�������Ѱ�ҡ�\n");
        message("vision", me->name() + "��չ��һ������̾�˿�����\n", env, ({ me }));
        me->set_short_desc(0);
        return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: search

�ڵ���Ѱ�Ҷ��������ҵ�ʲô�أ�ֻ�����֪����ĳЩ�ط��ܹ��ҵ�
�ö����������󲿷ֵط�ֻ���ҵ�һЩ��ͨ�Ķ�����������ҵ��˶�
������Ľ�������������˶�����һ�㡣

HELP );
        return 1;
}
