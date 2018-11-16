// Include file: daozhang.h
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
#include "wudang.h"
int do_yes();

void attempt_apprentice(object ob)
{
        int i;
        mapping fam,skill_status;
        string *sname;
        string *wudang_skills = ({
                "unarmed",        "taiji-quan",        "wudang-quan",
                "sword",        "taiji-jian",        "liangyi-jian",        "wudang-jian",
                "force",        "taiji-shengong",
                "dodge",        "tiyunzong",
                "literate",        "taoism",
                "parry",
        });

        if (! permit_recruit(ob))
                return;

        if( query("class", ob) == "bonze" )
        {
                command ("say ��ҵ������Ų�ͬ�����Ȼ�Ѿ��Ѿ����˼ң�������������ʲô�أ�");
                return;
        }
        if( query("shen", ob)<0 )
        {
                command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(ob) + "�Ƿ����ò�����");
                return;
        }
        if( query("gender", ob) == "����" )
        {
                command("say �����ڹ���������������������ϡ�");
                command("say �����޸����ԣ�������֮���ˣ�");
                return;
        }
        if( mapp(fam=query("family", ob)) && 
                (fam["family_name"] != "�䵱��") &&
                (skill_status = ob->query_skills()) )
        {
                sname  = keys(skill_status);

                for(i=0; i<sizeof(skill_status); i++)
                if (member_array(sname[i], wudang_skills) == -1)
                {
                        message_vision(this_object()->name()+"����һЦ��"+ RANK_D->query_respect(ob) + "�Ѿ�����" + fam["family_name"]+ "�ˣ���ôȴ��Ͷ���䵱��\n", ob);
                        message_vision(this_object()->name()+"���˶٣���ɫ�������䵱�����ô��ɣ��Ӳ�������Ӣ�ۡ�\n", ob);
                        command( "say ��������Ͷ���䵱��������������ɹ�����ʾ���⣡");
                        delete_temp("pending/apprentice", ob);
                        return;
                }
        }
        if( query("title", ob) != "�䵱��ͯ"
                 && query("family/family_name", ob) != "�䵱��" )
         {
                command("say ���䵱֮���������������˲�˥��ȫ���������Ծ�Ч����");
                command("say ����ϰ����ǰ��" + RANK_D->query_respect(ob) + "�Ƿ�Ը��Ϊ�䵱������Щ���飿");
                tell_object(ob, HIY"������Ӧ�Ļ������룢Ը�⣢���֡�\n"NOR);
                add_action("do_yes", "Ը��");
                return;
        }
        else
  if( query("wudang/offerring", ob)<query("age", ob)-11 )
                {
                        command("say δ���䣬��ѧ���ˡ���Ϊ�䵱�Ծ�Ч�����棬");
                        command("say " + RANK_D->query_respect(ob) + "�Ƿ񻹲������㣿");
                        delete_temp("pending/apprentice", ob);
                        return;
                }
        if( mapp(fam=query("family", ob)) && (fam["family_name"] == "�䵱��") )
                command("say ���ұ���ͬ�ţ�ƶ�����������ˣ�");
        else
        {
                command( "say ������������ʯΪ������Ϊ�䵱����Ч�����ڵ����������пڽԱ���");
                command( "say "+RANK_D->query_respect(ob)+"ʵ���ұ�����Ҳ��");
        }

        command("recruit "+query("id", ob));
        delete("class", ob);
}

int do_yes()
{
        object me, ob;

        me = this_object();
        ob = this_player();

        set("wudang/offerring", 1, ob);
        message_vision("$N����˵����Ը�⣡\n", ob);
        set("title", "�䵱��ͯ", ob);
        delete_temp("pending/apprentice", ob);
        command("haha ");
        command("say �ܺã��ܺã��ӽ�����������䵱һ����ϰѧͽ��");
        command("say ϣ��"+ RANK_D->query_respect(ob) +"�ڼ�Ŭ�����������������С�");

        return 1;
}