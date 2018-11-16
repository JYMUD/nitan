// engage.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object witness;
        object ob;
        object old;
        string msg;

        seteuid(getuid());

        if (! arg)
                return notify_fail("��Ҫ��˭��飿\n");

        if (me->is_busy() || me->is_fighting())
                return notify_fail("�ú�æ����ͷ�����飡\n");

        ob = present(arg, environment(me));

        if( objectp(old=query_temp("pending/engage", me)) && 
            (ob || arg == "cancel"))
        {
                if (old != ob)
                {
                        write("���������" + old->name(1) + "������ͷ��\n");
                        if (environment(old) == environment(me))
                                tell_object(old, me->name(1) + "����������������ͷ��\n");
                } else
                if (query_temp("pending/answer/" + query("id", me), old))
                        return notify_fail("���������˼�����ء�\n");

                delete_temp("pending/engage", me);
                delete_temp("pending/answer/"+query("id", me), old);
                if (arg == "cancel")
                        return 1;
        }

        if (! ob)
                return notify_fail("����û������ˡ�\n");

        if (query_temp("pending/answer/" + query("id", ob), me) &&
            query_temp("pending/engage", ob) == me )
                return notify_fail("����������������أ��㾿����Ӧ���ǲ���Ӧ��\n");


        if (! ob->is_character())
        {
                message_vision("$N�ճյ�����$n��������޸�"
                               "�Ұ�...�޸��Ұ�...�����Ƿ��ˡ�\n", me, ob);
                return 1;
        }

        if (ob == me)
        {
                message_vision("$NĿ����ͣ����۷�ֱ��\n", me);
                return 1;
        }

        if( query("gender", me) == "Ů��" && query("gender", ob) == "Ů��" || 
            query("gender", me) != "Ů��" && query("gender", ob) != "Ů��" )
        {
                write("�����" + ob->name(1) + "����������ƺ���̫���ʰɣ�\n");
                return 1;
        }

        if( query("class", me) == "bonze" )
        {
                message_vision("$N��$n�ߺߵ�����ҲҪ��飬��ҲҪ��飡\n", me, ob);
                return 1;
        }

        if( query("class", ob) == "bonze" )
        {
                message_vision("$N��������Ķ�$n������컹�װɣ���Ҫ�����飡\n", me, ob);
                return 1;
        }

        if( !query("can_speak", ob) )
        {
                message_vision("$N����$nɵЦ��һ����̬��ģ����\n", me, ob);
                return 1;
        }

        if( query("couple/couple_id", me) == query("id", ob) )
                return notify_fail("����Խ���ˮ��\n");

        if( query("couple", me) )
                return notify_fail("���Ҫ��ס��������̶����ھ�ʮ�������ػ��ߴ��������\n");

        if( query("couple", ob) )
                return notify_fail("����ôҲ�õ��˼��������˵�ɣ�\n");

        if( query("age", me)<18 )
        {
                message_vision("$N��$n������������Ҫ��쳤�������飡\n",
                               me, ob);
                return 1;
        }

        if( query("age", ob)<18 )
        {
                message_vision("$N��$n������������Ҫ��쳤����Ҫ�����飡\n",
                               me, ob);
                return 1;
        }

        me->start_busy(1);
        if (! objectp(witness = present("marriage witness", environment(me))))
        {
                if( query_temp("pending/engage_to", me) == query("id", ob) )
                {
                        CHANNEL_D->do_channel(this_object(), "rumor",
                                "��˵" + me->name(1) + "�¶����ģ�Ҫ��" +
                                ob->name(1) + "˽������");
                } else
                {
                        write("��������֤���˶�û�У�����˽�������Ҫ"
                              "��������������һ��������\n");
                        set_temp("pending/engage_to",query("id",  ob), me);
                        return 1;
                }
        } else
        {
                if (! living(witness))
                        return notify_fail("û����" + witness->name() +
                                           "����ſ�ڵ�����ô���㻹�ǵ�һ����ɡ�\n");

                if (witness->is_fighting())
                        return notify_fail(witness->name() + "��������ܣ�" +
                                           "�ﲻ�����æ��\n");

                return witness->do_witness(me, ob);
        }

        msg=(query("gender", me) == "Ů��")?"$N���������Ķ�$n��������Ȣ���Ұɣ���\n"
                                              : "$N֣�����µĶ�$n��������޸��Ұɣ���\n";

        message_vision(msg, me, ob);
        if (! living(ob))
        {
                write("Ȼ��" + ob->name() + "���Բ��ѣ��޷�����������\n");
                return 1;
        }

        if (! userp(ob))
        {
                write("����" + ob->name() + "��¶��ɫ������������������\n");
                return 1;
        }

        tell_object(ob, YEL + me->name(1) + "����������أ����Ӧ(right)���ǲ���Ӧ(refuse)��\n" NOR);
        set_temp("pending/answer/"+query("id", me)+"/right",
                     bind((: call_other, __FILE__, "do_right", ob, me :), ob), ob);
        set_temp("pending/answer/"+query("id", me)+"/refuse",
                     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob), ob);
        set_temp("pending/engage", ob, me);

        return 1;
}

