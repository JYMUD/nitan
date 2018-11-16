// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

int accept_fight(object ob)
{
        object me = this_object();
        object ob1, ob2, ob3, ob4, ob5, ob6;
        string msg1, msg2, msg3, msg4, msg5, msg6;
        int my_max_qi=query("max_qi", me);

        /*
        if (query_competitor() == ob)
                return 1;
        */

        if (query("qi") < query("eff_qi") * 2 / 3
            || query("jing") < query("eff_jing") * 2 / 3
            || query("neili") < query("max_neili") * 2 / 3)
        {
                // command("say �������е�ƣ�룬����Ъ�����˵��");
                return 0;
        }

        ob1 = present("tao genxian", environment(me));
        ob2 = present("tao ganxian", environment(me));
        ob3 = present("tao zhixian", environment(me));
        ob4 = present("tao yexian", environment(me));
        ob5 = present("tao huaxian", environment(me));
        ob6 = present("tao shixian", environment(me));

        msg1 = "�Ҹ���ͻȻ�ƽ�$N��һ����$N������׽ȥ��\n";
        msg2 = "�Ҹ���ͻȻ�ƽ�$N��һ����$N������׽ȥ��\n";
        msg3 = "��֦��ͻȻ�ƽ�$N��һ����$N�����׽ȥ��\n";
        msg4 = "��Ҷ��ͻȻ�ƽ�$N��һ����$N���ҽ�׽ȥ��\n";
        msg5 = "�һ���ͻȻ�ƽ�$N��һ����$N������׽ȥ��\n";
        msg6 = "��ʵ��ͻȻ�ƽ�$N��һ����$N���ҽ�׽ȥ��\n";

        command( "say ��ⷶ�׼����" );
        competition_with(ob);

        if (objectp(ob1) && ob1 != me) call_out("tear_and_kill", random(5), ob1, ob, msg1);
        if (objectp(ob2) && ob2 != me) call_out("tear_and_kill", random(5), ob2, ob, msg2);
        if (objectp(ob3) && ob3 != me) call_out("tear_and_kill", random(5), ob3, ob, msg3);
        if (objectp(ob4) && ob4 != me) call_out("tear_and_kill", random(5), ob4, ob, msg4);
        if (objectp(ob5) && ob5 != me) call_out("tear_and_kill", random(5), ob5, ob, msg5);
        if (objectp(ob6) && ob6 != me) call_out("tear_and_kill", random(5), ob6, ob, msg6);

        return 1;
}

string ask_me()
{
        return "���ù��������ֵܣ�����Ȼ�����ȥ������";
}

int accept_kill(object ob)
{
        object me = this_object();
        object ob1, ob2, ob3, ob4, ob5, ob6;

        delete_temp("win", ob);
        command( "say ����ı�ĺ������ɣ��ǲ��Ƕʼ��������ֵ�����������\n");

        if (objectp(ob1 = present("tao genxian", environment(me)))) ob1->kill_ob(ob);
        if (objectp(ob2 = present("tao ganxian", environment(me)))) ob2->kill_ob(ob);
        if (objectp(ob3 = present("tao zhixian", environment(me)))) ob3->kill_ob(ob);
        if (objectp(ob4 = present("tao yexian",  environment(me)))) ob4->kill_ob(ob);
        if (objectp(ob5 = present("tao huaxian", environment(me)))) ob5->kill_ob(ob);
        if (objectp(ob6 = present("tao shixian", environment(me)))) ob6->kill_ob(ob);

        return 1;
}

int tear_and_kill(object me, object ob, string msg)
{
    // �����������ʱ���еģ�����ִ��ǰ��Ҫ�ж�����������񶼻���
    if (! objectp(ob) || !objectp(me))
        return 1;

        if( !ob->is_fighting(me) || query("qi", ob)*2 >= query("max_qi", ob) )
        {
                delete_temp("caught", ob);
                return 1;
        }

        message_combatd(msg, ob);

        if( random(query("combat_exp", me))>query("combat_exp", ob)/2 )
        {
                addn_temp("caught", 1, ob);
                message_combatd("���$N��" + me->name() + "׽�����ţ�\n", ob);
                if( query_temp("caught", ob) == 4 )
                {
                        message_combatd("\n�ҹ�����׽��$N��֫��Ȼһ����$Nֻ����һ���ʹ����ʧȥ֪���ˡ�\n", ob);
                        delete_temp("caught", ob);
                        ob->unconcious();
                        set_temp("die_reason", "���ҹ�����˺���Ŀ���", ob);
                        ob->remove_all_enemy(0);
                        me->remove_all_enemy(0);
                        ob->die();
                        CHANNEL_D->do_channel(me,"chat",sprintf("%s���ҹ�����˺���Ŀ��ˣ�",ob->name()));
                }
        } else
        {
                message_combatd("$N�ɹ��������ˡ�\n", ob);
        }

        return 1;
}

void lost()
{
        object me, ob;

        ob = this_object();
        me = query_competitor();
        command( "say " + RANK_D->query_respect(ob) + "��Ȼ�м��֣��һ�������Ъ����ɣ��ɲ����Ҵ򲻹���ม�");

        if( ob->name() == "�Ҹ���")set_temp("win/tao1", 1, me);
        if( ob->name() == "�Ҹ���")set_temp("win/tao2", 1, me);
        if( ob->name() == "��֦��")set_temp("win/tao3", 1, me);
        if( ob->name() == "��Ҷ��")set_temp("win/tao4", 1, me);
        if( ob->name() == "�һ���")set_temp("win/tao5", 1, me);
        if( ob->name() == "��ʵ��")set_temp("win/tao6", 1, me);
        delete_temp("caught", me);
        ::lost();
}

void win()
{
        object me = query_competitor();

        if (! objectp(me))
        {
                command("heihei");
                return;
        }
        delete_temp("caught", me);
        command("say �������ˮƽҲ����ҵĹأ���ȥ���������ɡ�");
        ::win();
}
