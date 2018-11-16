// shizhe.h for fight and get letter from ShiZhe
int accept_object(object ob, object obj)
{
        object me = this_object();

        mapping my_fam=query("family", me);
        mapping ob_fam=query("family", ob);

        if( query("id", obj) == "tuijian xin5"
         && query_temp("have_letter", ob )
        && ob_fam["generation"] == my_fam["generation"] + 2)
        {
                set_temp("apprentice_ok", 1, ob);
                command("say �ã�"+query("name", ob)+"����Ը�����Ϊʦ��");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

        command("smile");
        command("say �ⶫ�����ҿ�û��ʲ���á�");
        command("give "+query("id", obj)+" to "+query("id", me));
        return 0;

}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

#include "mingjiao.h"

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam=query("family", me);

        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "����" )
        {
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }

        if ( ob_fam["generation"] <= my_fam["generation"] )
        {
                command("say " + RANK_D->query_respect(ob) + "��Сʹ����ҵ� !");
                return;
        }

        if ( ob_fam["generation"] == (my_fam["generation"] + 1) )
        {
                command("say " + ob_fam["master_name"] + "��ͽ�������ܵ���������ˣ������� !");
                command("recruit "+query("id", ob));
        }

        if ( ob_fam["generation"] == (my_fam["generation"] + 2) )
        {
                if( query_temp("apprentice_ok", ob) )
                {
                        delete_temp("have_letter", ob);
                        delete_temp("apprentice_ok", ob);

                        command("say ��" + ob_fam["master_name"] + "���������ҵİɣ������� !");
                        command("say ��ʹ���ֵ�һ����֮�ţ����ǿ�ϲ�ɺ� !");

                        command("say ��ϲ������Ϊ���̻��̷�����");
                        command("recruit "+query("id", ob));
                }
                else
                {
                        command("say " + RANK_D->query_respect(ob) + "����û���Ƽ��ţ�����Խ����ʦ��");
                        return;
                }
        }

        return;
}

