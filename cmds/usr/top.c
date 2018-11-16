// This program is a part of NT MudLIB
// Written by Lonely@nitan.org

#include <ansi.h>
#include <mudlib.h>

inherit F_CLEAN_UP;

string help = @HELP
�г��������а�

top gaoshou             - ����������а�
top average             - ������������ٶ����а�
HELP;

int top_list(object ob1,object ob2);
int get_score(object ob);
int top_average(object ob1, object ob2);
string *get_average(object ob);
int main(object me, string arg)
{

        object *list,*ob;
        int i, n;
        string msg;
        string arg1, arg2, arg3;
        string *res;

        if( time()-query_temp("last_top", me)<10 )
              return notify_fail("ϵͳ�������̾���������� ....\n");

        if( !wizardp(me) )
                set_temp("last_top", time(), me);

        if( !arg )
                return notify_fail(help);

        if( sscanf(arg, "%s %s %s", arg1, arg2, arg3) == 3 )
        {
                if( arg3 == "all" )
                        n = 200;
                else
                        n = to_int(arg3);
        }
        else if( sscanf(arg, "%s %s", arg1, arg2) == 2 )
        {
                if( arg2 == "all" )
                        n = 200;
                else if( to_int(arg2) )
                {
                        n = to_int(arg2);
                        arg2= 0;
                }
                else
                        n = 30;
        }
        else
        {
                n = 10;
                arg1 = arg;
        }

        if( n < 1 || n > 200 )
                return notify_fail("��ʾ������������С�� 1 ����� 200��\n");

        switch( arg1 )
        {
        case "average":
                if( !wizardp(me) ) return notify_fail("��������������ѯ���ܲ�����ҿ��š�\n");
                msg = NOR YEL"����"HIY"ǰ "+n+" ��������"NOR YEL"���а�\n"NOR;
                msg += NOR WHT"��������������������������������������������������������������������������������\n"NOR;
                msg += sprintf(HIW"%4s %-28s %-12s %12s %12s\n"NOR, "����", "���", "����", "Ǳ��", "���");
                msg += NOR WHT"��������������������������������������������������������������������������������\n"NOR;

                ob = filter_array(users(), (: playerp($1) && living($1) && !wizardp($1) :));
                list = sort_array(ob, (: top_average :));
                for (i = 0 ;i < n ; i++)
                {
                        if( i >= sizeof(list))
                                msg += sprintf("��  %-5s ��ʱ��ȱ����������������������������������\n"NOR,chinese_number(i+1));
                        else {
                                res = query_temp("average", list[i]);
                                if( list[i] == me ) msg += BBLU HIY;
                                msg+=sprintf("��%-5s%-22s%-12d%12d%12d��\n"NOR,chinese_number(i+1),query("name", list[i])+"("+
                                                        capitalize(query("id", list[i]))+")",
                                                        res[0],
                                                        res[1],
                                                        res[2]);
                        }
                }
                msg += "����������ʦ�����ߡ�˯�ߡ����Ծ������������񩤩�����\n";
                msg += "  " + NATURE_D->game_time() + "�ǡ�\n";
                write(msg);
                break;
        case "gaoshou":
                ob = filter_array(users(), (: playerp($1) && living($1) && !wizardp($1) :));
                list = sort_array(ob, (: top_list :));
                msg = HIR "\n\t  ======== Ц���������߸������а� ========\n" NOR;
                msg += HIR "\t  /                                      \\\n" NOR;   
                msg += sprintf(HIY "%-10s%-20s%-22s%-20s\n" NOR, "��������", "���մ���", "��������", "����");
                msg += HIM "---------------------------------------------------------------\n"NOR;
                for (i = 0 ;i < n ; i++)
                {
                        if( i >= sizeof(list))
                                msg += sprintf(HIW"   %-7s ��ʱ��ȱ��������������������������������\n"NOR,chinese_number(i+1));
                        else {
                                if( list[i] == me ) msg += BBLU HIY;
                                msg+=sprintf(HIW"   %-7s%-20s%-22s%-20s\n"NOR,chinese_number(i+1),query("name", list[i])+"("+
                                                        capitalize(query("id", list[i]))+")",
                                                        query("family/family_name", list[i])?list[i]->query_family():"��ͨ����",
                                                        "����͸¶");
                        }
                }
                msg += HIM "---------------------------------------------------------------\n"NOR;
                msg += HIR "\t  \\                                      /\n" NOR;
                msg += HIR "\t  ========================================\n" NOR;
                msg += HIC + NATURE_D->game_time() + "�ǡ�\n" NOR;
                write(msg);
                break;
        default:
                write(help);
                break;
        }
        return 1;

}

int top_list(object ob1, object ob2)
{
        int score1,score2;

        score1 = get_score(ob1);
        score2 = get_score(ob2);

        return score2 - score1;
}

int get_score(object ob)
{
        int tlvl,i,score;
        string *ski;
        mapping skills;

        reset_eval_cost();

        skills = ob->query_skills();
        if (!sizeof(skills)) return 1;
        ski  = keys(skills);
        for(i = 0; i<sizeof(ski); i++) {
                tlvl += skills[ski[i]];
        }  // count total skill levels
        score = tlvl/1;
        score+=query("max_neili", ob)/1;
        score += ob->query_str() + ob->query_int() + ob->query_dex() + ob->query_con();
        score+=query("combat_exp", ob)/10+query("reborn/times", ob)*1000000000;

        return score;
}

int top_average(object ob1, object ob2)

{
        string *score1, *score2;

        score1 = get_average(ob1);
        score2 = get_average(ob2);

        return to_int(score2[0]) - to_int(score1[0]);
}

string *get_average(object ob)
{
        int dexp, dpot, dmar, dt;
        string *res;

        dexp = query("combat_exp", ob) - query("last_examine/combat_exp", ob);
        dpot = query("potential", ob) - query("last_examine/potential", ob);
        dmar = query("experience", ob) - query("last_examine/experience", ob);
        dt = time() - query("last_examine/time", ob);
        res = ({ dexp * 60 / dt, dpot * 60 / dt, dmar * 60 /dt });
        set_temp("average", res, ob);
        return res;
}

