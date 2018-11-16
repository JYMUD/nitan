// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

#define MOON_BLADE    "/clone/lonely/moonblade"

mixed ask_blade();

void create()
{
        set_name("����", ({"qing qing", "qing"}));
        set("gender", "Ů��");
        set("age", 21);
        set("shen_type", -1);
        set("long", "
����һ����ɫ���·��������Ǵ������ʵ���գ�
������峺�ĺ�ˮ����ˮ�е�ӳ�ŵ�Զɽ������
���ض����ʡ�Ц�����£����ᣬ���࣬�߹���
�Ϲ���һ���䵶���䵶���ô��������ʣ�������
����һ������Բ������顣");

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

        set("combat_exp", 150000000);
        set("score", 0);

        set_skill("force", 600);
        set_skill("moshen-xinfa", 600);
        set_skill("chiyou-kuangzhanjue", 600);
        set_skill("dodge", 600);
        set_skill("moshen-bufa", 600);
        set_skill("jiutian-xiaoyaobu", 600);
        set_skill("strike", 600);
        set_skill("moshen-zhangfa", 600);
        set_skill("cuff", 600);
        set_skill("moshen-quanfa", 600);
        set_skill("sword", 600);
        set_skill("moshen-jianfa", 600);
        set_skill("blade", 600);
        set_skill("moshen-daofa", 600);
        set_skill("moon-blade", 600);
        set_skill("parry", 600);
        set_skill("literate", 600);
        set_skill("medical", 600);
        set_skill("mojiao-medical", 600);
        set_skill("motun-tianxia", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "chiyou-kuangzhanjue");
        map_skill("dodge", "jiutian-xiaoyaobu");
        map_skill("strike", "moshen-zhangfa");
        map_skill("cuff", "moshen-quanfa");
        map_skill("sword", "moshen-jianfa");
        map_skill("blade", "moon-blade");
        map_skill("parry", "moon-blade");

        prepare_skill("strike", "moshen-zhangfa");

        create_family("ħ��", 40, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.ting" :),
                (: perform_action, "blade.yue" :),
                (: exert_function, "recover" :),
        }) );

        set("inquiry", ([
                "Բ���䵶"      : (: ask_blade :),
                "Բ��ħ��"      : (: ask_blade :),
        ]));

        set_temp("apply/attack", 280);
        set_temp("apply/damage", 280);
        set_temp("apply/unarmed_damage", 280);
        set_temp("apply/armor", 280);

        set("master_ob", 5);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/blade")->wield();
        add_money("silver",70);
}

void attempt_apprentice(object ob)
{
        command("say �Ҳ���ͽ���㻹���������˰ɣ�");
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

int recognize_apprentice(object ob, string skill)
{
        object blade, owner;

        blade = find_object(MOON_BLADE);
        if (! blade) blade = load_object(MOON_BLADE);
        owner = environment(blade);

        if (owner != ob)
        {
                command("say �㻹�����õ�Բ���䵶����������ѧϰԲ�µ����ɣ�");
                return -1;
        }

        if (ob->query_skill(skill, 1) >= 600)
        {
                command("say ���ˣ��Ҿͽ��㵽����ɣ��书����"
                        "Ҫ���Լ����о����ǣ�");
                return -1;
        }

        if( query_temp("can_learn/qingqing/moon-blade", ob) && 
            skill == "blade")
                return 1;

        if( query_temp("can_learn/qingqing/moon-blade", ob) && 
            skill == "moon-blade")
                return 1;

        if (skill == "moon-blade")
        {
                if( query("family/family_name", ob) != "ħ��" )
                {
                        command("say ���������ԨԴ����ΪʲôҪ�����书��");
                        return -1;
                }

                message_vision("$N���˿�$n�����ͷ����Բ�µ���Ҳû��ʲô��ѧ�ġ�\n",
                               this_object(), ob);
                set_temp("can_learn/qingqing/moon-blade", 1, ob);
                return 1;
        }

        command("say ��ֻ����һ��Բ�µ�������ɲ�ҪΪ���ҡ�");
        return -1;
}

mixed ask_blade()
{
        object ob,owner;
        object gift;
        object me;

   int cost;
        me = this_player();
        if( query("family/family_name", me) != query("family/family_name") )
                return "����������";

        if( query("combat_exp", me)<2000000 )
                return "���书̫���ˣ��ͱ����ħ�̶����ˡ�";

   if( query("family/first", me) ) cost = 250; 
             else cost = 500; 
             if( query("family/gongji", me) < cost ) 
                     return "��Ϊ��ħ��Ч��������������ӵ���㹻��ʦ�Ź��������һ�Բ���䵶ʹ��ʱ��ɡ�";

        call_other(MOON_BLADE, "???");
        ob = find_object(MOON_BLADE);
        if (! objectp(ob))
                return "��û�ˣ�";

        if (objectp(owner = environment(ob)))
        {
                if(owner == me)
                {
                        destruct(ob);
                        return "��ʲô��˼����Ҫ���û����\n";
                }
                if(owner->is_character())
                {
                        return "���Ѿ���" + owner->name(1) + "�����ˡ��ȹ黹��������ȡ�ɡ�\n";
                }
                return "���Ѿ����˽����ˡ����ڲ�֪����ʲô�ط���\n";
        }
        ob->move(me, 1);
        ob->start_borrowing();
    addn("family/gongji", -cost, me); 
        message_vision("$N�ͳ�һ������ѿ�������䵶���ݸ�$n��"
                       "���������Ҫ�ú��ˣ������������ߡ���\n", this_object(), me);
        return 1;
}
