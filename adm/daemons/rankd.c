// rankd.c
// 1996-02-15 dts ranking related to "shen"

#pragma optimize
#pragma save_binary

#include <ansi.h>

string query_rank(object ob)
{
        mapping fam;
        mapping toplist;

        int shen;
        int budd;
        int tao;
        int exp;
        int age;
        int eatman;
        int i;
        string fname;

        if (ob->is_ghost())
                return HIB "�� ��  �� ��" NOR;

        if( query("reborn/times", ob) )
        {
                if( query("reborn/times", ob) == 3 )
                        return HIR "��Ԫ��������" NOR;
                if( query("reborn/times", ob) == 2 )
                        return HIR "��Ԫ�������" NOR;
                return HIR "��Ԫ��ת����" NOR;
        }

        toplist = COMPETE_D->query_tops();

        if (sizeof(toplist))
        {
                for (i = 0;i < sizeof(toplist);i ++)
                        if( toplist[i]["id"] == query("id", ob) )
                                return HIW + "�����µ�" + NOR + HIY +
                                       chinese_number(i + 1) + NOR + HIW + "��" + NOR;
        }

        if( query("is_vendor", ob) )
        {
                if (ob->query_profit() >= 100000000000)
                        return HIY "�� ��  �� ��" NOR;
                else if (ob->query_profit() >= 50000000000)
                        return HIY "����ҵ��ͷ��" NOR;
                else if (ob->query_profit() >= 10000000000)
                        return HIY "���� �� ����" NOR;
                else if (ob->query_profit() >= 5000000000)
                        return HIY "�� ��  �� ��" NOR;
                else if (ob->query_profit() >= 1000000000)
                        return HIY "���� �� ��" NOR;
                else if (ob->query_profit() >= 500000000)
                        return HIY "�� ��  �� ��" NOR;
                else if (ob->query_profit() >= 100000000)
                        return HIY "�� ��  �� ��" NOR;
                else if (ob->query_profit() >= 50000000)
                        return HIY "�� ��  �� ��" NOR;
                else if (ob->query_profit() >= 10000000)
                        return HIY "�� С  �� ��" NOR;
                else    return HIY "�� С  �� ��" NOR;
        }

        shen=query("shen", ob);
        exp=query("exp", ob);
        age=query("age", ob);
        budd = ob->query_skill("buddhism", 1);
        tao  = ob->query_skill("taoism", 1);
        eatman=query("combat/eatman", ob);
        fname=query("family/family_name", ob);

        if( query("rank_info/rank", ob) )
                return HIY"��"+query("rank_info/rank", ob)+"��"NOR;

        switch (fname)
        {
                case "������": budd = ob->query_skill("mahayana", 1); break;
                case "������": budd = ob->query_skill("buddhism", 1); break;
                case "�䵱��":
                case "ȫ���": budd = ob->query_skill("taoism", 1); break;
                case "��ɽ��": budd = ob->query_skill("sword", 1); break;
                case "������":
                case "��ɽ��": budd = ob->query_skill("sword", 1); break;
                case "��Ĺ��": budd = ob->query_skill("yunv-xinfa", 1); break;
                case "Ľ������": budd = ob->query_skill("douzhuan-xingyi", 1); break;
                case "����" :
                        budd = ob->query_skill("jiuyang-shengong", 1);
                        if (!budd)
                                budd = ob->query_skill("shenghuo-shengong", 1);
                        break;
                case"ؤ��":budd=query("family/beggarlvl", ob);break;
                case "������": budd = ob->query_skill("busi-shenlong", 1); break;
                case "���ư�": budd = ob->query_skill("tiezhang-zhangfa", 1); break;
                case "���ϻ���": budd = ob->query_skill("kurong-changong", 1); break;
                case "ѩɽ��": budd = ob->query_skill("longxiang-gong", 1); break;
                case "�һ���": budd = ob->query_skill("qimen-wuxing", 1); break;
                case "��������":
                case "�嶾��":
                case "������": budd = ob->query_skill("poison", 1);     break;
                case "�������": budd = ob->query_skill("xixing-dafa", 1);      break;
                case "��ң��": budd = ob->query_skill("beiming-shengong", 1);   break;
                case "���չ�": budd = ob->query_skill("bahuang-gong", 1);       break;
                case "�������": budd = ob->query_skill("lengyue-shengong", 1); break;
                case "ŷ������": budd = ob->query_skill("hamagong", 1); break;
                case "Ѫ����": budd = ob->query_skill("xuedao-daofa", 1);       break;
                case "ħ��": budd = ob->query_skill("moon-blade", 1);   break;
        } // switch (fname)

        switch(query("gender", ob) )
        {
                case "����":
                        switch(wizhood(ob))
                        {
                                case "(boss)": return HIW "�� ��  �� ��" NOR;
                                case "(admin)": return HIW "�� ��  �� ��" NOR;
                                case "(assist)": return HIR "�� ��  �� ��" NOR;
                                case "(arch)": return HIY "�� ��  �� ��" NOR;
                                case "(wizard)": return HIG "�� ��  �� ��" NOR;
                                case "(apprentice)": return HIC "�� ��  Ů ��" NOR;
                                case "(immortal)": return HIC "�� ��  �� ��" NOR;
                                default:
                                        budd = (int)ob->query_skill("pixie-jian", 1);
                                        if( budd >= 2000) return HIR "�� ��ǧ�� ��"NOR;
                                        if( budd >= 1800) return HIR "�� ��  �� ��"NOR;
                                        if( budd >= 1500) return HIR "�� ��ͷ ��"NOR;
                                        if( budd >= 1200) return HIM "������ǧ����"NOR;
                                        if( budd >= 900)  return MAG "�������ٻ���"NOR;
                                        if( budd >= 600) return MAG "��̫���ܹܡ�"NOR;
                                        if( budd >= 300) return MAG "�� ̫  �� ��"NOR;
                                        return MAG "�� С̫�� ��" NOR;
                        }
                case "Ů��":
                case "����":
                        switch(wizhood(ob))
                        {
                                case "(boss)": return HIW "�� ��  �� ��" NOR;
                                case "(admin)": return HIW "�� ��  �� ��" NOR;
                                case "(assist)": return HIR "�� Ů��� ��" NOR;
                                case "(arch)": return HIY "�� ��  Ů ��" NOR;
                                case "(wizard)": return HIG "�� ��  �� ��" NOR;
                                case "(apprentice)": return HIC "�� ��  �� ��" NOR;
                                case "(immortal)": return HIC "�� Ů���� ��" NOR;
                                default:
                                        if( query("combat/PKS", ob) > 20 && query("combat/PKS", ob) > query("combat/MKS", ob) / 4 )
                                                return HIR "��ɱ��Ůħ��" NOR;
                                        if( query("thief", ob)>10 )
                                                return "�� Ů���� ��";
                                        switch(fname) {
                                                case "����":
                                                        if(budd >= 2000) return HIR "�� ʥ  Ů ��" NOR;
                                                        if(budd >= 1700) return HIR "�������񼧡�" NOR;
                                                        if(budd >= 1400) return RED "�� ������ ��" NOR;
                                                        if(budd >= 1000) return RED "������������" NOR;
                                                        if(budd >= 600) return HIM "�� Ů���� ��" NOR;
                                                        if(budd >= 200) return CYN "�� Ů���� ��" NOR;
                                                        return CYN "�� ��  Ů ��" NOR;
                                                case "ؤ��":
                                                        if(budd >= 11) return HIW "�� ��  �� ��" NOR;
                                                        if(budd >= 10) return HIW "�� ������ ��" NOR;
                                                        if(budd >= 9) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 6) return HIG "�� ��  ͷ ��" NOR;
                                                        if(budd >= 5) return HIM "�� Ů���� ��" NOR;
                                                        if(budd >= 4) return HIM "�� Ů���� ��" NOR;
                                                        if(budd >= 2) return HIM "�� Ů���� ��" NOR;
                                                        return CYN "�� �л��� ��" NOR;
                                                case "������":
                                                        if( query("class", ob) != "bonze")break;
                                                        if (budd >= 600) return HIW "�� ��  �� ��" NOR;
                                                        if (budd >= 400) return HIW "�� ��  �� ��" NOR;
                                                        if (budd >= 90)  return HIW "�� ʦ  ̫ ��" NOR;
                                                        if (budd >= 60) return HIW "�� ������ ��" NOR;
                                                        if (budd >= 30 || age >= 20) return HIW "�� ɳ���� ��" NOR;
                                                        return HIW "�� ѧ��Ů ��" NOR;
                                                case "ѩɽ��":
                                                        if (budd >= 1800 && shen >= 0) return HIY "�� ��ϲ�� ��" NOR;
                                                        if (budd >= 1800 && shen < 0) return HIY "�� ��ϲħ ��" NOR;
                                                        if (budd >= 1400) return HIW "�� ��  Ů ��" NOR;
                                                        if (budd >= 900)  return HIW "�� ��  �� ��" NOR;
                                                        if (budd >= 600) return HIW "�� Ǭ���� ��" NOR;
                                                        if (budd >= 300 || age >= 20) return HIW "�� ����Ů ��" NOR;
                                                        return HIW "�� ��  �� ��" NOR;
                                                case "�һ���":
                                                        if (budd >= 1800) return HIW "�� ��  �� ��" NOR;
                                                        if (budd >= 1400) return HIC "�� ��  �� ��" NOR;
                                                        if (budd >= 1000) return WHT "�� ��  ʿ ��" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "�� ��  �� ��" NOR;
                                                        return "�� ��  Ů ��";
                                                case "��ң��":
                                                        if (budd >= 1800) return HIW "�� ��  �� ��" NOR;
                                                        if (budd >= 1400) return HIC "�� ��  �� ��" NOR;
                                                        if (budd >= 1000) return WHT "�� ��  ʿ ��" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "�� ��  �� ��" NOR;
                                                        return "�� ��  Ů ��";
                                                case "��ɽ��":
                                                        if (budd >= 1400) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 1000) return HIC "�� Ů���� ��" NOR;
                                                        if (budd >= 500 || age >= 18)  return YEL "�� Ů���� ��" NOR;
                                                        return "�� Ů���� ��";
                                                case "��ɽ��":
                                                case "������":
                                                        if (budd >= 1800) return HIW "�� ��  ʥ ��" NOR;
                                                        if (budd >= 1400) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 1000) return HIC "�� Ů���� ��" NOR;
                                                        if (budd >= 500 || age >= 18)  return YEL "�� Ů���� ��" NOR;
                                                        return "�� Ů���� ��";
                                                case "��Ĺ��":
                                                        if (budd >= 1800) return HIW "�� ��  Ů ��" NOR;
                                                        if (budd >= 1400) return HIY "�� ٻ  Ů ��" NOR;
                                                        if (budd >= 1000) return HIC "�� ��  Ů ��" NOR;
                                                        if (budd >= 500 || age >= 18)  return YEL "�� ��  Ů ��" NOR;
                                                        return "�� ��  ͯ ��";
                                                case "�䵱��":
                                                case "ȫ���":
                                                        if (budd >= 600) return HIY "�� ��  Ů ��" NOR;
                                                        if (budd >= 400) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 100) return HIY "�� ɢ  �� ��" NOR;
                                                        if (budd >= 50 || age >= 20) return HIY "�� ��  �� ��" NOR;
                                                        return "�� С���� ��";
                                                case "���ư�":
                                                        if (budd >= 1800) return WHT "�� �󵱼� ��" NOR;
                                                        if (budd >= 1400) return HIC "�� կ  �� ��" NOR;
                                                        if (budd >= 1000) return CYN "�� ��ͷĿ ��" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "�� ͷ  Ŀ ��" NOR;
                                                        return "�� С��� ��";
                                                case "�嶾��":
                                                case "��������":
                                                case "������":
                                                        if (budd >= 600) return HIB "�� ��  �� ��" NOR;
                                                        if (budd >= 500) return YEL "�� ��  �� ��" NOR;
                                                        if (budd >= 400) return MAG "�� ��  �� ��" NOR;
                                                        if (budd >= 100) return BLU "�� ����ɲ ��" NOR;
                                                        if (budd >= 50 || age >= 18)  return CYN "�� ��  �� ��" NOR;
                                                        return "�� ��ƨ�� ��";
                                                case "Ľ������":
                                                        if(budd >= 1900) return HIC "�� С  �� ��" NOR;
                                                        if(budd >= 1500) return HIC "�� ׯ  �� ��" NOR;
                                                        if(budd >= 1100) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 700) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 300) return HIC "�� ��Ѿ�� ��" NOR;
                                                        return HIC "�� Ѿ  �� ��" NOR;
                                                case "���չ�":
                                                        if(budd >= 1900) return HIC "�� ��  Ů ��" NOR;
                                                        if(budd >= 1500) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 1100) return HIC "�� ��  Ů ��" NOR;
                                                        if(budd >= 700) return HIC "����ңŮ�ɡ�" NOR;
                                                        if(budd >= 300) return HIC "�� ��  �� ��" NOR;
                                                        return HIC "�� ��  �� ��" NOR;
                                                case "�������":
                                                        if(budd >= 1900) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 1500) return HIC "�� �󻤷� ��" NOR;
                                                        if(budd >= 1100) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 700) return HIC "�� ̳  �� ��" NOR;
                                                        if(budd >= 300) return HIC "�� ��  �� ��" NOR;
                                                        return HIC "�� Ů��ͽ ��" NOR;
                                                case "���ϻ���":
                                                        if(budd >= 1900) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 1500) return HIC "��ھ�����ˡ�" NOR;
                                                        if(budd >= 1100) return HIC "�� Ů  �� ��" NOR;
                                                        if(budd >= 700) return HIC "�� Ů  �� ��" NOR;
                                                        if(budd >= 300) return HIC "�� Ů  �� ��";
                                                        return HIC "�� Ů  �� ��";
                                                case "�������":
                                                        if(budd >= 1900) return HIC "��ѩɽ�ɺ���" NOR;
                                                        if(budd >= 1500) return HIW "�� ������ ��" NOR;
                                                        if(budd >= 1100) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 700) return HIC "�� ��  ū ��" NOR;
                                                        if(budd >= 300) return YEL "�� ��  ͯ ��" NOR;
                                                        return HIC "�� ��  ͯ ��";
                                                case "ħ��":
                                                        if(budd >= 2000) return HIR "�� ħ  Ů ��" NOR;
                                                        if(budd >= 1700) return HIR "�� ��  �� ��" NOR;
                                                        if(budd >= 1400) return HIR "������ʥŮ��" NOR;
                                                        if(budd >= 1000) return RED "�� ʹ  �� ��" NOR;
                                                        if(budd >= 600) return RED "�� ��  Ů ��" NOR;
                                                        if(budd >= 200) return CYN "�� ��  ͽ ��" NOR;
                                                        return CYN "�� ��  ͽ ��" NOR;
                                                case "ŷ������":
                                                        if(budd >= 1900) return HIC "�������ħ��" NOR;
                                                        if(budd >= 1500) return HIC "������Ůħ��" NOR;
                                                        if(budd >= 1100) return HIC "������ħŮ��" NOR;
                                                        if(budd >= 700) return HIC "�����¼��ˡ�" NOR;
                                                        if(budd >= 300) return HIC "��������Ů��" NOR;
                                                        return HIC "��������Ů��";
                                        } // switch(fname)

                                        if( !query("class", ob)){
                                                if (shen >= 1500000) return HIC "��������Ů��" NOR;
                                                if (shen >= 1000000) return HIC "�������콿��" NOR;
                                                if (shen >= 500000) return HIC "������Ů����" NOR;
                                                if (shen >= 50000) return HIC "�� Ů���� ��" NOR;
                                                if (shen >= 5000) return HIC "�� Ů  �� ��" NOR;
                                                if (shen >= 500) return HIC "�� С��Ů ��" NOR;
                                                if (shen <= -1500000) return HIB "�� ��  �� ��" NOR;
                                                if (shen <= -1000000) return HIB "��������ɲ��" NOR;
                                                if (shen <= -500000) return HIB "������Ůħ��" NOR;
                                                if (shen <= -50000) return HIB "�� Ůħ�� ��" NOR;
                                                if (shen <= -5000) return HIB "�� Ůħͷ ��" NOR;
                                                if (shen <= -500) return HIB "�� СħŮ ��" NOR;
                                        }

                                        // û�����ɵĲŰ��������
                                        switch(query("class", ob)){
                                                case "bonze": return "�� �� �� ��";
                                                case "taoist":
                                                        if (age >= 20) return "�� ��  �� ��";
                                                        return "�� С���� ��";
                                                case "bandit": return "�� Ů���� ��";
                                                case "dancer": return GRN"�� ��  �� ��"NOR;
                                                case "scholar": return "�� ��  Ů ��";
                                                case "officer": return "�� Ů  �� ��";
                                                case "fighter": return "�� Ů���� ��";
                                                case "swordsman": return "�� Ů��ʿ ��";
                                                case "alchemist": return "�� Ů��ʿ ��";
                                                case "shaman": return "�� Ů��ҽ ��";
                                                case "beggar": return "�� �л��� ��";
                                                default:
                                                        if( query("couple", ob)){
                                                                if (age < 30) return "�� ��  �� ��";
                                                                if (age < 50) return "�����긾�ˡ�";
                                                                return "�� �ϸ��� ��";
                                                        }

                                                        if (age < 18) return "�� ��  Ů ��";
                                                        if (age < 30) return "������Ů�ӡ�";
                                                        if (age < 50) return "������Ů�ӡ�";
                                                        return "�� �ϴ�Ů ��";
                                        }//switch( query("class", ob) )

                        } // switch(wizhood(ob))
                default:
                        switch(wizhood(ob)) {
                                case "(boss)": return HIY "�� ��  �� ��" NOR;
                                case "(admin)": return HIW "�� ��  �� ��" NOR;
                                case "(assist)": return HIR "�� ��  �� ��" NOR;
                                case "(arch)": return HIY "�� ��  �� ��" NOR;
                                case "(wizard)": return HIG "�� ��  �� ��" NOR;
                                case "(apprentice)": return HIC "�� ��  ʦ ��" NOR;
                                case "(immortal)": return HIC "�� ��  �� ��" NOR;
                                default:
                                        if( query("combat/PKS", ob) > 20 && query("combat/PKS", ob) > query("combat/MKS", ob) / 4 )
                                                return HIR "��ɱ��ħ����" NOR;
                                        if( query("thief", ob)>10 )
                                                return "�� ��  �� ��";
                                        switch(fname) {
                                                case "����":
                                                        if(budd >= 2000) return HIW "�� ������ ��" NOR;
                                                        if(budd >= 1700) return WHT "������ʹ�ߡ�" NOR;
                                                        if(budd >= 1400) return HIC "�����̷�����" NOR;
                                                        if(budd >= 1000) return HIC "�����커����" NOR;
                                                        if(budd >= 600) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 200) return CYN "�� ��  �� ��" NOR;
                                                        return CYN "�� ��  �� ��" NOR;
                                                case "�һ���":
                                                        if (budd >= 1800) return HIW "�� ��  ʥ ��" NOR;
                                                        if (budd >= 1400) return HIC "�� ��  �� ��" NOR;
                                                        if (budd >= 1000) return WHT "�� ��  ʿ ��" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "�� ��  �� ��" NOR;
                                                        return "�� ƽ  �� ��";
                                                case "��ң��":
                                                        if (budd >= 1800) return HIW "�� ��  ʥ ��" NOR;
                                                        if (budd >= 1400) return HIC "�� ��  �� ��" NOR;
                                                        if (budd >= 1000) return WHT "�� ��  ʿ ��" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "�� ��  �� ��" NOR;
                                                        return "�� ƽ  �� ��";
                                                case "���ư�":
                                                        if (budd >= 1800) return WHT "�� ɽ���� ��" NOR;
                                                        if (budd >= 1400) return HIC "�� կ  �� ��" NOR;
                                                        if (budd >= 1000) return CYN "�� ��  �� ��" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "�� ͷ  Ŀ ��" NOR;
                                                        return "�� С��� ��";
                                                case "ؤ��":
                                                        if(budd >= 11) return HIW "�� ��  �� ��" NOR;
                                                        if(budd >= 10) return HIW "�� ������ ��" NOR;
                                                        if(budd >= 9) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 6) return HIG "�� ��  ͷ ��" NOR;
                                                        if(budd >= 5) return HIM "�� ��  �� ��" NOR;
                                                        if(budd >= 4) return HIM "�� ��  �� ��" NOR;
                                                        if(budd >= 2) return CYN "�� ��  �� ��" NOR;
                                                        return CYN "�� �л��� ��" NOR;
                                                case "������":
                                                        if( query("class", ob) != "bonze" )
                                                                return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 600) return HIY "�� ��  ɮ ��" NOR;
                                                        if (budd >= 500) return HIY "�� ʥ  ɮ ��" NOR;
                                                        if (budd >= 400) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 300) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 200) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 100) return HIY "�� ��  ʦ ��" NOR;
                                                        if (budd >= 50) return HIY "�� ��  �� ��" NOR;
                                                        return HIY "�� ɮ  �� ��" NOR;
                                                case "ѩɽ��":
                                                        if (budd >= 1800)
                                                                if (shen >= 0) return HIY "����ϲ������" NOR;
                                                                else return HIY "����ϲħ����" NOR;
                                                        if (budd >= 1400) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 900)  return HIY "�� �󻤷� ��" NOR;
                                                        if (budd >= 600) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 300 || age >= 20) return HIY "�� ��  ʿ ��" NOR;
                                                        return HIY "�� ��  �� ��" NOR;
                                                case "��ɽ��":
                                                        if (budd >= 1400) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 1000) return HIC "�� ��  �� ��" NOR;
                                                        if (budd >= 500 || age >= 18) return YEL "�� ��  �� ��" NOR;
                                                        return "�� ��  �� ��";
                                                case "��ɽ��":
                                                case "������":
                                                        if (budd >= 1800) return HIW "�� ��  �� ��" NOR;
                                                        if (budd >= 1400) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 1000) return HIC "�� ��  �� ��" NOR;
                                                        if (budd >= 500 || age >= 18) return YEL "�� ��  �� ��" NOR;
                                                        return "�� ��  �� ��";
                                                case "��Ĺ��":
                                                        if (budd >= 1800) return HIW "�� ��  �� ��" NOR;
                                                        if (budd >= 1400) return HIY "�� ��  �� ��" NOR;
                                                        if (budd >= 1000) return HIC "�� ��  �� ��" NOR;
                                                        if (budd >= 500 || age >= 18) return YEL "�� ��  �� ��" NOR;
                                                        return "�� ��  ͯ ��";
                                                case "�䵱��":
                                                case "ȫ���":
                                                        if (budd >= 600) return HIW "�� ��  �� ��" NOR;
                                                        if (budd >= 400) return HIW "�� ��  ʦ ��" NOR;
                                                        if (budd >= 100) return HIW "�� ��  �� ��" NOR;
                                                        if (budd >= 50 || age >= 20) return HIW "�� ��  ʿ ��" NOR;
                                                        return "�� ��  ͯ ��";
                                                case "��������":
                                                case "�嶾��":
                                                case "������":
                                                        if (budd >= 600) return HIB "�� ��  �� ��" NOR;
                                                        if (budd >= 500) return YEL "�� ��  �� ��" NOR;
                                                        if (budd >= 400) return MAG "�� ��  �� ��" NOR;
                                                        if (budd >= 100) return BLU "�� ��  �� ��" NOR;
                                                        if (budd >= 50 || age >= 18)  return CYN "�� ��  ħ ��" NOR;
                                                        return "�� ������ ��";
                                                case "Ľ������":
                                                        if(budd >= 1900) return HIC "�� ��  ү ��" NOR;
                                                        if(budd >= 1500) return HIC "�� ׯ  �� ��" NOR;
                                                        if(budd >= 1100) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 700) return HIC "�� ��  Ժ ��" NOR;
                                                        if(budd >= 300) return HIC "�� ׯ  �� ��" NOR;
                                                        return HIC "�� ׯ  �� ��" NOR;
                                                case "�������":
                                                        if(budd >= 1900) return HIC "�� ������ ��" NOR;
                                                        if(budd >= 1500) return HIC "�� �󻤷� ��" NOR;
                                                        if(budd >= 1100) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 700) return HIC "�� ̳  �� ��" NOR;
                                                        if(budd >= 300) return HIC "�� ��  �� ��" NOR;
                                                        return HIC "�� ��  ͽ ��" NOR;
                                                case "���ϻ���":
                                                        if(budd >= 1900) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 1500) return HIC "�� ��  ү ��" NOR;
                                                        if(budd >= 1100) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 700) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 300) return HIC "�� У  ξ ��" NOR;
                                                        return HIC "�� ��  ʿ ��" NOR;
                                                case "�������":
                                                        if(budd >= 1900) return HIC "��ѩɽ�ɺ���" NOR;
                                                        if(budd >= 1500) return HIW "�� ������ ��" NOR;
                                                        if(budd >= 1100) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 700) return HIC "�� ��  ū ��" NOR;
                                                        if(budd >= 300) return YEL "�� ��  ͯ ��" NOR;
                                                        return HIC "�� ��  ͯ ��";
                                                case "Ѫ����":
                                                        if (budd >= 1900)
                                                                if (shen >= 0) return HIR "�� ħ���� ��" NOR;
                                                        if(budd >= 1900) return HIR "�����⵶ħ��" NOR;
                                                        if(budd >= 1500) return HIC "�� ��  ħ ��" NOR;
                                                        if(budd >= 700) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 300) return HIC "�� ��  ͯ ��" NOR;
                                                        return HIC "�� ��  ͯ ��";
                                                case "ħ��":
                                                        if(budd >= 2000) return HIR "��ħ������" NOR;
                                                        if(budd >= 1700) return HIR "�� ��  ħ ��" NOR;
                                                        if(budd >= 1400) return HIR "�� ��  �� ��" NOR;
                                                        if(budd >= 1000) return RED "�� ��  �� ��" NOR;
                                                        if(budd >= 600) return RED "�� ʹ  �� ��" NOR;
                                                        if(budd >= 200) return CYN "�� ��  ͽ ��" NOR;
                                                        return CYN "�� ��  ͽ ��" NOR;
                                                case "ŷ������":
                                                        if(budd >= 1900) return HIC "������ħ����" NOR;
                                                        if(budd >= 1500) return HIC "�� ��ׯ�� ��" NOR;
                                                        if(budd >= 1100) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 700) return HIC "�� ��  �� ��" NOR;
                                                        if(budd >= 300) return HIC "������ͯ�ӡ�" NOR;
                                                        return HIC "������ͯ�ӡ�";
                                        } // switch(fname)
                                        if( !query("class", ob)){
                                                if (shen >= 1500000) return HIC "�������񻰡�" NOR;
                                                if (shen >= 1000000) return HIC "������������" NOR;
                                                if (shen >= 500000) return HIC "������������" NOR;
                                                if (shen >= 50000) return HIC "�� ��  �� ��" NOR;
                                                if (shen >= 5000) return HIC "�� ��  �� ��" NOR;
                                                if (shen >= 500) return HIC "�� ��  �� ��" NOR;
                                                if (shen <= -15000000) return HIB "������ħ��" NOR;
                                                if (shen <= -1000000) return HIB "��������ħ��" NOR;
                                                if (shen <= -500000) return HIB "�� ħ  �� ��" NOR;
                                                if (shen <= -50000) return HIB "�� ħ  �� ��" NOR;
                                                if (shen <= -5000) return HIB "�� ħ  ͷ ��" NOR;
                                                if (shen <= -500) return HIB "�� ��  ħ ��" NOR;
                                        }
                                        switch(query("class", ob)){
                                                case "bonze": return "�� ɮ  �� ��";
                                                case "taoist":
                                                        if (budd >= 50 || age >= 20) return "�� ��  ʿ ��";
                                                        return "�� ��  ͯ ��";
                                                case "lama": return "�� ��  �� ��";
                                                case "bandit": return "�� ��  �� ��";
                                                case "scholar": return "�� ��  �� ��";
                                                case "officer": return "�� ��  �� ��";
                                                case "fighter": return "�� ��  �� ��";
                                                case "swordsman": return "�� ��  ʿ ��";
                                                case "alchemist": return "�� ��  ʿ ��";
                                                case "shaman": return "�� ��  ҽ ��";
                                                case "beggar": return "�� �л��� ��";
                                                case "eunuch": return "�� ̫  �� ��";
                                                default:
                                                        if( query("marry", ob)){
                                                                if (age < 30) return "���������ӡ�";
                                                                if (age < 50) return "���������ӡ�";
                                                                return "�� ��ͷ�� ��";
                                                        }
                                                        if (age < 18) return "�� ��  �� ��";
                                                        if (age < 30) return "���������ӡ�";
                                                        if (age < 50) return "���������ӡ�";
                                                        return "�� �ϴ��� ��";
                                        }//switch( query("class", ob) )
                        } // switch(wizhood(ob))
        }//switch( query("gender", ob) )
}

