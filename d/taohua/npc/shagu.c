//Cracked by Kafei
// Kane

inherit NPC;
#include <ansi.h>
int auto_perform();
string ask_rudao();

void create()
{
        set_name("ɵ��", ({ "sha gu", "sha", "gu" }));
        set("long",
"��������Ů������ʱ�ƺ����˾��ţ��������������볣����Ȳ��˺ܶࡣ\n"
"����òƽƽ�������ܴ��������ɵЦ��������Ŷ��衣\n");
        set("gender", "Ů��");        
        set("age", 20);
        set("attitude", "heroism");
        set("shen_type", 0);
        set("str", 35);
        set("int", 10);
        set("con", 30);
        set("dex", 10);
        
        set("max_qi", 1100);
        set("max_jing", 800);
        set("neili", 1800);
        set("max_neili", 1800);
        set("jiali", 300);
        set("combat_exp", 50000);
/*
        set_temp("apply/armor", 100);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
*/        
        set_skill("force", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        set_skill("strike", 100);
        
        set("inquiry", ([
        "��" : (: ask_rudao :),
        "��һ��" : (: ask_rudao :),
        "��һ���" : (: ask_rudao :),
        ]));

        create_family("�һ���", 3, "����");
        set("amulet_count", 1);

        setup();
        carry_object("/clone/cloth/cloth")->wear();
        carry_object("/d/taohua/obj/huocha")->wield();
}

void init()
{
        ::init();
        add_action("do_agree", "agree");
}

string ask_rudao()
{
        object me, obj;

        me = this_player();
        
    if( query_temp("play_with_shagu", me)>1+random(2 )
        && query("amulet_count") > 0 ) {
                command("say ����������湻�õģ������������ɡ�\n");
                obj = new("/d/taohua/obj/amulet");
                obj->move(me);
                delete_temp("play_with_shagu", me);
                addn_temp("amulet_count", -1);
                message_vision("$N�ݸ�$nһ����������\n", this_object(), me);
        }
                
        if( query("family/master_name", me) == "��Ӣ"
         || query("family/master_name", me) == "��ҩʦ"){
                return "�㲻���һ���������������˶��ܴ����������ɵ����ġ�\n���汿����ɵ�û�����";
        }

        set_temp("pending/rudao", 1, me);
        return "үү˵�����ò������ĵ����ϵ���������ܰ��Ҽ����ᣬ\n�������ȥ��Ը��(agree)�Ļ��������ҡ�\n"; 
}


int do_agree()
{
        int i, k;

        write(CYN"\nɵ�������ָ��˵�����������е�������������������\n"NOR);
        
        set_temp("apply/armor", 100);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);

        k = 5+random(6);
        if( !query_temp("pending/rudao", this_player()) )
                return 0;
        for (i = 0; i < k; i++) {
                if( query("qi", this_player())<0
                || !present(this_player(), environment())) {
                write(CYN"\nɵ�������ָ��˵�����������е��������������������������ĵļһ��������\n"NOR);                        
                        delete_temp("apply/armor");
                        delete_temp("apply/attack");
                        delete_temp("apply/defense");
                        return 1;
                }
                COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon")); 
        }

        write(CYN"\nɵ�þ��˾��죬˵�����ðɣ���͹�ȥ�ɣ��ǵ������������������\n"NOR);        
        set_temp("shagu_pass", 1, this_player());

        delete_temp("apply/armor");
        delete_temp("apply/attack");
        delete_temp("apply/defense");
        return 1;
}


int accept_fight(object me)
{
        command("say ��Ү����Ү���������������ˣ�\n");
        call_out("play_with_shagu", 10, me);
        return 1;
}

int accept_kill(object me)
{
        if( query("family/family_name", me) == "�һ���"){
        command("say ���ұ���ͬ�ţ����Ҫ�Ӻ����ң�\n");
        set_temp("th_killer", 1, me);
        kill_ob(me);
        return 1;
        }
        return 0;
}

int play_with_shagu(object me)
{
        if( !me->is_fighting(this_object()) )
                return 1;
        command("say ���棡���棡��������棡");
        addn_temp("play_with_shagu", 1, me);
}