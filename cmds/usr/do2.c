// This program is a part of NT MudLIB
// do.c chain-command

inherit F_CLEAN_UP;

#define MAX_DO_COMMANDS 15

int main(object me, string arg)
{
        int do_times;
        int total_cmds;

        if( !arg || arg == "" )
                return notify_fail("������Ҫ�����´��ָ�\n");

        if( query_temp("do_chain", me) )
                return notify_fail("ϵͳ�ڴ�����Ĵ���ָ�\n");

        set_temp("do_chain", 1, me);
        foreach( string action in explode(arg, ",") )
        {
                do_times = 1;
                sscanf(action, "%d %s", do_times, action);

                if( do_times > MAX_DO_COMMANDS ) do_times = MAX_DO_COMMANDS;

                if( !strsrch(action, "do ") )
                {
                        delete_temp("do_chain", me);
                        tell_object(this_object(), "ָ�� do �в������� do ��ָ�\n");
                        return 1;
                }

                while( do_times-- && ++total_cmds )
                {
                        if( total_cmds > MAX_DO_COMMANDS && !wizardp(this_object()) )
                        {
                                delete_temp("do_chain", me);
                                tell_object(this_object(), "�㲻��һ���³��� "+MAX_DO_COMMANDS+" ��ָ�\n");
                                return 1;
                        }
                        me->command(me->process_input(action));
                }
        }
        delete_temp("do_chain", me);
        return 1;
}

int help(object me)
{
        write( @HELP
ָ���ʽ: do <����ָ��>

���ָ���������һ�ΰ�һ��ָ����ŷ������������·
������Ӷ�����ѹ���ɵ������
����ָ�����
(�����)ԭ ZMUD ����: e;s;s;enter door;kill liu mang;perform cuff.ji
(һ���)ʹ�� do �����: do e,s,s,enter door,kill liu mang,perform cuff.ji

HELP );
        MYGIFT_D->check_mygift(me, "newbie_mygift/do");
        return 1;
}