string query_respect(object ob)
{
        int age;
        string str;

        if (!ob) return "";
        if( stringp(str=query("rank_info/respect", ob)) )
                return str;

        age=query("age", ob);
        switch(query("gender", ob) )
        {
        case "Ů��":
                switch(query("class", ob) )
                {
                case "bonze":
                        if (age < 18) return "Сʦ̫";
                        else return "ʦ̫";
                        break;
                case "taoist":
                        if (age < 18) return "С�ɹ�";
                        else return "�ɹ�";
                        break;
                default:
                        if (age < 18) return "С����";
                        else if (age < 30) return "����";
                        else if (age < 40) return "����";
                        else return "����";
                        break;
                }
        case "����":
        default:
                switch(query("class", ob) )
                {
                case "bonze":
                        if (age < 18) return "Сʦ��";
                        else return "��ʦ";
                        break;
                case "taoist":
                        if (age < 18) return "����";
                        else return "����";
                        break;
                case "scholar":
                        if (age < 18) return "С�๫";
                        else if (age < 50) return "�๫";
                        else return "������";
                        break;
                case "fighter":
                case "swordsman":
                        if (age < 18) return "С�ϵ�";
                        else if (age < 50) return "׳ʿ";
                        else return "��ǰ��";
                        break;
                default:
                        if (age < 20) return "С�ֵ�";
                        else if (age < 50) return "׳ʿ";
                        else return "��ү��";
                        break;
                }
        }
}

