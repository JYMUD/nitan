// secularize.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        if( query("class", me) != "bonze" )
                return 0;

        if( stringp(query("family/family_name", me)) && 
            (query("family/family_name", me) == "������" || 
            query("family/family_name", me) == "������") )
        {
                write("��û������ʦ�����������Ի��ף�\n");
                return 1;
        }

        if( query_temp("pending/secularize", me) )
        {
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "��˵" + me->name(1) + "�������ƶ���������������ס�");
                delete("class", me);
                write("���������Դ���̾�˿����������س����ú��������ܡ�\n");

                if( stringp(query("purename", me)) )
                        me->set_name();
                return 1;
        }

        set_temp("pending/secularize", 1, me);
        write(YEL "�����Ҫ����������Ǵ��£���������˾��ģ��Ǿ�������һ��������\n" NOR);
        return 1;
}

int help (object me)
{
        write(@HELP
ָ���ʽ: secularize|huansu
 
���ָ������������ĵĳ������

HELP );
        return 1;
}