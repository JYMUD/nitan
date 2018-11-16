#include <ansi.h>
#include "duan.h"

inherit NPC;
inherit F_MASTER;
// inherit F_QUESTER;

mixed ask_skill1();

void create()
{
        set_name("���׷�", ({ "dao baifeng", "dao", "baifeng" }));
        set("title",  "�������������");
        set("nickname",  CYN "����ɢ��" NOR);
        set("gender", "Ů��");
        set("long", @LONG
���Ǹ���ò������������ã��Ǹ�������Ů�ӣ���
��Ӻ�����ʡ������Ǵ�����ʵ۶�����������ԭ��
���ˡ������ɷ�������մ���ǲݣ�һŭ֮����
��������˼ҡ�
LONG );
        set("age", 35);
        set("class", "royal");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 2500);
        set("max_jing", 1200);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 100);
        set("combat_exp", 800000);
        set("score", 8000);

        set_skill("force", 160);
        set_skill("duanshi-xinfa", 100);
        set_skill("kurong-changong", 160);
        set_skill("dodge", 160);
        set_skill("tiannan-bu", 160);
        set_skill("cuff", 140);
        set_skill("jinyu-quan", 140);
        set_skill("strike", 140);
        set_skill("wuluo-zhang", 140);
        set_skill("sword", 120);
        set_skill("duanjia-jian", 120);
        set_skill("whip", 400);
        set_skill("feifeng-bian", 160);
        set_skill("finger", 120);
        set_skill("qiantian-zhi", 120);
        set_skill("parry", 240);
        set_skill("buddhism", 200);
        set_skill("literate", 200);
        set_skill("martial-cognize", 140);

        map_skill("force", "kurong-changong");
        map_skill("dodge", "tiannan-bu");
        map_skill("finger", "qiantian-zhi");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("whip", "feifeng-bian");
        map_skill("sword", "duanjia-jian");
        map_skill("parry", "feifeng-bian");

        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");

        set("inquiry", ([
                "��������"   : (: ask_skill1 :),
        ]));

        create_family("���ϻ���", 15, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "whip.xi" :),
                (: perform_action, "cuff.man" :),
                (: perform_action, "strike.bian" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 4);
        setup();
        carry_object("/d/dali/npc/obj/cynrobe")->wear();
        carry_object("/d/dali/obj/fuchen")->wield();
        add_money("silver", 10);
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        command("sigh");
        command("say �����ѿ��ƺ쳾������������������");

        if( query("gender", ob) == "Ů��" )
                command("say �������㹦������ҵ��ǿ��Դ���һ�ױ޷���");

        return;
}

int recognize_apprentice(object ob, string skill)
{
        if( query("family/family_name", ob) != "���ϻ���" )
        {
                command("?");
                command("say ��������ز���ʶ����֪���´˷��Ǻ����⣿");
                return -1;
        }

        if( query("gender", ob) != "Ů��" )
        {
                command("sigh");
                command("say �����΢ĩ������ʲô���㻹��ȥ�������ѧ�ɡ�");
                return -1;
        }

        if( query("combat_exp", ob)<30000 )
        {
                command("say �����ھ�����ǳ������ʱ���������Ұɡ�\n");
                return -1;
        }

        if (skill != "feifeng-bian" && skill != "whip")
        {
                command("say ��ֻ���������׷ɷ�޷�������Ļ���ȥ�������ѧ�ɡ�");
                return -1;
        }

        if( !query_temp("can_learn/daobaifeng", ob) )
        {
                command("sigh");
                command("say ��Ȼ�㻹��������ף������Ҿͽ�����ˡ�");
                set_temp("can_learn/daobaifeng", 1, ob);
        }
        return 1;
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/feifeng-bian/xi", me) )
                return "�Ҳ����Ѿ��̸������𣿻���ʲô�������Լ��о���";

        if( query("family/family_name", me) != query("family/family_name") )
                return RANK_D->query_respect(me) + "�������޹ϸ𣬺γ����ԣ�";

        if (me->query_skill("feifeng-bian", 1) < 1)
                return "�����ҷɷ�޷���δѧ����ô������һ˵��";

        if( query("shen", me)<0 )
                return "�ߣ��㻹�����������ǵĻ��²���ô��";

        if( query("family/gongji", me)<300 )
                return "��������µµ��Ϊ����������ŵù��㣿";

        if (me->query_skill("force") < 150)
                return "����ڹ���Ϊ̫�ѧ������һ�С�";

        if( query("max_neili", me)<1200 )
                return "�������������������ôѧϰ��һ�У�";

        if (me->query_skill("feifeng-bian", 1) < 120)
                return "��ɷ�޷��Ļ�򻹲�������ȥ����������";

        message_sort(HIY "\n$n" HIY "��$N" HIY "���˵�ͷ���漴ȡ����"
                     "������������ұ������ٻ��裬������ʱ����һ����"
                     "һ����Ȧ�ӣ�����$N" HIY "��ȥ����ʽ�仯��Ϊ����"
                     "��\n\n" NOR, me, this_object());

        command("nod");
        command("say ���п��ƻ��ɣ���ʵ������������ȥ�������ڼ���ϰ��");
        tell_object(me, HIC "��ѧ���ˡ��������ࡹ��\n" NOR);
        if (me->can_improve_skill("whip"))
                me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("feifeng-bian"))
                me->improve_skill("feifeng-bian", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/feifeng-bian/xi", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}
