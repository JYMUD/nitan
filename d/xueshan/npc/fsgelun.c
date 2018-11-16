// /d/xueshan/npc/fsgelun.c
// Summer 9/26/1996.
// Rama modified for hx

#include <ansi.h>
inherit NPC;

string ask_fashi();
void create()
{
        set_name("��������", ({ "jisi lama", "jisi", "lama" }));
        set_weight(3000000);
        set("long",
"�������ڵĽ���ɮ�����ð�������������ŷ��������Ż��ۣ�ͷ����ñ��\n"
"������ɱ֮����\n");
        set("gender", "����");
        set("age", 20);
        set("attitude", "heroism");
        set("class","bonze");
        set("shen_type", -1);
        set("str", 50);

        set("max_qi", 500);
        set("max_jing", 450);
        set("neili", 500);
        set("max_neili", 500);
        set("jiali", 40);
        set("combat_exp", 50000);
        set("score", 5000);

        set_skill("force", 50);
        set_skill("dodge", 55);
        set_skill("parry", 60);
        set_skill("staff", 60);
        set_skill("cuff", 60);
        set_skill("hammer", 60);


        set("inquiry", ([
                "׼������" : (: ask_fashi :),
                "preparation" : (: ask_fashi :),
        ]) );

        setup();
        switch( random(3) )
        {
                case 0:
                         carry_object("/clone/weapon/falun")->wield();
                         break;
                case 1:
                         carry_object("/d/xueshan/obj/fachu")->wield();
                         break;
                case 2:
                         carry_object("/d/xueshan/obj/faling")->wield();
        }
        carry_object("/d/xueshan/obj/lamajiasha")->wear();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}


void greeting(object ob)
{
        int bonus;
        mixed exp1, exp2;

        exp1=query("combat_exp", ob);
        exp2=query_temp("������", ob);
        if( !query_temp("������", ob))return ;
        {
message_vision("�������Ｑ��ææ�Ը�С����������̳����񣬵����͡�\n\n", ob);
message_vision(HIR"$N��ȼ�˼�̳�е�ľ�������ͣ������һ�������\n", ob);
message_vision(HIB"һ˿����������̳��ȽȽ���𡣻�����$N�𷨸��٣��ǻ���ȥ��\n", ob);
message_vision(RED"$N����­������һ��ˮ�����ۡ���һ���͵س������ܻ����罫��ȥ��\n", ob);

message_vision(HIC"$N���ȴ�����������̣����������дǣ�������һ˿������$N��ǰ���۳��Ρ�\n", ob);
message_vision(HIG"����Խ��Խ�࣬��Ȼ�ʳ����Σ�$N��ָ���Σ��������ԣ�ָ������֮·��\n", ob);
message_vision(HIW"$N�ֳַ��壬���߱�ҡ�������ж��ܴ����䡣ͻȻ���һ��������������\n", ob);
message_vision(HIY"��Ժ���â����һ����������ָֻ���ƽ����������ϡ�\n"NOR, ob);
                if (exp2 > exp1)
                {
                        bonus= ob->query_skill("lamaism",1) / 2;
                        if( ob->set_temp("��ҷ���") )

{
                               addn("combat_exp", random(200)+100, ob);
                               addn("family/gongji", random(8)+4, ob);
                                if( query("potential", ob)>ob->query_potential_limit() )
                                        addn("potential", 1, ob);
                                else
                                        addn("potential", random(30)+50, ob);
                                ob->start_busy(6);
}
                                else
{
                       if (exp2- exp1 > exp1)
             {
                            addn("combat_exp", random(200)+500, ob);
                               addn("max_neili", random(5)+1, ob);
                             addn("family/gongji", random(8)+4, ob);
                                if( query("potential", ob)>ob->query_potential_limit() )
                                        addn("potential", 1, ob);
                                else
                                        addn("potential", random(100)+50, ob);
                               ob->start_busy(6);
                             }
                          else
{
                                addn("combat_exp", random(300)+200, ob);
                               addn("family/gongji", random(8)+4, ob);
                  if( query("potential", ob)>ob->query_potential_limit() )
                                        addn("potential", 1, ob);
                                else
                             addn("potential", random(100)+50, ob);
                                ob->start_busy(6);
}
                }
                 }
                else
message_vision(HIR"\n$N��֪���������˸�����ɷ�н��µ������ȣ������ǰ�æ�ˡ�\n"NOR, ob);
                                addn("jing", -20, ob);
                                ob->start_busy(6);
                                delete_temp("������", ob);
                command("say �����Ѿ�����,����������������");
                ob->apply_condition("gelunbu",1+random(5));
if (present("corpse",this_object()))
destruct(present("corpse",this_object()));
if (present("skeleton",this_object()))
destruct(present("skeleton",this_object()));
                command("go north");
                command("go east");
                command("go east");
                command("go south");
                                        }
}



string ask_fashi()
{
        mapping fam;
        object ob = this_player();

        if( query("short", environment(this_object())) != "ǰԺ" )
                return "�������������£���û�����᣿";
        if( !(fam=query("family", ob)) || fam["family_name"] != "ѩɽ��" )
                return "����������������ë�棬Ҳ������ƨ���£�";

        if ( ob->query_skill("lamaism",1) < 60)
                return "��������ķ�����ú��أ�û�����㿪̳�����¡�";
       if( query("max_neili", ob)<300 )
              return "�������������ѽ��û�����㿪̳�����¡�";
       if( query("jingli", ob)<200 )
              return "��ľ���������ѽ��û�����㿪̳�����¡�";
         if(ob->query_condition("gelunbu")>0)
         return "��ո���������,��������Ϲ����ʲ��?";

        set_temp("����", 1, ob);
        return "��λ������Ҫ����λʩ��������ѽ��";
}

int accept_object(object who, object ob)
{
        object myenv ;
        if( !query_temp("����", who) )

        {
message_vision("��������Ц�Ŷ�$N˵�����ֳ�����������ʲô�ã��������Լ����Űɣ�\n", who);
                return 0 ;
        }
        if( query("killed_by", ob) != query("id", who) )
{
               message_vision("�������������Ķ�$N˵�������Լ�ɱ�Ļ�������?\n", who);
           return 0;
}

        if( query("name", ob) == "��ͷʬ��" )
{
               message_vision("�������������Ķ�$N˵���Դ�û���˻���ô���ȣ�\n", who);
           return 0;
}
        delete_temp("����", who);

        if( query("id", ob) == "corpse" )
        {
                message_vision("��������Ц�Ŷ�$N˵��������ȥ��̳�ɣ�\n", who);
                set_temp("������",query("combat_exp",  ob), who);
                if( query("userp", ob) )

                        set_temp("��ҷ���", 1, who);
//      who->set_leader(this_object());
//                destruct(ob);
                command("go north");
                command("go west");
                command("go west");
                command("go south");
                return 1;
        }
        else
                 message_vision("���������$N˵�����ֶ������������£�ֱ������ʡ�¡�\n", who);
        return 0;
}
