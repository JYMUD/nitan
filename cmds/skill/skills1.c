// skills.c

#include <ansi.h>

inherit F_CLEAN_UP;

string *valid_types = ({
        "force",
        "dodge",
        "unarmed",
        "cuff",
        "strike",
        "finger",
        "hand",
        "claw",
        "sword",
        "blade",
        "staff",
        "hammer",
        "club",
        "whip",
        "dagger",
        "throwing",
        "parry",
        "magic",
        "medical",
        "poison",
        "chuixiao-jifa",
        "tanqin-jifa",
        "guzheng-jifa",
        "cooking",
});

string *skill_level_desc = ({
        BLU"����һ��",BLU"��������",BLU"����ҳ�",BLU"��ѧէ��",BLU"����ǿǿ",
        HIB"�����ž�",HIB"����é®",HIB"��֪һ��",HIB"����ͨͨ",HIB"ƽƽ����",
        CYN"ƽ������",CYN"��ͨƤë",CYN"��������",CYN"������",CYN"����С��",
        HIC"����С��",HIC"������Ⱥ",HIC"�������",HIC"�������",HIC"�ڻ��ͨ",
        HIG"�������",HIG"¯����",HIG"��Ȼ����",HIG"���д��",HIG"���д��",
        YEL"��Ȼ��ͨ",YEL"�������",YEL"�޿�ƥ��",YEL"����Ⱥ��",YEL"����似",
        HIY"�����뻯",HIY"��ͬ����",HIY"����Ⱥ��",HIY"�Ƿ��켫",HIY"�����ױ�",
        RED"��������",RED"һ����ʦ",RED"�������",RED"�񹦸���",RED"������˫",
        WHT"��������",WHT"���춯��",WHT"������",WHT"������ʥ",WHT"�������",
        HIW"��ǰ����",HIW"���˺�һ",MAG"��ز�¶",HIM"��ɲ�",HIR"��豹���"
});

string *knowledge_level_desc = ({
        BLU"��ѧէ��",BLU"�����ž�",HIB"��֪һ��",HIB"��������",
        CYN"������",CYN"����С��",HIC"�ڻ��ͨ",HIC"�������",
        GRN"��Ȼ���",GRN"��Ȼ��ͨ",YEL"��ͬ����",YEL"������˫",
        HIY"������",RED"�����ױ�",WHT"������ʥ",HIW"��ǰ����",
});

int sort_skill(string sk1, string sk2, mapping spos);
int filter_for_enable(string skill, string skill1);
int filter_for_main(string skill, string skill1);
int filter_for_combine(string skill, string skill1);
string skill_level(string type, int level)
{
        int grade;


        switch(type)
        {
                case "knowledge":
                        grade = level / 200;
                        if( grade >= sizeof(knowledge_level_desc) )
                                grade = sizeof(knowledge_level_desc)-1;
                        return knowledge_level_desc[grade];
                default:
                        grade = level / 100;
                        if( grade < 0 ) grade = 0;
                        if( grade >= sizeof(skill_level_desc) )
                                grade = sizeof(skill_level_desc)-1;
                        return skill_level_desc[grade];
        }
}