string query_rude(object ob)
{
        int age;
        string str;

        if( stringp(str=query("rank_info/rude", ob)) )
                return str;

        age=query("age", ob);
        switch(query("gender", ob) )
        {
        case "Ů��":
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 18 ) return "С����";
                        if( age < 30 ) return "����";
                        else return "������";
                        break;
                case "taoist":
                        if( age < 18 ) return "С��Ů";
                        if( age < 30 ) return "��Ů";
                        else return "������";
                        break;
                default:
                        if( age < 18 ) return "С��Ƥ";
                        if( age < 25 ) return "С����";
                        if( age < 40 ) return "������";
                        else return "����̫��";
                        break;
                }
        case "����":
        default:
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 18 ) return "С��ͺ";
                        if( age < 50 ) return "��ͺ¿";
                        else return "��ͺ¿";
                        break;
                case "taoist":
                        if( age < 18 ) return "С��ë";
                        if( age < 30 ) return "��ţ����";
                        else return "����ë";
                        break;
                case "scholar":
                        if( age < 18 ) return "С�����";
                        else if( age < 50 ) return "�������";
                        else return "��ͯ��";
                        break;
                default:
                        if( age < 20 ) return "С���˵�";
                        if( age < 30 ) return "ֱ����";
                        if( age < 50 ) return "����";
                        if( age < 80 ) return "��ƥ��";
                        else return "�ϲ���";
                        break;
                }
        }
}

