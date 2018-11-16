#include <ansi.h>
#include "lingxiao.h"

inherit NPC;
inherit F_MASTER;

mixed ask_skill1();
string ask_book();
string ask_skill();

void create()
{
        set_name("ʷ����", ({"shi popo", "shi", "popo"}));
        set("long", "����ѩɽ�������˰����ڵ����ӣ���˵����������\n"
                    "�ò��ϣ�ʮ��ǰ���𡰽���һ֦����ʷС��������\n"
                    "����ȴ�����˲�֪��\n");
        set("title", "�����ɿ�ɽ��ʦ");
        set("gender", "Ů��");
        set("age", 58);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 4200);
        set("max_jing", 3500);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 200);
        set("combat_exp", 2000000);

        set("inquiry",([
                "���ڵ���":(:ask_book:),
                "����׹��":(:ask_skill:),
  "���汩��" : (: ask_skill1 :),
        ]));

        set_skill("force", 220);
        set_skill("xueshan-neigong", 220);
        set_skill("wuwang-shengong", 180);
        set_skill("dodge", 220);
        set_skill("taxue-wuhen", 220);
        set_skill("cuff", 220);
        set_skill("lingxiao-quan", 220);
        set_skill("strike", 220);
        set_skill("piaoxu-zhang", 220);
        set_skill("sword", 200);
        set_skill("hanmei-jian", 200);
        set_skill("yunhe-jian", 200);
        set_skill("xueshan-jian", 200);
        set_skill("blade", 240);
    set_skill("jinwu-blade", 240);
        set_skill("parry", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 180);

        map_skill("force", "wuwang-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "xueshan-jian");
      map_skill("blade", "jinwu-blade");
  map_skill("parry", "jinwu-blade");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("������", 5, "���ŷ���");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
     (: perform_action, "blade.jinwu" :),
                (: perform_action, "cuff.jue" :),
                (: perform_action, "strike.piao" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("count", 1);
        setup();

        carry_object("/clone/weapon/chaidao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        if( query("family/master_name", me) == "������" || 
           query("family/master_name", me) == "����" )
        {
                command("say �٣����Ȼ�����Ϲ�С��Ϊʦ������������������������");
                return;
        }

        if( query("shen", me)<10000 )
        {
                command("say ���书��������֮�ˣ����߿���");
                return;
        }

        if( query("combat_exp", me)<200000 )
        {
                command("say �����ڽ�������̫ǳ�����Ƕ�������������ɡ�");
                return;
        }

        if ((int)me->query_skill("xueshan-neigong", 1) < 100)
        {
                command("say �㱾�ŵ��ڹ��ķ�̫���������֮���������ҡ�");
                return;
        }

        command("haha");
        command("say �����Ҿ������㣬����������������ձ���ʤ���Ǹ��Ϲ�");
        command("recruit "+query("id", me));
}
mixed ask_skill1()
{
        object me;

        me = this_player();
  if( query("can_perform/jinwu-blade/chi", me) )
                return "�����Ҳ����Ѿ��̹��������Լ���ȥ�����ɣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�����������ģ����ҹ�����";

 if (me->query_skill("jinwu-blade", 1) < 1)
                return "�������ڵ�����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<800 )
                return "����ѩɽ����µµ��Ϊ���������ܷ��Ĵ��������";

        if (me->query_skill("force") < 150)
                return "����ڹ�����̫ǳ���������������ҡ�";

  if (me->query_skill("jinwu-blade", 1) < 120)
                return "��Ľ��ڵ���������������Ȼ������˼���ҡ�";

        message_vision( HIY "$n" HIY "�����������н�������ز���Ҳ"
                       "�㲻��������\n����ѩɽ�������ƽ�֮������"
                       "�ɼ����ˡ�ѩɽ�ɽ�����\n��ʮ���У��ҽ�����"
                       "�书����ʤ��һ�ȴ����ʮ���С�\n������ʮ"
                       "����������ʮ���У����һ������ϸ�ˣ���˵\n"
                       "�Űγ�����񵶴��϶���ֱ���������ֵ�������"
                       "ʹ����\n֮ʱ�����Ծ���գ�����ֱ��������"
                       "���ֽ̽������\n������η����Է��ӶݵĿ�϶"
                       "��������������$N" HIY "��$N" HIY "��\n˼��"
                       "�Σ�����ʩΪ������Ծ�𣬰���лӵ�ֱ������"
                       "��\nһ������������������ߣ��������ǳ�ɳ��"
                       "��ܲ���\nҶ�����缤�����Ŷ��裬��Ȼ����"
                       "���ˡ�\n" NOR, me, this_object());
        command("heng");
        command("say ��һ�пɾ���ѩɽ���������Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ����汩������\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
 if (me->can_improve_skill("jinwu-blade"))
     me->improve_skill("jinwu-blade", 1500000);
        me->improve_skill("martial-cognize", 1500000);
  set("can_perform/jinwu-blade/chi", 1, me);
        addn("family/gongji", -800, me);
        return 1;
}
string ask_book()
{
        object me,ob;
        ob=this_player();

        if( query("family/master_id", ob) == "bai wanjian" )
        {
                if (query("count") == 1)
                {
                        command("say �����򽣵ĵ������Ǿ͸���ɡ�");
                        message_vision(HIG"ʷ�����ͳ�һ��С���ӣ�����$N��\n\n"NOR,ob);
                        me=new(BOOK_DIR+"jinwu-book");
                        me->move(ob);
                        addn("count", -1);
                        return "��úö��������Ϲ�Ľ����ö��ˡ�\n";
                }
                else return"���������������Ѿ����������ˡ�\n";
        }
        if( query("family/master_id", ob) == "bai zizai" )
        {
                if (query("count") == 1)
                {
                        command("say �����Ϲ�ĵ������Ǿ͸���ɡ�");
                        message_vision(HIG"ʷ�����ͳ�һ��С���ӣ�����$N��\n\n"NOR,ob);
                        me=new(BOOK_DIR+"jinwu-book");
                        me->move(ob);
                        addn("count", -1);
                        return "��úö��������Ϲ�Ľ����ö��ˡ�\n";
                }
                else return "���������������Ѿ����������ˡ�\n";
        }

        command("say �߿�����Ȼ��̫��Ҫ�����ˣ�");
        message_vision(HIG"ʷ���ź���һ��������$N��\n\n"NOR,ob);

        return "�����뿪�������ǣ�ȴҲ�����Ҵ����书��\n";
}

int recognize_apprentice(object ob)
{
        mapping myfam;
        myfam=query("family", ob);
//      if ( myfam["family_name"] == "������") return 1 ;
        if( query_temp("tmark/shi", ob) == 1 )
        message_vision("ʷ���ź���һ������$N˵����������첻���ٽ��ˣ����´������ɡ�\n", ob);
        if( !query_temp("tmark/shi", ob))return 0;
        addn_temp("tmark/shi", -1, ob);
        return 1;
}

int accept_object(object who, object ob)
{
        if( query("id", ob) == "jinwu zhang" )
        {
                if( !query_temp("tmark/shi", who) )
                        set_temp("tmark/shi", 0, who);
                message_vision("ʷ���Žӹ������ȣ����Ǻǡ�Ц����������������˵����\n�ã��ã��ã��ѵ�����ҹ���Ů���£��治���ðɣ�\n������������пգ��ͽ���һ�Ṥ��ɡ�\n", who);
                addn_temp("tmark/shi", 900, who);
                return 1;
        }
        return 0;
}

string ask_skill()
{
        object me=this_object();
        object ob= this_player();

  if( query("can_perform/jinwu-blade/jinwu", ob) )
                return "�㲻���Ѿ�ѧ�����𣬻�������ʲô��";

        if( query("family/master_id", ob) != "shi popo" )
 return "�㲻���ҵĵ��ӣ��߿���";

    if ((int)ob->query_skill("jinwu-blade",1) < 100)
                return "��Ľ��ڵ����������ң��ò������С�";

          if ((int)ob->query_skill("xueshan-neigong",1) < 100)
             return "���ѩɽ�ڹ��ķ���򲻹����ò������С�";

        if( query("max_neili", ob)<1000 )
                return "�����������һЩ�����Ͱɡ�";

        message_vision( HIY "$n" HIY "�����������н�������ز���Ҳ"
                       "�㲻��������\n����ѩɽ�������ƽ�֮������"
                       "�ɼ����ˡ�ѩɽ�ɽ�����\n��ʮ���У��ҽ�����"
                       "�书����ʤ��һ�ȴ����ʮ���С�\n������ʮ"
                       "����������ʮ���У����һ������ϸ�ˣ���˵\n"
                       "�Űγ�����񵶴��϶���ֱ���������ֵ�������"
                       "ʹ����\n֮ʱ�����Ծ���գ�����ֱ��������"
                       "���ֽ̽������\n������η����Է��ӶݵĿ�϶"
                       "��������������$N" HIY "��$N" HIY "��\n˼��"
                       "�Σ�����ʩΪ������Ծ�𣬰���лӵ�ֱ������"
                       "��\nһ������������������ߣ��������ǳ�ɳ��"
                       "��ܲ���\nҶ�����缤�����Ŷ��裬��Ȼ����"
                       "���ˡ�\n" NOR, ob, this_object());
        command("heng");
        tell_object(ob, HIC "��ѧ���ˡ�����׹�ء���\n" NOR);
    set("can_perform/jinwu-blade/jinwu", 1, ob);
        return "��һ�пɾ���ѩɽ���������Լ���ȥ���ɡ�";
}
