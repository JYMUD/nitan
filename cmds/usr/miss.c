// miss ׷Ѱ��Ʒ

#include <ansi.h>
#include <command.h>

inherit F_CLEAN_UP;

int main(object me, string str)
{
        object ob;

        return notify_fail("�ù����Ѿ��رա�\n");
        if( me->is_busy() || query("doing", me) )
                return notify_fail("��Ķ�����û����ɣ�����׷Ѱ��Ʒ��\n"); 

        if (me->is_fighting())
                return notify_fail("������ս���أ����ǰ���ս���ɡ�\n"); 

        if (! str)
                return notify_fail("��Ҫ׷Ѱʲô��Ʒ��\n");

        if( !stringp(str=query("can_summon/"+str, me)) )
                return notify_fail("�㲻֪�����׷Ѱ�����Ʒ��\n");

        if (me->is_ghost())
                return notify_fail("���㻹������׷Ѱ�ɡ�\n");

        if( query("no_magic", environment(me)) || query("maze", environment(me)) )
                return notify_fail("���������޷���Ӧ�������Ʒ��������ʩ��׷Ѱ��\n");

        if (! objectp(ob = find_object(str)) || ! environment(ob))
                return notify_fail("���������Ҳ�޷���Ӧ�������Ʒ��\n");

        ob->receive_miss(me);
        return 1;
}

int help(object me)
{
write(@HELP
ָ���ʽ : miss <������Ʒ��ID>

��ָ�������׷Ѱ�����Ƶ���Ʒ��������һ���ľ�������������
HELP
    );
    return 1;
}
