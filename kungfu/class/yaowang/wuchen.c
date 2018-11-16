#include <ansi.h>
#include "yaowang.h"

#define SHENNONG    "/clone/lonely/shennongjian"
#define SHENPIAN    "/clone/lonely/yaowang_book"

inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;
inherit F_COAGENT;

mixed ask_shennong();
mixed ask_shenpian();

void create()
{
        set_name("����", ({ "wu chen", "wu", "chen" }));
        set("nickname", HIR "����ҩ��" NOR);
        set("long",@LONG
����һλ�������ص����ߣ���ɫ���飬����֪������
�ųơ�����ҩ������������������֮ǰ��Ƣ�����Ǳ�
�ꡣ�����Һ������������������������ģ����н�
�棬���Ǹ���һ�����ճ����ط����ٸ���΢����ʱ��
���ڣ���������������
LONG );
        set("title", HIG "ҩ���ȹ���" NOR);
        set("gender", "����");
        set("age", 68);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 40);
        set("int", 40);
        set("con", 40);
        set("dex", 40);
        set("per", 20);

        set("max_qi", 6000);
        set("max_jing", 5000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 200);
        set("combat_exp", 2500000);
        set("score", 10000);

        set_skill("force", 380);
        set_skill("yaogu-xinfa", 360);
        set_skill("shennong-xinjing", 380);
        set_skill("dodge", 360);
        set_skill("xuefu-mizong", 300);
        set_skill("strike", 300);
        set_skill("dusha-zhang", 300);
        set_skill("hand", 300);
        set_skill("lansha-shou", 300);
        set_skill("jiuqu-zhegufa", 300);
        set_skill("parry", 300);
        set_skill("staff", 320);
        set_skill("shennong-zhang", 320);
        set_skill("throwing", 320);
        set_skill("xuwen-qixingding", 300);
        set_skill("wuxing-jueming", 320);
        set_skill("literate", 350);
        set_skill("poison", 300);

        set_skill("dispel-poison", 500 );
        set_skill("yaowang-shenxin", 500 );
        set_skill("medical", 500);
        set_skill("yaowang-miaoshu", 500 );
        set_skill("baicao-jue", 500 );
        set_skill("bencao-changshi", 500);
        set_skill("hunting", 300);

        map_skill("force", "shennong-xinjing");
        map_skill("dodge", "xuefu-mizong");
        map_skill("strike", "dusha-zhang");
        map_skill("hand", "jiuqu-zhegufa");
        map_skill("throwing", "wuxing-jueming");
        map_skill("parry", "jiuqu-zhegufa");
        map_skill("staff", "shennong-zhang");
        map_skill("poison", "yaowang-shenxin");
        map_skill("medical", "baicao-jue");

        prepare_skill("hand", "jiuqu-zhegufa");

        create_family("ҩ����", 1, "����");
        set("class", "bonze");

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: perform_action, "sword.duo" :),
                (: perform_action, "whip.tengshe" :),
                (: perform_action, "whip.panying" :),
                (: perform_action, "whip.bohu" :),
                (: perform_action, "whip.suolong" :),
                (: perform_action, "claw.lianhuan" :),
                (: perform_action, "strike.duchan" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),

        }) );

        setup();

        set("inquiry", ([
                "��ũ�"   : (: ask_shennong :),
                "ҩ����ƪ" : (: ask_shenpian :),
                "���Ǻ���" : "���Ǻ��������µ�һ������ҩ���Σ�",
                "���˷�"   : "�Ǻǣ������Һ��Ǹ��һ���䣬�������һ��ָͷ�������������Ǳ��������ˡ�",
         ]) );

        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0 )
        {
                command("say ����������Ϊ��������ͽ���ˣ�����������ӡ�");
                return;
        }

        if( query("shen", ob)<100000 )
        {
                command("say ��ϰ�Ҷ���ҽ�������뽫���з�����λ���ҿɲ�ϣ����������������ͽ��һ�㡣");
                return;
        }

        if( query("combat_exp", ob)<300000 )
        {
                command("say �����ھ�����ǳ����᲻��ʲô��������ȥ�����㾭��ɡ�");
                return;
        }
        if( query("family/master_name", ob) == "ʯ����" )
        {
                command("say ����Ѿ���ʯ�������£�����Ϊ֮!");
                return;
        }

        if ((int)ob->query_skill("yaogu-xinfa", 1) < 150)
        {
                command("say �㱾�ŵ��ķ���ѧ�Ĳ�������");
                return;
        }

        if ((int)ob->query_skill("literate", 1) < 120)
        {
                command("say �����������ѧ�ʶ�ûѧ�ã�����δ��������Ķ���ҽ����");
                return;
        }

        if ((int)ob->query_skill("yaowang-miaoshu", 1) < 120)
        {
                command("say ���Ȱ�ҩ����������͸�����������Ұɡ�");
                return;
        }

        if ((int)ob->query_skill("dispel-poison", 1) < 120)
        {
                command("say ������������о�͸������");
                return;
        }

        command("pat"+query("id", ob));
        command("say ����������Ȼ��������ģ��Ϸ�����������ͽ�ܡ�");
        command("say �������˲��ܷŹƣ����о���û��ҩ�Ķ�ҩ���Ʋ���ʹ�á��Ҽ�!");
        command("recruit "+query("id", ob));
        set("title", "����ҩ���״�����", ob);
        return;
}

