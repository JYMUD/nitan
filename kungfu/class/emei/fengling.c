// This program is a part of NT MudLIB

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#include <ansi.h>
#include "emei.h"

mixed ask_skill1();
mixed ask_skill2();

void create()
{
       set_name("����ʦ̫", ({"fengling shitai", "fengling", "shitai", "feng", "ling"}));
       set("long", "�����Ƕ����ɵڶ��������˷���ʦ̫��\n"
                   "����Ŀ���飬����Ѱ������һ�㣬��\n"
                   "����һ˿����֮����\n");
        set("gender", "Ů��");
        set("age", 62);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("max_qi", 7000);
        set("max_jing", 6000);
        set("neili", 8000);
        set("max_neili", 8000);
        set("jiali", 250);
        set("level", 30);
        set("combat_exp", 5000000);

        set_skill("force", 700);
        set_skill("emei-jiuyang", 700);
        set_skill("emei-xinfa", 700);
        set_skill("linji-zhuang", 700);
        set_skill("dodge", 700);
        set_skill("zhutian-bu", 700);
        set_skill("finger", 700);
        set_skill("tiangang-zhi", 700);
        set_skill("hand", 700);
        set_skill("jieshou-jiushi", 700);
        set_skill("strike", 700);
        set_skill("jinding-zhang", 700);
        set_skill("piaoxue-zhang", 700);
        // set_skill("sixiang-zhang", 700);
        set_skill("sword", 700);
        set_skill("huifeng-jian", 700);
        set_skill("emei-jian", 700);
        set_skill("blade", 700);
        set_skill("yanxing-dao", 700);
        set_skill("parry", 700);
        set_skill("martial-cognize", 700);
        set_skill("literate", 700);
        set_skill("mahayana", 700);
        set_skill("buddhism", 700);

        set("no_teach", ([
                "emei-jiuyang" : "����Ҿ������˲�ȱ��ȫ�ľ����񹦣��ټ�ʮ��ׯ"
                                 "ʤ֮ǧ�����㻹��ѧ�����ˡ�",
        ]));

        map_skill("force", "emei-jiuyang");
        map_skill("dodge", "zhutian-bu");
        map_skill("finger", "tiangang-zhi");
        map_skill("hand", "jieshou-jiushi");
        map_skill("strike", "piaoxue-zhang");
        map_skill("sword", "huifeng-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("parry", "jinding-zhang");

        prepare_skill("strike", "piaoxue-zhang");

        create_family("������", 2, "������");

        set("inquiry",([
                "���"     : "Ҫ����Ҿ�����",
                "����"     : "Ҫ����Ҿ�����",
                "�ƺ�����" : (: ask_skill1 :),
                "�������" : (: ask_skill2 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "strike.yun" :),
                (: perform_action, "strike.zhao" :),
                (: exert_function, "recover" :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
        }));

       set("master_ob", 5);
        setup();

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        carry_object(WEAPON_DIR"changjian")->wield();
        carry_object(CLOTH_DIR"ni-cloth")->wear();
        carry_object(CLOTH_DIR"ni-shoe")->wear();
}

void attempt_apprentice(object ob)
{
        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<50000 )
        {
                command("say ��������������黹���ò���������ʱ���������㡣");
                return;
        }

        if( query("combat_exp", ob)<500000 )
        {
                command("sigh");
                command("say ��Ľ�������̫ǳ�������ȶ����������˵�ɡ�");
                return;
        }

        if ((int)ob->query_skill("mahayana", 1) < 150)
        {
                command("say �������͹�����Ϊ�����У��úø������");
                return;
        }

        if ((int)ob->query_skill("linji-zhuang", 1) < 150)
        {
                command("say �ټ�ʮ��ׯ���Ҷ��ҵ�һ�湦����úú���ϰ��");
                return;
        }

        name=query("name", ob);
        new_name = "��" + name[2..3];
        NAME_D->remove_name(query("name", ob),query("id", ob));
        set("name", new_name, ob);
        NAME_D->map_name(query("name", ob),query("id", ob));

        command("say ��������");
        command("say �����ұ�����Ϊͽ������" + new_name + "��");
        command("recruit "+query("id", ob));
}

mixed ask_skill1()
{
        object me;

        me = this_player();
        if( query("can_perform/piaoxue-zhang/yun", me) )
                return "��һ���Ҳ����Ѿ������������𣿻���ʲô�������Լ���ȥ���ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�������������������֪���´���������";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���ҵĵ��Ӳ���ѧϰ���У��㻹���߰ɡ�";

        if (me->query_skill("piaoxue-zhang", 1) < 1)
                return "����Ʈѩ�����ƶ�ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<1800 )
                return "��Զ������������Ĺ��׻���������������ʱ���ܴ��㡣";

        if (me->query_skill("force") < 200)
                return "����ڹ�����̫ǳ������ѧ������һ�С�";

        if( query("max_neili", me)<2000 )
                return "�����������̫ǳ������ѧ������һ�С�";

        if (me->query_skill("piaoxue-zhang", 1) < 150)
                return "���Ʈѩ�����ƻ��δ��������ѧ������һ�С�";

        if( query("shen", me)<40000 )
                return "��������������黹���ò���������ʱ�����ܴ�����С�";

        message_sort(HIY "\n$n" HIY "΢΢һЦ����$N" HIY "˵��������Ȼ����"
                     "�⹦���Ѵ�����˾��磬Ҳ��������ƽʱ��һ�����ࡣ����"
                     "�ұ㴫����У�ϣ���պ��ܽ��Ҷ����ɷ����󡣡�˵�꣬"
                     "$n" HIY "��$N" HIY "������ǰ����$N" HIY "��������ϸ˵"
                     "���á�\n\n" NOR, me, this_object());

        command("nod");
        command("say �ղ�����˵���㶼�������𣿼����˾���ȥ���ɡ�");
        tell_object(me, HIC "��ѧ���ˡ��ƺ����ơ���\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("piaoxue-zhang"))
                me->improve_skill("piaoxue-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/piaoxue-zhang/yun", 1, me);
        addn("family/gongji", -1800, me);
        return 1;
}

mixed ask_skill2()
{
        object me;

        me = this_player();
        if( query("can_perform/piaoxue-zhang/zhao", me) )
                return "��һ���Ҳ����Ѿ������������𣿻���ʲô�������Լ���ȥ���ɡ�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�������������������֪���´���������";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���ҵĵ��Ӳ���ѧϰ���У��㻹���߰ɡ�";

        if (me->query_skill("piaoxue-zhang", 1) < 1)
                return "����Ʈѩ�����ƶ�ûѧ����̸ʲô���п��ԣ�";

        if( query("family/gongji", me)<2200 )
                return "��Զ������������Ĺ��׻���������������ʱ���ܴ��㡣";

        if (me->query_skill("force") < 700)
                return "����ڹ�����̫ǳ������ѧ������һ�С�";

        if( query("max_neili", me)<3500 )
                return "�����������̫ǳ������ѧ������һ�С�";

        if (me->query_skill("piaoxue-zhang", 1) < 180)
                return "���Ʈѩ�����ƻ��δ��������ѧ������һ�С�";

        if( query("shen", me)<40000 )
                return "��������������黹���ò���������ʱ�����ܴ�����С�";

        message_sort(HIY "\n$n" HIY "����������$N" HIY "��ͷ��˵��������"
                     "�ɣ��ѵ���������ģ������Ҿͽ�������ʾһ�飬�ɵÿ�"
                     "���ˣ����������䣬ֻ��$n" HIY "�����ھ������������"
                     "����ž���죬�����Ѫ��ɷ�Ǿ��ˡ��漴$n" HIY "һ����"
                     "�ȣ�˫��Я����������֮��������ǰ�ĳ�����ʱֻ������"
                     "�ꡱһ�����죬ǰ���±�һ����ڴֵ�����Ӧ�����ϣ���"
                     "֦��������δ������ǰ�ַɳ����ɣ���ŵ�����ɽ��֮��"
                     "������������ɽ���»��������ڶ���Ⱥɽ�лص��˺�һ"
                     "�����ʧ������$n" HIY "΢΢һЦ������һ������������"
                     "���ھ�����$N" HIY "��ȥ����$N" HIY "���ѿ���Ŀ�ɿ�"
                     "����\n\n" NOR, me, this_object());

        command("say ��������ȥ��һ��Ҫ�ڼ���ϰ�����ܷ��ӳ�����������");
        tell_object(me, HIC "��ѧ���ˡ�������ա���\n" NOR);

        if (me->can_improve_skill("strike"))
                me->improve_skill("strike", 1500000);
        if (me->can_improve_skill("piaoxue-zhang"))
                me->improve_skill("piaoxue-zhang", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/piaoxue-zhang/zhao", 1, me);
        addn("family/gongji", -2200, me);
        return 1;
}

int accept_ask(object me, string topic) 
{ 
        switch (topic) 
        { 
        case "����" : 
        case "�������" : 
               return MASTER_D->teach_pfm(me, this_object(), 
                             ([ "perform" : "can_exert/linji-zhuang/niepan", 
                                "name"    : "�������",
                                "sk1"     : "linji-zhuang", 
                                "lv1"     : 1000, 
                                "sk2"     : "force", 
                                "lv2"     : 1000, 
                                "reborn"  : 1,
                                "gongxian": 3000, ])); 
                break; 
        default: 
                return 0; 
        } 
} 