int main(object me, string arg)
{
        object ob;
        mapping skl, lrn, map;
        string *sname, *mapped;
        string str, skill1;
        string skillname, skcolor;
        string *basic;
        mixed  *lists;
        string *others;
        string fname;
        int valid_check;
        int lvl;
        int i, k;

        seteuid(getuid());

        skill1 = 0;
        if (! arg)
                ob = me;
        else
        {
                string *temp;
                if (sscanf(arg, "%s of %s", skill1, arg) == 2)
                        ; else
                if (temp = explode(arg, " "))
                {
                        if (sizeof(temp) < 2)
                                arg = "me";
                        else
                                arg = implode(temp[0..sizeof(temp) - 2], " ");
                        skill1 = temp[sizeof(temp) - 1];

                        if (file_size(SKILL_D(skill1) + ".c") <= 0)
                        {
                                if (sizeof(temp) < 2)
                                        arg = skill1;
                                else
                                        arg += " " + skill1;
                                ob = present(arg, environment(me));
                                skill1 = 0;
                        }
                } else
                {
                        // if the user was not wizard, I will
                        // treat the arg as skill1, and the
                        // object he check is hiself.
                        if (! wizardp(me) && (! (ob = present(arg, environment(me))) ||
                            ! ob->is_character() ||
                            ! me->is_apprentice_of(ob)))
                        {
                                skill1 = arg;
                                arg = "me";
                        }
                }

                if (ob && ! ob->is_character())
                        ob = 0;

                if (skill1 && file_size(SKILL_D(skill1) + ".c") <= 0)
                {
                        if (objectp(ob))
                        {
                                arg = 0;
                                skill1 = 0;
                        } else
                                return notify_fail("û��(" + skill1 +
                                                   ")���ּ��ܡ�\n");
                }

                if (! ob || ! ob->is_character())
                {
                        if (arg == "me")
                                ob = me;
                        else
                                ob = present(arg, environment(me));

                        if (! ob || ! ob->is_character()) ob = find_player(arg);
                        if (! ob || ! ob->is_character()) ob = find_living(arg);
                }

                if (! ob || ! ob->is_character() || ! me->visible(ob))
                        return notify_fail("��Ҫ�쿴˭�ļ��ܣ�\n");
        }

        if (ob != me)
        {
                // call the player, if the player has override the
                // the function & return a nonzero valud, I will
                // return success.
                if ((int)ob->skills(me, skill1))
                        return 1;
        }

        if (ob == me || wizardp(me) ||
            ob->is_apprentice_of(me) ||
            me->is_apprentice_of(ob) ||
            query("couple/couple_id", me) == query("id", ob) || 
            query("couple/child_id", me) == query("id", ob) || 
            me->is_brother(ob) || ob->is_owner(me))
                valid_check = 1;
        else
        {
                fname=query("league/league_name", me);
                if( stringp(fname) && fname == query("league/league_name", ob) )
                        valid_check = 1;
                else
                if( !playerp(ob) && stringp(fname=query("bunch/bunch_name", me)) && 
                    fname == query("bunch/bunch_name", ob) )
                        valid_check = 1;
                else
                        valid_check = 0;
        }

        if (! valid_check)
                return notify_fail("ֻ����ʦ����ʦͽ/����/���/ͬ�˹�ϵ����"
                                   "���ܲ쿴���˵ļ��ܡ�\n");

        skl = ob->query_skills();
        if (! sizeof(skl))
        {
                write((ob==me ? "��" : ob->name()) +
                      "Ŀǰ��û��ѧ���κμ��ܡ�\n");
                return 1;
        }

        // calucate spos to sort
        sname = keys(skl);

        str = (ob == me ? "��" : ob->name()) + "Ŀǰ��ѧ����";
        // filter array by skill1
        if (skill1)
        {
                // filter the skill array by skill1
                if (member_array(skill1, valid_types) != -1)
                {
                        // skill1 is a basic skill
                        sname = filter_array(sname, (: filter_for_enable :), skill1);
                        // sname = sort_array(sname, (: sort_skill :), ob);
                        sname = sort_array(sname, (: $(skl)[$2] - $(skl)[$1] :));
                        str += to_chinese(skill1) + "����ؼ���";
                } else
                if (SKILL_D(skill1)->main_skill() &&
                    member_array(SKILL_D(skill1)->main_skill(), sname) == -1)
                {
                        // skill1 is a sub skill
                        skill1 = SKILL_D(skill1)->main_skill();
                        sname = filter_array(sname, (: filter_for_main :), skill1);
                        str += to_chinese(skill1) + "�е���ʽ";
                } else
                {
                        sname = filter_array(sname, (: filter_for_combine :), skill1);
                        str += to_chinese(skill1) + "�Ϳ��Լ����Ļ����似���ܹ������ļ���";
                }
        } else
                str += "���м���";

        if (! sizeof(sname))
        {
                write("��Ŀǰ��û�����ոü��ܡ�\n");
                return 1;
        }

        // sort all the skills
        // select all the basic skill of the skill list
        basic = filter_array(valid_types, (: member_array($1, $(sname)) != -1 :));

        // allocate the string array for each basic skill
        lists = allocate(sizeof(basic));

        // allocate the other skill for none apply to all the basic skill
        others = ({ });

        // select out all the special skill & other skill
        sname -= basic;
        for (i = 0; i < sizeof(sname); i++)
        {
                // let's check every special skill & other skill
                if (! sname[i]) continue;

                // enable for basic skill
                for (k = 0; k < sizeof(basic); k++)
                {
                        string main_skill;

                        if (file_size(SKILL_D(sname[i]+".c")) < 0)
                                log_file("skills", sprintf("the file %s is no exists.\n", SKILL_D(sname[i]+".c")));
                        if (SKILL_D(sname[i])->valid_enable(basic[k]))
                        {
                                // yes, I record this special skill
                                if (! lists[k])
                                        lists[k] = ({ sname[i] });
                                else
                                        lists[k] += ({ sname[i] });

                                // Is this a sub skill ?
                                if (main_skill = SKILL_D(sname[i])->main_skill())
                                {
                                        // yes, I select out all the other sub skills
                                        int st;
                                        for (st = i + 1; st < sizeof(sname); st++)
                                        {
                                                if (! sname[st]) continue;
                                                if (file_size(SKILL_D(sname[st]+".c")) < 0)
                                                        log_file("skills", sprintf("the file %s is no exists.\n", SKILL_D(sname[st]+".c")));
                                                if (sname[st] &&
                                                    SKILL_D(sname[st])->main_skill() == main_skill)
                                                {
                                                        // record it
                                                        lists[k] += ({ sname[st] });
                                                        sname[st] = 0;
                                                }
                                        }
                                }

                                break;
                        }
                }

                if (k == sizeof(basic))
                        // It can enable on basic skill, it must be a others skill
                        others += ({ sname[i] });
        }

        // let me combine all the skill in string array: sname
        sname = ({ });
        for (i = 0; i < sizeof(basic); i++)
        {
                sname += ({ basic[i] });
                if (lists[i]) sname += lists[i];
        }

        sname += others;

        // get the skill map
        map = ob->query_skill_map();
        if (mapp(map)) mapped = values(map);
        if (! mapped) mapped = ({});

        lrn = ob->query_learned();
        if (! mapp(lrn)) lrn = ([]);
        str += "\n\n";
        str += HIC "��" HIY "��������������������������������������������������������������" HIC "��\n" NOR;

        for (i = 0; i < sizeof(sname); i++)
        {
                int percent;
                skillname = to_chinese(sname[i]);
                switch (strlen(skillname))
                {
                case 6:
                        skillname = sprintf("%c%c %c%c %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3],
                                             skillname[4], skillname[5]);
                        break;
                case 4:
                        skillname = sprintf("%c%c    %c%c", skillname[0], skillname[1],
                                             skillname[2], skillname[3]);
                        break;
                }

                if (member_array(sname[i], valid_types) != -1)
                        skcolor = CYN;
                else
                        skcolor = WHT;

                if (! objectp(find_object(SKILL_D(sname[i]))) &&
                    ! objectp(load_object(SKILL_D(sname[i]))))
                {
                        write(HIR "Error(No such skill):" + sname[i] + "\n" NOR);
                        continue;
                }
                lvl = skl[sname[i]];
                percent = lrn[sname[i]] * 100 / ((lvl + 1) * (lvl + 1) + 1);
                if (percent > 100) percent = 100;
                str += sprintf("%s%s%s%-40s" NOR WHT " - %-10s" NOR WHT "%4d/%3d%%\n" NOR,
                        skcolor,
                        (lrn[sname[i]] >= (skl[sname[i]]+1) * (skl[sname[i]]+1)) ? HIM : "",
                        (member_array(sname[i], mapped)==-1? "  ": "��"),
                        skillname + " (" + sname[i] + ")",
                        filter_color(skill_level(SKILL_D(sname[i])->type(), lvl)),
                        lvl, percent);
        }

        str += HIC "��" HIY "��������������������������������������������������������������" HIC "��\n" NOR;
        str = column_string(str, SKILLS_D->skill_mix_stats(ob), 70);
        me->start_more(str);
        return 1;
}