mixed ask_shennong()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "ҩ����" )
                        message_vision(CYN "$N" CYN "���һ������$n" CYN "����"
                                       "�����ѵ�������������ô����������ھ�"
                                       "Ȼ���������һ�һ��������а������Ȼ����"
                                       "������Ҫ��ũﵣ���\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "��Цһ������$n" CYN "˵��"
                                       "������һ��а����ͽ������̰ͼ���ɱ��"
                                       "��\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "ҩ����" )
                return "�㲻������ҩ���ȵģ���������ʲô��";

        if( query("family/master_id", me) != query("id") )
                return "ֻ���ҵĵ��Ӳ�������ũﵡ�";

        if( query("shen", me)<100000 )
                return "�������������û�����������ũ��Ҳ��̸ܽ��㡣";

        if (me->query_skill("shennong-zhang", 1) < 120)
                return "������ũ�ȷ���ûѧ�ã���������ũ�Ҳ�ǰ״";

        ob = find_object(SHENNONG);
        if (! ob) ob = load_object(SHENNONG);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "��ũ����ڲ�������������";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "��������һ�������Ѿ�����ũﵽ����ͬ��ʦ�ֵ���ȥ�ˡ�";

                if( query("family/master_id", owner) == query("id") )
                        return "�ţ���ũ�������ʱ����ͬ��ʦ�ֵ�"+query("name", owner)+
                               "���ã���Ҫ�þ�ȥ�����ɡ�";
                else
                        return "���ŵ���ũ�����������"+query("name", owner)+
                               "֮�֣���ȥ����ȡ�����ɣ�";
        }

        ob->move(this_object());
        message_vision(HIC "$N" HIC "΢΢һЦ�������������ũ����"
                       "��ȥ����ס��ǧ�򲻿�����Ϊ����������\n" NOR,
                       this_object(), me);
        command("giveshennongjianto"+query("id", me));
        return 1;
}

mixed ask_shenpian()
{
        object me;
        object ob;
        object owner;

        me = this_player();
        if (me->is_bad())
        {
                if( query("family/family_name", me) == "ҩ����" )
                        message_vision(CYN "$N" CYN "���һ������$n" CYN "����"
                                       "�����ѵ�������������ô����������ھ�"
                                       "Ȼ���������һ�һ��������а�����������"
                                       "����ҩ����ƪ�������㣿��\n" NOR,
                                       this_object(), me);
                else
                        message_vision(CYN "$N" CYN "��Цһ������$n" CYN "˵��"
                                       "������һ��а����ͽ������̰ͼ���ɱ��"
                                       "��\n" NOR,
                                       this_object(), me);
                return 1;
        }

        if( query("family/family_name", me) != "ҩ����" )
                return "�㲻������ҩ���ȵģ���������ʲô��";

        if( query("family/master_id", me) != query("id") )
                return "����δ��Ϊ�ҵĵ��ӣ��Ҳ��ܽ���ҩ����ƪ�������㣡";

        if( query("shen", me)<100000 )
                return "�������������û���������ҩ����ƪ���Ҳ��ܸ��㡣";

        if (me->query_skill("yaowang-shenxin", 1) < 100)
                return "��ҩ��������δѧ�ã���������Ҳ��������";

        ob = find_object(SHENPIAN);
        if (! ob) ob = load_object(SHENPIAN);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "���⡶ҩ����ƪ�����ڲ�������������";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "��������һ�������Ѿ��ѡ�ҩ����ƪ�������ͬ��ʦ�ֵ��ˡ�";

                if( query("family/master_id", owner) == query("id") )
                        return "�ţ���ҩ����ƪ����������ͬ��ʦ�ֵ�"+query("name", owner)+
                               "�����ȥ�����ɡ�";
                else
                        return "���ŵġ�ҩ����ƪ������������"+query("name", owner)+
                               "֮�֣���ȥ����ȡ�����ɣ�";
        }

        ob->move(this_object());
        message_vision(HIC "$N" HIC "΢΢һЦ���������Ȿ��ҩ����ƪ������"
                       "���㣬��ס��ǧ�򲻿�����Ϊ����������\n" NOR,
                       this_object(), me);
        command("giveyaowangshenpianto"+query("id", me));
        return 1;
}

int accept_object(object me, object ob)
{
        int r;
        if (r = ::accept_object(me, ob))

                return r;

        if (base_name(ob) != SHENNONG)
        {
                command("say ��������ֶ�����ʲô��");
                return 0;
        }

        if( query("family/master_id", me) != query("id") )
                command("say ��л��λ" + RANK_D->query_respect(me) + "�����ű��ｻ�ء�");
        else
                command("say �ܺã��ܺã�");
        destruct(ob);
        return 1;
}

void unconcious()
{
        die();
}