string query_self(object ob)
{
        int age;
        string str;

        if( stringp(str=query("rank_info/self", ob)) )
                return str;

        age=query("age", ob);
        switch(query("gender", ob) )
        {
        case "Ů��":
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 50 ) return "ƶ��";
                        else return "����";
                        break;
                case "taoist":
                        return "ƶ��";
                        break;
                default:
                        if( age < 20 ) return "СŮ��";
                        if( age > 50 ) return "����";
                        else return "���";
                        break;
                }
        case "����":
        default:
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 18 ) return "С��";
                        if( age < 40 ) return "ƶɮ";
                        else return "����";
                        break;
                case "taoist":
                        if( age < 18 ) return "С��";
                        if( age < 30 ) return "ƶ��";
                        else return "�ϵ�";
                        break;
                case "scholar":
                        if( age < 30 ) return "����";
                        else return "����";
                        break;
                default:
                        if( age < 50 ) return "����";
                        else return "��ͷ��";
                        break;
                }
        }
}

string query_self_rude(object ob)
{
        int age;
        string str;

        if( stringp(str=query("rank_info/self_rude", ob)) )
                return str;

        age=query("age", ob);
        switch(query("gender", ob) )
        {
        case "Ů��":
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 50 ) return "ƶ��";
                        else return "����";
                        break;
                case "taoist":
                        return "���ɹ�";
                        break;
                default:
                        if( age < 20 ) return "������";
                        if( age < 30 ) return "��������";
                        else return "����";
                        break;
                }
        case "����":
        default:
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 50 ) return "�������";
                        else return "�Ϻ�����";
                        break;
                case "taoist":
                        if( age < 30 ) return "��ɽ��";
                        return "�ϵ���";
                        break;
                case "scholar":
                        if( age < 50 ) return "���๫";
                        else return "�Ϸ�����";
                        break;
                default:
                        if( age < 20 ) return "����ү��";
                        if( age < 40 ) return "��ү��";
                        else return "����";
                        break;
                }
        }
}

