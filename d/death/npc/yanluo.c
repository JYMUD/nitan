// This program is a part of NITAN MudLIB

#include <ansi.h>
inherit NPC;

mixed ask_quest();
mixed ask_reborn();

void create()
{
        set_name("ʮ������", ({ "shidian yanluo", "shidian", "yanluo", "shi", "yan"}));
        set("long", "һλ������ף��������룬�����۵Ĵ󺺡�\n"
                    "����������ʮ�����ޡ�\n");
        set("title", HIR "ڤ���ز�����ǰ" NOR);
        set("nickname", HIY "��˾�ܹ�" NOR);
        set("gender", "����");
        set("age", 3000);
        set("attitude", "friendly");
        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

        set("max_qi", 30000);
        set("max_jing", 30000);
        set("neili", 50000);
        set("max_neili", 50000);
        set("jiali", 1000);

        set("combat_exp", 50000000);

        set_skill("unarmed", 1000);
        set_skill("finger", 1000);
        set_skill("claw", 1000);
        set_skill("strike", 1000);
        set_skill("hand", 1000);
        set_skill("cuff", 1000);
        set_skill("parry", 1000);
        set_skill("dodge", 1000);
        set_skill("force", 1000);
        set_skill("jiuyin-shengong", 1000);
        set_skill("magic", 1000);
        set_skill("literate", 1000);

        map_skill("parry", "jiuyin-shengong");
        map_skill("force", "jiuyin-shengong");
        map_skill("dodge", "jiuyin-shengong");
        map_skill("unarmed", "jiuyin-shengong");
        map_skill("finger", "jiuyin-shengong");
        map_skill("strike", "jiuyin-shengong");
        map_skill("hand", "jiuyin-shengong");
        map_skill("cuff", "jiuyin-shengong");
        map_skill("claw", "jiuyin-shengong");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "ʮ�����������̾�˿�����\n" NOR,
                CYN "ʮ������̾��������׿Ǻ���ȸ��ë���õ㣬�����������Ͱ׻�����Ū������\n" NOR,
                CYN "ʮ������̾������ס������������л��ǣ�������Ѱ찡��\n" NOR,
                CYN "ʮ������̾�������޾�Ҫ���ˣ��ز��ϴ�Ҫ�����Ƶ�������ԭ�ϻ�û���룬�������Ǻð���\n" NOR,
                CYN "ʮ������̾�����ز��ϴ�����������Ҫ������\n" NOR,
                CYN "ʮ�����ޱ�Թ����ƽ���޹ʵ�Ҫʲô���������ϴ�Ҳ���ǵġ�\n" NOR,
        }));

        set("inquiry", ([
                "������"   : (: ask_quest :),
                "����"     : (: ask_quest :),
                "����"     : (: ask_quest :),
                "����"     : (: ask_quest :),
                "����"     : (: ask_quest :),
                "����"     : (: ask_quest :),
                "ԭ��"     : (: ask_quest :),
                "ҩ��"     : (: ask_quest :),
                "ת��"     : (: ask_reborn :),
                "����"     : (: ask_reborn :),
                "ת��"     : (: ask_reborn :),
                "ת������" : (: ask_reborn :),
                "�ز���"   : "����������ϴ�û���ǵ�������",
                "����"     : "�����������������ĵ������˳��˿���ƽ����������Ҳ����Ҫһ����������",
                "������"   : "�����������������ĵ������˳��˿���ƽ����������Ҳ����Ҫһ����������",
                "����"     : "������Ҫһ���׻��Ĺ�ͷ��������������ô������ô��",
                "�׻���"   : "������Ҫһ���׻��Ĺ�ͷ��������������ô������ô��",
                "��ȸ��ë" : "�Ƕ���������ûʲô�õģ���ȴ����������������ԭ�ϡ�",
                "����"     : "�Ƕ���������ûʲô�õģ���ȴ����������������ԭ�ϡ�",
                "����׿�" : "�ǿ����������׵���ͦ�ã�����Ū���������˺þö�û�ҵ���",
                "���"     : "����׿����������׵���ͦ�ã�����Ū���������˺þö�û�ҵ���",
                "�׿�"     : "����׿����������׵���ͦ�ã�����Ū���������˺þö�û�ҵ���",
                "����"     : "����������ʱ����ڱ�ˮ��̶��û��������ȥ׽ʱȴû������",
                "��ˮ��̶" : "��ˮ��̶�����κ������棬��վ�������������͵��ˣ���������ȥ��ô��ϡ�����Ѫ������",
                "����Ѫ��" : "�ⶫ�������ڵظ��ֻ�˾��Ѱ�ҵ������š�Ҫ���ǡ�������Ե����",
                "�׻�"     : "�Ǵ�����Ϣ�ڼ���˾����ĺ�ɭ��������˺ü�������ȥ׽�������ȫ�����ˡ�",
                "��ɭ��"   : "��ɭ����ȫ�����������С�ָ�ϳ�����Ҫ������û�����Ϸ���",
                "ָ�ϳ�"   : "���ǻƵ����������ķ���֮һ���������䵽�����������û������",
                "����˾"   : "����˾�������޵�Ķ��ߡ�",
                "�ֻ�˾"   : "�ֻ�˾�������޵�Ķ��ߡ�",
                "���޵�"   : "�����Ҳ���ң����Ǳ����İ���",
                "��ȸ"     : "��������������������������ȸ��������˵�Ǳ�ë���������ޱ�֮�أ�ҪѰ�����ϱ���Ҫ���б��",
                "����"     : "�ظ��и���ʯ��Ի����ɫ��󡹣����Ǹ����ö���ı��",
                "��ɫ���" : "�����ţ��ⶫ���������������ع��������",
                "�ع���"   : "������һ����Ҳ������ʮ��֮һ��",
                "������"   : "�������ߵ����������ǵظ�����ߵĽ�����ƽʱ�����濴�ء�",
                "����"     : "�Ϳ����κ��ŵ�ţͷһ�����ǵظ���������",
                "����"     : "�ǳ��ڹ��������Ѫ�ص�����������⣬��ôŪ����������",
                "������"   : "�Ҳ٣������Ҳ���ң���ȥ������ԳԿ���֪���ˡ�",
                "Ѫ�ص���" : "Ѫ�ص����������޵�ı��ߣ���Ҫ��ȥ����ô��ϡ�����ѥ����",
                "����ѥ"   : "���ǵز����Ķ�������Ҳֻ�Ƽ���һ�Ρ�",
        ]));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "finger.zhi" :),
                (: perform_action, "strike.zhang" :),
                (: perform_action, "cuff.quan" :),
                (: perform_action, "hand.shou" :),
                (: perform_action, "claw.zhua" :),
                (: exert_function, "recover" :),
                (: exert_function, "shield" :),
        }) );

        set("count", 1);
        create_family("��˾", 0, "�ܹ�");

        setup();
        carry_object(__DIR__"obj/cloth2")->wear();
}

