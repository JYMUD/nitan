// This program is a part of NT MudLIB

#include <ansi.h>

inherit F_CLEAN_UP;

#define DATA_PATH      "/data/bug/"
#define BUG_D   "/adm/daemons/bugd"
#define PER_REPORT_TIME_LIMIT   60

#define LIST_OPT_ALL    (1<<0)

string help = @HELP

bug -a                          ���� bug �ر�
bug -l                          �г� bug ����
bug <���>                      ��ȡ bug ��ϸ����
bug -r <���>                   ��Ӧ bug ��������       ��ʦר��
bug -d <���>[.<�ظ����>]      ɾ�� bug ĳƪ��ĳƪ�ظ� ��ʦר��
bug                             ��ȡ�������            ��ʦר��
bug [ID]                        ��ȡĳ�˵Ĵ������      ��ʦר��

HELP;

string big_number_check(mixed bn)
{
        int negtive;

        if( !bn ) return 0;

        if( intp(bn) )
                return bn+"";
        else if( !stringp(bn) )
                return 0;

        if( bn[0] == '-' )
        {
                bn = bn[1..];
                negtive = 1;
        }

        bn = replace_string(bn, ",", "");

/*
        if( bn[<1] == 'k' || bn[<1] == 'K' )
                bn = bn[0..<2]+"000";
        else if( bn[<1] == 'm' || bn[<1] == 'M' )
                bn = bn[0..<2]+"000000";
        else if( bn[<1] == 'g' || bn[<1] == 'G' )
                bn = bn[0..<2]+"000000000";
*/
        while(bn[0]=='0') bn = bn[1..];

        foreach(int i in bn)
                if( i < '0' || i > '9' )
                        return 0;

        if( bn == "" )
                return 0;
        else
                return negtive ? "-"+bn : bn;
}

void edit_bug_content(object me, string title, string content)
{
        string number;

        if( time()-query_temp("bug_report", me)<PER_REPORT_TIME_LIMIT )
                return tell_object(me, "������ٸ� "+(PER_REPORT_TIME_LIMIT + query_temp("bug_report", me) - time())+" �������ٻر�һ�� Bug��\n"NOR);

        number = BUG_D->add_bug(me, title, content);

        tell_object(me, HIY"��л��� Bug �ر�ʹ������������������\n"NOR);
        tell_object(me, HIY"\n�ѽ������ر��� Bug �������Ͽ��У����Ϊ "+number+"�������� bug -l ��ʱע�⴦��״����\n"NOR);

        set_temp("bug_report", time(), me);

        me->finish_input();
}

void input_bug_title(object me, string title)
{
        if( !title || !title[0] )
        {
                tell_object(me, "ȡ�� Bug �ر����롣\n");
                return me->finish_input();
        }

        if( strlen(filter_color(title,1)) > 30 )
        {
                tell_object(me, "�ر����ⲻ�ó��� 30 ����Ԫ��\n");
                return me->finish_input();
        }

        if( query_temp("big5", me) )
                title = LANGUAGE_D->Big52GB(title);

        tell_object(me, "��������� Bug �ر�����Ϊ����"+title+NOR+"��\n");
        tell_object(me, HIY"���������ر��� Bug ��ϸ���ݡ�\n"NOR);
        me->edit( (: edit_bug_content, me, title :) );
}

void edit_reply_content(object me, string number, string status, string content)
{
        BUG_D->reply_bug(me, number, status, content);

        tell_object(me, "��Ӧ��ŵ� "+number+" �� Bug ��ϡ�\n");

        me->finish_input();
}

void confirm_input_reply(object me, string number, string status, string confirm)
{
        if( stringp(confirm) )
                confirm = lower_case(confirm);

        switch(confirm)
        {
                case "yes":
                case "y":
                        tell_object(me, HIY"�����봦����ϸ���ݡ�\n"NOR);
                        me->edit( (: edit_reply_content, me, number, status :) );
                        return;
                default:
                        tell_object(me, HIY"�����봦����ϸ���ݡ�\n"NOR);
                        BUG_D->reply_bug(me, number, status);
                        me->finish_input();
                        break;
        }
}


