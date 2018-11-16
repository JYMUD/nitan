// This program is a part of NT MudLIB
// /kungfu/class/xueshan/jiumozhi.c �Ħ��

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "xueshan.h"

mixed ask_me();
mixed ask_skill();

void create()
{
        set_name("�Ħ��", ({ "jiumo zhi", "zhi" ,"ming wang"}));
        set("nickname", HIG "��������" NOR);
        set("long",@LONG
������ѩɽ�µ����ţ��˳ƴ����������Ħ�ǡ����Է��о�����о���
��һ��������ģ�ͷ��ɮñ��
LONG
        );
        set("title","ѩɽ������");
        set("gender", "����");
        set("age", 60);
        set("attitude", "friendly");
        set("shen_type", -1);

        set("str", 32);
        set("int", 40);
        set("con", 31);
        set("dex", 31);

        set("max_qi", 5800);
        set("max_jing", 2900);
        set("neili", 7100);
        set("max_neili", 7100);
        set("jiali", 100);
        set("level", 40);
        set("combat_exp", 2500000);

        set_skill("force", 600);
        set_skill("xiaowuxiang", 600);
        set_skill("mizong-neigong", 600);
        set_skill("dodge", 600);
        set_skill("shenkong-xing", 600);
        set_skill("parry", 600);
        set_skill("unarmed", 600);
        set_skill("sword", 600);
        set_skill("mingwang-jian", 600);
        set_skill("hammer", 600);
        set_skill("dali-chu", 600);
        set_skill("xiangmo-chu", 600);
        set_skill("lamaism", 600);
        set_skill("literate", 600);
        set_skill("strike", 600 );
        set_skill("huoyan-dao", 600);
        set_skill("cuff", 600);
        set_skill("yujiamu-quan", 600);
        set_skill("hand", 600);
        set_skill("dashou-yin", 600);
        set_skill("martial-cognize", 600);
        set_skill("longxiang-gong", 600);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("parry", "mingwang-jian");
        map_skill("sword", "mingwang-jian");
        map_skill("strike","huoyan-dao");
        map_skill("cuff", "yujiamu-quan");
        map_skill("hammer", "xiangmo-chu");

        prepare_skill("strike", "huoyan-dao");
        prepare_skill("hand", "dashou-yin");

        create_family("ѩɽ��", 1, "����");
        set("class", "bonze");

        set("inquiry", ([
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "����" : (: ask_me :),
                "�������" : (: ask_skill :),
        ]));

        set("master_ob", 5);
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/xueshan/obj/r-jiasha")->wear();
        carry_object("/d/xueshan/obj/sengmao")->wear();

        add_money("silver",50);
}

mixed ask_me()
{
        object me;

        me = this_player();
        if( query("can_perform/huoyan-dao/fen", me) )
                return "�������Ѿ�ѧ���ˣ�ʣ�µľ�Ҫ�����Լ�����ϰ�ˡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "��Ȼ��������ѩɽ��֮�ˣ���ʲô��̸�ġ�";

        if (me->query_skill("huoyan-dao", 1) < 120)
                return "��Ļ��浶����Ϊ��������������������˵�ɣ�";

        if( query("family/gongji", me)<300 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        message_vision(HIC "$n" HIC "����һ������·���ε���Ϯ����$N"
                       HIC "��$N" HIC "��æ���ָ񵲣���������$n"
                       HIC "���������ÿ�ν�ǰ������\n" NOR,
                       me, this_object());
        command("simle");
        tell_object(me, HIG "��ͨ���˷���İ��\n" NOR);
        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("huoyan-dao"))
                me->improve_skill("huoyan-dao", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 90000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huoyan-dao/fen", 1, me);
        addn("family/gongji", -300, me);
        return 1;
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("gender", ob) != "����" )
        {
                command("say ��ϰ�����ڹ���Ҫ����֮�塣");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "������ذɣ�");
                return;
        }

        if( query("class", ob) != "bonze" )
        {
                command("say �ҷ��ŵ����������ࡣ");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "������ذɣ�");
                return;
        }

        if( query("family/family_name", ob) != "ѩɽ��" )
        {
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�ȷǱ��µ��ӣ�������ذɣ�");
                return;
        }

        if ((int)ob->query_skill("lamaism", 1) < 150) {
                command("say ����ѩɽ�£���ϰ�����ķ�����Ҫ�ġ�");
                command("say ��λ" + RANK_D->query_respect(ob) +
                        "�Ƿ�Ӧ�ö�����б��ŵ��ķ���");
                return;
        }

        command("recruit "+query("id", ob));
        set("title", HIY"����"NOR, ob);
}

mixed ask_skill()
{
        object me;

        me = this_player();

        if( query("can_perform/huoyan-dao/yan", me) )
                return "��������ʲô���Լ���ȥ������";

        if( query("family/family_name", me) != query("family/family_name") )
                return "���ֲ���ʶ�㣬���������ʲô��";

        if (me->query_skill("huoyan-dao", 1) < 1)
                return "�������ϻ��浶��ûѧ�����������У�";

        if( query("family/gongji", me)<400 )
                return "��Ϊѩɽ��Ч��������������ʱ�����ܴ��㡣";

        if( query("shen", me)>-3000 )
                return "��Ϊ��̫������������ʱ�����ܴ��㡣";

        if (me->query_skill("force") < 120)
                return "����ڹ���Ϊ���㣬��ѧ������һ�С�";

        if( query("max_neili", me)<800 )
                return "���������Ϊ���㣬���������ߵ������ɡ�";

        if (me->query_skill("huoyan-dao", 1) < 80)
                return "����ѻ��浶�������������ҡ�";

        message_sort(HIY "\n$n" HIY "��$N" HIY "���˵�ͷ���ȵ���������"
                     "ϸ�ˡ����������䣬ֻ��$n" HIY "�߾����еĸյ�����"
                     "���л�����̣����ƾ��ˣ����ڴ�ʱ���Ǳ��յ���Я��"
                     "������ײ��֮����Ȼ���䡣ֱ��$N" HIY "����Ŀ�ɿڴ�"
                     "��\n\n" NOR, me, this_object());

        command("nod");
        command("say �������˾��Լ���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ�������ס���\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("huoyan-dao"))
                me->improve_skill("huoyan-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/huoyan-dao/yan", 1, me);
        addn("family/gongji", -400, me);

        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "���޽���" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huoyan-dao/xiuluo",
                           "name"    : "���޽���",
                           "sk1"     : "huoyan-dao",
                           "lv1"     : 100,
                           "sk2"     : "strike",
                           "lv2"     : 120,
                           "gongxian": 800, ]));
                break;

        case "������" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/huoyan-dao/honglian",
                           "name"    : "������",
                           "sk1"     : "huoyan-dao",
                           "lv1"     : 150,
                           "sk2"     : "strike",
                           "lv2"     : 150,
                           "gongxian": 800, ]));
        case "ʮ��ʮ��" : 
                return MASTER_D->teach_pfm(me, this_object(), 
                        ([ "perform" : "can_perform/longxiang-gong/longxiang", 
                           "name"    : "ʮ��ʮ��", 
                           "sk1"     : "longxiang-gong", 
                           "lv1"     : 1000, 
                           "sk2"     : "force", 
                           "lv2"     : 1000,
                           "reborn"  : 1,
                           "gongxian": 3000, ])); 
                break; 
                break;
        default:
                return 0;
        }
}

