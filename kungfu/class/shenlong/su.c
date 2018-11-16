// This program is a part of NT MudLIB
// su.c ����

#include "shenlong.h"

inherit NPC;
inherit F_UNIQUE;
inherit F_MASTER;
inherit F_QUESTER;

mixed ask_huimou();
mixed ask_hengchen();
mixed ask_huixiang();
void create()
{
        set_name("����", ({ "su quan", "su" }));
        set("title",  HIY"������"NOR"��������" );
        set("long", "�����������̽����鰲ͨ�ķ��ˡ�\n");
        set("gender", "Ů��");
        set("age", 23);
        set("attitude", "friendly");
        set("str", 35);
        set("int", 30);
        set("con", 30);
        set("dex", 38);

        set("max_qi", 3500);
        set("max_jing", 1800);
        set("neili", 3700);
        set("max_neili", 3700);
        set("jiali", 50);
        set("level", 30);
        set("combat_exp", 620000);
        set("shen_type", -1);

        set_skill("force", 450);
        set_skill("shenlong-xinfa", 450);
        set_skill("dodge", 480);
        set_skill("yixing-bufa", 460);
        set_skill("hand", 450);
        set_skill("sword", 450);
        set_skill("meiren-sanzhao", 450);
        set_skill("strike", 480);
        set_skill("shenlong-bashi", 450);
        set_skill("huagu-mianzhang", 420);
        set_skill("parry", 450);
        set_skill("staff", 450);
        set_skill("shedao-qigong", 420);
        set_skill("literate", 400);
        set_skill("medical", 400);
        set_skill("shenlong-mixin", 400);
        set_skill("martial-cognize", 200);
        set_skill("shenlong-jian", 400);

        map_skill("force", "shenlong-xinfa");
        map_skill("dodge", "yixing-bufa");
        map_skill("strike", "huagu-mianzhang");
        map_skill("hand", "shenlong-bashi");
        map_skill("sword", "shenlong-jian");
        map_skill("parry", "shedao-qigong");
        map_skill("staff", "shedao-qigong");
        prepare_skill("strike", "huagu-mianzhang");
        prepare_skill("hand", "shenlong-bashi");

        create_family("������", 1, "��������");

        set("inquiry", ([
                "������" : "һ�������벻���������̵�(join shenlongjiao)��",
                "���"   : "һ�������벻���������̵�(join shenlongjiao)��",
                "�˽�"   : "�����������˽̣���ô�����һ����������𣬲��������Ѿ������ˡ�",
                "�ں�"   : "���겻�ϣ������ɸ����������룡������ʥ��",
                "rujiao" : "һ�������벻���������̵�(join shenlongjiao)��",
                "tuijiao": "�����������˽̣���ô�����һ����������𣬲��������Ѿ������ˡ�",
              "��������" : (: ask_huimou :),
              "С�����" : (: ask_hengchen :),
              "�������" : (: ask_huixiang :),
        ]));

        set("chat_chance_combat", 50);
        set("chat_msg_combat", ({
                (: command("smile") :),
                (: command("haha") :),
                (: command("chat ƾ����" + RANK_D->query_rude(this_player())+",Ҳ����̫��үͷ�϶���?\n") :),
                (: command("say ���ò��ͷ�����������\n") :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang2" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "staff.chang3" :),
                (: perform_action, "staff.chang3" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
        }) );
        set("master_ob", 5);
        setup();
        carry_object("/d/shenlong/npc/obj/ycloth")->wear();
        carry_object(__DIR__"obj/duanjian")->wield();
        add_money("silver", 50);
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && ! is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 2, ob);
        }
        add_action("do_join", "join");
}

void greeting(object ob)
{
        object obj;
        if (! objectp(ob)) return;
        if (interactive(ob) && objectp(obj = present("used gao", ob)))
        {
                   set("combat_exp", 100000);
                   set("qi", 100);
                   set("jing", 100);
        }
}

void attempt_apprentice(object ob)
{
        command("say �ðɣ���ͺ���ѧ�书�ɡ�");
        command("recruit "+query("id", ob));
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

        case "��Ů����" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/meiren-sanzhao/wuqing",
                           "name"    : "��Ů����",
                           "sk1"     : "meiren-sanzhao",
                           "lv1"     : 100,
                           "sk2"     : "sword",
                           "lv2"     : 100,
                           "sk3"     : "force",
                           "lv3"     : 100,
                           "gongxian": 600,
                           "shen"    : -10000, ]));
                break;

        default:
                return 0;
        }
}

