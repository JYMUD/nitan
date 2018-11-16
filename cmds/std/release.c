// fang.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;

        if (! arg)
                return notify_fail("��Ҫ��˭�����ϵ��\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("��Ҫ��˭�����ϵ��\n");

        if( query_temp("owner", ob) != query("id", me) )
                return notify_fail("�㲢����" + ob->name() + "�����˰�����ʲô����\n");

        if( query("can_speak", ob) )
                message_vision("$N�����߰ɣ�" + ob->name() +
                               "�����߰ɡ�\n", me, ob);
        else
                message_vision("$N�ܴȱ��ذ�$n���룬����ع���Ȼ�ˡ�\n", me, ob);

        if( query_temp("comedby", me) == ob )
                delete_temp("comedby", me);

        delete_temp("owner", ob);
        delete_temp("owner_name", ob);
        ob->set_leader(0);
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : release <����>

��ָ�����������ĸ����߻���ѱ���Ķ��������ū״̬��

HELP );
        return 1;
}