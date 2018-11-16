// hu.c ����ţ
// shilling 97.2
#include <ansi.h>;
inherit NPC;
inherit F_MASTER;

//void attempt_apprentice(object ob);
int ask_me();

void create()
{
        set_name("����ţ", ({ "hu qingniu", "hu" }));
        set("long", 
                "���������̺ųƼ������ȵĺ���ţ����˵����ͨҽ������������\n"
                "���������Ӳ�ҽ������ʿ��\n");
        set("gender", "����");
            set("title",HIG "����" NOR "����");
        set("nickname","����ҽ��");
        set("age", 50);
        set("class", "shaman");
        set("attitude", "peaceful");
        set("str", 25);
        set("int", 27);
        set("con", 25);
        set("dex", 25);
        set("inquiry", ([
                "����" : (:ask_me:),
        ]) );

        set("max_qi", 1500);
        set("max_jing", 600);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 60);
        set("combat_exp", 150000);
        set("score", 80000);

        set_skill("force", 90);
        set_skill("dodge", 90);
        set_skill("unarmed",90);
        set_skill("parry", 90);

        create_family("����", 35, "����");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

int ask_me()
{
        object ob;
        ob=this_player();

        if( query("family/family_name", ob) != "����" )
                return notify_fail("�㲻�����������µ��ӣ��Ҳ�����Ϊ�����ˡ�\n");
        if( query("eff_qi", ob) == query("max_qi", ob) )
        {
                command("?"+query("id", ob));
                command("say ��û�����κ��˰���\n");
                return 1;
        }
        else
        {
                message_vision("����ţι$N����һ��ҩ��,Ȼ����ϥ���£�˫������$N�ı��ġ�\n", ob);
                remove_call_out("recover");
                call_out("recover",2,ob);
                return 1;
        }
}


int recover(object ob)
{
        set("eff_qi",query("max_qi",  ob), ob);
        set("eff_jing",query("max_jing",  ob), ob);
        message_vision("��Լ����һ�Ѳ��ʱ�ݣ�����ţ������վ��������\n",ob);
        command("say ��������Ѿ�ȫ����,����������\n");
        return 1;
}