int do_right(object me, object ob)
{
        object witness;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

        if (! living(ob))
                return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

        if( query_temp("pending/engage", ob) != me )
                return notify_fail("�˼������Ѿ���������������ˡ�\n");

        delete_temp("pending/engage", ob);

        if( query("couple", ob) )
                return notify_fail("�˼��Ѿ�����ˣ��㻹�ǲ�Ҫȥ�˻�ˮ�ˣ�\n");

        if( query("couple", me) )
                return notify_fail("���Ҫ��ס��������̶����ھ�ʮ�������ػ��ߴ��������\n");

        if( query("class", me) == "bonze" )
                return notify_fail("���飿�����Ȼ��װɣ�\n");

        if( query("class", ob) == "bonze" )
                return notify_fail("���飿�����ȵ��˼һ��װɣ�\n");

        if( witness=query_temp("pending/marriage_witness", ob) )
                return witness->do_right(me, ob);

        if( query("gender", me) == "Ů��" )
        {
                switch(query("character", me) )
                {
                case "�ĺ�����":
                        message_vision("$N΢΢��Ц�����ðɣ���"
                                       "С����Ҿ�ͬ����ɡ�\n", me, ob);
                        break;

                case "������":
                        message_vision("$N�ߴ��Ķ�$n�����ð�...\n", me, ob);
                        break;

                case "��������":
                        message_vision("$N�������Ķ�$n�����ðɣ�\n", me, ob);
                        break;

                default:
                        message_vision("$N������$n������Ц������"
                                       "���ð�������ϲ�����ˣ�\n", me, ob);
                        break;
                }
        } else
        {
                switch(query("character", me) )
                {
                case "�ĺ�����":
                        message_vision("$N΢΢��Ц�����ðɣ����Ǿ�������",
                                       me, ob);
                        break;

                case "������":
                        message_vision("$NЦ���еĶ�$n�����ܺúܺã���...��...\n", me, ob);
                        break;

                case "��������":
                        message_vision("$N�����緢�Ķ�$n�����ã�\n", me, ob);
                        break;

                default:
                        message_vision("$N������$n������Ц������"
                                       "���ð�������ϲ�����ˣ�\n", me, ob);
                        break;
                }
        }

        set("couple/couple_id",query("id",  ob), me);
        set("couple/couple_name", ob->name(1), me);
        addn("static/marry", 1, me);
        me->save();
        set("couple/couple_id",query("id",  me), ob);
        set("couple/couple_name", me->name(1), ob);
        addn("static/marry", 1, ob);
        ob->save();
        CHANNEL_D->do_channel(this_object(), "rumor",
                              "��ϲ" + me->name(1) + "��" +
                              ob->name(1) + "˽������" +
                              (random(2) ? "�ս�����" : "����˫�ɡ�"));
        return 1;
}

int do_refuse(object me, object ob)
{
        object witness;

        if (! ob || environment(ob) != environment(me))
                return notify_fail("��ϧ�����˼��Ѿ���������ˡ�\n");

        if (! living(ob))
                return notify_fail("�˼�������������˵�Ļ����������˰ɡ�\n");

        if( query_temp("pending/engage", ob) != me )
                return notify_fail("�˼������Ѿ���������������ˡ�\n");

        delete_temp("pending/engage", ob);

        if( query("couple", me) )
        {
                message_vision("$N��ü�������Ѿ�����ˣ����Ҫ��"
                               "��ʵ�ڲ��ܴ�Ӧ��\n", me, ob);
                return 1;
        }

        if( witness=query_temp("pending/marriage_witness", ob) )
                return witness->do_refuse(me, ob);

        if( query("gender", me) == "Ů��" )
        {
                switch(query("character", me) )
                {
                case "�ĺ�����":
                        message_vision("$N��ü��Ŀ��$n����������"
                                "����������⣿\n", me, ob);
                        break;

                case "������":
                        message_vision("$Nݸ��һЦ����$n������Ҫ�ˣ�"
                                "����ô������̫���ʣ������Ժ�"
                                "��˵�ɣ�\n", me, ob);
                        break;

                case "��������":
                        message_vision("$N�ɸɴ��Ķ�$n�����Ҳ�ͬ"
                                "�⣬�����������İɣ�\n", me, ob);
                        break;

                default:
                        message_vision("$N������$n����Ц����Ҫ�ã�"
                                "�ó����������ƽ���Ƹ�����"
                                "��ǧ����������˵�ɣ�\n", me, ob);
                        break;
                }
        } else
        {
                switch(query("character", me) )
                {
                case "�ĺ�����":
                        message_vision("$N��ü��Ŀ��$n�����������"
                                "������\n", me, ob);
                        break;

                case "������":
                        message_vision("$N����ת�˼�ת����$n�����α�"
                                "�ż������¶������Ժ���˵��\n", me, ob);
                        break;

                case "��������":
                        message_vision("$Nҡҡͷ����$n�����������䲻"
                                "���㣬�㻹����Ѱ�߾Ͱɣ�\n", me, ob);
                        break;

                default:
                        message_vision("$N������$n����Ц������������"
                                "�αؽ���أ�������Ҳͦ�õ�ô��\n", me, ob);
                        break;
                }
        }

        return 1;
}

int help(object me)
{
           write( @HELP
ָ���ʽ: engage <someone>

��ĳ�������飬������Ǻ��л�����ã��������˰ɣ�

see also : divorce
HELP );
           return 1;
}
