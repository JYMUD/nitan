#include <ansi.h>
inherit NPC;

string ask_staff();
void create()
{
        set_name("����", ({"a xiu", "xiu", "a"}));
        set("gender", "Ů��");
        set("title", "����������Ů");
        set("age", 16);
        set("long", "����������������Ů��ʮ������͡���������\n"
                    "�������ˡ�\n");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("con", 30);
        set("per", 30);
        set("int", 24);
        set("dex", 30);

        set("max_qi", 800);
        set("max_jing", 500);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 10);
        set("combat_exp", 100000);
        set("score", 2000);
  set("count", 1);

        set("inquiry", ([
                    "ʯ����"   : "���ȥ�����͵���Ҳ��֪����������ô���ˡ�",
                    "������"   : "ֻ���Ҳ�����ô��������ɲ���",
                    "ʯ����"   : "�ߣ��Ǹ��һ������ϧ��",
                    "����"   : "�����ҵ�ѽ��",
                    "������"   : "������үүѽ��",
                    "������" : (: ask_staff :),
        ]) );
        set("chat_chance", 5);
        set("chat_msg", ({
                "����������ƽ����̶ˮ��˵����̶����֣����������ʲô������\n",
                "���忴��Զɽ�����ư��ƣ�̾������Ҫʲôʱ��Ŵ����͵�������\n",
                       CYN "�����Ȼ��򭲻�죬����������ʲô����֮�¡�\n" NOR,
        }) );

        set_skill("force", 100);
        set_skill("xueshan-neigong", 100);
        set_skill("wuwang-shengong", 80);
        set_skill("dodge", 80);
        set_skill("taxue-wuhen", 80);
        set_skill("cuff", 80);
        set_skill("lingxiao-quan", 80);
        set_skill("strike", 80);
        set_skill("piaoxu-zhang", 80);
        set_skill("sword", 80);
        set_skill("hanmei-jian", 80);
        set_skill("blade", 120);
        set_skill("jinwu-blade", 120);
        set_skill("parry", 80);
        set_skill("literate", 100);
        set_skill("martial-cognize", 20);

        map_skill("force", "wuwang-shengong");
        map_skill("dodge", "taxue-wuhen");
        map_skill("cuff", "lingxiao-quan");
        map_skill("strike", "piaoxu-zhang");
        map_skill("sword", "hanmei-jian");
        map_skill("blade", "jinwu-blade");
        map_skill("parry", "jinwu-blade");

        prepare_skill("strike", "piaoxu-zhang");
        prepare_skill("cuff", "lingxiao-quan");

        create_family("������", 7, "����");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "blade.chi" :),
                (: exert_function, "recover" :)
        }) );

        setup();
        
        carry_object("/clone/weapon/mudao")->wield();
        carry_object("/clone/cloth/xian-cloth")->wear();
        carry_object("/clone/cloth/boots")->wear();
        carry_object("/clone/cloth/belt")->wear();
}

string ask_staff()
{
        object ob;
        object me;
        me = this_player();

        if(query("count") < 1)
                return "��λ" +RANK_D->query_respect(me)+"�����Ǳ�Ǹ���������Ѿ����˰��Ҹ����̴�ȥ�ˡ�";
    if( query("combat_exp", me)<200000 )
                return "���书��δ���ң������Ұѽ����Ƚ����㣿";
        addn("count", -1);
        ob=new(WEAPON_DIR"treasure/jinwu-staff");
        if ( ob->violate_unique() )
        {
                destruct( ob );
                return "���书��δ���ң������Ұѽ����Ƚ����㣿";
        }
        else
        {
                ob->move(this_player());
                return "��λ" +RANK_D->query_respect(me)+"������Ұ���ѽ����ȴ��������̣����Ƕ�л�ˡ�";
        }
}
void attempt_apprentice(object ob)
{
        command("say ���ǲ���ͽ�ģ����������ʦ���Ǻ��ˡ�");
}