varargs string query_close(mixed ob, int a1, int a2)
{
        if (! a1 && this_player())
                a1=query("age", this_player());

        if (! a2 && objectp(ob))
                a2=query("age", ob);

        switch (objectp(ob) ? query("gender", ob) : ob)
        {
        case "Ů��":
                if (a1 >= a2)
                        return "����";
                else
                        return "���";
                break;

        default:
                if (a1 >= a2)
                        return "�ܵ�";
                else
                        return "���";
        }
}

varargs string query_self_close(mixed ob, mixed me, int a1, int a2)
{
        if (! a1 && this_player())
                a1=query("age", this_player());

        if (! a2 && objectp(ob))
                a2=query("age", ob);

        switch (objectp(me) ? query("gender", me) :
                this_player() ? query("gender", this_player()) : me)
        {
        case "Ů��" :
                if (a1 >= a2)
                        return "�����";
                else
                        return "С����";
                break;

        default :
                if (a1 >= a2)
                        return "������";
                else
                        return "С����";
        }
}

varargs string new_short(object ob, int withshort)
{
        mixed tmp;
        string icon = "", str;

        if (! objectp(ob))
        {
                CHANNEL_D->do_channel(this_player(), "chat", "object��������");
                return "";
        }
        if( !query_temp("apply/id", ob) || !query_temp("apply/name", ob) || !query_temp("apply/short", ob) )
                str = query("name", ob) + "(" +query("id", ob) + ")" +(! withshort ? "" : ob->short());
        else
                str = query_temp("apply/name", ob)[0] + "(" +query_temp("apply/id", ob)[0] + ")" +
                        (! withshort ? "" : query_temp("apply/short", ob)[0]);
        if( (tmp=query("icon", ob)) )
        {
                if (intp(tmp))
                        icon = sprintf("%d", tmp);
                else if (stringp(tmp))
                        icon = tmp;
                else
                        icon = "00901";
        }
        else
        {
                if (userp(ob))
                        icon=(query("gender", ob) == "����")?"1174":"1173";
                else
                if (living(ob))
                        icon = "00901";
                else icon = "00961";
        }
        while (sizeof(icon) < 5)
                icon = "0" + icon;

        return str + icon;
}
