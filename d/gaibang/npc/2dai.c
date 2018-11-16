#include <ansi.h>
inherit NPC;

#include "fight.h"

void create()                                                                   
{
        NPC_D->generate_cn_name(this_object());
        set("gender", "����");
        set("long", "����λ�������õ�ؤ����ӣ�üĿ��͸����Ӣ����\n");
        set("title", "ؤ���������");
        set("age", 38);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 1800);
        set("max_jing", 1200);
        set("neili", 1600);
        set("max_neili", 1600);
        set("jiali", 150);
        set("combat_exp", 100000);

        set_skill("force", 70);
        set_skill("huntian-qigong", 70);
        set_skill("dodge", 70);
        set_skill("feiyan-zoubi", 70);
        set_skill("staff", 70);
        set_skill("fengmo-zhang", 70);
        set_skill("hand", 70);
        set_skill("shexing-diaoshou", 70);
        set_skill("strike", 70);
        set_skill("xiaoyaoyou", 70);
        set_skill("parry", 70);
        set_skill("begging", 70);
        set_skill("checking", 70);
        set_skill("literate", 70);
        set_skill("martial-cognize", 50);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("staff", "fengmo-zhang");
        map_skill("strike", "xiaoyaoyou");
        map_skill("hand", "shexing-diaoshou");
        map_skill("parry", "fengmo-zhang");

        prepare_skill("hand", "shexing-diaoshou");

        create_family("ؤ��", 20, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "staff.luan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 20);
        set_temp("apply/unarmed_damage", 20);
        set_temp("apply/armor", 70);

        setup();

        carry_object("/clone/weapon/zhubang")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}