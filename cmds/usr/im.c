// im.c

#include <ansi.h>

#define IM_D "/adm/daemons/imd.c"

inherit F_CLEAN_UP;

int who_list(object me);
int register(object me,string pro);
void register_step1(string arg,object me,string pro);
void register_step2(string arg,object me,string pro,string account);
int help(object me);

int main(object me, string arg)
{
        string who, msg;
        if(!arg) return help(me);
        if(arg == "login") 
        {
                if( query_temp("im_fd", me) 
                && IM_D->query_users()[query_temp("im_fd", me)]["obj"] == me)   
                {
                        tell( me, "\n[IM Message]:�����ڵ����У����� im quit ���ߡ�\n");
                        return 1;
                }

                tell( me, "\n[IM Message]:��ʼ���뼴ʱͨѶ���顣\n");
                IM_D->login_irc(me);
                return 1;
        }

        if(!undefinedp(query_temp("im_fd", me))) 
        {
                if(arg == "who")
                { 
                        who_list(me);
                        return 1;
                }
                
                if(arg == "quit") 
                {
                        IM_D->send_command(query_temp("im_fd", me),"QUIT\r\n");
                        delete_temp("im_fd", me);
                        tell( me, "\n[IM Message]:��ʱͨѶ���������ˡ�\n");
                        return 1;
                }

                if(sscanf(arg,"tell %s %s",who,msg) == 2)
                        return IM_D->process_send_msg(me,who,msg);

                if(arg == "register msn") 
                {       
                        register(me,"MSN");
                        return 1;
                }
                
                if(arg == "register yahoo") 
                {
                        register(me,"YAHOO");
                        return 1;
                }
                
                if(sscanf(arg,"add %s %s",who,msg) == 2)
                {
                        if(who != "msn" && who != "yahoo")
                        {
                                tell( me, "\n[IM Message]:Ŀǰֻ�ܼ��� msn ���� yahoo �ĺ���������\n");
                                return 1;
                        }
                        IM_D->send_command(query_temp("im_fd", me), "PRIVMSG #bitlbee :add "+who+" "+msg);

                        tell( me, "\n[IM Message]:��� "+msg +" ������� "+who +" ����������\n");
                        return 1;
                }

                if(sscanf(arg,"remove %s",who) == 1)
                {
                        int fd = query_temp("im_fd", me);

                        if(!undefinedp(IM_D->query_users()[fd]["list"]) 
                        && !undefinedp(IM_D->query_users()[fd]["list"][who]))
                        {
                                IM_D->send_command(fd,  "PRIVMSG #bitlbee :remove "+who);
                                tell( me, "\n[IM Message]:��� "+who +" ����ĺ�������ɾ����\n");
                                return 1;
                        }

                        tell( me, "\n[IM Message]:û�������Ŷ��\n");
                        return 1;
                }

                if(arg == "yes") 
                {
                        IM_D->send_command(query_temp("im_fd", me), "PRIVMSG #bitlbee : yes");
                        tell( me, "\n[IM Message]:��ͬ��������������ĺ���������\n");
                        return 1;
                }

                if(arg == "no")
                {
                        IM_D->send_command(query_temp("im_fd", me),  "PRIVMSG #bitlbee : no");
                        tell( me, "\n[IM Message]:�㲻ͬ��������������ĺ���������\n");
                        return 1;
                }

                if(sscanf(arg,"nick %s",msg))
                {
                        tell( me, "\n[IM Message]:�㽫���ָ�Ϊ��"+msg+"��\n");
                        IM_D->send_command(query_temp("im_fd", me),  "PRIVMSG #bitlbee :nick msn \""+msg+"\"");
                        return 1;
                }
                tell( me,"\n[IM Message]:û�������Ŷ��\n");
        }
        else 
                tell( me,"�㲢û�е���\n");
        return 1;
}

void who_list(object me)
{
        mapping map = IM_D->query_users();
        tell( me,"���������б�\n");

        foreach(int fd,mapping m in map)
        {
                if(m["obj"] == me && me->query_id(1) == m["id"] )
                {
                        foreach(string k,string* v in m["list"])
                        {
                                if(v[2] == m["id"] || v[2] == "root") continue;

                        tell( me, sprintf("(%-4s)[%-10s] %-70s \n",v[3]=="G"?"�뿪":"����",v[2],v[4]+"("+v[0]+"@"+v[1]+")"));
                        }
                }
        }
        return;
}

void register(object me,string pro)
{
        tell( me,"[IM Message] ��������� "+pro+" �ʺţ����ǰ� . ȡ��:");
        input_to("register_step1",me, pro);
        return;
}

void register_step1(string arg,object me,string pro)
{
        if(arg[0] == '.') 
        {
                tell( me, "[IM Message] ȡ���趨��\n");
                return;
        }

        if(strlen(arg) < 5) 
        {
                tell( me, "[IM Message] ��������� "+pro+" �ʺţ����ǰ� . ȡ��:");
                input_to("register_step1",me,pro);
        }

        tell( me, "[IM Message] ��������� "+pro+" ���룬���ǰ� . ȡ��:");
        input_to("register_step2",me,pro,arg);
}

void register_step2(string arg,object me,string pro,string account)
{
        if(arg[0] == '.') 
        {
                tell( me, "[IM Message] ȡ���趨��\n");
                return;
        }


        if(strlen(arg) < 5) 
        {
                tell( me, "[IM Message] ��������� "+pro+" ���룬���ǰ� . ȡ��:");
                input_to("register_step2",me,pro,account);
        }

        IM_D->del_account( query_temp("im_fd", me), pro);
        IM_D->register_account( query_temp("im_fd", me),pro,account,arg);
        tell( me, "[IM Message] "+pro+" �ʺ��������޸���ϡ�\n");
}

int help(object me)
{
        write(@HELP
ָ���ʽ : im [�������]
            
    ���ָ��������������·�����еļ�ʱͨѶ���塣Ŀǰ֧Ԯ��         
��ʱͨѶ������ MSN �� YAHOO ����

    �������ǵڼ���ʹ�ã�Ҫʹ�� im ʱ�������ȴ� im login ��
����Ķ�����

    ��Ϊ��·����Ĺ�ϵ����ЩѶϢ���ܻ��ӳ�һЩʱ��Ż��յ���
     
     im login           - ���� im ϵͳ��
     im quit            - �ǳ� im ϵͳ��
     im who             - �г���ĺ���������
     im register msn    - ע�� msn �ʺš�
     im register yahoo  - ע�� yahoo �ʺš�
     im add <protocol> <account> - �������ѡ�
     im remove <account>- �Ƴ����ѡ�
     im no              - ��ͬ�����˰���������������
     im yes             - ͬ�����˰���������������
     im nick <nick>     - �޸� msn ���ǳơ�
     im tell <id> <msg> - ��Ѷ��ĳ�ˡ�
HELP
        );
        return 1;
}