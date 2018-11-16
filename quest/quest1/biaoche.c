// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>
inherit ITEM;

mapping default_dirs = ([
        "north"     : "����",
        "south"     : "����",
        "east"      : "����",
        "west"      : "����",
        "northup"   : "����",
        "southup"   : "�ϱ�",
        "eastup"    : "����",
        "westup"    : "����",
        "northdown" : "����",
        "southdown" : "�ϱ�",
        "eastdown"  : "����",
        "westdown"  : "����",
        "northeast" : "����",
        "northwest" : "����",
        "southeast" : "����",
        "southwest" : "����",
        "up"        : "����",
        "down"      : "����",
        "enter"     : "����",
        "out"       : "����",
]);

void create()
{       
        seteuid(getuid());
        set_name(HIW "�ڳ�" NOR, ({ "biao che", "cart", "che" }));
        set_weight(300000);
        set("no_get", 1);
        set("unit", "��");
        set("value", 0);
        set("long", 
                HIW "һ�������ھֵ��ڳ���һ����ͷ��׼���ϳ�(drive)����ء�" NOR); 
        set("no_clean_up",1);
        setup();
        call_out("destroy1", 2, this_object());
}

void init()
{
        if( query("id", this_player()) == query("owner", this_object()) )
        {
                add_action("do_gan", "gan"); 
                add_action("do_gan", "drive");
        }
}

void start_escape_me()
{
        call_out("destroy2", (int)query("time"), this_object());
}

int destroy2(object ob)
{
        object me;
        if (objectp(ob))
        {
                /*
                message("channel:rumor", MAG "���ھִ��š�����" + query("owner_name") +
                        "���͵��ڳ�δ�����ڵִ�����ھ�������ǰȥ�ӹ��ڳ���\n" NOR, users());
                */
                tell_object(all_inventory(environment(ob)),
                            HIW "��Ȼ��ԶԶ����һȺ�ˣ�ԭ��������ͷ����ǰ���ˣ�Ϊ�׵���ʦ\n" +
                            "�������ﻹ��������������̵ģ�������ô��Ҳ��û��������ͷ\n" +
                            "����Ϊ���˸����ˣ������Ӱ���һ�ˣ���˵�꣬һ���˵�������\n" +
                            "�����ﳤ��ȥ��\n" NOR);

                remove_call_out("destroy1");
                remove_call_out("destroy2");

                me=present(query("owner", ob),environment(ob));
                if (objectp(me))
                {
                        delete_temp("apply/short", me);
                        delete_temp("quest_yunbiao/have_task", me);
                        set_temp("quest_yunbiao/finished_time", time(), me);
                }
                destruct(ob);
        }
        return 1;
}


int do_gan(string arg)
{        
        object me, ob, env, obj, robber, *killer;
        string item, dir, dest, target;
        int reward_exp, reward_pot, reward_score, flag, i;
        int lvl;

        mapping exit;
        me = this_player();
        ob = this_object();

        if (! arg) return notify_fail("��Ҫ��ʲô��\n");

        if( query("id", me) != query("owner", ob) )
                return notify_fail("��ϵĲ����Լ����ڳ��ɣ�\n"); 

        if (sscanf(arg, "%s to %s", item, dir) != 2 
        ||  item != "biao che" && item != "che")
                return notify_fail("ָ�gan �ڳ� to ���� \n");        
                        
        if (me->is_busy())
                return notify_fail("��������æ������\n");

        flag = 0;
        killer = all_inventory(environment(me));
        for (i = 0; i < sizeof(killer); i++)
        {
                if (objectp(killer[i]) 
                 && query("want_kill", killer[i]) == query("id", me) )
                flag = 1;
        }

        if (flag)   
                return notify_fail(CYN "�㻹���Ȱ���ǰ�ĵ��˽������˵�ɣ�\n" NOR);
        
        env = environment(me);
        if (! env) return notify_fail("��Ҫȥ���\n");

        if( !mapp(exit=query("exits", env)) || undefinedp(exit[dir]) )
                return notify_fail("����������ȥ��\n");
        
        dest = exit[dir];

        if (! (obj = find_object(dest)))
                call_other(dest, "???");
        if (! (obj = find_object(dest)))
                return notify_fail("����������ȥ��\n");

        if (! undefinedp(default_dirs[dir]))
                target = default_dirs[dir];
        else
                target=query("short", obj);

        message_vision(HIG "$N�����ڳ���" + target + "ʻȥ��\n" NOR, me);  
        
        if( file_name(obj) != query("file", ob) )
        {
                if (ob->move(obj) && me->move(obj)) 
                {
                        all_inventory(env)->follow_me(me, dir);
                        message_vision(HIG "$N�����ڳ�ʻ�˹�����\n" NOR, me);
                        lvl = me->query_skill("driving"); 
                        if (random(lvl + 100) < 50) 
                        me->start_busy(random(2) + 2);
                        else me->start_busy(1);
                        if (me->can_improve_skill("driving")) 
                                me->improve_skill("driving", 1); 
                }

                if( random(12)<2 && !query("no_fight", environment(ob)) )
                {
                        robber = new(__DIR__"robber");
                        set("want_kill",query("id",  me), robber);
                        robber->move(environment(ob));  
                        robber->kill_ob(me);
                        robber->check_me();  
                        me->start_busy(1);
                        robber->start_busy(1);
                }
        } else
        {
                reward_exp=query("combat_exp", me)/30000;
                reward_exp=reward_exp+query_temp("quest_yunbiao/bonus", me)*20;
                reward_exp = reward_exp / 2 + random(reward_exp);
                if (reward_exp > 500) reward_exp = 500;
#ifdef DB_SAVE
                if (MEMBER_D->is_double_reward(me)) 
                        reward_exp *= 2;
#endif
                reward_pot = reward_exp;
                reward_score = reward_exp / 40;
                /*
                message("channel:rumor",HIM"���ھִ��š�"+query("name", me)+
                        "���͵��ڳ�����ǧ����࣬����˳���ִ\n" NOR,
                        users());
                */
                tell_object(me, HIW "�ڴ˴�������������" +
                            CHINESE_D->chinese_number(reward_exp) + "��ʵս���顢" +
                            CHINESE_D->chinese_number(reward_pot) + "��Ǳ�ܼ�\n" +
                            CHINESE_D->chinese_number(reward_score) + "���ۺ����۽�����\n" NOR);

                addn("quest_yunbiao/reward_exp", reward_exp, me);
                addn("quest_yunbiao/reward_potential", reward_pot, me);
                addn("combat_exp", reward_exp, me);
                addn("potential", reward_pot, me);
                addn("score", reward_score, me);

                delete_temp("quest_yunbiao/have_task", me);
                set_temp("quest_yunbiao/finished_time", time(), me);
                delete_temp("apply/short", me);
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        }   
        return 1;
}

int destroy1(object ob)
{
        object me;

        if (! objectp(ob) || ! environment(ob))
                return 1;

        if (objectp(ob) && ! present(query("owner", ob), environment(ob)))
        {
                me=find_player(query("owner", ob));
                if( !me)me=find_living(query("owner", ob));
                if (objectp(me))
                {
                        delete_temp("quest_yunbiao", me);
                        delete_temp("apply/short", me);
                }

                message("channel:rumor", HIB "���ھִ��š�" + query("owner_name") +
                        "���͵��ڳ��ڰ�·���˸����ˣ�\n" NOR, users());
                remove_call_out("destroy1");
                remove_call_out("destroy2");
                destruct(ob);
        } else
        {
                remove_call_out("destroy1");
                call_out("destroy1", 2, ob);
                return 1;
        }
}
