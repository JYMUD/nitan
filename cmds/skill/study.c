// Written by Lonely@ChinaMUD.cn
// study.c

#include <skill.h>
#include <command.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object where = environment(me);
        object ob;
        string zhao_name, book_name;
        mixed sname;
        string *args;
        string *fams;
        mapping skill, needs;
        string *need_sk;
        mixed need_lvl;
        int my_skill, cost, times, i;
        int lvl, neili_cost, t1, t2, t3, t4;
        int c, r;
        int t = time();

        if( !arg )
                return notify_fail("��Ҫ��ʲô��\n");

        if( query("pigging", where) )
                return notify_fail("�㻹��ר�Ĺ���ɣ�\n");

        if( me->is_busy() )
                return notify_fail(BUSY_MESSAGE); 
        
        if( t == query_temp("time/study", me) )
                return notify_fail("��ողŶ����飨�����Ҫ�������飬����ָ������Ĵ�������\n");
        
        if( me->is_fighting() )
                return notify_fail("���޷���ս����ר�������ж���֪��\n");

        if( !arg || (i = sizeof(args = explode(arg, " "))) < 1)
                return notify_fail("ָ���ʽ��study|du <�鼮> <����>\n");

        i--;
        if( i >= 1 && sscanf(args[i], "%d", times) && times)
                i--;
        else
                times = 1;
        if( args[i] == "with" && i >= 1 )
                i--;
        book_name = implode(args[0..i], " ");

        c=200+query_temp("apply/study_times", me);
        if( present("study emblem", me) ) 
                c += 300;

        if( query("special_skill/wisdom", me) )
                c += 800;
                
        if( times < 1 || times > c)
                return notify_fail("�����������һ�Σ����Ҳ"
                                   "���ܳ���" + chinese_number(c) + "�Ρ�\n");

        if( !objectp(ob = present(book_name, me)) )
                return notify_fail("û�Ȿ��ɶ�����\n");

        if( !mapp(skill=query("skill", ob)) )
                return notify_fail("���޷�����������ѧ���κζ�����\n");

        if( !me->query_skill("literate", 1) )
                return notify_fail("���Ǹ���ä����ѧ���Ļ�(literate)�ɡ�\n");

        if( query("no_fight", environment(me)) && 
            //(query("doing", me) != "scheme" || this_player(1)) )
            (query("doing", me) != "scheme") )
                return notify_fail("���޷�������ط����Ķ��顣\n");

        message("vision", me->name() + "��ר�ĵ��ж�" + ob->name() +
                "��\n", environment(me), me);

        if( query("combat_exp", me)<skill["exp_required"]){
                write("���ʵս���鲻�㣬����ô��Ҳû�á�\n");
                return 1;
        }

        if( !undefinedp(skill["family_name"]) ) {
                fams = query("reborn/fams", me);
                if( !me->query_family() || (me->query_family() != skill["family_name"] && 
                    (!arrayp(fams) || member_array(skill["family_name"], fams) == -1)) )
                {
                        write("���" + skill["family_name"] + "�������ķ����˽⣬����ô��Ҳû�á�\n");
                        return 1;
                }
        }

        if( skill["difficulty"] - (int)me->query_int() > 0 )
                return notify_fail("����Ŀǰ����������û�а취ѧ������ܣ��㻹�Ƕ�ѧ���Ļ��ɡ�\n");
             
        cost = skill["jing_cost"] + skill["jing_cost"] 
                * (skill["difficulty"] - (int)me->query_int())/12;
        if( cost < 1 ) cost = 1;

        if( mapp(needs=query("skill/need", ob))){
                foreach( need_sk in keys(needs) ) {
                        // check all skills
                        need_lvl = needs[need_sk];
                        if( functionp(need_lvl) )
                                need_lvl = evaluate(need_lvl);
                        else
                        if( !intp(need_lvl) )
                                need_lvl = 0;

                        if( me->query_skill(need_sk, 1) < need_lvl )
                                // not reach the line
                                return notify_fail("���ж���һ��������������ͨ��" +
                                                   to_chinese(need_sk) +
                                                   "�Ļ������������������ĺ��塣\n");
                        // check next skill
                }
        }

        sname=query("skill/name", ob);
        if( functionp(sname) )
                sname = evaluate(sname, ob);  
        notify_fail("����Ŀǰ����������û�а취ѧ������ܡ�\n");
        if( !SKILL_D(sname)->valid_learn(me) )
                return 0;

        if( !XUE_CMD->can_learn(me, sname) )
                return 0;

        if( me->query_skill(sname, 1) > skill["max_skill"] )
                return notify_fail("���ж���һ��������Ƿ���"
                                   "������˵�Ķ�����Զ�̫ǳ"
                                   "�ˣ�û��ѧ���κζ�����\n");

        if( me->query_skill(sname, 1) < skill["min_skill"] )
                return notify_fail("���ж���һ���������ȴ����"
                                   "������ż��ܵ���⻹̫ǳ"
                                   "����������ջ�\n");

        if( !me->query_skill(sname, 1) )
                me->set_skill(sname, 0);

        my_skill = me->query_skill(sname, 1);
        if( !me->can_improve_skill(sname) ) {
                return notify_fail("Ҳ����ȱ��ʵս���飬���" +
                                   ob->name() + "������˵��"
                                   "���������޷���ᡣ\n");
        }

        set_temp("time/study", t, me);
        r = (int)me->query_skill("literate", 1) / 2 + 1;
        r+=r*query_temp("apply/study_effect", me)/100;
        if( query("time_reward/study", me) )
                r += r * 50 / 100; 
                
        t1=query("jing", me)/cost;
        t2 = times - t1;
        if( t2 > 0 ) {
                lvl = me->query_skill("force");
                if( lvl <= 0 ) lvl = 1;

                neili_cost =  cost * 60 / lvl;
                if( query("breakup", me) )
                        neili_cost = neili_cost * 7 / 10;

                if( neili_cost < 20 ) neili_cost = 20;

                if( query("neili", me) >= neili_cost*t2){
                        t4 = times;
                        addn("neili", -neili_cost*t2, me);
                } else {
                        t3=query("neili", me)/neili_cost;
                        t4 = t1 + t3;
                        if( t4 == 0 ) {
                               write("������̫���ˣ����һ��Ҳû�п���ȥ��\n");
                                return 1;
                        }

                        set("neili", 0, me);
                }
        } else
                t4 = times;

        if( times > t1 )
                me->receive_damage("jing", cost * t1);
        else
                me->receive_damage("jing", cost * times);

        if( query("env/auto_regenerate", me) )
                SKILL_D("force/regenerate")->exert(me, me);

        me->improve_skill(sname, r * t4);

        if( zhao_name = SKILL_D(sname)->query_skill_name(my_skill) )
                write(sprintf("���ж���" + chinese_number(t4) +
                      "���й�%s�ļ��ɣ��ԡ�%s����һ���ƺ���Щ�ĵá�\n",
                      to_chinese(sname), zhao_name));
        else
                write(sprintf("���ж���"+chinese_number(t4) +
                      "���й�%s�ļ��ɣ��ƺ��е��ĵá�\n",
                      to_chinese(sname)));

        if( t4 < times )
                write("�������Ѿ�����ƣ�룬�޷������ж���֪��\n");

        return 1;
}

int help(object me)
{
        write( @HELP
ָ���ʽ: study|du <��Ʒ����> [����]
          study|du <��Ʒ����> with [����]

���ָ��ʹ�����ͨ���Ķ����Ż�������Ʒ��ѧĳЩ����, ��ǰ��
��: �㲻���Ǹ�����ä���������㲻���ڲ���ս���ĵط����顣

see also : learn
HELP );
        return 1;
}
