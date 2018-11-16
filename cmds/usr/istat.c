// This program is a part of NT MudLIB
// stats cmds

#include <ansi.h>
#include <mudlib.h>
#include <command.h>

inherit F_CLEAN_UP;

int jingmai_effect(object ob, string str)
{
        if( query("jingmai/finish", ob) )
                return ZHOUTIAN_D->query_jingmai_effect(str);
        else
                return query("jingmai/" + str, ob);
}               

int main(object me, string arg)
{
        object ob;
        string sp;

        seteuid(getuid(me));

        if( !wizardp(me) && time()-query_temp("last_stats", me)<5 )
                return notify_fail("ϵͳ�������̾���������� ....\n");

        set_temp("last_stats", time(), me);
        MYGIFT_D->check_mygift(me, "newbie_mygift/istat");
        if (arg && arg != "")
        {
                if( wizardp(me) || query("couple/child_id", me) )
                {
                        ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character())
                                ob = find_player(arg);

                        if (! ob || ! ob->is_character())
                                ob = find_living(arg);

                        if (! ob || ! ob->is_character() || ! me->visible(ob))
                                return notify_fail("��Ҫ�쿴˭��״̬��\n");

                        if( !wizardp(me) && query("couple/child_id", me) != query("id", ob) )
                                return notify_fail("��Ҫ�쿴˭��״̬��\n");

                } else
                        return notify_fail("ֻ����ʦ�ܲ쿴���˵�״̬��\n");
        } else
                ob = me;

        sp = HIM + (ob == me ? "��" : ob->name(1)) + "Ŀǰ�ĸ���������Ч��һ��\n" NOR;
        sp += HIC "��" HIY "��������������������������������������������������������������" HIC "��\n" NOR;

        sp += sprintf(HIC "���������ӡ�" HIG " %9d / %-9d"
                      HIC "�����Ը��ӡ�" HIG " %9d / %d\n"
                      HIC "�����Ǹ��ӡ�" HIG " %9d / %-9d"
                      HIC "�������ӡ�" HIG " %9d / %d\n",
                      jingmai_effect(ob, "str")+query_temp("apply/attribute", ob)+query_temp("apply/str", ob),1000,
                      jingmai_effect(ob, "int")+query_temp("apply/attribute", ob)+query_temp("apply/int", ob),1000,
                      jingmai_effect(ob, "con")+query_temp("apply/attribute", ob)+query_temp("apply/con", ob),1000,
                      jingmai_effect(ob, "dex")+query_temp("apply/attribute", ob)+query_temp("apply/dex", ob),1000);

        sp += sprintf(HIC "��Ǳ�����ޡ�" HIM " %9d / %-9d"
                      HIC "��������ޡ�" HIM " %9d / %d\n"
                      HIC "���������ޡ�" HIM " %9d / %-9d"
                      HIC "���������ޡ�" HIM " %9d / %d\n"
                      HIC "����Ѫ���ޡ�" HIM " %9d / %-9d"
                      HIC "���������ޡ�" HIM " %9d / %d\n",
                      jingmai_effect(ob, "pot")+query_temp("apply/max_potential", ob),10000000,
                      jingmai_effect(ob, "mar")+query_temp("apply/max_experience", ob),10000000,
                      jingmai_effect(ob, "neili")+query_temp("apply/max_neili", ob),1000000,
                      jingmai_effect(ob, "jingli")+query_temp("apply/max_jingli", ob),5000000,
                      jingmai_effect(ob, "qi")+query_temp("apply/max_qi", ob),1000000,
                      jingmai_effect(ob, "jing")+query_temp("apply/max_jing", ob),500000);

        sp += sprintf(HIC "���о�������" HIY " %9d / %-9d"
                      HIC "���о�Ч����" HIY " %9s / %s\n"
                      HIC "����ϰ������" HIY " %9d / %-9d"
                      HIC "����ϰЧ����" HIY " %9s / %s\n"
                      HIC "��ѧϰ������" HIY " %9d / %-9d"
                      HIC "��ѧϰЧ����" HIY " %9s / %s\n"
                      HIC "����ȡ���ġ�" HIY " %9d / %-9d"
                      HIC "����ȡЧ����" HIY " %9s / %s\n",
                      jingmai_effect(ob, "research_times")+query_temp("apply/research_times", ob),3000,
                      jingmai_effect(ob, "research_effect")+query_temp("apply/research_effect", ob)+"%","1500%",
                      jingmai_effect(ob, "practice_times")+query_temp("apply/practice_times", ob),3000,
                      jingmai_effect(ob, "practice_effect")+query_temp("apply/practice_effect", ob)+"%","1500%",
                      jingmai_effect(ob, "learn_times")+query_temp("apply/learn_times", ob),3000,
                      jingmai_effect(ob, "learn_effect")+query_temp("apply/learn_effect", ob)+"%","1500%",
                      jingmai_effect(ob, "derive_times")+query_temp("apply/derive_times", ob),3000,
                      jingmai_effect(ob, "derive_effect")+query_temp("apply/derive_effect", ob)+"%","1500%");

        sp += sprintf(WHT "�������ȼ���" HIW " %9d / %-9d"
                      WHT "�������ȼ���" HIW " %9d / %d\n"
                      WHT "�������ȼ���" HIW " %9d / %-9d"
                      WHT "���мܵȼ���" HIW " %9d / %d\n"
                      WHT "���������С�" HIW " %9s / %-9s"
                      WHT "�����з�����" HIW " %9s / %s\n"
                      WHT "�������˺���" HIG " %9d / %-9d"
                      WHT "�������˺���" HIG " %9d / %d\n"
                      WHT "�������˺���" HIG " %9s / %-9s"
                      WHT "��ս��������" HIG " %9d / %d\n"
                      WHT "�������˺���" HIG " %9d / %-9d"
                      WHT "�����ӱ�����" HIG " %9d / %d\n"
                      /*
                      WHT "�������˺���" HIG " %9d / %-9d"
                      WHT "�����챣����" HIG " %9d / %d\n"
                      */
                      WHT "�������мܡ�" HIY " %9s / %-9s"
                      WHT "�����Ӷ�����" HIY " %9s / %s\n"
                      WHT "�����ӹ�����" HIY " %9s / %-9s"
                      WHT "�������ڹ���" HIY " %9s / %s\n",
                      jingmai_effect(ob, "attack")+query_temp("apply/attack", ob),3000,
                      jingmai_effect(ob, "defense")+query_temp("apply/defense", ob),3000,
                      query_temp("apply/dodge", ob),3000,query_temp("apply/parry", ob),3000,
                      query_temp("apply/ap_power", ob)+"%","200%",query_temp("apply/dp_power", ob)+"%","200%",
                      jingmai_effect(ob, "damage")+query_temp("apply/damage", ob),200000,
                      jingmai_effect(ob, "damage")+query_temp("apply/unarmed_damage", ob),200000,
                      jingmai_effect(ob, "da_damage")+query_temp("apply/da_power", ob)+"%","200%",
                      jingmai_effect(ob, "armor")+query_temp("apply/armor", ob),200000,
                      query_temp("apply/damage1", ob),200000,query_temp("apply/armor1", ob),200000,
                      //query_temp("apply/damage2", ob),200000,query_temp("apply/armor2", ob),200000,
                      query_temp("apply/avoid_parry", ob)+"%","90%",query_temp("apply/avoid_dodge", ob)+"%","90%",
                      query_temp("apply/avoid_attack", ob)+"%","90%",query_temp("apply/avoid_force", ob)+"%","90%");

        sp += sprintf(RED "���� �� ����" RED " %9s / %-9s"
                      RED "����    ����" RED " %9s / %s\n"
                      RED "���� �� ����" RED " %9s / %-9s"
                      RED "����    ��" RED " %9s / %s\n"
                      RED "��ľ �� ����" RED " %9s / %-9s"
                      RED "����    ľ��" RED " %9s / %s\n"
                      RED "��ˮ �� ����" RED " %9s / %-9s"
                      RED "����    ˮ��" RED " %9s / %s\n"
                      RED "���� �� ����" RED " %9s / %-9s"
                      RED "����    ��" RED " %9s / %s\n"
                      RED "���� �� ����" RED " %9s / %-9s"
                      RED "����    ����" RED " %9s / %s\n",
                      query_temp("apply/add_poison", ob)+"%","90%",query_temp("apply/reduce_poison", ob)+"%","90%",
                      query_temp("apply/add_metal", ob)+"%","90%",query_temp("apply/avoid_metal", ob)+"%","90%",
                      query_temp("apply/add_wood", ob)+"%","90%",query_temp("apply/avoid_wood", ob)+"%","90%",
                      query_temp("apply/add_water", ob)+"%","90%",query_temp("apply/avoid_water", ob)+"%","90%",
                      query_temp("apply/add_fire", ob)+"%","90%",query_temp("apply/avoid_fire", ob)+"%","90%",
                      query_temp("apply/add_earth", ob)+"%","90%",query_temp("apply/avoid_earth", ob)+"%","90%");
                              
        sp += sprintf(HIB "�������ָ���" HIB " %9d / %-9d"
                      HIB "�������ָ���" HIB " %9d / %d\n"
                      HIB "�������ָ���" HIB " %9d / %-9d"
                      HIB "����ת������" HIB " %9s / %s\n"
                      HIB "��͵ȡ������" HIB " %9s / %-9s"
                      HIB "��͵ȡ������" HIB " %9s / %s\n"
                      HIB "�����⽱����" HIB " %9s / %-9s"
                      HIB "�����⾭�顿" HIB " %9s / %s\n"
                      HIB "������Ǳ�ܡ�" HIB " %9s / %-9s"
                      HIB "��������᡿" HIB " %9s / %s\n"
                      HIB "������������" HIB " %9s / %-9s"
                      HIB "������æ�ҡ�" HIB " %9s / %s\n",
                      query_temp("apply/ref_neili", ob),500,query_temp("apply/ref_qi", ob),200,
                      query_temp("apply/ref_jing", ob),200,query_temp("apply/qi_vs_neili", ob)+"%","90%",
                      query_temp("apply/suck_neili", ob)+"%","90%",query_temp("apply/suck_qi", ob)+"%","90%",
                      query_temp("apply/add_reward", ob)+"%","120%",query_temp("apply/add_exp", ob)+"%","210%",
                      query_temp("apply/add_pot", ob)+"%","210%",query_temp("apply/add_mar", ob)+"%","210%",
                      query_temp("apply/add_force", ob)+"%","210%",query_temp("apply/avoid_busy", ob)+"%","90%");
                      
        sp += sprintf(WHT "��Ѱ �� �ʡ�" HIM " %9s / %-9s"
                      WHT "��Ѱ �� �ʡ�" HIM " %9s / %s\n"
                      WHT "��ɱ    ¾��" CYN " %9s / %-9s"
                      WHT "����    ����" CYN " %9s / %s\n"
                      WHT "��˫���˺���" CYN " %9s / %-9s"
                      WHT "����    �ס�" CYN " %9s / %s\n"
                      WHT "����    ä��" CYN " %9s / %-9s"
                      WHT "��������ä��" CYN " %9s / %s\n"
                      WHT "����ħ���塿" CYN " %9s / %-9s"
                      WHT "��ս���塿" CYN " %9s / %s\n",
                      query_temp("apply/gold_find", ob)+"%","100%",
                      jingmai_effect(ob, "magic_find")+query_temp("apply/magic_find", ob)+"%","300%",
                      query_temp("apply/slaughter", ob)+"%","90%",query_temp("apply/clear_force", ob)+"%","90%",
                      query_temp("apply/double_damage", ob)+"%","200%",query_temp("apply/through_armor", ob)+"%","90%",
                      query_temp("apply/add_blind", ob)+"%","90%",query_temp("apply/avoid_blind", ob)+"%","90%",
                      query_temp("apply/absorb_blood", ob)+"%","90%",query_temp("apply/full_self", ob)+"%","90%");
                      

        sp += sprintf(HIY "����    ����" HIM " %9s / %-9s"
                      HIY "�����ӱ�����" HIM " %9s / %s\n"
                      HIY "��ѣ    �Ρ�" HIM " %9s / %-9s"
                      HIY "������ѣ�Ρ�" HIM " %9s / %s\n"
                      HIY "����    ����" HIM " %9s / %-9s"
                      HIY "������������" HIM " %9s / %s\n"
                      HIY "��æ    �ҡ�" HIM " %9d / %-9d"
                      HIY "������æ�ҡ�" HIM " %9d / %d\n"
                      HIY "����    ����" HIM " %9s / %-9s"
                      HIY "������������" HIM " %9s / %s\n"
                      HIY "��׷���˺���" HIM " %9s / %-9s"
                      HIY "�������˺���" HIM " %9s / %s\n"
                      HIY "���˺����ɡ�" HIM " %9s / %-9s"
                      HIY "��ԡѪ������" HIM " %9s / %s\n"                      
                      HIY "���� ɱ �ʡ�" HIM " %9s / %-9s"
                      HIY "���������ܡ�" HIM " %9d / %d\n",
                      query_temp("apply/add_freeze", ob)+"%","90%",query_temp("apply/avoid_freeze", ob)+"%","90%",
                      query_temp("apply/add_dizziness", ob)+"%","90%",query_temp("apply/avoid_dizziness", ob)+"%","90%",                    
                      query_temp("apply/add_forget", ob)+"%","90%",query_temp("apply/avoid_forget", ob)+"%","90%",
                      query_temp("apply/add_busy", ob),90,query_temp("apply/reduce_busy", ob),90,
                      query_temp("apply/add_weak", ob)+"%","90%",query_temp("apply/avoid_weak", ob)+"%","90%",
                      query_temp("apply/add_damage", ob)+"%","200%",
                      jingmai_effect(ob, "reduce_damage")+query_temp("apply/reduce_damage", ob)+"%","90%",
                      query_temp("apply/counter_damage", ob)+"%","90%",query_temp("apply/avoid_die", ob)+"%","90%",
                      query_temp("apply/fatal_blow", ob)+"%","90%",query_temp("apply/add_skill", ob),3000);

        sp += HIC "��" HIY "��������������������������������������������������������������" HIC "��\n" NOR;

        sp += sprintf(HIG + (ob == me ? "��" : ob->name()) + HIG "��%s���Ѿ������� " NOR + HIC "%s\n" NOR,
                        LOCAL_MUD_NAME(), time_period(query("online_time", ob)));

        /*
        if (MEMBER_D->is_valid_member(ob))
                sp += sprintf(HIG + (ob == me ? "��" : ob->name()) + HIG "��������������ʱ�仹�� " NOR + HIY "������\n" NOR);
        else
        */
        {
                if( query("online_time", ob)/3<query("offline_time", ob) )
                        set("offline_time",query("online_time",  ob)/3, ob);
                sp += sprintf(HIG + (ob == me ? "��" : ob->name()) + HIG "��������������ʱ�仹�� " NOR + HIY "%s\n" NOR,
                              time_period(query("online_time", ob)/3-query("offline_time", ob)));
        }

        sp += sprintf(HIG + (ob == me ? "��" : ob->name()) + HIG "�����˫������ʱ�仹�� " NOR + HIW "%s\n" NOR,
                      time_period(query("time_reward/quest", ob)));
        sp += sprintf(HIG + (ob == me ? "��" : ob->name()) + HIG "����ĸ�Ч����ʱ�仹�� " NOR + HIM "%s\n" NOR,
                      time_period(query("time_reward/study", ob)));


        me->start_more(sp);
        return 1;
}
