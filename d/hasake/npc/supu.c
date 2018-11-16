#include <ansi.h>
inherit NPC;
int ask_me();
string* goods = ({
       __DIR__"obj/shoujuan",
       __DIR__"obj/yangpi",
       __DIR__"obj/madao",
       __DIR__"obj/shoujuan",
       __DIR__"obj/shoujuan",
       __DIR__"obj/shoujuan",
       __DIR__"obj/jiunang",
       __DIR__"obj/shoujuan",
});
void destob(object ob);
void create()
{
        set_name("����", ({ "supu"}));
        set("gender", "����");
        set("age", 21);
        set("long", "һ������Ĺ�����������, �����˵�һ��ʿ��³�˵Ķ��ӡ�\n");
        set("attitude", "heroism");
        set("combat_exp", 70000);
        set("shen", 3000);
        set("str", 32);
        set("int", 20);
        set("con", 24);
        set("dex", 20);
        set("max_qi", 600);
        set("max_jing", 600);
        set("neili", 400);
        set("max_neili", 400);
        set_skill("unarmed", 30);
        set_skill("blade", 40);
        set_skill("parry", 40);
        set_skill("dodge", 40);
        set("inquiry", ([
            "����" : "�������ҵ������ˣ���ÿ��ɱ��Ұ�Ƕ���������Ƥ��\n",
            "������" : "���ĸ質����������ˣ�����˵���������񳪵û��á�
���⼸��������һֱû���������裬һֱû�ڼ�������\n",
            "ˤ��" : (: ask_me :),
            "����" : (: ask_me :),
            "��үү" : "���Ǽ����˰����������������ҵ����ƣ���ҽţ����ƥ�ļ�����\n",
            "��³��" : "�����Ұ������ǹ�������ĵ�һ��ʿ��������\n",
        ]) );
        setup();
        set("chat_chance", 10);
        set("chat_msg", ({
"�����Ժ����µ�: ��ҲҪѧ�Ұ�����Ϊ�����˵�һ��ʿ��\n",
"������������: ���Ķ�ȥŪһ���ϵȵ���Ƥ���͸�������? \n",
        }) );
        carry_object(__DIR__"obj/wandao")->wield();
        carry_object(__DIR__"obj/yangao")->wear();
        carry_object(__DIR__"obj/jiunang");
}

int ask_me()
{
        if( query_temp("supu_fight", this_player())){
            command("say ���ǲ��Ǳ��Թ�����");
            return 1;
            } 
        if( !query_temp("supu_accept", this_player())){
            command("say ���ǲ�ԭδ����һ��ʿ����ƾʲô���ұ����أ�");
            return 1;
            } 
        else {
        message_vision("$N����$nһ�ۣ��ò�̫��׼�ĺ���˵����
����δ���Ĳ�ԭ��һ��ʿ����λ����"+RANK_D->query_respect(this_player())+"��ͺ����д�(fight)���°ɣ�\n", this_object(), this_player());
        set_temp("supu1", 1, this_player());
        return 1;
        }
}

int accept_fight(object ob)
{
        object me;
        me = this_object();
        if( query("eff_qi", me)<query("max_qi", me) || 
           query("qi", me)<query("eff_qi", me) || 
           query("neili", me)<query("max_neili", me)){
           message_vision(CYN"$N��$n˵���һ�û����Ϣ�ã����һ����ɡ�\n"NOR, ob, me);
           return 0;
           }
        if( query_temp("supu1", ob)){
        message_vision(CYN"$N��$n˵���ðɣ����Ҿ�ͬ���д꼸�аɣ��㵽Ϊֹ��\n"NOR, ob, me);
        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        delete_temp("supu1", ob);
        delete_temp("supu_accept", ob);
        return 1;
        }
        else return 0;
}

int checking(object me, object ob)
{
        object good;
        int my_max_qi, his_max_qi;
           seteuid(getuid());
        my_max_qi=query("max_qi", me);
        his_max_qi=query("max_qi", ob);
        if (me->is_fighting()){
                call_out("checking",1, me, ob);
                return 1;
                }
        if ( !present(ob, environment()) ) return 1; 
        if( (query("qi", me)*100/my_max_qi) <= 50){
            message_vision(CYN"$N��$n��ס����̾�����Ǻ��˹�Ȼ��һ�㣬�ҷ����ˣ�����һЩ���\n"NOR, me, ob);
             good = new(goods[random(sizeof(goods))]); 
            set("owner",query("id",  ob), good);
            good->move(ob);
            set_temp("supu_fight", 1, ob);
            message_vision("$N����$nһ�����\n", me, ob);
            message_vision(CYN"$N˵������Ҫ��ȥ�㰢���ˣ���Ե������ɡ�\n"NOR, me);            
            message_vision("$N���Ż���Ƥ�뿪��"+query("short", environment(me))+"��\n",me);
            destruct(this_object());
            return 1;
            }
        if( (query("qi", ob)*100/his_max_qi)<50){
                message_vision(CYN"$N����$nһƲ�죬˵�������Ǻ��˵���ѧ������ˡ�\n"NOR, me,ob);
                message_vision("$N��$n���˸��񣬴�ͷɥ�����뿪�����\n",ob, me);
//                ob->move("/u/snowman/hj/road");
//                message_vision("$N��ͷɥ�����߻�����\n", ob);
                return 1;
               }
        return 1;
}

int accept_object(object who, object ob)
{
        if( !who || environment(who) != environment() ) {return 0;}
        if ( !objectp(ob) ) {return 0; }
        if ( !present(ob, who) ) return 0;
        if (userp(ob)) {
               command("?"+query("id", who));
               command("say ���⺺��ǿ�������˴������ʲô��");
               this_object()->kill_ob(who);    
               return notify_fail("��⣬�����ˣ�\n");
               }
        if( query("name", ob) == "����Ƥ"){
                command("ah"+query("id", who));
                command("say ��ɱ���˴���ǣ�������Ҳ�Ǹ���ʿ��Ҫ��Ҫ���ұ���һ�£�\n");                
                set_temp("supu_accept", 1, who);
        message_vision("$N����$nһ�ۣ��ò�̫��׼�ĺ���˵����
����δ���Ĳ�ԭ��һ��ʿ����λ����"+RANK_D->query_respect(this_player())+"��ͺ����д�(fight)���°ɣ�\n", this_object(), this_player());
        set_temp("supu1", 1, this_player());
                call_out("destob",0,ob);                         
            return 1;
        }        
        command("smile"+query("id", who));
        command("say лл������");
        call_out("destob",0,ob);  
        return 0;
}
void destob(object ob)
{
        destruct(ob);
}
