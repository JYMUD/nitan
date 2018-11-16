// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "mojiao.h"

inherit NPC;
inherit F_MASTER;
//inherit F_QUESTER;

void create()
{
        set_name("����", ({"ding peng", "ding", "peng"}));
        set("title", "ħ�̽���");
        set("nickname", HIR"����"NOR);
        
        set("gender", "����");
        set("age", 24);
        
      set("long","
һλ��ʮ��������꣬һ���ز����£����ϵ�һ�ѵ��������أ��������䣬��������
��С¥һҹ�����꡽�߸��֡�\n");
        set("attitude", "peaceful");

        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 20000);
        set("max_qi", 20000);
        set("jing", 10000);
        set("max_jing", 10000);
        set("neili", 130000);
        set("max_neili", 130000);
        set("jiali", 3000);

        set("combat_exp", 350000000);
        set("score", 0);
        set_skill("force", 800);
        set_skill("moshen-xinfa", 800);
        set_skill("chiyou-kuangzhanjue", 800);
        set_skill("dodge", 800);
        set_skill("moshen-bufa", 800);
        set_skill("jiutian-xiaoyaobu", 800);
        set_skill("strike", 800);
        set_skill("moshen-zhangfa", 800);
        set_skill("cuff", 800);
        set_skill("moshen-quanfa", 800);
        set_skill("sword", 800);
        set_skill("moshen-jianfa", 800);
        set_skill("blade", 800);
        set_skill("moshen-daofa", 800);
        set_skill("moon-blade", 800);
        set_skill("parry", 800);
        set_skill("literate", 800);
        set_skill("medical", 800);
        set_skill("mojiao-medical", 800);
        set_skill("motun-tianxia", 800);
        set_skill("martial-cognize", 800);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "moshen-jianfa");
        map_skill("blade", "moon-blade");
        map_skill("parry", "moon-blade");

        prepare_skill("strike", "moshen-zhangfa");


        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.ting" :),
                (: perform_action, "blade.yue" :),
                (: exert_function, "recover" :),
        }) );

        
        create_family("ħ��", 39, "����");
  

        set_temp("apply/attack", 280);
        set_temp("apply/damage", 280);
        set_temp("apply/unarmed_damage", 280);
        set_temp("apply/armor", 280);
                        
        set("master_ob", 5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/kungfu/class/mojiao/obj/blade")->wield();
        add_money("silver",70);
}

void attempt_apprentice(object ob)
{
        if( query("family/family_name", ob) != "ħ��" )
         {
                 command("say ���������ԨԴ����ΪʲôҪ�����书��");
                 return;
                }
        if (! permit_recruit(ob))  return;
        if( query("combat_exp", ob)<2000000 )
        {
                command("���书̫���ˣ��ͱ����ħ�̶����ˡ�");
                 return;
               }

        if ((int)ob->query_skill("chiyou-kuangzhanjue", 1) < 400) 

        {
                command("say ���̵��ڹ��ķ��㻹û���ã���Ҫ���¿๦���У�");
                return;
        }
      
        command("recruit "+query("id", ob));
}

int accept_ask(object me, string topic)
{
          switch (topic)
        {
        case "��ʱ������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/moon-blade/yue",
                           "name"    : "��ʱ������",
                           "sk1"     : "moon-blade",
                           "lv1"     : 300,
                           "dodge"   : 300,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "С¥һҹ������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/moon-blade/ting",
                           "name"    : "С¥һҹ������",
                           "sk1"     : "moon-blade",
                           "lv1"     : 300,
                           "dodge"   : 300,
                           "gongxian": 1000,
                           "shen"    : -50000, ]));
                break;

        case "�����ϣ����ϵ�" :
                  return MASTER_D->teach_pfm(me, this_object(),
                          ([ "perform" : "can_perform/moon-blade/dao",
                             "name"    : "�����ϣ����ϵ�",
                             "sk1"     : "moon-blade",
                             "lv1"     : 400,
                             "dodge"   : 400,
                             "gongxian": 1000,
                             "shen"    : -50000, ]));
                  break;
        default:
                return 0;
        }

}
