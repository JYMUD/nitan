// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;
inherit F_COAGENT;
inherit F_MASTER;
inherit F_GUARDER;

#define JIAN "/clone/lonely/huanlingjian"

string ask_me();

void create()
{
        set_name("����", ({"yang xiao","yang","xiao",}));
        set("long",
        "����һλ�������������ײ����ۡ�\n"
        "����ò���ţ�ֻ��˫ü�����´������¶��������������ƣ������Դ�˥�����\n"
        "֮�ࡣ�����Բ�������ɫĮȻ���ƺ��ĳ�Զ����������ʲô���顣\n"
        );

        set("title",HIG "����" HIR "������ʹ" NOR);
        set("level",11);
        set("gender", "����");
        set("attitude", "peaceful");

        set("age", 42);
        set("shen_type", 1);
        set("per", 29);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 3500);
        set("max_jing", 1500);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("combat_exp", 1000000);
        set("score", 800000);

        set_skill("force", 220);
        set_skill("dodge", 220);
        set_skill("parry", 220);
        set_skill("sword", 220);
        set_skill("cuff", 220);
        set_skill("strike", 220);
        set_skill("literate", 220);

        set_skill("shenghuo-xinfa", 220);
        set_skill("lingxu-bu", 220);
        set_skill("shenghuo-bu", 220);
        set_skill("pili-quan", 220);
        set_skill("shenghuo-quan", 220);
        set_skill("guangming-zhang", 220);
        set_skill("liehuo-jian", 220);
        set_skill("xiaoyao-jian", 220);
        set_skill("martial-cognize", 220);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "lingxu-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("cuff", "shenghuo-quan");
        map_skill("parry", "xiaoyao-jian");
        map_skill("sword", "xiaoyao-jian");

        prepare_skill("cuff", "shenghuo-quan");
        prepare_skill("strike", "guangming-zhang");

        set("inquiry", ([
                "����ʥ����"  : (: ask_me :),
                "����ʥ����"  : (: ask_me :),
                "ʥ����"      : (: ask_me :),
        ]));

        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: command("perform sword.kuai") :),
                (: command("perform sword.qi") :),
                (: command("perform sword.fei") :),
                (: command("perform cuff.jin") :),
        }) );
        set_temp("apply/attack", 120);
        set_temp("apply/damage", 120);
        set_temp("apply/unarmed_damage", 120);
        set_temp("apply/armor", 120);

        set("inherit_title",HIG"����"HIC"���̷���"NOR);
        create_family("����", 34, "������ʹ");
        set("master_ob",4);
        set("coagents", ({
                ([ "startroom" : "/d/mingjiao/dadian",
                   "id"        : "zhang wuji" ]),
        }));
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/mingjiao/obj/baipao")->wear();
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        /*
        case "����Ǭ��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/pomopima-jian/zui",
                           "name"    : "����Ǭ��",
                           "sk1"     : "pomopima-jian",
                           "lv1"     : 120,
                           "force"   : 180,
                           "gongxian": 700,
                           "shen"    : 80000, ]));
                break;
        */
        case "�ɽ���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xiaoyao-jian/fei",
                           "name"    : "�ɽ���",
                           "sk1"     : "xiaoyao-jian",
                           "lv1"     : 60,
                           "gongxian": 400,
                           "shen"    : 80000, ]));
                break;


        case "�콣��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xiaoyao-jian/kuai",
                           "name"    : "�콣��",
                           "sk1"     : "xiaoyao-jian",
                           "lv1"     : 160,
                           "dodge"   : 260,
                           "gongxian": 680,
                           "shen"    : 85000, ]));
                break;


        case "�潣��" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xiaoyao-jian/qi",
                           "name"    : "�潣��",
                           "sk1"     : "xiaoyao-jian",
                           "lv1"     : 160,
                           "neili"   : 3000,
                           "gongxian": 780,
                           "shen"    : 88000, ]));
                break;


         case "���齣" :
                return MASTER_D->give_item(me, this_object(),
                               (["item"     :  JIAN,
                                 "master"   :  1,
                                 "sk1"      :  "xiaoyao-jian",
                                 "lv1"      :  120,
                                 "shen"     :  80000 ]));
                  break;
        default:
                return 0;
        }
}


void init()
{
        object me,ob;
        me = this_object ();
        ob = this_player ();

        ::init();

        if (interactive(ob) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, me, ob);
        }
}

#include "yangxiao.h"
