// xuanzhen.c �������

inherit NPC;
inherit F_MASTER;

#include <ansi.h>
#include "yunlong.h"

int ask_weiwang();
string ask_me();

void create()
{
        set_name("�������", ({ "xuan zhen", "xuan", "zhen" }));
        set("gender", "����");
        set("title", HIR "��ػ�"HIG"��ľ��"NOR"����");
        set("long", "\n��λ��Ĭ���Եĵ��ˣ�������ػ���ľ�û�����\n"+
                "������ľ����һ�����ĺ��֣�һ������ʹ�ó����뻯��\n");
        set("age", 55);
        set("class", "taoist");
        set("int", 30);

        set("qi", 2800);
        set("max_qi", 2800);
        set("jing", 1200);
        set("max_jing", 1200);
        set("shen_type", 1);

        set("combat_exp", 100000);
        set("attitude", "friendly");

        set_skill("force", 80);
        set_skill("unarmed", 80);
        set_skill("parry", 80);
        set_skill("dodge", 80);
        set_skill("sword", 100);
        set_skill("whip", 80);
        set_skill("hand", 70);
        set_skill("claw", 70);
        set_skill("yunlong-shengong", 70);
        set_skill("yunlong-shenfa", 70);
        set_skill("yunlong-xinfa", 70);
        set_skill("yunlong-bian", 70);
        set_skill("yunlong-jian", 80);
        set_skill("yunlong-shou", 50);
        set_skill("yunlong-zhua", 50);
        set_temp("apply/attack", 70);
        set_temp("apply/defense", 70);
        set_temp("apply/damage", 60);

        map_skill("force", "yunlong-shengong");
        map_skill("dodge", "yunlong-shenfa");
        map_skill("parry", "yunlong-jian");
        map_skill("sword", "yunlong-jian");
        map_skill("hand", "yunlong-shou");
        map_skill("claw", "yunlong-zhua");
        map_skill("whip", "yunlong-bian");

        prepare_skill("hand", "yunlong-shou");
        prepare_skill("claw", "yunlong-zhua");
        create_family("������",2, "����");
        set("book_count", 1);
        set("inquiry", ([
                "�½���" :  "�������ǵ��ܶ�����",
                "��ػ�" :  "ֻҪ��Ӣ�ۺú���������������ػ�(join tiandihui)��\n",
                "���" :  "������������ػ�ɣ�\n",
                "���帴��" : "ȥҩ�̺͹ײĵ���ϸ���ưɣ�\n",
                "����" :  (: ask_weiwang :),
                "��������" : (: ask_weiwang :),
                "������" : (: ask_me :),
        ]));
        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: command("smile") :),
                (: command("haha") :),
                (: command("chat ��λ" + RANK_D->query_respect(this_player())+",������ԩ�޳𣬺α����?\n") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("unwield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield changjian") :),
                (: command("wield bian") :),
                (: command("wield bian") :),
                (: command("wield bian") :),
                (: command("wield bian") :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "sword.xian" :),
                (: perform_action, "whip.chan" :),
                (: perform_action, "whip.chan" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: command("unwield bian") :),
                (: command("unwield bian") :),
                (: command("unwield bian") :),
                (: command("unwield bian") :),
                      }) );
        set("master_ob", 4);
        setup();
        carry_object(CLOTH_DIR"daopao")->wear();
        carry_object(CLOTH_DIR"male-shoe")->wear();
        carry_object(WEAPON_DIR"changbian")->wield();
        carry_object(WEAPON_DIR"changjian");
        add_money("gold", 1);
}
string ask_me()
{
        mapping fam;
        object ob;

        if( !(fam=query("family", this_player())) || 
                fam["family_name"] != "������")
                return RANK_D->query_respect(this_player()) +
                "�뱾��������������֪�˻��Ӻ�̸��";
        if (query("book_count") < 1)
                return "�������ˣ����ɵ������澭���ڴ˴���";
        addn("book_count", -1);
        ob = new("/clone/book/yljing2");
        ob->move(this_player());
        return "�ðɣ��Ȿ�������������û�ȥ�ú����С�";
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

//      if ((int)ob->query("weiwang") < 50) {
//              command("say ���������书�������Ե���Ҫ��Ҳ�Ǽ��ߡ�");
//              command("say " + RANK_D->query_respect(ob) + "������" +
//                      "��������ػᣬ�����ҿ��Կ�������Ϊͽ��");
//              return;
//      }
        if( query("party/party_name", ob) != "��ػ�" ){
                command("say ���������书�������Ե���Ҫ��Ҳ�Ǽ��ߡ�");
                command("say " + RANK_D->query_respect(ob) + "������" +
                        "��������ػᣬ�����ҿ��Կ�������Ϊͽ��");
                command("say �㲻�Ǳ�����֣��Ҳ������㣡");
                return;
        }
        command("say �ðɣ���Ȼ" + RANK_D->query_respect(ob) + "Ҳ��" +
                "�ұ����ˣ������������ɡ�");
        command("recruit "+query("id", ob));
}
void init()
{
        ::init();
        add_action("do_join","join");
/*
        remove_call_out("greeting");
        call_out("greeting", 1, this_player());
*/
}

int ask_weiwang()
{
        command("tell "+query("id", this_player())+"�����ڵĽ���������"+(query("weiwang", this_player())));
        say("\n����˵�������������ֵ�ܸߣ���Щ�˼����㲻������ɱ�㣬��������书�����㱦����\n"
        +"�����㻹���Լ����ᣬ�������ȥ����Ŀ�꣬����ȥǮׯȡǮҲ������Ϣ ����������\n");
        say("������˵��ɱĳЩ���˻��ĳЩ���˿�����߽���������\n");
        return 1;
}

/*
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ||
                file_name(environment(ob))!="/d/beijing/andao1") return;
        if( query("weiwang", ob) >= 50 )
        switch( random(3))
        {
                case 1:
                        say("����Ц������λ"+RANK_D->query_respect(ob)+"���Ҵ���ȥ���ðɡ�\n");
                        ob->move("/d/beijing/dating");
                        message_vision("$N�����˴�����\n",ob);
                        break;
                default:
                        say("����˵������λ" + RANK_D->query_respect(ob) + "�����Ա㡣\n");
                        break;
        }
        else say( "����Ц������λ" + RANK_D->query_respect(ob)
                                + "�����������ʲô��\n");
}
*/

int recognize_apprentice(object ob)
{
        if( query("party/party_name", ob) != "��ػ�" ){
                message_vision("$Nҡ��ҡͷ��\n",this_object());
                command("tell"+query("id", ob)+"������ػ�����Ҳ��̡�\n");
                return 0;
        }
        return 1;
}
#include "/kungfu/class/yunlong/tiandihui.h";
