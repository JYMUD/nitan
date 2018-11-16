// This program is a part of NT MudLIB

#include <ansi.h>
#define BATTLEFIELD2_D    "/adm/daemons/battlefieldd2.c"

inherit F_CLEAN_UP;

int help(object me)
{
        write(@HELP
ս��ָ����Ա������뿪ս��

fbattle info                          - ��ʾĿǰս����Ѷ
fbattle join                          - �����μ���һ���ε�ս��
fbattle cancel                        - ȡ������

HELP );
        return 1;
}

int main(object me, string arg)
{
        switch(arg)
        {
                case "info":
                {
                        string msg;
                        string *players = BATTLEFIELD2_D->get_sorted_players();
                        string score = "";
                        string ppl = "";
                        int count = 0;
                        
                        msg = "Ŀǰ�� "+sizeof(players)+" λ��Ҳ���ս����"+(member_array(me->query_id(1), players)==-1?"��δ����ս��":"��������֮һ")+"��\n";
                                                
                        if( sizeof(players) > 0 )
                        {
                                object player;
                
                                foreach(string id in players)
                                {
                                        if( !objectp(player = find_player(id)) )
                                                continue;
                        
                                        if( ++count <= 3 )
                                                score += player->query_idname()+"��";
                                        
                                        ppl += player->query_idname()+NOR"("+BATTLEFIELD2_D->get_player_score(id)+")��";
                                        if( count % 5 == 0 )
                                                ppl += "\n";
                                                                                                      
                                }
                                
                                msg += "������ս��ͳ�ƣ�\n"+ppl[0..<3]+"��\n";
                                
                                msg += "Ŀǰս����������ǰ����Ϊ��"+score[0..<3]+"��\n";
                        }
                        
                        tell_object(me, msg);
                        break;
                }
                case "join":
                        BATTLEFIELD2_D->join_battle(me);
                        break;
                case "cancel":
                        BATTLEFIELD2_D->cancel_battle(me);
                        break;
                default:
                        tell_object(me, "��������ȷ��ָ���ʽ(help fbattle)��\n");
                        break;
        }
        return 1;
}
