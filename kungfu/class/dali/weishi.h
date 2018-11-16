// weishi.h ��������ʿ, ��ʦ
int ask_me()
{
        object ob, me;
        me = this_object();
        ob = this_player();
        if ((int)ob->query_skill("kurong-changong",1) < 60)
        {
                command("say ���뵱��ʿ���������깦�ɡ�\n");
                return 1;
        }
        
        if( query("guard", ob) == "���������ҳ�" )
        {
                set_temp("fight_ok", 1, ob);
                command("say �ã���Ȼ������д裬�ǾͿ���ı�������ˡ�\n");
                return 1;
        }
        else
        {
                command("say ֻ�мҳ���������ʿ��\n");
                return 1;
        }
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
                command("say ������ʤ����������Ǵ���μҵĺõ��ӣ���ϲ���ˣ�\n");
                command("say ����Ѿ�����ʤ�δ�����ʿ��\n");
                upgrade_title(ob, "����������ʿ");
                return 1;
        }
        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say ����" + RANK_D->query_respect(ob) + 
                        "���ö����ϰ�������ڴ���μ��������г���ͷ�أ�\n");
                return 1;
        }
        return 1;  
}
void upgrade_title(object ob,string arg)
{
//        string title;
//        title=arg+clear_title(ob->query("title"));
        set("guard", arg, ob);
}
/*
string clear_title(string arg)
{
        if (strsrch(arg, "�������������ҳ�") >= 0)
        {
                arg = replace_string(arg, "�������������ҳ�","");
        }
        return arg;
}
*/
void attempt_apprentice(object ob)
{
        if( (query("guard", ob) != "����������ū") && 
            (query("family/family_name", ob) != "����μ�") )
        {
                command("shake"+query("id", this_player()));
                command("say ������Ͷ�����Ϊ�����������㽭�����񣬲�����ͽ�ˡ�\n");
                return;
        }
        if( query("shen", ob)<0 )
        {
                command("say �Ҵ�������������������ֺڵ�����򽻵�������ذɣ�");
                return;
        }
        if( query("combat_exp", ob)>10000 || query("age", ob)>17 )
        {
                command("say �����������˴�������Ҳ����̫�����˰ɣ�");
                return;
        }
        command("say �ܺã��ܺá������븮���㵱���ұ�������������Ҳ�Ͳ����Լ����ˡ�\n");
        command("recruit "+query("id", ob));
        if( query("gender", ob) == "����" )
                set("guard", "���������Ҷ�", ob);
        else
                set("guard", "���������Ů", ob);
}
