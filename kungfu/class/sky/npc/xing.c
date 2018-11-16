#include <ansi.h>

inherit NPC;
string ask_tianjidao();

void create()
{
        set_name(HIW "�Ǿ���" NOR, ({ "xingjun yan", "xingjun", "yan"}));
        set("long", HIW "һ���������ص����ߣ������Ӳ������˽����ˡ�\n" NOR);         
        set("title", HIY "����ػ���" NOR);
        set("gender", "����");
        set("age", 999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);
        set("per", 35);

        set("max_qi", 9999999);
        set("max_jing", 9999999);
        set("max_neili", 999999);
        set("neili", 999999);
        set("jiali", 2500);
        set("combat_exp", 8000000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.bafa" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );

        set_skill("dodge", 420);
        set_skill("parry", 420);
        set_skill("hand", 440);
        set_skill("unarmed", 440);
        set_skill("shou-yin", 440);
        set_skill("wudu-shu", 420);
        set_skill("force", 400);
        set_skill("changsheng-jue", 400);
        set_skill("blade", 320);
        set_skill("jingzhong-bafa", 420);
        set_skill("literate", 400);
        set_skill("martial-cognize", 400);

        map_skill("force", "changsheng-jue");
        map_skill("blade", "jingzhong-bafa");
        map_skill("dodge", "wudu-shu");
        map_skill("parry", "jingzhong-bafa");
        map_skill("hand", "shou-yin");
        map_skill("unarmed", "shou-yin");
        set("inquiry", ([
                "�켫��" : (: ask_tianjidao :),
                
        ]));
        prepare_skill("hand", "shou-yin");

        setup();

        carry_object(__DIR__"obj/cloth2")->wear();
}

string ask_tianjidao()
{
        object me;
        object ob_hlp;
        int i;
        
        me = this_player();
        
        if (me->query("int") < 32 ||
            me->query("con") < 32 ||
            me->query("str") < 32 ||
            me->query("dex") < 32)
            return "����������Ի������������켫�����ҿ��㻹���Ȼ�ȥ�ɡ�\n";


        if (! me->query("scborn/ok"))
                return "�߿����߿���û������æ��\n";
        
        if (me->query_skill("yinyang-shiertian", 1) && ! me->query("thborn/ok"))
                return "�����书�Ѿ��������£��α����̰��?\n";

        if (me->query_skill("lunhui-sword",1))
                return "�ߣ��������ӣ���Ȼ���̰�ģ�\n";
                                        
        // �Ѿ��������
        if (me->query("lunhui-sword_quest/tianjidao/finish"))
                return "�Ǻǣ��������ϴ���Щ���˿�����Ϸ�ȼü֮������\n";

        // ��������
        if (! me->query("lunhui-sword_quest/tianjidao/give_quest"))
        {
                command("shake");
                command("say ����ǰ���Ϸ򽫽�����һ����ϱ��׸�Ū���ˣ���֪����Ǻã�");
                command("say ������Ѽ���30�����˿���Ϸ����а취��������һ��");
                command("��������");
                command("tan");
                command("say �����˿���Ƿ��ֻ����ɽ������������У�����������Ǵ�����ˣ�");
                command("look " + me->query("id"));
                command("say ����������Ѽ���30�����˿���Ϸ��Ϸ����ﵹ����һЩ�������书���Դ��ڸ��㡣");
                tell_object(me, this_object()->name() + HIG "��������Ѽ�30�����˿���Ͽ�ȥ�ɣ�\n" NOR);
                me->set("lunhui-sword_quest/tianjidao/give_quest", 1);
                me->save();
                return "��ô�������ǿ��ǣ�";
        }
        
        // �������
        
        if (! objectp(ob_hlp = present("tiancan si", me)))
                return "��ô����30�����˿�Ѽ�������\n";
                
        if (base_name(ob_hlp) != "/clone/quarry/item/cansi2")
                return "��ô����30�����˿�Ѽ�������\n";
        
        if ("/adm/daemons/stored"->get_ob_amount(me, ob_hlp) >= 30)
        {
                for (i = 1; i <= 30; i++)
                {
                        destruct(ob_hlp);
                        ob_hlp = present("tiancan si", me);
                }
        }
        else
        {
                return "��ô����30�����˿�Ѽ�������\n";
        }
        
        command("hehe");
        command("nod");
        command("say ��Ȼ����������æ���ã��Ϸ�Ҳ����ŵ�ԣ����㡸�켫��������");
        
        message_sort(HIC "\n$N" HIC "����ǰȥ����$n" HIC "��������˵�˼��䣬Ȼ�����ó�һ���飬ָָ��㣬"
                     "$n" HIC "��ס�ص�ͷ������üͷ������������ͷ��˼ ����\n���ã�$n" HIC "��Цһ�����ƺ�"
                     "�Ըղŵ�������������\n", this_object(), me);
                             
        tell_object(me, HIG "��ϲ�������ˡ��켫����������Ŀǰ�ȼ�Ϊ10����\n");
        me->set_skill("tianji-dao", 10);
        me->set("lunhui-sword_quest/tianjidao/finish", 1);
        
        return "��л�ˣ�";
        
                
}
