// renwoxing.c
// Update by haiyan

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

int ask_bijian();
string ask_jing();
mixed no_learn();
mixed ask_pfm();

void create()
{
        set_name("������", ({ "ren woxing", "ren","woxing" }));
        set("title", GRN "������̽���" NOR );
        set("long", "ֻ����һ�ų��������ף���ɫѩ�ף����ް��Ѫɫ��üĿ���㣬
������ߣ�һͷ�ڷ���������һϮ������\n");
        set("gender", "����");
        set("class", "scholar");
        set("age", 55);
        set("attitude", "friendly");
        set("shen_type", -1);
        set("str", 30);
        set("per", 27);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("yijinjing_count", 1);

        set("max_qi", 7000);
        set("max_jing", 1000);
        set("neili", 4000);
        set("max_neili", 4000);
        set("jiali", 400);
        set("combat_exp", 6000000);
        set("score", 500000);

        set_skill("force", 700);
        set_skill("riyue-xinfa", 700);
        set_skill("xixing-dafa", 700);
        set_skill("yijinjing", 600);
        set_skill("tianmo-jian", 700);
        set_skill("riyue-jian", 700);
        set_skill("cuff", 700);
        set_skill("xuwu-piaomiao", 700);
        set_skill("hand", 700);
        set_skill("huanmo-longtianwu", 700);
        set_skill("literate", 700);
        set_skill("dodge", 700);
        set_skill("unarmed", 700);
        set_skill("piaomiao-shenfa", 700);
        set_skill("parry", 700);
        set_skill("sword", 700);
        set_skill("damo-jian", 600);
        set_skill("taiji-jian", 600);
        set_skill("huifeng-jian", 600);
        set_skill("taishan-sword", 600);
        set_skill("hengshan-jian", 600);
        set_skill("hengshan-sword", 600);
        set_skill("huashan-sword", 600);
        set_skill("songshan-sword", 600);
        set_skill("richu-dongfang", 600);
        set_skill("martial-cognize", 600);

        map_skill("dodge", "piaomiao-shenfa");
        map_skill("force", "xixing-dafa");
        map_skill("sword", "tianmo-jian");
        map_skill("parry", "tianmo-jian");
        map_skill("cuff", "xuwu-piaomiao");
        map_skill("hand", "huanmo-longtianwu");

        prepare_skill("cuff", "xuwu-piaomiao");
        prepare_skill("hand", "huanmo-longtianwu");

        set("no_teach", ([
            "xixing-dafa"    : "���ѽ����Ǵ�д���ر�����ȥ�����Լ��ж�����û�ս��㡣",
            "yijinjing"      : "�׽�������־���������ϰ�ã�ȴҲδ��Ҫ�졣",
            "damo-jian"      : (: no_learn :),
            "taiji-jian"     : (: no_learn :),
            "huifeng-jian"   : (: no_learn :),
            "taishan-sword"  : (: no_learn :),
            "hengshan-jian"  : (: no_learn :),
            "hengshan-sword" : (: no_learn :),
            "huashan-sword"  : (: no_learn :),
            "songshan-sword" : (: no_learn :),
        ]));

        create_family("�������", 1, "����");

        set("inquiry", ([
                "���Ǵ�" : "��д���ر���������÷ׯδ��ȡ�أ���ȥ���Ұɡ�\n",
                "�Ƚ�"     : (: ask_bijian :),
                "����"     : (: ask_bijian :),
                "�׽"   : (: ask_jing :),
                "��ľ��"   : "Ҫ�ú�ľ��Ϸ����ȿ�����Ľ�����\n",
                "����"     : (: ask_pfm :),
                "һ������" : (: ask_pfm :),
        ]) );

        set("master_ob",4);
        setup();
        carry_object("/d/wudang/obj/bluecloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void attempt_apprentice(object ob)
{
     if(! permit_recruit(ob))  return;

     if( query("family/master_name", ob) == "��������" )
     {
          command("say �����" + RANK_D->query_rude(ob) +
                  "�����Ѹ����Ǹ�����������������ʲô������ҹ���");
          return;
     }

     if( query("combat_exp", ob)<250000 )
     {
          command("say �㾭��̫���ˣ�����Ҫ�ٶ��ĥ����");
          return;
     }

     if((int)ob->query_skill("riyue-xinfa", 1) < 140)
     {
          command("say ���̵��ڹ��ķ��㻹û���ã���Ҫ���¿๦���У�");
          return;
     }

     command("haha");
     command("recruit "+query("id", ob));
     command("say �ã��Ϸ�����ֵ�һ��ͽ�������������������ھ�Ҫ���ˣ�");
     set("title", HIR"������̴󻤷�"NOR, ob);
}

int ask_bijian()
{
        object obj, me = this_player(), ob = this_object();
        message_vision("$N����˵���������������Ұݼ�����ǰ�����������ָ�̡���\n
$nЦ���������ÿ������������Ҽ�į���ɶ�л��������\n", me, ob );
        message_vision("$N���������ҡ���\n
$n���˵�ͷ��˵��������ֻ��������Ľ�����������Ĺ�
�У���˵����Ҳδ����ʤ�����㡣��\n\n", me, ob);
        command("enable sword damo-jian");
        say(HIR"�����д��һ���������ֽ�������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("������̾�˿�����˵��������һ�С���\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword taiji-jian");
        say(HIR"�����д��һ�������䵱��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("������̾�˿�����˵�����������С���\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword huifeng-jian");
        say(HIR"�����д��һ���������ҽ�������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("������̾�˿�����˵�����������С���\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword songshan-sword");
        say(HIR"�����д��һ��������ɽ��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("������̾�˿�����˵�����������С���\n");
                command("enable sword tianmo-jian");
                return 1;
        }

        command("enable sword taishan-sword");
        say(HIR"�����д��һ������̩ɽ��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("������̾�˿�����˵�����������С���\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword huashan-sword");
        say(HIR"�����д��һ��������ɽ��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("������̾�˿�����˵�����������С���\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword hengshan-sword");
        say(HIR"�����д��һ��������ɽ��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("������̾�˿�����˵�����������С���\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        command("enable sword hengshan-jian");
        say(HIR"�����д��һ��������ɽ��������"NOR);
        COMBAT_D->do_attack(ob, me, query_temp("weapon"));
        if( query("qi", me)<0 || !present(me,environment()) )
        {
                say("������̾�˿�����˵����������û�����С���\n");
                command("enable sword tianmo-jian");
                return 1;
        }
        if( query_temp("heimuling", me) )
            say("������˵��������������λ" + RANK_D->query_respect(me) +
                "�书������ȥ����ɱ�˶��������Ǹ���������\n");
        else
        {
            say("������˵��������λ" + RANK_D->query_respect(me) +
                "�����Ҿ�����һ���ľ��ɡ���\n");
            set_temp("heimuling", 1, me);
        }
            obj = new("/d/heimuya/obj/heimu-ling");
            obj -> move(me);
        command("enable sword tianmo-jian");
        return 1;
}

mixed no_learn()
{
        command("shake");
        command("say �⹦��������ʱ������ģ�Ҳ��֪���öԲ��ԣ���Ͳ�Ҫѧ�ˡ�");
        return -1;
}

mixed ask_pfm()
{
     object me = this_player();

     if( query("can_perform/tianmo-jian/chuanxin", me) )
           return RANK_D->query_respect(me) + "������Ϸ��д�һ�����գ�";

     if( query("family/family_name", me) != query("family/family_name") )
           return "�����书�������֣���λ" + RANK_D->query_respect(me) +
                  "��Ȼ��ѧ�������������������Σ�";

     if (me->query_skill("tianmo-jian", 1) < 250)
           return "�����ħ������Ƿ��򣬻����������У��ٶ�����ȥ�ɣ�";

     message_vision(HIY "$n" HIY "��$N" HIY "���˵�ͷ�����н�������Ԧ��������ϸ�ˡ�\n" HIW
                    "ֻ��$n" HIW "˫��һ�㣬�ڿն������г���ǰ̽��������������ת" HIW
                    "��Ȧ��һ����Ӱ��ֱ��$N" HIW "������\n" NOR,
                    me, this_object());
     say(HIC"������ƮȻ���䣬�������ʣ�΢Ц������������û�У���\n"NOR);
     tell_object(me, HIY "��ѧ���ˡ�һ�����ġ���һ�С�\n" NOR);
     if (me->can_improve_skill("sword"))
             me->improve_skill("sword", 160000);
     set("can_perform/tianmo-jian/chuanxin", 1, me);
     return 1;
}

string ask_jing()
{
     object me, ob;
     string msg;

     me = this_player();
     if( query("family/family_name", me) != query("family/family_name") )
            return "�����׽������������������ϰ�ã��������ò�����";

     if( query("family/master_id", me) != query("id") )
            return "��˵�������ָ�ɮ�����ļ�¼��������֪�����Ǽ١�";


     if (objectp(present("yijinjing", me)))
            return "�㲻�����о����ˣ���������ʲô��";

     if( query_temp("ask_jing", me) && time()-query_temp("ask_jing", me)<120 )
            return "����˵�˾��鲻���Ϸ����ϣ��㲻����ô��";

     if (random(3) != 0 || query("yijinjing_count") < 1)
     {
            if( query_temp("ask_jing", me) )
                  msg = "�Ϸ�δ���������һأ����ٵȵȰɡ�";
            else
                  msg = "�����ʱ�������Ϸ����ϡ�";
            set_temp("ask_jing", time(), me);
            return msg;
     }

     addn("yijinjing_count", -1);
     ob = new("/clone/book/yijinjing");
     ob->move(me);
     return "��������ҪС���պã�ǧ����ʾ�����ˡ�";
}

void reset()
{
     set("yijinjing_count", 1);
}