int sort_skill(string sk1, string sk2, object ob)
{
        return ob->query_skill(sk2, 1) - ob->query_skill(sk1, 1);
}

int filter_for_enable(string skill, string skill1)
{
        return (skill == skill1) || (SKILL_D(skill)->valid_enable(skill1));
}

int filter_for_main(string skill, string skill1)
{
        return (SKILL_D(skill)->main_skill() == skill1);
}

int filter_for_combine(string skill, string skill1)
{
        return (SKILL_D(skill1)->valid_enable(skill)) ||
               (SKILL_D(skill)->valid_combine(skill1)) ||
               (skill == skill1);
}

int help(object me)
{
        write(@HELP
ָ���ʽ : skills|cha [<������> of <ĳ�� | me >] | [<ĳ��>]

���ָ���������(��)��ѯ��ѧ���ļ��ܡ�

��Ҳ����ָ��һ��������ʦͽ��ϵ�Ķ����� skills ���Բ�֪�Է��ļ���״����
Ҳ���Բ�ѯĳ��ĳ��ܵ����������skills taiji-shengong of song�� ����
��skills literate of me�� �����ַ�����ѯʱ�����¼��������

1 �����ѯ�ļ�����һ�ֻ����似����ͬʱ�������������ֻ����似�Ļ�������
  ���������书���ܡ�

2 �����ѯ�ļ�����һ���似�е�ĳЩ��ʽ·�������罵��ʮ���ƣ����ǽ���ʮ
  �����е�������β�ȣ�����ʾ���ѧ����֮��ص���ʽ·�����������Ѿ���
  �����似�ڻ��ͨ��������ͨ������ʾ(3)��

3 �����ѯ�ļ�����һ����ͨ���似������ʾ���Լ����Ļ����似�����Ϳ�����
  ֮�������书��

ʹ�ø���������˽���ѧ�����书���ܡ���Ҳ�ѯ��ʱ����Ҫָ��me��������
��ֱ������<������>������

��ʦ���Բ�ѯ�κ��˻� NPC �ļ���״����

HELP
    );
    return 1;
}
