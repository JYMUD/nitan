// save.c

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object link_ob;
        int lasttime;

        seteuid(getuid());

        if( !objectp(link_ob=query_temp("link_ob", me)) )
                return notify_fail("�㲻�Ǿ����������߽��룬���ܴ��档\n");

        lasttime=time()-query("last_save", me);
        if( lasttime >= 0 && lasttime < 30)
                return notify_fail("Ϊ�˽���ϵͳ���أ��벻ҪƵ��������ȡ�\n");

        if( query("valid_startroom", environment(me))){
                set("startroom", base_name(environment(me)), me);
                write("�����´����߽���ʱ��������￪ʼ��\n");
        }

        if( (int)link_ob->save() && (int)me->save() ) {
                write("����������ϡ�\n");
                set("last_save", time(), me);
                return 1;
        } else {
                write("����ʧ�ܡ�\n");
                return 0;
        }
}

int help(object me)
{
        write(@HELP
ָ���ʽ��save

��������ܶ��Ľ����������
HELP
        );
        return 1;
}