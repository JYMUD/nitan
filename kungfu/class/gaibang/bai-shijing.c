// This program is a part of NT MudLIB

#include <ansi.h>
#include "gaibang.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

#include "fight.h"

mixed ask_skill1();

void create()
{
        set_name("������", ({ "bai shijing", "bai", "shijing" }));
        set("long", @LONG
����һλ��ü�԰׵���ؤ��˫Ŀ��͸��һ˿��
����������ؤ��Ĵ������ϰ����������õĲ�
˿�������������������Ѿá�
LONG);
        set("nickname", HIR "���峤��" NOR);
        set("title", "ؤ��Ŵ�����");
        set("gender", "����");
        set("age", 48);
        set("attitude", "peaceful");
        set("class", "beggar");

        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 4000);
        set("max_jing", 3000);
        set("neili", 4300);
        set("max_neili", 4300);
        set("jiali", 180);
        set("level", 30);
        set("combat_exp", 2200000);
        set("score", 300000);
        set("shen_type", 1);

        set_skill("force", 220);
        set_skill("huntian-qigong", 220);
        set_skill("dodge", 220);
        set_skill("feiyan-zoubi", 220);
        set_skill("unarmed", 200);
        set_skill("cuff", 200);
        set_skill("changquan", 200);
        set_skill("jueming-tui", 200);
        set_skill("strike", 200);
        set_skill("xiaoyaoyou", 200);
        set_skill("hand", 240);
        set_skill("chansi-shou", 240);
        set_skill("parry", 200);
        set_skill("staff", 220);
        set_skill("fengmo-zhang", 220);
        set_skill("jiaohua-bangfa", 220);
        set_skill("begging", 250);
        set_skill("checking", 250);
        set_skill("literate", 180);
        set_skill("training", 160);
        set_skill("martial-cognize", 200);

        map_skill("force", "huntian-qigong");
        map_skill("unarmed", "jueming-tui");
        map_skill("strike", "xiaoyaoyou");
        map_skill("staff", "fengmo-zhang");
        map_skill("hand", "chansi-shou");
        map_skill("parry", "chansi-shou");
        map_skill("dodge", "feiyan-zoubi");

        prepare_skill("hand", "chansi-shou");

        create_family("ؤ��", 18, "����");

        set("inquiry", ([
                "��˿����" : (: ask_skill1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.qin" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 200);

        set("master_ob", 4);
        setup();
        carry_object(__DIR__"obj/cloth")->wear();
        carry_object(WEAPON_DIR"gangzhang")->wield();
}

void attempt_apprentice(object ob)
{
        string title=query("title", ob);
        int lvl=query("family/beggarlvl", ob);

        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_str() < 26)
        {
                command("say ����ؤ�������һ���Ը���Ϊ����" +
                        RANK_D->query_respect(ob) + "����̫�����ƺ�����ѧؤ��Ĺ���");
                return;
        }

        if( query("combat_exp", ob)<120000 )
        {
                command("say ��Ľ������鲻�������������λ����ѧϰ�ɡ�");
                return;
        }

        if( query("shen", ob)<20000 )
        {
                command("say ����Ϊؤ����ӣ���Ȼ�������£�");
                return;
        }

        if( query("family/beggarlvl", ob)<4 )
        {
                command("say ���ڱ���ĵ�λ̫�ͣ�������������ʦ��ѧϰ�ɡ�");
                return;
        }

        if (ob->query_skill("force") < 90)
        {
                command("say ����ڹ���򻹲�����������������ʦ��ѧϰ�ɡ�");
                return;
        }
        command("hmm");
        command("say ����������ǣ��ɱ�������鷳��");
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

        if( query("can_perform/chansi-shou/qin", me) )
                return "�����Ҳ����Ѿ��̻�������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�����������ز���ʶ����֪�˻��Ӻ�˵��";

        if (me->query_skill("chansi-shou", 1) < 1)
                return "������˿�����ֶ�ûѧ����̸���п��ԣ�";

        if( query("family/gongji", me)<400 )
                return "��������ؤ����������Ϊ����������ʱ�����ܴ��㡣";

        if( query("shen", me)<30000 )
                return "����������»����ò�������������ʱ�����ܴ��㡣";

        if (me->query_skill("chansi-shou", 1) < 120)
                return "��Ĳ�˿�����ֻ�򻹲�����������ȥ���ߵ������ɡ�";

        if (me->query_skill("force") < 150)
                return "�����ڵ��ڹ���Ϊ���㣬�������ߵ������ɡ�";

        message_sort(HIY "\n$n" HIY "��Цһ��������һ�ӣ��漴ֻ����"
                     "˫�ֺ��ۺ�Ť����ץ��˦��ֱ��$N" HIY "����Ҫ��"
                     "��$N" HIY "��״���ɴ󾪣���æ�����ұܣ��мܲ�"
                     "�⣬��ʼ��δ�ܰ���$n" HIY "�ľ�����������Ϊ��"
                     "����\n\n" NOR, me, this_object());

        command("say ������ô��");
        tell_object(me, HIC "��ѧ���ˡ���˿���á���\n" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 1500000);
        if (me->can_improve_skill("chansi-shou"))
                me->improve_skill("chansi-shou", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/chansi-shou/qin", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}