mixed ask_huimou()
{
        object me;

         me = this_player();
         if( query("can_perform/shenlong-bashi/huimou", me) )
                return "�Լ�����������������ǰ���£�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�����Ķ����ģ���������";

        if( query("shen", me)>-50000 )
                return "��Ҫ�ú�Ϊ�����Ч�����ֶ�Ҫ���ݸ������Ҳ��ܴ������ž��У�";

        if (me->query_skill("shenlong-bashi", 1) < 150)
                return "���������ʽ�ַ��������������ö���ϰ��ϰ��";

        if (me->query_skill("force", 1) < 150)
                return "����ڹ�����㣬ѧ���������������";


         message_vision(HIY "$n" HIY "��ͷ����˵�������㿴���ˣ���Ȼ����ת����彣��˵������������"
                     "���������˵������΢����������Ť�����㷴�ߣ����彣��С����ȥ����"
                     "������æ������ܣ�$n˳�Ʒ�������������§ס�彣����ͷ�������־���"
                     "��������彣�����ĵ�Ѩ���ϡ�"NOR, me, this_object());

        tell_object(me, HIG "��ѧ���˹���������" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 150000);
        if (me->can_improve_skill("shenlong-bashi"))
                me->improve_skill("shenlong-bashi", 150000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shenlong-bashi/huimou", 1, me);
        return 1;
}

mixed ask_hengchen()
{
        object me;

        me = this_player();
        if( query("can_perform/shenlong-bashi/hengchen", me) )
        return "�Լ�����������������ǰ���£�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�����Ķ����ģ���������";

        if( query("shen", me)>-80000 )
                return "��Ҫ�ú�Ϊ�����Ч�����ֶ�Ҫ���ݸ������Ҳ��ܴ������ž��У�";

        if (me->query_skill("shenlong-bashi", 1) < 150)
                return "���������ʽ�ַ��������������ö���ϰ��ϰ��";

        if (me->query_skill("force", 1) < 150)
        return "����ڹ�����㣬ѧ������С����¡�";

        message_vision(HIY"$n" HIY "�����Ե������彣��������㣬��̤�����������м�װ�ֵ���ס��"
                       "ͷ�������$n�Դ��������Լ��ؿ����䣬�彣���ܾ��е�һ����Ȼ��գ�"
                       "��˳���ڵ���һ������彣�����������������������彣�����ġ�"NOR,
                       me, this_object());

        command("say �������Ů���еĵڶ��С�����С����¡���");
        tell_object(me, HIG "��ѧ����С����¡�" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 150000);
        if (me->can_improve_skill("shenlong-bashi"))
                me->improve_skill("shenlong-bashi", 150000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shenlong-bashi/hengchen", 1, me);
        return 1;
}

mixed ask_huixiang()
{
        object me;

        me = this_player();
        if( query("can_perform/shenlong-bashi/huixiang", me) )
                return "�Լ�����������������ǰ���£�";

        if( query("family/family_name", me) != query("family/family_name") )
                return "�����Ķ����ģ���������";

        if( query("shen", me)>-100000 )
                return "��Ҫ�ú�Ϊ�����Ч�����ֶ�Ҫ���ݸ������Ҳ��ܴ������ž��У�";

        if (me->query_skill("shenlong-bashi", 1) < 160)
                return "���������ʽ�ַ��������������ö���ϰ��ϰ��";

        if (me->query_skill("force", 1) < 160)
                return "����ڹ�����㣬ѧ�����������衣";

        message_vision(HIY"$n" HIY "���彣��������ס��˫������������ִ�������������ķ������ͷ"
                     "��֮�У�$nЦ����������ϸ�ˣ���������ǰ���ߣ��������������˫�ֻ�ת"
                     "����һ�У������彣�����ġ�"NOR, me, this_object());

        command("say �������Ů���еĵڶ��С�����������衹��");
        tell_object(me, HIG "��ѧ���˷�����衣" NOR);
        if (me->can_improve_skill("hand"))
                me->improve_skill("hand", 150000);
        if (me->can_improve_skill("shenlong-bashi"))
                me->improve_skill("shenlong-bashi", 150000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/shenlong-bashi/huixiang", 1, me);
        return 1;
}
