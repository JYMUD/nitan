#include <ansi.h>
inherit NPC;

int ask_me();
int ask_ok();

void create()
{
        set_name("��С��", ({ "jiang xiaotie", "jiang", "xiaotie" }) );
        set("title", HIB"ҩ����"NOR+WHT"����"NOR);
        set("long", "���ǻش��õĹ��£�����ش��õ����ۡ�\n" );
        set("gender", "����" );
        set("age", 17);
        set("combat_exp", 10000);
        set("attitude", "friendly");

        set("inquiry", ([
                "job" : (: ask_me :),
                "ok" : (: ask_ok :),
        ]));

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

        if( query("party/party_name", ob) == "ҩ����"){
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

int ask_me()
{
        object ob, me;
        me = this_player();

        if( query("family/family_name", me) != "ҩ����"){
                command("say �㲻������Ļ�ƣ����ֻ���ô��������أ�\n");
                return 1; }
        if( query_temp("work_pass", me)){
                command("say ������ȥ����������\n");
                return 1; }

        if( (int)me->query_skill("medical",1)>=40 ) {
                command("say �㲻��Ҫ�����ֻ�ģ�\n");
                return 1; }

        if( !query_temp("renwu_name", me)){
                ob = new(__DIR__"obj/saoba");
                ob->move(me);
                message_vision(YEL"��δ����$Nһ֧ɨ�ѡ�\n"NOR, me);
        switch ( random(7) ) {
        case 0 :
                set_temp("renwu_name", "��Ϣ��", me);
                command("say ��ȥ��ɨ(dasao)һ����Ϣ�Ұɣ�\n");
                return 1;
        case 1 :
                set_temp("renwu_name", "����", me);
                command("say ��ȥ��ɨ(dasao)һ�±����ɣ�\n");
                return 1;
        case 2 :
                set_temp("renwu_name", "����", me);
                command("say ��ȥ��ɨ(dasao)һ�������ɣ�\n");
                return 1;
        case 3 :
                set_temp("renwu_name", "ͥԺ", me);
                command("say ��ȥ��ɨ(dasao)һ��ͥԺ�ɣ�\n");
                return 1;
        case 4 :
                set_temp("renwu_name", "�ش���", me);
                command("say ��ȥ��ɨ(dasao)һ�´��Űɣ�\n");
                return 1;
        case 5 :
                set_temp("renwu_name", "����", me);
                command("say ��ȥ��ɨ(dasao)һ�����ݰɣ�\n");
                return 1;
        case 6 :
                set_temp("renwu_name", "����", me);
                command("say ��ȥ��ɨһ�������ɣ�\n");
                return 1;
                }
        }
        else {
                command("say ���Ȱѻ����ɣ�\n");
                return 1;
        }
}

int ask_ok()
{
            object money, me;
          int amount, i,exp,pot;
          exp = 25+random(5);
          pot = 5+random(5);
        me = this_player();
        amount = random(3);
        i = random(20);
        if( query_temp("renwu_wancheng", me) >= 100){
                delete_temp("renwu_wancheng", me);
                delete_temp("renwu_name", me);
                if ( present("saoba", me) ) {
                        message_vision ("$N�������е�ɨ�ѡ�\n", me);
                        destruct(present("saoba", me));
                        money = new ("/clone/money/silver");
                        money->move(me);
                        money->add_amount(amount);
                          addn("combat_exp", exp, me);
                          addn("potential", pot, me);
                          command("say �ã��ɵò�����������ģ�\n");
                                tell_object(me, HIC "������" + chinese_number(exp) + "��" 
                                 "�����" + chinese_number(pot) + "��Ǳ�ܡ�"
                                 "\n" NOR);
                        if(i=1) {addn("max_jingli",1,me);} 
                } else { 
                        command("hmm"+query("id", me));
                        command("say ��û�ã�����ɻ��ѹ��߶����ˣ�\n");
                        }
        } else {
                command("say ��Ͽ�ȥ�ѻ���갡��\n");
                }
        return 1;
}
