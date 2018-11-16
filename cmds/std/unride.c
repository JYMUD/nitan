// Filename : /cmds/std/unride.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me)
{
        object ob, follower;

        if( !objectp(ob=query_temp("is_riding", me)) )
                return notify_fail("����ʲô�£�������û���\n");

        message_vision("$N��$n�Ϸ������¡�\n", me, ob);
        ob->move( environment(me) );
        ob->delele_temp("is_rided_by");
        delete_temp("is_riding", me);
        // �����е���Ҳ����
        if (objectp(follower = query_temp("is_rided_follow", ob)))
        {
                delete_temp("is_riding_follow", follower);
                delete_temp("is_rided_follow", ob);
                //message_vision("$Nǿ��Ҫ������������\n", me);
                message_vision("$N��$n�Ϸ������¡�\n", follower, ob);
        }
        return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ : unride | xia
 
���ָ�������������ŵ���ѱ���Ķ�������������
 
HELP );
    return 1;
}