mixed ask_quest()
{
        object ob;
        object me;
        me = this_player();

        if( query_temp("to_answer", me) )
                return "��������ô��ô���£����׸ɻ��ǲ��ɰ���";

        if( query("over_quest/hell_quest/������", me) )
                return "�ϴε��������Ƕ�лл���ˡ�";

        if( query("hell_quest/������", me) )
                return "��Ҫ��ԭ���㶼����������������ô��ô���£�";

        if( !me->is_ghost() && !wizardp(me) && !query("reborn_offer", me) )
                return "�ף�������ô���������ˣ�";

        /*
        if (query("over") > 1)
                return "�����Ҷ��Ѿ�׼�����ˣ�����Ҫ��İ�æ�ˡ�";

        if (query("count") < 1)
                return "���ˣ����Ѿ�������ȥ�ˡ�";
        */

        if( query("combat_exp", me)<2000000000 )
                return "����������������̫���ˣ��ǰﲻ���ҵġ�";

        message_vision(HIC "\nʮ��������ϸ�Ĵ�����$N" HIC "��һ��\n" NOR, me);
        command("say ��������");
        command("whisper"+query("id", me)+"���Ǹմ��������İɣ�����������ƺ�"
                "�书�������ܹ����Ҹ�æ�𣿵ز�\n�������ڽ�����Ϊ��������������������"
                "��������ǧ����������Ѿ�׼�����ˣ������в����������ǡ���\n��������"
                "������ҩ�������ܰ���ȥŪ���³�֮����Ȼ����ĺô���");

        remove_call_out("answer");
        call_out("answer", 0, me);
        set_temp("to_answer", 1, me);
        add_action("do_accept", "accept");
        return 1;
}

