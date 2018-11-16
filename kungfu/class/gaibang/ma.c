// This program is a part of NT MudLIB
// ma.c ���Ԫ

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;

mixed ask_skill1();

void create()
{
        set_name("���Ԫ", ({ "ma dayuan", "ma", "dayuan" }));
        set("long", @LONG
����һ����ʮ����ľ�׳���ӣ���Ŀ��࣬˫
Ŀ��硣���˾���ؤ�︱�������Ԫ��
LONG);
        set("nickname", CYN "��צ����" NOR);
        set("title", "ؤ�︱����");
        set("gender", "����");
        set("age", 48);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4500);
        set("max_jing", 3500);
        set("neili", 4800);
        set("max_neili", 4800);
        set("jiali", 220);
        set("combat_exp", 2500000);
        set("level", 30);
        set("score", 500000);
        set("shen_type", 1);

        set_skill("force", 240);
        set_skill("huntian-qigong", 240);
        set_skill("dodge", 240);
        set_skill("feiyan-zoubi", 240);
        set_skill("unarmed", 200);
           set_skill("cuff", 200);
        set_skill("changquan", 200);
        set_skill("jueming-tui", 200);
        set_skill("claw", 240);
        set_skill("suohou-gong", 240);
        set_skill("strike", 200);
        // set_skill("tongchui-zhang", 240);
        set_skill("dragon-strike", 200);
        set_skill("parry", 240);
        set_skill("staff", 240);
        set_skill("dagou-bang", 240);
        set_skill("fumo-zhang", 240);
        set_skill("begging", 280);
        set_skill("checking", 280);
        set_skill("literate", 260);
        set_skill("martial-cognize", 240);

        set("no_teach", ([
                "dagou-bang"    : "�򹷰�������ֻ�м�λ�����ܹ�ѧ"
                                  "ϰ��Ҫѧȥ�Ұ�����",
                "dragon-strike" : "����ʮ��������ֻ�кͰ���ѧϰ��",
        ]));

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "chanquan");
        map_skill("strike", "dragon-strike");
        map_skill("staff", "dagou-bang");
        map_skill("claw", "suohou-gong");
        map_skill("parry", "suohou-gong");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("claw", "suohou-gong");

        create_family("ؤ��", 18, "������");

        set("inquiry", ([
                "��צ����" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.suo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",4);
        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(__DIR__"obj/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if( query("combat_exp", ob)<200000 )
        {
                command("say ��Ľ������鲻�������������λ����ѧϰ�ɡ�");
                return;
        }

        if( query("shen", ob)<30000 )
        {
                command("say ����Ϊؤ����ӣ���Ȼ�������£�");
                return;
        }

        if( query("family/beggarlvl", ob)<5 )
        {
                command("say ���ڱ���ĵ�λ̫�ͣ����������λ����ѧϰ�ɡ�");
                return;
        }

        if ((int)ob->query_str() < 26)
        {
                command("say �ҵ������Ը���Ϊ�������������У��������˰ɡ�");
                return;
        }

        if (ob->query_skill("force") < 150)
        {
                command("say ����ڹ���򻹲��������������λ����ѧϰ�ɡ�");
                return;
        }
        command("nod");
        command("say �ҽ��ձ�����Ϊͽ�������ڿ�Ŭ������������һ����Ϊ��");
        command("recruit "+query("id", ob));

        if( query("class", ob) != "beggar" )
                set("class", "beggar", ob);

        if (lvl > 0)
        {
                set("family/beggarlvl", lvl, ob);
                set("title", title, ob);
        }
}

mixed ask_skill1()
{
        object me;
        me = this_player();

        if( query("can_perform/suohou-gong/suo", me) )
                return "�Լ���ȥ��ϰ�������Ǿ������ݡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ǽ����������͵���ţ�����������";

        if (me->query_skill("suohou-gong", 1) < 1)
                return "��ѧ�������𣿲�ѧ�������С�";

        if( query("family/gongji", me)<400 )
                return "����ؤ����������Ϊ����������ʱ�����ܴ��㡣";

        if( query("shen", me)<20000 )
                return "�������������ò�������������ʱ�����ܴ��㡣";

        if (me->query_skill("suohou-gong", 1) < 150)
                return "��������������ң�Ҫ��������";

        message_sort(HIY "\n$n" HIY "Ц��Ц����$N" HIY "�������ԣ���"
                     "����$N" HIY "���ߵ����Ը��˼��䣬��ʱ����ȭ��צ"
                     "�Ȼ���ʾ��ȫ���������еľ�΢Ҫ�裬$N" HIY "һ"
                     "����һ�߲�ס�ص�ͷ��\n\n" NOR, me, this_object());

        command("nod");
        command("say �����������Ҫ�����ڣ��ɼ�����ˣ�");
        tell_object(me, HIC "��ѧ���ˡ���צ������\n" NOR);

        if (me->can_improve_skill("claw"))
                me->improve_skill("claw", 1500000);
        if (me->can_improve_skill("suohou-gong"))
                me->improve_skill("suohou-gong", 1500000);

        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/suohou-gong/suo", 1, me);
        addn("family/gongji", -400, me);
        return 1;
}
