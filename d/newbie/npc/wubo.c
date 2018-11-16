// �л�Ե�Ļ����λعŴ壬���µõ�����skill�İ��� ����Ϊ�����޵е���ϼ���
inherit NPC;
inherit F_MASTER;

#include <ansi.h>

void create()
{
        set_name("�䲮", ({ "wu bo", "wu", "bo" }) );
        //set("nickname", HIY "���ָ���" NOR);
        set("title", HIC "��������" NOR);
        set("gender", "����");
        set("age", 30);
        set("long", "���ǹŴ����������������԰���Ϊʦ��bai wuqing zi��ѧϰ�书��\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("con", 30);
        set("int", 24);
        set("dex", 30);

        set("max_qi", 883400);
        set("max_jing", 881700);
        set("neili", 882800);
        set("max_neili", 882800);

        set("combat_exp", 1500000);
        set("score", 5000000);

        set_skill("sword", 30);
        set_skill("unarmed", 30);
        set_skill("blade", 30);
        set_skill("force", 30);
        set_skill("dodge", 30);
        set_skill("parry", 30);
        set_skill("mieshenquan", 30);
        set_skill("tianjian", 30);
        set_skill("juedao", 30);
        set_skill("xiaoyaobu", 30);
        set_skill("zhanshenjue", 30);
        set_skill("literate", 50);
        set_skill("martial-cognize", 50);

        map_skill("unarmed", "mieshenquan");
        map_skill("sword", "tianjian");
        map_skill("blade", "juedao");
        map_skill("parry", "tianjian");
        map_skill("force", "zhanshenjue");
        map_skill("dodge", "xiaoyaobu");

        set_temp("apply/damage", 100);
        set_temp("apply/armor", 100);

        set("inquiry", ([
               "�ϴ峤"   :  "��������ʦ����ʲô������������\n",
               "����"     :  "������ʦ�֣���Ҫ�����������\n",
        ]));

        create_family("�Ŵ�", 1, "����");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{

        /*
        if( query("newbie_quest/leixing", ob) != "baishi" )
        {
             command("shake");
             command("say û������ʦ�ϴ峤�������ҿɲ�������Ϊͽ��");
             return;
        }
        */  
              
        if( query("family", ob) )
        {
             command("yi");
             command("say ��ʦ����˭��");
             return;
        }

        command("say �ðɣ��Ҿ��������ˡ�");
        command("recruit "+query("id", ob));

        ob->save();

        return;
}

void init()
{
        tell_object(this_player(), HIG "��ʦ��ʹ��ָ�� bai ʦ��ID(bai wu bo)��\n" NOR);
        tell_object(this_player(), HIY "�鿴ʦ��������ʹ�� skills ʦ��ID(skills wu bo)��\n" NOR);
}

void unconcious()
{
        die();
}