void answer(object me)
{
        tell_object(me, HIR "\n��Ը�����(accept)ʮ�����޵�������\n" NOR);
}

int do_accept()
{
        object me = this_player();
        if( query_temp("to_answer", me) )
        {
                tell_object(me, HIR "\n���������ʮ������Ѱ����������"
                                "����ԭ�ϡ�\n" NOR);
                message_vision( CYN "\nʮ�����ޡ�����������Ц������\n"
                                NOR, me);
                message_vision( CYN "ʮ�����޶�$N" CYN "˵�������Ϸ��"
                                "��лл���ˡ�\n"NOR, me);
                set("hell_quest/������", 1, me);
                set("wang_get/����", 1, me);
                set("wang_get/����", 1, me);
                set("wang_get/����", 1, me);
                set("wang_get/���", 1, me);
                delete_temp("to_answer", me);
                remove_call_out("give_gold");
                call_out("give_gold", 2, me);
                addn("count", -1);
        }
        return 1;
}

int give_gold(object me)
{
        message_vision(HIW "\nʮ����������һ�ӣ���ʱ���һ��ѽ��ӣ���"
                       "��$N" HIW "��\n"NOR, me);
        message_vision(CYN "ʮ������˵����������������������ٻ�����"
                       "��������Ļƽ��㹻�㹺����ߡ�\n"NOR, me);
        tell_object(me, HIC "\n������һǧ��" NOR + YEL "�ƽ�" NOR +
                        HIC "��\n" NOR);
        MONEY_D->pay_player(me, 10000000);
        return 1;
}

