//Cracked by Roath
// /kungfu/class/emei/zhou.h
// yasuko: 2000/08/17
// mantian: may/21/2001
// kick out ppl for those learn pxj after bai zhou
// xiaojian for fixing all of the bugs June 22,2001
// xQin 06/01 add a log for expelled students 
#include <ansi.h>

void init()
{
        object ob,me;
        ob=this_player();
        me=this_object();

        ::init();

        set_heart_beat(1);

        if(interactive(ob)
                 && query("family/family_name", ob) == "������"
                 && query("gender", ob) == "����"
                && (int)ob->query_skill("pixie-jian", 1) >=1) {
                if( !query("pxj_warning", ob)){
                        set("pxj_warning", 1, ob);
                        command("hmm");
                        command("say ��а������,��Ϊ��ȥ͵ѧ��а����? �Ͽ�Ĺ�����,�����´μ����㶨������!\n");
                } else {
                command("look "+getuid(ob));
                command("hmm "+getuid(ob));
                command("sneer "+getuid(ob));
                command("say "+RANK_D->query_rude(ob)+"��Ȼѧ�˾����澭�ϵĹ���Ϊ��ȥѧ��а���������ҽ̵Ĳ����ã�");
                command("expell"+query("id", ob));
                command("say ���ɣ�");
                delete("pxj_warning", ob);
                write_file("/kungfu/class/emei/zhou_log.c",
                sprintf("%s(%s)wasexpelledbyzhouduetopxj%d(%d).\n",query("id", this_player()),ctime(time())));
                }
        }
}
string ask_jiuyin()
{
        object ob,me=this_player();
        if( query("family/master_name", me) != "������" )
                return RANK_D->query_respect(this_player())+"�����ز���ʶ���γ������أ�";
        ob=new(__DIR__"obj/jiuyin-paper");
        if (present("juan pian",me)) return "�ף������ϲ��Ǵ��ž����澭������ô�������ң�";
        if (!ob) return "�ţ�����㵹��û���⣬ֻ�Ǹձ���ĵ��ӽ����ˣ����һ���������ʰɡ�";
        if( !query("jiuyin/first", me)){
                command ("say ���ǵ�һ����������澭�ɣ�\n
            ������Ƭ���ܳ����ľ����澭��ԭ���������콣���ʵҲ����ʲô���˵Ķ�����
            ����ȥ�����ɡ�\n
            Ϊʦ��ǰ���᲻���£�ֻ֪���������ϵ���ʽ����(xiulian)����Ȼ��չ�ܿ죬��
            ��Խ����������Խ�����ա��������Ǳ������(lingwu)�����澭�е����У��վ���
            ��������ɡ���Ȼ������Ļ������ܶࡣ��Ҫ����ʲô�����׵ģ���ֱ�ӹ�������
            ѧ�ɡ�\n");
                set("jiuyin/first", 1, me);
        }
        ob->move(me);
        message_vision("$n�ݸ�$Nһ����Ƭ��\n",me,this_object());
        command("rumor"+query("name", me)+"Ū���˾����澭�ܳ�����");
        return "��סʦ���Ļ���ǧ��Ҫ̰������������ʱ��ͺ��Ī���ˡ�";
}

void attempt_apprentice(object ob)
{
    mapping fam;
    int last_betray,shen;
        
        //xiaojian: added a check before recruiting, i.e. won't recruit pxj dizi.

                if ((int)ob->query_skill("pixie-jian", 1) >=1) {
                        command("ah"+query("id", ob));
                        command("say СŮ���볯͢������������֪��λ���˵����кι��ɣ�");
                        return;
                 }

        // Yinli and Qianzhu-wandu: by yasuko
        if ((int)ob->query_skill("qianzhu-wandu", 1) >=1 ) {
                command("sneer"+query("id", ob));
                command("say ��λ" + RANK_D->query_respect(this_player())
                + "�������ԨԴ��ǳ�����¿ɲ��������ӵܡ�");
                return;
        }
        // Emei dizi(Linji-zhuang & Pixie-jian)��by yasuko
        if( query("family/family_name", ob) == "������"){
                if ((int)ob->query_skill("linji-zhuang", 1) < 90) {
                        command ("say " + RANK_D->query_respect(this_player()) +
                                 "���ټ�ׯ��Ƿ�� ����ѧϰ�ϳ��书��\n");
                        return;
                }
                if ((int)ob->query_skill("pixie-jian", 1) >=1) {
                        command("sigh4 " );
                        command("say ��λ" + RANK_D->query_respect(this_player())
                                + "��Ȼ��ϡ�����ŵ��书���ֺα��������أ�");
                        return;
                }
        }
        // Betryer
        else {
                // Ppl who has betraied zhou and left from emei
                last_betray=query("zhou-betray", ob);
                if( last_betray>0 && last_betray != query("betrayer", ob )
                 && query("combat_exp", ob) >= 10000){
                        command ("say " + RANK_D->query_respect(this_player()) +
                        "��Ȼ�ѳ�����, �˿����ȴ������. \n");
                        command ("say " + RANK_D->query_respect(this_player()) + "��"
                        +query("family/family_name", ob)+"���֣����ɿɲ���������");
                        return;
                }
                // Gaibang Hinghand
                if( query("family/family_name", ob) == "ؤ��" && query("rank", ob)>1){
                        command("say " + RANK_D->query_respect(ob) + "��ؤ����֣�ˡ�Ҳ������㡣");
                        return;
                }
                // Pixie-jian: by yasuko
                if ((int)ob->query_skill("pixie-jian", 1) >=1) {
                        command("ah"+query("id", ob));
                        command("say СŮ���볯͢������������֪��λ���˵����кι��ɣ�");
                        return;
                 }
                // Peaceful life 1: by yasuko
                shen=query("shen", ob);
                if (shen >0) {
                        if (random(shen) >= 1000 ) {
                                command("xixi"+query("id", ob));
                                command("say " + RANK_D->query_respect(this_player()) + 
                                "����Զ������ʦͽ֮��ʵ������ɱСŮ���ˡ�");
                                return;
                        }
                }
                if (shen <0) {
                        shen = 0 - shen;
                        if (random(shen) >= 1000 ) {
                                command("hmm" );
                                command("say ����" + RANK_D->query_respect(this_player()) + 
                                "�Ǻڵ����쵱�����������������ϴ�ĸ��棬���Ҿ������㡣");
                                return;
                        }
                }
                // Peaceful life 2: by yasuko
                if( random(query("PKS", ob)/query("death_times", ob))>10){
                        command("lazy");
                        command("say ��λ" + RANK_D->query_respect(this_player()) + 
                        "��ô������ɱ����СŮ���µúܣ�����������ɡ�");
                        return;
                }
        }
        // Giving everybody one chance to enter emei
        if ((int)ob->query_skill("claw", 1) < 40) {
                command("say �ҿ�������ѧ�����澭�ϵĹ���ɣ���ȥѧ�������צ�������ɡ�");
                return;
        }
        if ((int)ob->query_skill("jiuyin-baiguzhao", 1) < 40) {
                command("say �ҿ�������ѧ�����澭�ϵĹ���ɣ���ȥѧ��������ľ���צ�����ɡ�");
                return;
        }
        command("say �ðɣ���͸������ѧ�ɡ�"); 
        command("say ������ɼ�ס��, Ҫ��������ʦ��, �ҿɲ���������.\n");
        command("recruit "+query("id", ob));
        set("emei", 1, ob);
        set("zhou-betray",query("betrayer",  ob), ob);
        command("whisper"+query("id", ob)+
                        " �´�������ʱ�������϶��ڽ�һ���������º������Ҿͻ����˴������.\n");
}
