// stop.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        int cost, i = 0;

        seteuid(getuid());

        if (! arg)
                return notify_fail("��Ҫ����˭��\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("��Ҫ����˭��\n");

        if( query_temp("owner", ob) != query("id", me) )
                return notify_fail("�˼Ҳ�������Ļ��ġ�\n");

        if (! ob->is_fighting())
                return notify_fail(ob->name() + "���ڲ�û�кͱ��˲�����\n");

        if( query("can_speak", ob) )
                message_vision("$N���һ��������" + ob->name() + "��ס�֣���\n",
                               me);
        else
                message_vision("ֻ��$N����$n����һ�����ڣ�$n���һ�ܣ���ҧ�ˣ�\n",
                               me, ob);

        ob->force_me("halt");
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : stop <����>

��ָ�����������ĸ����߻���ѱ���Ķ���ֹͣ�������ˡ�
HELP );
        return 1;
}