int accept_object(object me, object ob)
{
        object obn;

        int exp, pot, mp;

        exp = 150000 + random(20000);
        pot = 5000 + random(5000);
        mp = 15 + random(10);

        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, me) ) return notify_fail("��û�����������\n");

         if( query("id", ob) != "long dan"
         && query("id", ob) != "hu gu"
     && query("id", ob) != "zhu yu"
     && query("id", ob) != "xuanwu jiake" )
        {
                message_vision(CYN "ʮ������ҡ��ҡͷ����������������ʲô��\n" NOR, me);
                        return 0;
        }

        if( query("over_quest/hell_quest/������", me) )
        {
                message_vision(CYN "ʮ�����޶�$N" CYN "Ц�������Ѿ����ұ������е�ԭ��"
                               "�ˣ���������������Լ��ðɡ�\n" NOR, me);
                        return 0;
        }

        if( !query("hell_quest/������", me) )
        {
                message_vision(CYN "ʮ�����޵����޹�����»������㻹���Լ����Űɡ�\n"
                               NOR, me);
                        return 0;
        }

       if( query("id", ob) == "long dan" )
        {
                if( query("over_quest/hell_quest/ԭ��/����", me )
                   && query("over_quest/hell_quest/ԭ��/����", me )
                   && query("over_quest/hell_quest/ԭ��/���", me) )
                {
                        message_vision(HIW "ʮ�����޼�����������ϲ��������������ԭ�϶�"
                                       "�ѱ��룬���ڿ��Կ�ʼ�����ϴ�Ҫ���������ˣ���"
                                       "�������\n���������������ǰ�Ҵ�������ɽ����"
                                       "�ı������Ҳû�ã��͵��ǳ��ͺ��ˡ���\n"
                                       NOR, me);

                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("magic_points", mp, me);
                        /*
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        */
                        tell_object(me, HIR "\n��ɹ���Ϊʮ�����ޱ�����������ԭ�ϡ�\n"
                                        NOR);

                        tell_object(me, HIC "\n������һ��" NOR + HIW "����쾧" NOR +
                                        HIC "��\n"
                                        NOR);

                        tell_object(me, HIC "������" + chinese_number(exp) + "��"
                                        "���顢" + chinese_number(pot) + "��Ǳ����"
                                        "��" + chinese_number(mp) + "����ۡ�\n" NOR);

                        set("over_quest/hell_quest/������", 1, me);
                        delete("hell_quest/������", me);
                        delete("over_quest/hell_quest/ԭ��/����", me);
                        delete("over_quest/hell_quest/ԭ��/����", me);
                        delete("over_quest/hell_quest/ԭ��/���", me);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        addn("over", 1);
                        return 1;
                }
           else {
                        if( query("over_quest/hell_quest/ԭ��/����", me) )
                        {
                                message_vision( HIY "ʮ�����޼�����������$N" HIY "ҡ"
                                                "ͷ�����������Ѿ��������ˣ��㻹�ǿ�ȥ"
                                                "Ѱ������ԭ�ϰɡ�\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "ʮ�����޿�����������ϲ����̫��"
                                                  "�ˣ������������׻������ҵõ��ˡ�\n"
                                                  NOR, environment(me));
                                set("over_quest/hell_quest/ԭ��/����", 1, me);
                                destruct(ob);
                                return 1;
                        }
                }
        }

         if( query("id", ob) == "hu gu" )
        {
                if( query("over_quest/hell_quest/ԭ��/����", me )
                   && query("over_quest/hell_quest/ԭ��/����", me )
                   && query("over_quest/hell_quest/ԭ��/���", me) )
                {
                        message_vision(HIW "ʮ�����޼��ǻ��ǣ���ϲ��������������ԭ�϶�"
                                       "�ѱ��룬���ڿ��Կ�ʼ�����ϴ�Ҫ���������ˣ���"
                                       "�������\n���������������ǰ�Ҵ�������ɽ����"
                                       "�ı������Ҳû�ã��͵��ǳ��ͺ��ˡ���\n"
                                       NOR, me);

                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("magic_points", mp, me);
                        /*
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        */
                        tell_object(me, HIR "\n��ɹ���Ϊʮ�����ޱ�����������ԭ�ϡ�\n"
                                        NOR);

                        tell_object(me, HIC "\n������һ��" NOR + HIW "����쾧" NOR +
                                        HIC "��\n"
                                        NOR);

                        tell_object(me, HIC "������" + chinese_number(exp) + "��"
                                        "���顢" + chinese_number(pot) + "��Ǳ����"
                                        "��" + chinese_number(mp) + "����ۡ�\n" NOR);

                        set("over_quest/hell_quest/������", 1, me);
                        delete("hell_quest/������", me);
                        delete("over_quest/hell_quest/ԭ��/����", me);
                        delete("over_quest/hell_quest/ԭ��/����", me);
                        delete("over_quest/hell_quest/ԭ��/���", me);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        addn("over", 1);
                        return 1;
                }
           else {
                        if( query("over_quest/hell_quest/ԭ��/����", me) )
                        {
                                message_vision( HIY "ʮ�����޼��ǻ��ǣ���$N" HIY "ҡ"
                                                "ͷ�����������Ѿ��������ˣ��㻹�ǿ�ȥ"
                                                "Ѱ������ԭ�ϰɡ�\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "ʮ�����޼��ǻ��ǣ���ϲ����̫��"
                                                  "�ˣ��ǰ׻������������ǵùԹԵİѹ�"
                                                  "ͷ��������\n"
                                                  NOR, environment(me));
                                set("over_quest/hell_quest/ԭ��/����", 1, me);
                                destruct(ob);
                                return 1;
                        }
                }
        }

     if( query("id", ob) == "zhu yu" )
        {
                if( query("over_quest/hell_quest/ԭ��/����", me )
                   && query("over_quest/hell_quest/ԭ��/����", me )
                   && query("over_quest/hell_quest/ԭ��/���", me) )
                {
                        message_vision(HIW "ʮ�����޼������𣬴�ϲ��������������ԭ�϶�"
                                       "�ѱ��룬���ڿ��Կ�ʼ�����ϴ�Ҫ���������ˣ���"
                                       "�������\n���������������ǰ�Ҵ�������ɽ����"
                                       "�ı������Ҳû�ã��͵��ǳ��ͺ��ˡ���\n"
                                       NOR, me);

                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("magic_points", mp, me);
                        /*
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        */
                        tell_object(me, HIR "\n��ɹ���Ϊʮ�����ޱ�����������ԭ�ϡ�\n"
                                        NOR);

                        tell_object(me, HIC "\n������һ��" NOR + HIW "����쾧" NOR +
                                        HIC "��\n"
                                        NOR);

                        tell_object(me, HIC "������" + chinese_number(exp) + "��"
                                        "���顢" + chinese_number(pot) + "��Ǳ����"
                                        "��" + chinese_number(mp) + "����ۡ�\n" NOR);

                        set("over_quest/hell_quest/������", 1, me);
                        delete("hell_quest/������", me);
                        delete("over_quest/hell_quest/ԭ��/����", me);
                        delete("over_quest/hell_quest/ԭ��/����", me);
                        delete("over_quest/hell_quest/ԭ��/���", me);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        addn("over", 1);
                        return 1;
                }
           else {
                        if( query("over_quest/hell_quest/ԭ��/����", me) )
                        {
                                message_vision( HIY "ʮ�����޼������𣬶�$N" HIY "ҡ"
                                                "ͷ�����������Ѿ��������ˣ��㻹�ǿ�ȥ"
                                                "Ѱ������ԭ�ϰɡ�\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "ʮ�����޿������𣬴�ϲ��������"
                                                  "�������ȷ����ȸ��ë������лл���ˡ�\n"
                                                  NOR, environment(me));
                                set("over_quest/hell_quest/ԭ��/����", 1, me);
                                destruct(ob);
                                return 1;
                        }
                }
        }

      if( query("id", ob) == "xuanwu jiake" )
        {
                if( query("over_quest/hell_quest/ԭ��/����", me )
                   && query("over_quest/hell_quest/ԭ��/����", me )
                   && query("over_quest/hell_quest/ԭ��/����", me) )
                {
                        message_vision(HIW "ʮ�����޼�������׿ǣ���ϲ��������������"
                                       "ԭ�϶��ѱ��룬���ڿ��Կ�ʼ�����ϴ�Ҫ��������"
                                       "�ˣ������\n��İ��������������ǰ�Ҵ�������"
                                       "ɽ�����ı������Ҳû�ã��͵��ǳ��ͺ��ˡ���\n"
                                       NOR, me);

                        addn("combat_exp", exp, me);
                        addn("potential", pot, me);
                        addn("magic_points", mp, me);
                        /*
                        if( query("potential", me)>me->query_potential_limit() )
                                set("potential", me->query_potential_limit(), me);
                        */
                        tell_object(me, HIR "\n��ɹ���Ϊʮ�����ޱ�����������ԭ�ϡ�\n"
                                        NOR);

                        tell_object(me, HIC "\n������һ��" NOR + HIW "����쾧" NOR +
                                        HIC "��\n"
                                        NOR);

                        tell_object(me, HIC "������" + chinese_number(exp) + "��"
                                        "���顢" + chinese_number(pot) + "��Ǳ����"
                                        "��" + chinese_number(mp) + "����ۡ�\n" NOR);

                        set("over_quest/hell_quest/������", 1, me);
                        delete("hell_quest/������", me);
                        delete("over_quest/hell_quest/ԭ��/����", me);
                        delete("over_quest/hell_quest/ԭ��/����", me);
                        delete("over_quest/hell_quest/ԭ��/����", me);
                        obn = new("/d/death/obj/tianjing");
                        obn->move(me);
                        destruct(ob);
                        addn("over", 1);
                        return 1;
                }
           else {
                        if( query("over_quest/hell_quest/ԭ��/���", me) )
                        {
                                message_vision( HIY "ʮ�����޼�������׿ǣ���$N" HIY "ҡ"
                                                "ͷ�����ⶫ�����Ѿ��������ˣ��㻹�ǿ�ȥ"
                                                "Ѱ������ԭ�ϰɡ�\n" NOR, me);
                                return 0;
                        }
                   else {
                                message("vision", HIY "ʮ�����޿�������׿ǣ���ϲ�����ã�"
                                                  "̫���ˣ��ǳ��ڹ걻��ɵ��˰ɣ�\n"
                                                  NOR, environment(me));
                                set("over_quest/hell_quest/ԭ��/���", 1, me);
                                destruct(ob);
                                return 1;
                        }
                }
        }

}

