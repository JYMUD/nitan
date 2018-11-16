// du.h for fight and apprentice to 3-du

#include "shaolin.h"

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam=query("family", me);

        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( !(ob_fam=query("family", ob)) || 
            ob_fam["family_name"] != "������")
        {
                command("say " + RANK_D->query_respect(ob) +
                        "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }

        if( query("class", ob) != "bonze" && 
            ob_fam["family_name"] == "������") 
        {
                command("say " + RANK_D->query_respect(ob) +
                        "���׼ҵ��ӣ�����������ѧ�ա�");
                return;
        }

        if (ob_fam["generation"] <= my_fam["generation"])
        {
                command("say " + RANK_D->query_respect(ob) +
                        "��ƶɮ����ҵ� !");
                return;
        }

        if (ob_fam["generation"] == (my_fam["generation"] + 1))
        {
                command("say " + ob_fam["master_name"] +
                        "��ͽ�������ܵ���������ˣ������� !");
                command("recruit "+query("id", ob));
        }

        if (ob_fam["generation"] == (my_fam["generation"] + 2))
        {
                if( query_temp("valid_in_fumoquan", ob) == 1 )
                {
                        if (ob->query_skill("dodge",1) >= 120 &&
                            ob->query_skill("force",1) >= 120 &&
                            ob->query_skill("parry",1) >= 120 &&
                            ob->query_skill("buddhism",1) >= 120)
                        {
                                command("say ���ܹ���շ�ħȦ����������");
                                command("say ƶɮ�ֵ�һ����֮�ţ���ϲ�ɺأ�");

                                name=query("name", ob);
                                new_name = "��" + name[2..3];
                                set("name", new_name, ob);
                
                                command("say �ӽ��Ժ���ķ�������" +
                                        new_name + "��");
                                command("recruit "+query("id", ob));
                        }
                        else
                        command("say ƶɮҪ�յ�������֮�ţ��㻹�ǻ�ȥ"
                                "����ʦ��ѧϰ�ɣ�");
                } else
                {
                        command("say " + RANK_D->query_respect(ob) +
                                "��û�ܹ���շ�ħȦ���Ҳ������㡣");
                        return;
                }
        }
        return;
}
