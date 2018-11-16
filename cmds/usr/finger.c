// finger.c

inherit F_CLEAN_UP;

void create()
{
        seteuid(getuid());
}

int main(object me, string arg)
{
        object *ob;

        if( !wizardp(me) && time()-query_temp("last_finger", me)<10 )
                return notify_fail("ϵͳ�������̾���������� ....\n");  

        set_temp("last_finger", time(), me);

        if (! arg)
        {
                if( query("jing", me)<50 )
                        return notify_fail("��ľ����޷����С�\n");

                if (! wizardp(me))
                        me->receive_damage("jing", 50);

                me->start_more(FINGER_D->finger_all());
        } else
        if (arg == "-m")
        {
                if (! wizardp(this_player()))
                        return notify_fail("����Ȩʹ�� -m ������\n");
                ob = filter_array(users(), (: $1->name() != $1->name(1) :));
                me->start_more(FINGER_D->user_list(ob), 0);
        } else
        {
                if( query("jing", me)<15 )
                        return notify_fail("��ľ����޷����С�\n");

                if (! wizardp(me))
                        me->receive_damage("jing", 15);

                if ((arg == "lonely") && ! wizardp(me))
                        return notify_fail("û�������ҡ�\n");

                write(FINGER_D->finger_user(arg));
        }
        return 1;
}

int help(object me)
{
  write(@HELP
ָ���ʽ : finger [-m] [ʹ��������]
 
���ָ����û��ָ��ʹ��������������ʾ�����������������
���������ϡ���֮�������ʾ�й�ĳ����ҵ����ߣ�Ȩ�޵����ϡ�
���ʹ���� -m �����������г�ʹ����ߵ���ҡ�
 
see also : who
HELP );
    return 1;
}