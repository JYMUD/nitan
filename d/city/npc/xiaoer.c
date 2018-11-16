#include <ansi.h>
#include <command.h>

inherit NPC;

void create()
{
        set_name("��С��", ({ "xiao er", "xiao", "waiter" }) );
        set("gender", "����" );
        set("age", 22);
        set("long", "��λ��С����Ц�����æ��������ʱ������ڲ����ϵ�Ĩ��������\n");
        set("combat_exp", 100);
        set("attitude", "friendly");
        set("rank_info/respect", "С����");
        setup();
        if (clonep()) keep_heart_beat();
}

string accept_ask(object me, string topic)
{
        switch (random(5))
        {
        case 0:
                return "�ˣ���æ���أ������������¥������ֵ����İɣ�";

        case 1:
                return "���ɶ��û����æ����ô��";

        case 2:
                return "��ѽѽ����û����æ����ô��Ҫ������Ϣ��ȥ��������¥������ֵܰɣ�";

        case 3:
                return "������ݵ��ϰ��ﰢ��ɩ��ϢҲ��ͨ����Щү��ʲô����������Ҫ��������ȥ��";

        default:
               return "��������¥������ֵ���Ϣ�Ž���ͨ����ȥ�����İɡ�";
        }
}

void init()
{       
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        // add_action("do_drop", "drop");
}

void greeting(object ob)
{
        if ( ! ob || environment(ob) != environment() ) return;
        switch( random(2) )
        {
        case 0:
                say( CYN "��С��Ц�����˵������λ" + RANK_D->query_respect(ob)
                   + CYN + "�������ȱ��裬ЪЪ�Ȱɡ�\n" NOR);
                break;
        case 1:
                say( CYN "��С���ò����ϵ�ë��Ĩ��Ĩ�֣�˵������λ" + RANK_D->query_respect(ob)
                   + CYN + "����������\n" NOR);
                break;
        }
}

int accept_object(object me, object ob)
{
        
        if( query("money_id", ob) && ob->value() >= 1000 )
        {
                tell_object(me, CYN "С��һ������˵������л���ϣ��͹�����¥ЪϢ��\n" NOR);
                set_temp("rent_paid", 1, me);
                return 1;
        }

        switch (random(6))
        {
        case 0:
                command("say �ã��ã�");
                break;
        case 1:
                command("say ����Ҫ�Ķ���ȫ���ң�");
                break;
        }

        if (! ob->is_character())
        {
                destruct(ob);
                return -1;
        }
        return 1;
}

void heart_beat()
{
        string start_room;
        object ob;

        if (stringp(start_room = query("startroom"))
           && find_object(start_room) == environment())
        {
                foreach (ob in all_inventory(environment()))
                {
                        if (! ob->is_character()
                           || interactive(ob)
                           || playerp(ob)
                            || query_temp("owner", ob) )
                                continue;

                        if( stringp(start_room=query("startroom", ob) )
                           && find_object(start_room) == environment())
                                continue;

                        if( query("id", ob) == "corpse" )
                                message_vision(HIC "\n$N" HIC "վ������$n" HIC "�ൽ"
                                               "���⣬Ȼ�����������µ����˻�����\n\n"
                                               NOR, this_object(), ob);
                        else if( query("race", ob) != "Ұ��" )
                                message_vision(CYN "\n$N" CYN "��$n" CYN "����ǸȻ��˵"
                                               "�����Բ�ס��С���Ѿ������ˡ�\n" HIC "$n"
                                               HIC "����һ㶣�ҡ��ҡͷ���������ֵ�ת��"
                                               "��ȥ��\n" NOR, this_object(), ob);
                        ob->move("/d/city/beidajie1");
                }
        }
        ::heart_beat();
}

int do_drop(string arg)
{
        int i;
        object *obs;
        object ob;
        object me;

        if (! arg)
                return 0;

        me = this_player();
        if (objectp(ob = present(arg, me)) &&
            ob->is_character() && ! playerp(ob))
        {
                addn_temp("static/drop_npc", 1, me);
                if( query_temp("static/drop_npc", me)>1 && 
                    query("combat_exp", me) >= 50000 )
                {
                        message_vision(CYN "\n$N" CYN "��ŭ���������" + RANK_D->query_rude(ob)
                                       + CYN "�����������ң�\n" NOR + HIC "˵��$N" HIC "һ����"
                                       "�У������ʱ���˳������������ţ���$n" HIC "��" + ob->name()
                                       + HIC "һ�����˳�ȥ��\n\n" NOR, this_object(), me);

                        ob->move("/d/city/beidajie1");
                        me->move("/d/city/beidajie1");
                        message("vision", HIC "ֻ���͵괦�鶣���һ����죬���" + me->name()
                                          + HIC "��" + ob->name() + HIC "һ����˳�����\n"
                                          NOR, environment(me), me);

                        me->receive_damage("qi", 1);
                        ob->die();
                        me->unconcious();
                        return 1;
                }

                message_vision(CYN "\n$N" CYN "ŭ���������������������ֲ��ǹײĵ꣬����Ҫ��"
                               "���˽������\n" NOR + HIC "˵��$N" HIC "һ���֣���ʱ����һȺ"
                               "���δ󺺣���$n" HIC "��" + ob->name() + HIC "һ����˳�ȥ��\n\n"
                               NOR, this_object(), me);

                ob->move("/d/city/beidajie1");
                me->move("/d/city/beidajie1");
                message("vision", HIC "ֻ���͵괦����һ���������" + me->name() + HIC "���˸�"
                                  "�˳����������������" + ob->name() + HIC "Ҳ�����˳�����"
                                  "\n" NOR, environment(me), me);
                me->receive_damage("qi", 1);
                return 1;
        }

        if (! DROP_CMD->main(me, arg))
                return 0;

        if (! GET_CMD->main(this_object(), arg))
                return 1;

        obs = all_inventory(this_object());
        for (i = 0; i < sizeof(obs); i++)
                if (! obs[i]->is_character()) destruct(obs[i]);
        if (! random(5))
        {
                switch (random(4))
                {
                case 0:
                        command("say �㲻Ҫ��Ҫ��");
                        break;
                case 1:
                        command("sigh"+query("id", this_player()));
                        command("say ��̣������������");
                        break;
                case 2:
                        command("say �ܼ��ӣ��ܼ��ӣ�");
                        break;
                default:
                        command("heihei");
                        break;
                }
        }
        return 1;
}