mixed ask_reborn()
{
        object who;
        object *all;

        who = this_player();

        /*
        if( query("reborn/times", who) )
        {
                message_vision("$N��$nһ���֣��������Ѿ�ת���ֻع��ˣ��ҿ��Ͳ����˰ɣ�\n",
                               this_object(), who);
                return 1;
        }
        */

        if( query("reborn_lunhui", who) )
        {
                message_vision("$N��$nһ���֣��������Ѿ���ս�������������ˣ��������ҵز����ɣ�\n",
                               this_object(), who);
                who->move("/d/death/yanluodian");
                return 1;
        }

        if( !query("reborn_offer", who) || query("reborn_offer", who) != "finish" )
        {
              message_vision("$N��$nһ���֣�������û���յ���������������Ƿ�û����������׼�����Լ��\n",
                               this_object(), who);
                return 1;
        }

        if( !query("over_quest/hell_quest/������", who) )
        {
                message_vision("$N��$nһ���֣��������Ȱ����ҵ���������ҩ�������ܵõ�ת���Ļ�Ե��\n",
                               this_object(), who);
                return 1;
        }

        all = deep_inventory(who);
        foreach( object user in all )
                if( userp(user) )
                        return notify_fail("���Ȱ������ϱ��ŵ��˷�������˵��\n");

        message_vision("$N˫������һ�£�$n����ͻȻ������ȥ������\n",
                       this_object(), who);

        switch(random(6))
        {
        case 0:
                tell_object(who, BLU "\n������Լ������½�����Χ������ʵ����ɣ�����עĿ��\n" NOR);
                who->move("/d/death/liudaolunhui/tiandao");
                break;
        case 1:
                tell_object(who, BLU "\n������Լ������½���\n" NOR);
                who->move("/d/death/liudaolunhui/chushengdao");
                break;
        case 2:
                tell_object(who, BLU "\n������Լ������½�������ƺ�û�˽��ޡ�����\n" NOR);
                who->move("/d/death/liudaolunhui/eguidao");
                break;
        case 3:
                tell_object(who, BLU "\n������Լ������½�����Χһ�ж�����ת������\n" NOR);
                who->move("/d/death/liudaolunhui/rendao");
                break;
        case 4:
                tell_object(who, BLU "\n������Լ������½����½����ƺ��������޾�����Ԩ��\n" NOR);
                who->move("/d/death/liudaolunhui/diyudao");
                break;
        default:
                tell_object(who, BLU "\n������Լ������½���׹���޾��ĺڰ�������\n" NOR);
                who->move("/d/death/liudaolunhui/xiuluodao");
                break;
        }
        return 1;
}

void attempt_apprentice(object ob)
{
        command("say ��������ô˵Ҳ�������еײ�Ĺ����ģ�Ҫ�ݵظ������μ�ȥ�� ");
        return;
}
