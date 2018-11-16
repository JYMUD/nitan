


#include <ansi.h>
#include <emotion.h>

inherit F_CLEAN_UP;

#define BAR     "��������������������������������������������������������������������������������\n"

string help = @HELP
�����ѯָ��

���ָ����г�Ŀǰ���п���ʹ�õı���ָ��

ָ���ʽ:
semote
semote -t               �鿴����ָ���ʹ�����б�
semote -l               �鿴����ָ��ļ���˵��
semote <�������>       �鿴 <�������> ����ϸ����ѶϢ


���ָ��: command
HELP;

int help(object me) 
{

        write(help);
        return 1;
}


private string replace_keys(string description)
{

        description = replace_string(description, "$ME", HIC"��"NOR);
        description = replace_string(description, "$YOU", HIG"ĳ��"NOR);
        description = replace_string(description, "$T", HIM"����"NOR);

        return description;
}

int main(object me, string arg)
{
        string msg;

        if( arg == "-t" )
        {
                int i;
                string *emotions = EMOTE_D->query_emotions();
                mapping emotion_sort = allocate_mapping(sizeof(emotions));

                foreach( string e in emotions )
                emotion_sort[e] = EMOTE_D->query_emotion(e)[USE];

                emotions = sort_array(emotions, (: count( $(emotion_sort)[$1],">",$(emotion_sort)[$2] )? -1:1:));

                msg = "����ָ��ʹ������:\n";
                foreach( string e in emotions )
                        msg += sprintf("%4s %-20s %-10s ��\n", HIW+(++i)+"."NOR, e, emotion_sort[e]);

                me->start_more(msg+"\n");
                return 1;
        }
        else if( arg == "-l" )
        {
                int i;
                string *emotions = EMOTE_D->query_emotions();
                mapping emotion_sort = allocate_mapping(sizeof(emotions));

                foreach( string e in emotions )
                emotion_sort[e] = EMOTE_D->query_emotion(e)[NOTE];

                emotions = sort_array(emotions, (: strcmp($1, $2) :));

                msg = "����ָ����˵��\n";
                foreach( string e in emotions )
                {
                        msg += sprintf("%4s %-20s %-10s\n", HIW+(++i)+"."NOR, e, emotion_sort[e]||WHT"�޼��"NOR);
                }
                me->start_more(msg+"\n");
                return 1;
        }
        else if( arg )
        {
                array emotion = EMOTE_D->query_emotion(arg);

                if( undefinedp(emotion) )
                        return tell(me, "û�� " + arg + " �������ָ�\n", "CMDMSG");

                msg = "���� "+arg+" ֮��ϸ�������£�\n"BAR;

                msg += NOR WHT"1.�޶����޸�������    ��"NOR+replace_keys(emotion[NONE_ALL])+"\n";
                msg += NOR WHT"2.�޶����и�������    ��"NOR+replace_keys(emotion[NONE_ALL_ARG])+"\n";
                msg += NOR WHT"3.����Ϊ�Լ��޸������֣�"NOR+replace_keys(emotion[ME_ALL])+"\n";
                msg += NOR WHT"4.����Ϊ�Լ��и������֣�"NOR+replace_keys(emotion[ME_ALL_ARG])+"\n";
                msg += NOR WHT"5.����Ϊĳ���޸������֣�"NOR+replace_keys(emotion[YOU_ALL])+"\n";
                msg += NOR WHT"6.����Ϊĳ���и������֣�"NOR+replace_keys(emotion[YOU_ALL_ARG])+"\n";
                msg += NOR WHT"7.����ע��            ��"NOR+(emotion[NOTE] || "��ע��")+"\n";
                msg += NOR WHT"8.ʹ�ô���            ��"NOR+emotion[USE]+" ��\n";
        }
        else
        {
                int size;
                string *emotions = sort_array(EMOTE_D->query_emotions(), 1);

                size = sizeof(emotions);
                msg = "Ŀǰ���� "+size+" �ֱ���ָ�����ʹ�ã��б����£�\n"BAR;

                msg += sprintf("%-=80s", sprintf("%@-:10s", emotions)) + "\n";
                msg += "\n������ semote <�������> �ۿ���ϸ������\n";
        }

        me->start_more(msg + BAR);

        return 1;
}

