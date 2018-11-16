// MenZhu.h for fight and get letter from MenZhu
#include "mingjiao.h"

int accept_object(object ob, object obj)
{
        object me = this_object();

        mapping ob_family=query("family", ob);

        if( query_temp("have_letter", ob) && present("tuijian xin2",ob) )
        {
                command("say �������������ҵ��Ƽ���ȥ������ʹ���� ?");
                return 0;
        }

        if( (query("id", obj) == "tieyan ling" )
        && ob_family["family_name"] == "����"
         && ob_family["generation"] == query("family/generation", me)+1
         && !query_temp("have_letter", ob) )
        {
                set_temp("fight_ok", 1, ob);
                command("say �ã���Ȼ�ѵõ�������ɣ����Ǿ�����֤һ���书��");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }
        
        command("?");
        command("say �ⶫ�����ҿ�û��ʲ���á�");
        return 0;

}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

int accept_fight(object ob)
{
        object me  = this_object();
        
        if( !query_temp("fight_ok", ob))return 0;

        remove_call_out("checking");
        call_out("checking", 1, me, ob);

        delete_temp("fight_ok", ob);
        
        return 1;
}

int checking(object me, object ob)
{

        object obj;
        int my_max_qi, his_max_qi;

        my_max_qi=query("max_qi", me);
        his_max_qi=query("max_qi", ob);

        if (me->is_fighting()) 
        {
                call_out("checking",2, me, ob);
                return 1;
        }

        if ( !present(ob, environment()) ) return 1; 

        if( (query("qi", me)*100/my_max_qi) <= 50 )
        {
                command("say ������ʤ����������������̵ļѵ��� ! ��ϲ���� !\n");
                message_vision("$N����$nһ���Ƽ��š�\n", me, ob);
                set_temp("have_letter", 1, ob);
                obj=new("/d/mingjiao/obj/tuijianxin-2");
                obj->move(ob);
                return 1;
        }

        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say ����" + RANK_D->query_respect(ob) + 
                "���ö����ϰ�������������������г���ͷ�� !\n");
                return 1;
        }

        return 1;  
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        string mingjiao_party;

        if (! permit_recruit(ob) )
                return;

        mingjiao_party=query("can_apprentice_menzhu", ob);

        if( query("family/family_name", ob) && query("family/family_name", ob) != "����" )
        {
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }

        if( !mapp(query("family", ob)) && !stringp(mingjiao_party) )
        {
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }

        if( !mapp(query("family", ob)) )
        {
                command("say ԭ���ǽ���ʹ�߽������İ�����ô��͸�����ѧ�㹦��ɣ�\n");
                command("hehe");
                command("recruit "+query("id", ob));
                return;
        }                

        if( query("family/generation", me) >= query("family/generation", ob) )
        {
                command("say " + RANK_D->query_respect(ob) + "����������ҵ� !");
                return;
        }

        if( query("family/generation", ob) == query("family/generation", me)+1 )
        {
                command("say "+query("family/master_name", ob)+"��ͽ�������ܵ���������ˣ�������!");
                command("recruit "+query("id", ob));
        }

        return;
}
