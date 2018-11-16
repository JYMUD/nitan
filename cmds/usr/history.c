// This program is a part of NT mudlib

#include <ansi.h>
#include <mudlib.h>
inherit F_CLEAN_UP; 

#define HCMD            0
#define HTIME           1

#define DEFAULT_SIZE    25

string help = @HELP
ָ������

���ָ��������������ʹ�ù���ָ���¼��������͸������ָ����ʹ������ָ���¼

!!              �ظ���һ��ָ��
!<ָ����>     �ظ� <ָ����> ��ָ��

ָ���ʽ:
history <ָ����>                ��ʾ��� <ָ����> �ʵ�ָ������
history <ʹ���ߴ���>            ��ʾ <ʹ����> ��ָ������ (��ʦר��)
history <ָ����> <ʹ���ߴ���>   ��ʾ <ʹ����> ��� <ָ����> �ʵ�ָ������ (��ʦר��)
history <ʹ���ߴ���> <ָ����>   ͬ��

history game                    ��ʾ��Ϸ���ش���ʷ�¼�

���ָ��: 
HELP;

int main(object me, string arg)
{
        int i, ttl_size, size, start;
        string msg;
        string *cmd_history;
        object ob;

        if( !wizardp(me) && time()-query_temp("last_history", me)<3 ) 
        { 
                write("ϵͳ�������̾���������� ....\n");   
                return 1; 
        } 

        if( arg == "game" )
        {
                string *game_history = HISTORY_D->query_history();        
                
                msg = MUD_FULL_NAME"�ش���ʷ�¼�\n";
                msg += WHT"��������������������������������������������������������������������������������������������\n"NOR;
                msg += HIC"��� ʱ��              ID        �¼�\n"NOR;
                msg += WHT"��������������������������������������������������������������������������������������������\n"NOR;
                
                for(i=0;i<sizeof(game_history);i+=4)
                {
                        msg +=sprintf(HIW"%-5d"NOR CYN"%-18s"NOR YEL"%-10s"NOR HIC"%s\n"NOR, i/4+1, TIME_D->replace_ctime(game_history[i]), game_history[i+2],game_history[i+3]);
                }
                
                msg += WHT"��������������������������������������������������������������������������������������������\n"NOR;
                me->start_more(msg);
                return 1;
        }
        
        if( wizardp(me) && arg == "-l" )
        {
                object *sortusers;
                
                msg = "���� �������                   ָ����   �ٶ�(ÿ��)   ���ƽ�� ϵͳ����\n";
                msg += WHT"������������������������������������������������������������������������������\n"NOR;
                sortusers = filter_array(users(), (: playerp($1) :));
                sortusers = sort_array(sortusers, (: to_float($1->total_command_count())/(time() - query_temp("logon_time", $1)) < to_float($2->total_command_count())/(time() - query_temp("logon_time", $2)) ? 1 : -1 :));


                foreach(ob in sortusers)
                {
                        cmd_history = ob->query_history();
                        
                        msg += sprintf("%-3d. %-27s%-9d%-13.2f%-8.2f %-8s %s\n", 
                                ++i, 
                                ob->query_idname(), 
                                ob->total_command_count(), 
                                to_float(ob->total_command_count())/(time() - query_temp("logon_time", ob)),
                                sizeof(cmd_history) ? to_float(sizeof(cmd_history))/((cmd_history[<1][1] - cmd_history[0][1])||1) : 0.,
                                count(ob->query_total_timecost(), "/", ob->total_command_count()||1),
                                query("cmdlimit", ob) ? HIR"(Limited)"NOR:"",
                        );

                }
                msg += WHT"������������������������������������������������������������������������������\n"NOR;
                me->start_more(msg);
                return 1;
        }
        if( !arg || !wizardp(me) ) ob = me;
        else if( sscanf(arg, "%d %s", size, arg) == 2 ) ob = find_player(arg);
        else if( sscanf(arg, "%s %d", arg, size) == 2 ) ob = find_player(arg);
        else if( sscanf(arg, "%d", size) == 1 ) ob = me;
        else ob = find_player(arg);

        if( !objectp(ob) )
                return tell(me, "û�� " + arg + " ��λ��ҡ�\n");

        if( ob != me && wiz_level(me->query_id(1)) < wiz_level(ob->query_id(1)) )
                return tell(me, pnoun(2, me) + "û��Ȩ�޲���" + ob->query_idname() + "����ʷָ���¼��\n");

        cmd_history = ob->query_history();

        if( !(ttl_size = sizeof(cmd_history)) )
                return tell(me, (me==ob ? pnoun(2, me):ob->query_idname()) + "û���κ���ʷָ���¼��\n");

        if( size <= 0 ) size = DEFAULT_SIZE;
        if( size > ttl_size ) size = ttl_size;
        
        msg = (me==ob ? pnoun(2, me):ob->query_idname())+"�ܹ��� "+ttl_size+" ��ָ��¼��ָ��ƽ���ٶ� "+(ob->total_command_count() > 0 ? sprintf("%.2f", to_float(ob->total_command_count())/((time() - query_temp("logon_time", ob))||1)) : 0)+" (ָ����/��)������Ϊ����� "+size+" ��: \n"; 


        start = ttl_size - size;

        i = ob->total_command_count() - size;
        foreach(array cmd in cmd_history[start..])
                msg += sprintf(HIW" [%4d]"NOR + WHT" %s"NOR" %s\n"NOR, (++i), ctime(cmd[HTIME])[11..18], cmd[HCMD]);

        me->start_more(msg);
        return 1;
}

int help(object me) 
{
        write(help);
        return 1;
}
