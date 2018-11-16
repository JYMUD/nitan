// This program is a part of NITAN MudLIB

#include <ansi.h>
#include "wudang.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

mixed ask_me();

void create()
{
        set_name("����Ϫ", ({ "zhang songxi", "zhang" }));
        set("nickname", "�䵱����");
        set("long",
                "��������������ĵ�������Ϫ��\n"
                "��������ʮ�꣬�����ܸɣ������Ƕ�ı���ơ�\n");
        set("gender", "����");
        set("age", 40);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 26);
        set("int", 33);
        set("con", 26);
        set("dex", 28);

        set("max_qi", 4700);
        set("max_jing", 2400);
        set("neili", 5100);
        set("max_neili", 5100);
        set("jiali", 90);
        set("combat_exp", 1250000);
        set("score", 50000);

        set_skill("force", 170);
        set_skill("yinyun-ziqi", 170);
        set_skill("taiji-shengong", 170);
        set_skill("dodge", 150);
        set_skill("tiyunzong", 150);
        set_skill("unarmed", 160);
        set_skill("taiji-quan", 160);
        set_skill("strike", 160);
        set_skill("wudang-zhang", 160);
        set_skill("hand", 160);
        set_skill("paiyun-shou", 160);
        set_skill("parry", 180);
        set_skill("sword", 160);
        set_skill("wudang-jian", 160);
        set_skill("blade", 160);
        set_skill("xuanxu-dao", 160);
        set_skill("taiji-jian", 160);
        set_skill("taoism", 140);
        set_skill("literate", 150);

        set("no_teach", ([
                "taiji-shengong" : "Ҫ��ѧϰ̫����������������̡�",
                "taiji-jian"     : "̫���������������״���",
                "taiji-quan"     : "̫��ȭ�����������״���",
        ]));

        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "xuanxu-dao");
        map_skill("sword", "wudang-jian");
        map_skill("blade", "xuanxu-dao");
        map_skill("strike", "wudang-zhang");

        prepare_skill("unarmed", "taiji-quan");
        prepare_skill("strike", "wudang-zhang");

        create_family("�䵱��", 2, "����");

        set("inquiry", ([
                "�һ���": (: ask_me :),
                "����"  : (: ask_me :),
        ]));

        set("coagents", ({
                ([ "startroom" : "/d/wudang/houyuan",
                   "id"        : "yu lianzhou" ]),
                ([ "startroom" : "/d/wudang/sanqingdian",
                   "id"        : "song yuanqiao" ]),
        }));

        set("chat_chance_combat", 40);
        set("chat_msg_combat", ({
                (: perform_action, "blade.huan" :),
                (: exert_function, "recover" :),
        }) );

        set("master_ob", 4);
        setup();
        carry_object(WEAPON_DIR"blade")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<6000 )
        {
                command("say ���䵱���������������ɣ��Ե���Ҫ���ϡ�");
                command("say �ڵ��з��棬" + RANK_D->query_respect(ob) +
                        "�Ƿ����ò�����");
                return;
        }

        if ((int)ob->query_skill("yinyun-ziqi",1) < 60)
        {
                command("say ���䵱����ע���ڹ��ķ�" + RANK_D->query_respect(ob)+
                        "�Ƿ�Ӧ�����䵱�ķ��϶��µ㹦��?");
                return;
        }

        if ((int)ob->query_skill("taoism", 1) < 60)
        {
                command("say ϰ����Ϊ��ǿ�����壬һζ�������ǲ���ȡ�ġ�");
                command("say �ҿ��㻹��Ҫ���������Է�����������������"
                        "����ĵ����ķ���");
                return;
        }

        command("say �ðɣ��Ҿ��������ˡ�");
        command("say ϣ�����ܺú��ù�������аħ�����");
        command("recruit "+query("id", ob));
        if( query("class", ob) != "taoist" )
                set("class", "taoist", ob);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/xuanxu-dao/huan", me) )
                return "�Ҷ��̸����ˣ��Լ��úö���ϰ�ɣ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "���������䵱�ɵ��ˣ��γ����ԣ�";

        if (me->query_skill("xuanxu-dao", 1) < 1)
                return "�������鵶����ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<150 )
                return "��Ϊ���䵱��Ч�����������������Ȳ�æ���㡣";

        if( query("shen", me)<10000 )
                return "������������������Ļ��ܲ������Ҳ��ܴ�����У�";

        if (me->query_skill("xuanxu-dao", 1) < 100)
                return "������鵶���������ң�Ҫ��������";

        message_vision(HIY "$n" HIY "���˵�ͷ�����ֻ������иֵ�������һ"
                       "����Բ\nȦ��ÿ�о����Ի��δ̳��������ջء�������"
                       "������\n��������ֱ����$N" HIY "�ۻ����ҡ�\n" NOR,
                       me, this_object());
        command("smile");
        command("say ������������鵶����Ҫ�裿");
        tell_object(me, HIC "��ѧ���ˡ��һ�������\n" NOR);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("xuanxu-dao"))
                me->improve_skill("xuanxu-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/xuanxu-dao/huan", 1, me);
        addn("family/gongji", -150, me);

        return 1;
}
