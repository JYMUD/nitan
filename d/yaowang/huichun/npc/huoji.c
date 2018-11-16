#include <ansi.h>
inherit NPC;
//inherit F_DEALER;

void create()
{
        set_name("���", ({ "huo ji", "huo", "ji" }) );
        set("title", HIB"ҩ����"NOR+YEL"����"NOR);
        set("gender", "����" );
        set("age", 22);
        set("combat_exp", 100);
        set("attitude", "friendly");

        setup();
        add_money("silver", 5);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{       
        object ob = this_player();

        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int greeting(object ob)
{
        int i=(query("eff_qi", ob)*100)/query("max_qi", ob);

        if( query("family/family_name", ob) == "ҩ����"){
                command("say ��λ�ֵ������ˣ��������\n");
                return 1;}

        if (i<=30) {
                command("wa"+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"�����������˰������뵽������ҩ����ҽʦ���㿴���ɣ�\n");
                return 1;}

        if (i<=60) {
                command("look"+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"�����˵ò��ᰡ�����뵽�������˰ɣ�\n");
                return 1;}

        if (i<=90) {
                command("pat"+query("id", ob));
                command("say "+RANK_D->query_respect(ob)
                        +"�������˵��ˣ����������ҩ���¾�û���ˣ�\n");
                return 1;}

        else {
        switch( random(4) ) {
                case 0:
                        command("bow"+query("id", ob));
                        break;
                case 1:
                        command("nod"+query("id", ob));
                        break;
                case 2:
                        command("hi"+query("id", ob));
                        break;
                case 3:
                        command("welcome"+query("id", ob));
                        break;
                }
        }
}