void input_reply_status(object me, string number, string arg)
{
        string status;

        switch(arg)
        {
                case "1":       status = HIR"δ����"NOR;        break;
                case "2":       status = HIY"������"NOR;        break;
                case "3":       status = HIC"���޸�"NOR;        break;
                case "4":       status = HIR"�޷��޸�"NOR;      break;
                case "5":       status = HIW"���账��"NOR;      break;
                case "6":       status = HIM"���ٻر�"NOR;      break;
                default:        status = HIR"δ����"NOR;        break;
        }

        tell_object(me, "�Ƿ����봦����ϸ���ݣ�(Yes/No):");
        input_to( (: confirm_input_reply, me, number, status :) );
}

int main(object me, string arg)
{
        object ob;
        string number;
        mapping data;

        MYGIFT_D->check_mygift(me, "newbie_mygift/bug");
        if( wizardp(me) )
        {
                if( !arg || !arg[0] )
                {
                        if( !query_temp("bug_msg", me) )
                                return notify_fail("������û�д���������ϡ�\n");

                        me->start_more(query_temp("bug_msg", me));
                        return 1;
                }
                else if( ob = find_player(arg) )
                {
                        if( !query_temp("bug_msg", ob) )
                                return notify_fail(ob->query_idname()+"����û�д���������ϡ�\n");
                        me->start_more(query_temp("bug_msg", ob));
                        return 1;
                }
                else if( sscanf(arg, "-r %s", number) )
                {
                        if( !BUG_D->bug_exists(number) )
                                return notify_fail("��û�б�� "+number+" �� Bug ���ڡ�\n"NOR);

                        data = restore_variable(read_file(DATA_PATH+number)); 
                        tell_object(me, HIY"������Ŀǰ����״����ţ�\n[1]"HIR"δ����"NOR" [2]"HIY"������"NOR" [3]"HIC"���޸�"NOR" [4]"HIR"�޷��޸�"NOR" [5]"HIW"���账��"NOR" [6]"HIM"���ٻر�"NOR"\n");
                        tell_object(me, CYN+"\n"+data["content"]+"\n"+NOR+":"); 
                        input_to( (: input_reply_status, me, number :) );
                        return 1;
                }
                else if( sscanf(arg, "-d %s", number) )
                {
                        int reply;

                        sscanf(number, "%s.%d", number, reply);

                        if( !BUG_D->bug_exists(number) )
                                return notify_fail("��û�б�� "+number+" �� Bug ���ڡ�\n"NOR);

                        if( reply > 0 )
                        {
                                BUG_D->remove_bug(me, number, reply);
                                tell_object(me, "ɾ����ŵ� "+number+" �� Bug �ĵ� "+reply+" ƪ��Ӧ��\n"NOR);
                        }
                        else
                        {
                                BUG_D->remove_bug(me, number);
                                tell_object(me, "ɾ����ŵ� "+number+" �� Bug ���������ϡ�\n"NOR);
                        }

                        return 1;
                }
        }

        if( !arg )
                return notify_fail(help);

        else if( arg == "-l" )
        {
                me->start_more(BUG_D->list_bug(1));
                return 1;
        }
        else if( arg == "-a" )
        {
                tell_object(me, HIW"��ӭʹ��"WHT"����(Bug)�ر�ϵͳ\n"NOR HIG"�ر� Bug ʱ����������ʱ�䡢���ڵ�λ�á��´����ָ����ϵͳ��ʾ��ѶϢ\n��ϸ�����Ͻ����԰�����ʦ���ٽ���������� Bug��\n"NOR);
                tell_object(me, HIY"���������ر��� Bug ����(�����⣬����ϸ����)����ֱ�Ӱ� Enter ȡ�����롣\n:"NOR);
                input_to( (: input_bug_title, me :) );
                return 1;
        }
        else if( big_number_check(arg) )
        {
                if( !BUG_D->bug_exists(arg) )
                        return notify_fail("��û�б�� "+arg+" �� Bug ���ڡ�\n"NOR);

                tell_object(me, BUG_D->query_bug(arg));
                return 1;
        }
        else return notify_fail(help);
}

int help(object me)
{
        write(help);
        MYGIFT_D->check_mygift(me, "newbie_mygift/bug");
        return 1;
}
