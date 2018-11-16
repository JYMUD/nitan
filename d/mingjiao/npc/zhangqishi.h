// ZhangQiShi.h for fight and get letter from ZhangQiShi
#include "mingjiao.h"

void init()
{
        object me,ob;
        me = this_object () ;
        ob = this_player () ;

        ::init();

        if( interactive(this_player()) && query_temp("fighting", this_player()) )
        {
                COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon") );
                addn_temp("beat_count", 1, this_player());
        }       
}

int accept_object(object ob, object obj)
{
        string name;
        string job_flg;
        object me = this_object();

        mapping ob_family=query("family", ob);
        name=query("id", obj);

        if( name == "huo qiang" && query("id", me) == "xin ran" )
        {
                job_flg = judge_jobmsg(ob,1);

                if ( job_flg !=  "�����ǹ" ) 
                {
                        command("hmm"+query("id", ob));
                        command("say ����û����������������Ļ�ǹ�����ǹ����Σ�գ����������ˡ�");
                        destruct(obj);
                        return 1;
                }
                else
                {
                        command("thumb "+query("id", ob));
                        command("say ��λ�ֵ�������!��ȥ�ú���Ϣ��Ϣ��");
                        destruct(obj);
                        call_out("reward",0,ob,"�����ǹ"); 
                        return 1;
                }
        }

        if( query_temp("have_letter", ob) && present("tuijian xin3",ob) )
        {
                command("say �������������ҵ��Ƽ���ȥ����ɢ������ ?");
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

        if( query("id", obj) == "tuijian xin2"
         && query_temp("have_letter", ob )
         && ob_family["generation"] == query("family/generation", me)+2 )
        {
                set_temp("apprentice_ok", 1, ob);
                command("say �ã�"+query("name", ob)+"����Ը�����������");
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
                obj=new("/d/mingjiao/obj/tuijianxin-3");
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
        object me;
        mapping ob_family;
        string qi,new_rank;

        me=this_object();

        if (! permit_recruit(ob) )
                return;

        if( !mapp(ob_family=query("family", ob)) || ob_family["family_name"] != "����" )
        {
                command("say " + RANK_D->query_respect(ob) + "�뱾��������������֪�˾��Ǻ����⣿");
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
                return;
        }

        if( query("family/generation", ob) == query("family/generation", me)+2 )
        {
                if( query_temp("apprentice_ok", ob) )
                {
                        delete_temp("have_letter", ob);
                        delete_temp("apprentice_ok", ob);
        
                        command("say ������ !");
                        command("say �����ֵ�һ����֮�ţ����ǿ�ϲ�ɺ� !");
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
