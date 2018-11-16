// assist.c

#include <ansi.h>
 
inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object ob;
        object *team;
        object *assistors;
        mapping q;

        if (! arg)
        {
                if( objectp(ob=query_temp("quest/assist", me)) )
                        write("������������" CYN + ob->name(1) +
                              NOR "������ɵ�����\n");
                else
                        write("�����ڲ�û�а����κ���������ɵ�����\n");
                return 1;
        }

        if (arg == "cancel" || arg == "none")
        {
                if( objectp(ob=query_temp("pending/assist", me)) )
                {
                        write("������˰���" + ob->name(1) + "����ͷ��\n");
                        delete_temp("pending/assist", me);
                        return 1;
                }

                if( !objectp(ob=query_temp("quest/assist", me)) )
                {
                        write("�����ڲ�û��ȥ�������˰���\n");
                        return 1;
                }

                if (environment(ob) == environment(me))
                        message_vision("$N����һ���֣���$n�������һ���"
                                       "�£��Ȳ������ˣ������ټ�����\n",
                                       me, ob);

                // �������״̬
                delete_temp("quest/assist", me);
                team = me->query_team();
                if (arrayp(team) && team[0] == ob)
                {
                        // ���ڰ�������Ķ����У��Զ����
                        me->dismiss_team();
                        message_vision("$N�뿪��$n�Ķ��顣\n",
                                       me, ob);
                }
                return 1;
        }

        if( objectp(ob=query_temp("quest/assist", me)) )
        {
                write("�����ڲ������������" + ob->name(1) +
                      "�������ô���ǲ�����ȡ��(assist cancel)�ˣ�\n");
                return 1;
        }

        // ����ĳ���������
        ob = present(arg, environment(me));
        if (! objectp(ob))
        {
                write("�������˭��\n");
                return 1;
        }

        if( !stringp(query("family/family_name", ob)) || 
            query("family/family_name", ob) != query("family/family_name", me) )
        {
                write("���" + ob->name() + "������ͬһ������"
                      "��ѽ��������ݺ���ֻ���öԷ������ˡ�\n");
                return 1;
        }

        if (! living(ob))
        {
                write("����" + ob->name() + "����û��������ú����ˡ�\n");
                return 1;
        }

        if( ob == query_temp("pending/assist", me) )
        {
                write("�������" + ob->name(1) + "�������˼һ�û�д�Ӧ���ء�\n");
                return 1;
        }

        if( query("quest", me) )
        {
                write("������������������������æ���Լ���"
                      "������˵�ɣ�\n");
                return 1;
        }

        write("�������ʼ����" + ob->name(1) + "�������\n");
        message_vision("$N��$n������" + ob->name() +
                       "���Һ���һ��ȥ�ɣ���\n", me, ob);
        set_temp("pending/assist", ob, me);
        if (! playerp(ob))
        {
                message_vision("$n��$N˵�����һ��б������Ŷ��"
                               "�������æ������\n", me, ob);
                return 1;
        }

        tell_object(ob, YEL + me->name(1) + YEL "����������һ"
                    "ͬ����������Ƿ�ͬ��(right|refuse " +
                    query("id", me)+")��\n"NOR);

        ob->set_temp("pending/answer/"+query("id", me)+"/right",
                     bind((: call_other, __FILE__, "do_right", ob, me :), ob));
        ob->set_temp("pending/answer/"+query("id", me)+"/refuse",
                     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob));

        return 1;
}

// ��ŵ�Է�����
int do_right(object me, object ob)
{
        object *ob_team;

        if( query_temp("pending/assist", ob) != me )
        {
                // �Է���û��˵Ը�����������
                write(ob->name() + "����û���������ѽ���㻹�������ʰɣ�\n");
                return 1;
        }

        delete_temp("pending/assist", ob);

        // �Է�Ը���������
        message_vision("$Nˬ��Ķ�$n˵�����ðɣ���л�ˣ���\n",
                       me, ob);
        tell_object(ob, me->name(1) + "Ը�������İ�����\n");
        set_temp("quest/assist", me, ob);

        if (! pointerp(me->query_team()) || me->is_team_leader())
        {
                if (sizeof(me->query_team()) >= 12)
                {
                        write("����������е���̫���ˣ�û������" +
                              ob->name(1) + "���룬������������"
                              "�Ͳ������ˡ�\n");
                        return 1;
                }

                // �Ҳ��ڶ����л����Ҿ��Ƕ�������䣬���ð��ּ������
                if (pointerp(ob_team = ob->query_team()))
                {
                        // ����Ҳ��һ�������У��������ĸ�����
                        if (ob_team[0] == me)
                                // �����Ѿ����ҵĶ�������
                                return 1;

                        // ���������������У����˳���
                        ob->dismiss_team();
                }

                // ���ּ����ҵĶ���
                me->add_team_member(ob);
                message_vision("$n������$N�Ķ��飬һͬ���߽�����\n",
                               me, ob);
        } else
                tell_object(me, "��" + ob->name() + "��������"
                            "���Ǻ�����һ�������У�������Ե�"
                            "����������Է���Ӱɣ�\n");

        return 1;
}

// �ܾ��Է�����
int do_refuse(object me, object ob)
{
        object *ob_team;

        if( query_temp("pending/assist", ob) != me )
        {
                // �Է���û��˵Ը����������أ����ʲô�أ�
                write(ob->name() + "����û���������ѽ����ܾ�ʲô��\n");
                return 1;
        }

        delete_temp("pending/assist", ob);
        message_vision("$Nҡҡͷ���Ե�������ĺ����������ˣ�"
                       "�������ڻ�����Ҫ�Ͷ���ݡ���\n", me, ob);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : assist <���ID>

���ָ���ʾ���������һ����һͬ������Ż������ҳ��Ϸ������
��ɱ�����񡣵�Ȼ����������ͬ�ţ������㵱ʱû�����������
��ͬ�������İ�������ô����Զ����뵽�Է��Ķ����У����ǶԷ�
������һ�������в��Ҳ��Ƕӳ�����
HELP );
        return 1;
}