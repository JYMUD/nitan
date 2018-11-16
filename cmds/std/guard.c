// guard.c

inherit F_CLEAN_UP;

mapping default_dirs = ([
        "north":        "��",
        "south":        "��",
        "east":         "��",
        "west":         "��",
        "northup":      "����",
        "southup":      "�ϱ�",
        "eastup":       "����",
        "westup":       "����",
        "northdown":    "����",
        "southdown":    "�ϱ�",
        "eastdown":     "����",
        "westdown":     "����",
        "northeast":    "����",
        "northwest":    "����",
        "southeast":    "����",
        "southwest":    "����",
        "up":           "��",
        "down":         "��",
        "out":          "��",
        "in" :          "��",
        "enter" :       "����",
]);

int main(object me, string arg)
{
        string dir;
        object ob, *guards;
        object env;
        mixed old_target;

        if (me->is_busy() || me->is_fighting())
                return notify_fail("������û�а취����ȥ�������£�\n");

        old_target=query_temp("guardfor", me);

        if (! arg || arg == "")
        {
                if (objectp(old_target))
                        if (living(old_target))
                                write("�������ػ���" + old_target->name() +
                                      "��\n");
                        else
                                write("��������" + old_target->name() +
                                      "һ�ԣ���ֹ�������ߡ�\n");
                else
                if (stringp(old_target))
                        write("������ס��" + default_dirs[old_target] +
                              "�ķ��򣬲�׼�κ����뿪��\n");
                else
                             return notify_fail("ָ���ʽ��guard <����> | "
                                           "<��Ʒ> | <����>\n");

                return 1;
        }

        env = environment(me);
        ob = present(arg, env);

        if (ob)
        {
                if (ob == me)
                        return notify_fail("�����Լ�������˵��Ҳ��"
                                           "�����԰ɡ�\n");
                if( query("jing", me)*100/query("max_jing", me)<60 )
                        return notify_fail("�������޷����о�������" + ob->name() + "��\n");
                set_temp("guardfor", ob, me);
        } else
        if( query("exits/"+arg, env) )
        {
                if ((base_name(env))[0..10]=="/data/room/")
                        return notify_fail("�����Ǳ��˼����׼����Ұ��\n");
                if( query("no_fight", env) )
                        return notify_fail("���ﲻ׼ս������Ҳ��׼��ס����ȥ·��\n");
                if( query("max_room", env) )
                        return notify_fail("������סլ������׼��ס����ȥ·��\n");
                if( query("jing", me)*100/query("max_jing", me)<75 )
                        return notify_fail("�������޷����о��������������\n");
                set_temp("guardfor", arg, me);
        } else
        if (arg != "cancel")
                return notify_fail("��Ҫ����˭��ʲ�ᣬ�����ĸ�����\n");

        if (objectp(old_target))
        {
                if( arrayp(guards=query_temp("guarded", old_target)) )
                {
                        guards -= ({ me, 0 });
                        if (! sizeof(guards))
                        {
                                delete_temp("guarded", old_target);
                        } else
                                set_temp("guarded", guards, old_target);
                }
                if (interactive(old_target))
                        tell_object(old_target, me->name() +
                                    "���ٱ������ˡ�\n");
        } else
        if (stringp(old_target))
        {
                guards=query_temp("guarded/"+old_target, env);
                if (arrayp(guards))
                {
                        guards -= ({ me, 0 });
                        if (! sizeof(guards))
                        {
                                delete_temp("guarded/"+old_target, env);
                        } else
                                set_temp("guarded/"+old_target, guards, env);
                }
        }
        delete_temp("guardfor", me);

        if (arg=="cancel")
        {
                write("ʲôҲ�������ˣ����Ǻ����ɡ�\n");
                return 1;
        }

        if (objectp(ob))
        {
                guards=query_temp("guarded", ob);
                if (! arrayp(guards))
                        guards = ({ me });
                else
                {
                        guards -= ({ 0 });
                        guards += ({ me });
                }
                set_temp("guarded", guards, ob);
                if (living(ob))
                        message_vision("$N��ʼ����$n��\n", me, ob);
                else
                        message_vision("$Nվ�����ϵ�$nһ����������"
                                       "�����ȡ�ߡ�\n", me, ob);
                set_temp("guardfor", ob, me);
        } else
        {
                guards=query_temp("guarded/"+arg, env);
                if (! arrayp(guards))
                        guards = ({ me });
                else
                {
                        guards -= ({ 0 });
                        guards += ({ me });
                }
                set_temp("guarded/"+arg, guards, env);
                message("vision", me->name() + "�����������������ܣ�"
                                  "��֪��Ҫ��ʲô��\n", env, ({ me }));
                tell_object(me, "�㿪ʼ��ס��" + default_dirs[arg] +
                               "�ķ������κ���ͨ�С�\n", me);
                set_temp("guardfor", arg, me);
        }

        return 1;
}

int help(object me)
{
        write(@TEXT
ָ���ʽ��guard [<ĳ��>|<����ĳ��>|<ĳ������>|cancel]

���ָ�����������÷�ʽ���ֱ����᣺

guard <ĳ��>      ����<ĳ��>�����������ܵ�����ʱ�������߻���
                  ������ս����

guard <����ĳ��>  ��ס���ڵ��ϵ�ĳ����������ֹ�������ã�ֻҪ
                  �㻹��������䣬����û��æ�������£����˾�
                  �޷��������������

guard <ĳ������>  ��סĳ�����ڷ�ֹ�����˴���������뿪������
                  ��������������ܵĵ��˻���·��������£���
                  ���㵱ʱ��æ�������赲���ˡ�

guard cancel      ȡ����ǰ�� guard ����

ע�⣬ֻҪ��һ�ƶ�������Ʒ�ͳ��ڵ�����״̬�ͻ��������Ƕ���
��ı���״̬��Ȼ��Ч��ֻҪ�㵽�˱�������������Ȼ�������á�
���⣬����������״̬��ʱ�򣬻����ľ�������������ˣ�����Զ�
�������״̬��
TEXT );
        return 1;
}