// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.
// guojing.c ����

inherit NPC;
#include <ansi.h>

string *degree_desc = ({
        BLU "ʿ��" NOR,
        BLU "�λ�" NOR,
        HIC "�ν�" NOR,
        HIC "�Խ�" NOR,
        HIY "����" NOR,
        HIY "����" NOR,
        HIR "����" NOR,
        HIR "�ᶽ" NOR,
});

string clear_degree(string arg);
string ask_canjun(string arg);
string ask_jianlou();
string ask_lianzhu();
string ask_fuming();
string ask_shoucheng();
string ask_chetui();

int ask_degree();
int add_degree(object ob,int lv);

void create()
{
        set_name("����", ({"guo jing", "guo", "jing"}));
        set("nickname", HIY "����" NOR);
        set("title", "�����Ǵ�");
        set("gender", "����");
        set("age", 41);
        set("long",
                "�������˳Ʊ����Ĺ����������ɹųɼ�˼���Ľ���������\n"
                "�����߹֡�ȫ�������ڵ���������ؤ�����߹��͡�����ͯ����\n"
                "��ͨ���˵�ͽ�ܣ���������书��������һ����ɫ���ۣ���̬\n"
                "���࣬�غ����Ŀ��͸��һ�����ϡ�\n");
        set("attitude", "friendly");
        set_max_encumbrance(100000000);
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);
        set("chat_chance", 1);
        set("chat_msg", ({
                "����̾�˿����������ɹű��ù��������£�һ�����ٳ���ƣ��ض��ֲ�����ߣ���....\n",
                "����˵���������ݹ���������֪�ɺã����һ��Ҫ�ش�Įȥ��������\n",
        }));

        set("inquiry", ([
                "�ܲ�ͨ" : "��������ܴ���ˣ������ڿɺã�\n",
                "����ͯ" : "�ܴ��һ��������û��������\n",
                "���߹�" : "ʦ�����˳ԣ�����ϲ���档�����棬����Ϊ���ҳԵġ�\n",
                "��ҩʦ" : "������̩ɽ���ˡ��������ĺ����������ײ���β�ġ�\n",
                "һ�ƴ�ʦ" : "���¶Դ�ʦ�����м���\n",
                "ŷ����" : "����϶����������λʦ����һ���������ˣ������������ݡ�\n",
                "����"   : "�ض����ҵİ��ޣ�������������\n",
                "�ض�"   : "�ض������ض��ˡ�������ô����\n",
                "��ܽ"   : "���Ů�����ֱ��ֲ�������\n",
                "����"   : "��������������Ⱳ���ֶ��򡣵�Ը���ܿ���һ����\n",
                "����²" : "�����ҵ�С���ӡ�\n",
                "���"   : "����ȷʵ�г�Ϣ��\n",
                "����"   : "����������а�ʦ֮�ꡣ\n",
                "�𴦻�" : "������屡���죬������ܡ�\n",
                "�����" : "�����Ҵ�ʦ����\n",
                "���"   : "�����Ҷ�ʦ����\n",
                "������" : "��������ʦ����\n",
                "��ϣ��" : "��������ʦ����\n",
                "�Ű���" : "��������ʦ����\n",
                "ȫ��" : "��������ʦ����\n",
                "��СӨ" : "��������ʦ����\n",
                "ؤ��"   : "ؤ��Ӣ�ۼ������ˣ�����������������ǡ�\n",
                "��ʦ"   : "�����ɹ���Χ��������������������ͽ����\n",
                "�س�"   : (: ask_shoucheng :),
                "����"   : (: ask_fuming :),
                "����"   : (: ask_chetui :),
                "�ѻ�"   : (: ask_jianlou :),
                "�������":   (: ask_lianzhu :),
                "�߷�"   :   (: ask_degree :),
                "�ξ�"   :   (: ask_canjun :),
                ]));

        set("qi", 10000);
        set("max_qi", 10000);
        set("jing", 8000);
        set("max_jing", 8000);
        set("neili", 34000);
        set("max_neili", 34000);
        set("jiali", 500);

        set("combat_exp", 25000000);
        set("score", 200000);

        set_skill("force", 320);
        set_skill("xiantian-gong", 320);
        set_skill("yijin-duangu", 320);
        set_skill("guoshi-xinfa", 280);
        set_skill("dodge", 300);
        set_skill("feiyan-zoubi", 280);
        set_skill("jinyan-gong", 300);
        set_skill("shexing-lifan", 300);
        set_skill("unarmed", 300);
        set_skill("changquan", 300);
        set_skill("strike", 320);
        set_skill("dragon-strike", 320);
        set_skill("sword", 280);
        set_skill("yuenv-jian", 280);
        set_skill("parry", 320);
        set_skill("literate", 120);
        set_skill("zuoyou-hubo", 400);
        set_skill("martial-cognize", 320);
        set_skill("craft-cognize", 280);
        set_skill("array-cognize", 280);
        set_skill("arrow", 400);
        set_skill("lianzhu-arrow", 400);

        map_skill("arrow", "lianzhu-arrow");
        map_skill("force", "yijin-duangu");
        map_skill("strike", "dragon-strike");
        map_skill("unarmed", "changquan");
        map_skill("sword", "yuenv-jian");
        map_skill("dodge", "shexing-lifan");
        map_skill("parry", "xianglong-zhang");

        prepare_skill("strike", "dragon-strike");
        
        create_family("����", 1, "����");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform strike.fei twice") :),
                (: command("perform strike.hui twice") :),
                (: command("perform strike.zhen twice") :),
                (: command("perform strike.qu and strike.hui") :),
                (: command("perform strike.fei and strike.hui") :),
                (: command("perform strike.zhen and strike.hui") :),
                (: command("perform strike.zhen and strike.fei") :),
                (: exert_function, "shield" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }));

        set_temp("apply/damage", 300);
        set_temp("apply/unarmed_damage", 300);
        set_temp("apply/armor", 500);

        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object me = this_player();
        object ob;
        ::init();

        if( query("jungong", me)>100 )
                add_action("do_study", "qingjiao");
                
        if (interactive(ob = this_player())
           && userp(ob)
           && !query_temp("mark/guofu_wait", ob )
           && !is_fighting())
        {
                if( query("mark/guofu_over", ob) )
                {
                        command("hmm");
                        command("say �Ҳ���������ı��·�����ܻ������");
                        command("say ���壬���ģ���" + ob->name() + NOR + CYN "��ȥ��");
                        message_vision(HIC "\nֻ��$N" HIC "һ���֣���ʱ��������������"
                                       "λ���꣬��$n" HIC "���˳�ȥ��\n\n",
                                       this_object(), ob);
                        ob->move("/d/xiangyang/westjie1");
                        tell_room(environment(ob), HIC "\nֻ����λ�������" + ob->name() +
                                                   HIC "�ӹ����������˹�����\n" NOR, ({ ob }));
                } else
                if( query("mark/guofu_out", ob )
                 && query("combat_exp", ob)<100000 )
                {
                        command("say �����ڵ��书�Ѿ���һ���ĵ����ˣ�Ӧ�ö��߶��߶���");
                        command("say �����Ǵ�������������������󡣶��壬���ģ��Ϳͣ�");
                        message_vision(HIC "\nֻ��$N" HIC "һ���֣���ʱ��������������"
                                       "λ���꣬��$n" HIC "���˳�ȥ��\n\n",
                                       this_object(), ob);
                        ob->move("/d/xiangyang/westjie1");
                        tell_room(environment(ob), HIC "\nֻ����λ��������" + ob->name() +
                                                   HIC "�ӹ����������˹�����\n" NOR, ({ ob }));
                } else
                if ((int)ob->query_condition("killer"))
                {
                        command("sigh");
                        command("say ��ɱ�����֮�أ�������Ҳ�������㣬�㻹���߰ɡ�");
                        command("say ���壬���ģ��Ϳͣ�");
                        message_vision(HIC "\nֻ��$N" HIC "һ���֣���ʱ��������������"
                                       "λ���꣬��$n" HIC "���˳�ȥ��\n\n",
                                       this_object(), ob);
                        ob->move("/d/xiangyang/westjie1");
                        set("mark/guofu_over", 1, ob);
                        delete("mark/guofu_ok", ob);
                        tell_room(environment(ob), HIC "\nֻ����λ�������" + ob->name() +
                                                   HIC "�ӹ����������˹�����\n" NOR, ({ ob }));
                } else
                // ������ڣ������������������书
                if( query("mark/guofu_ok", ob)//��ȷ�ϱ������ڹ���
                   && query("mark/guofu_job", ob)>200//�ڹ�������������������
                   && query("combat_exp", ob)>10000//��ȷ�Ͼ���ֵ��һ�������֮��
                   && query("combat_exp", ob)<50000
                   && !query_temp("job_name", ob)//�ܴ�ʱû����ȡ����
                   && !query("family/family_name", ob)//��û�а�ʦ
                   && !query("can_learn/3skills/guojing", ob)//�ݱ�֤��ǰδ���������
                   && ! stringp(ob->query_skill_mapped("force"))) //�� û�м��������ڹ�
                {
                        command("look "+query("id", ob));
                        command("yi");
                        command("whisper "+query("id", ob)+"�����ҹ����ڹ���Ҳ��"
                                "һ����ʱ��\n�ˣ���ô��һ��֮��Ҳû�У��Ժ��������߽�"
                                "���������š���\n�����ˣ��ӽ�������ÿ�쵽����������"
                                "�Ҵ����㼸��򵥵�\n�����书���ˡ�\n" NOR);
                        set("can_learn/3skills/guojing", 1, ob);
                }
         }
}

string ask_shoucheng()
{
        object *ene;
        object me = this_player();

        if (is_fighting())
        {
                ene = query_enemy();

                if (sizeof(ene) > 1)
                        return "����" + RANK_D->query_respect(me) + "�Ե�Ƭ�̣����Ⱥ���" +
                                sizeof(ene) + "λ�����д輸�£���\n";
                if (sizeof(ene) == 1)
                        return "����" + RANK_D->query_respect(me) + "�Ե�Ƭ�̣����Ⱥ�" +
                                ene[0]->name() + "�д輸�£���\n";
        }

        if( query_temp("guo_shoucheng/mark_shadi", me) )
                return "��" + RANK_D->query_respect(me) + "���������س��������𣡡�\n";

        if( query_temp("guo_shoucheng/mark_jianlou", me) )
                return "��" + RANK_D->query_respect(me) + "�������оѻ��������𣡡�\n";

        if( query("combat_exp", me)<100000 )
                       return "��" + RANK_D->query_respect(me) + "���޸���֮�������Ǳ��������Ϊ�ã���\n";

               if ((int)me->query_skill("force", 1) < 60)
                       return "�س��Ǽ�Σ�չ������ҿ�" + RANK_D->query_respect(me) + "�Ļ����������㣡\n";

               if ((int)me->query_condition("jobshadi_failed"))
               {
                message_vision("$N����$nҡ��ҡͷ˵������ʧ���˻�������??\n", this_object(), me);
                return "��" + RANK_D->query_respect(me) + "�㻹�Ǳ��������Ϊ�ã���\n";
               }

               if( query_temp("guo_shoucheng/failed", me) )
               {
                 delete_temp("guo_shoucheng", me);
                 me->apply_condition("jobshadi_failed", 4);
                 return "���������ӣ����һ������ң���������\n";
               }

              if ((int)me->query_condition("jobshadi_limit"))
               {
                message_vision("$N����$nҡ��ҡͷ˵���㲻���������س�������??\n", this_object(), me);
                return "��" + RANK_D->query_respect(me) + "�������ĸ�λ��ȥ����\n";
               }

               if ((int)me->query_condition("guojob2_busy"))
               {
                message_vision(CYN "$N����$nҡ��ҡͷ˵��ƣ��֮ʦ������ս����\n" NOR,
                            this_object(), me);
                return "��" + RANK_D->query_respect(me) + "�㻹����Ϣһ�������ɣ���\n";
               }

               if( query("shen", me)>0 )
               {
                switch (random(2)) {
                case 0:
                        set_temp("guo_shoucheng/mark_shadi", 1, me);
                        set_temp("guo_shoucheng/carry_location", "eastgate1", me);
                        return "�������ɹ������ַ���ԭ����λ" +
                                RANK_D->query_respect(me) + "ȥ�������Ű����ξ��سǰɡ�";

                       break;
                case 1:
                        set_temp("guo_shoucheng/mark_shadi", 2, me);
                        set_temp("guo_shoucheng/carry_location", "northgate1", me);
                        return "�������ɹ������ַ���ԭ����λ" + RANK_D->query_respect(me) + "ȥ�������Ű����ξ��سǰɡ�";

                               break;
                }
        }
        else
        {
        switch( random(2) ) {
                case 0:
                        set_temp("guo_shoucheng/mark_shadi", 3, me);
                        set_temp("guo_shoucheng/carry_location", "southgate1", me);
                return "�������ɹ������ַ���ԭ����λ"+RANK_D->query_respect(me)+"ȥ��ȸ���Ű����ξ��سǰɡ�";

                       break;
                case 1:
                        set_temp("guo_shoucheng/mark_shadi", 4, me);
                        set_temp("guo_shoucheng/carry_location", "westgate1", me);
                return "�������ɹ������ַ���ԭ����λ"+RANK_D->query_respect(me)+"ȥ�׻����Ű����ξ��سǰɡ�";

                       break;
                }
        }
}


string ask_jianlou()
{
        object *ene;
        object me = this_player();

        if (is_fighting())
        {
                ene = query_enemy();

                if (sizeof(ene) > 1)
                        return "����"+RANK_D->query_respect(me) +
                               "�Ե�Ƭ�̣����Ⱥ���" + sizeof(ene) + "λ�����д輸�£���\n";
                if (sizeof(ene) == 1)
                        return "����" + RANK_D->query_respect(me) + "�Ե�Ƭ�̣����Ⱥ�"
                                + ene[0]->name() + "�д輸�£���\n";
        }

        if( query_temp("guo_shoucheng/mark_shadi", me) )
                return "��"+RANK_D->query_respect(me)+"���������س��������𣡡�\n";

        if( query_temp("guo_shoucheng/mark_jianlou", me) )
                return "��"+RANK_D->query_respect(me)+"�������оѻ��������𣡡�\n";

        if ((int)me->query_condition("jobshadi_failed"))
        {
                message_vision(
                        "$N����$nҡ��ҡͷ˵������ʧ���˻�������??\n", this_object(), me);
                return "��"+RANK_D->query_respect(me)+"�㻹�Ǳ��������Ϊ�ã���\n";
        }

        if( query_temp("guo_shoucheng/failed", me) )
        {
                delete_temp("guo_shoucheng", me);
                me->apply_condition("jobshadi_failed",4);
                return "���������ӣ����һ������ң���������\n";
        }

        if ((int)me->query_skill("arrow", 1) < 50)
        {
                message_vision(CYN"$N����$nҡ��ҡͷ˵����Ļ�������̫���ˣ�\n"NOR,
                               this_object(), me);
                return "��"+RANK_D->query_respect(me)+"������������ʤ�ΰ�����\n";
        }

        if ((int)me->query_condition("jobjianlou_limit"))
        {
                message_vision("$N����$nҡ��ҡͷ˵���㲻����������������𣿣�\n",
                                this_object(), me);
                return "��"+RANK_D->query_respect(me)+"�����������ĸ�λ��ȥ����\n";
        }

        if ((int)me->query_condition("guojob2_busy"))
        {
                message_vision(CYN"$N����$nҡ��ҡͷ˵��ƣ��֮ʦ������ս����\n"NOR,
                                this_object(), me);
                return "��"+RANK_D->query_respect(me)+"�㻹����Ϣһ�������ɣ���\n";
        }

        set_temp("guo_shoucheng/mark_jianlou", 2, me);
        set_temp("guo_shoucheng/where", "east_out", me);
        return "���Ǿ�������λ"+RANK_D->query_respect(me) +
               "ǰ���������ŵĶ��Ǽ�¥������ѻ��ɹż��ֵ�����ɡ�\n��";
}

string ask_fuming()
{
        int job_pot, job_exp, job_sco, reward;
        int job_mar;
        object me = this_player();

        if( !me->query_condition("jobshadi_failed") && query_temp("guo_shoucheng/failed", me) )
        {
                delete_temp("guo_shoucheng", me);
                me->apply_condition("jobshadi_failed",4);
                return "���������ӣ����һ�����������������\n";
        }

        if( query_temp("guo_shoucheng/help_killed", me )
             && !query_temp("guo_shoucheng/job_over", me) )
        {
                job_exp=(query_temp("guo_shoucheng/help_killed", me))*80;
                job_pot = job_exp / 2;
                job_sco = job_pot / 2;
                job_mar = job_pot / 2;

                if (job_exp > 2000) job_exp = 2000;
                if (job_pot > 1000) job_pot = 1000;

/*
                if( query_temp("warquest/guard", me) )
                {
                        job_exp += 2000;
                        job_pot += 1000;
                        addn_temp("warquest/reward", 200, me);
                }
#ifdef DB_SAVE
                if (MEMBER_D->is_double_reward(me))
                {
                        job_exp *= 2;
                        job_pot *= 2;
                        job_mar *= 2;
                        job_sco *= 2;
                }
#endif
                addn("combat_exp", job_exp, me);
                addn("potential", job_pot, me);
                addn("score", job_sco, me);
                addn("experience", job_mar, me);
*/
                GIFT_D->bonus(me, ([ "exp" : job_exp, "pot" : job_pot, "mar" : job_mar, "score" : job_sco ]));

/*
                tell_object(me, HIW "�㱻������" + chinese_number(job_exp) + "�㾭��ֵ��" +
                                chinese_number(job_pot) + "��Ǳ�ܺ�" + chinese_number(job_sco) + "��������ᡣ\n" NOR);
*/
                delete_temp("guo_shoucheng", me);
                me->apply_condition("guojob2_busy", 2);
                //addn("guo_shoucheng/reward_exp", job_exp, me);
                //addn("guo_shoucheng/reward_potential", job_pot, me);

                return "��"+RANK_D->query_respect(me) + "��Ϊ��ɱ�У���������\n";
        }

        if( !query_temp("guo_shoucheng/mark_shadi", me )
                 && !query_temp("guo_shoucheng/mark_jianlou", me )
                 || !query_temp("guo_shoucheng/job_over", me) )
                return "�������û�������ɣ�������ʲô������\n";

        if( query_temp("guo_shoucheng/killed_mgb", me)<1 )
        {
                delete_temp("guo_shoucheng", me);
                return "����ɱ�˼������˰����ʹ�ǰ���ӻ����ˣ�\n";
        }

        message_vision(CYN "$N��$n˵������"+RANK_D->query_respect(me)+"�����ˣ�ȥ��Ϣһ�°ɣ���\n" NOR, this_object(), me);

        job_exp=(query_temp("guo_shoucheng/killed_mgb", me))*100;
        job_exp += query_temp("guo_jianlou/killed_mgb", me)*100;
        job_pot = job_exp / 2;
        job_sco = job_pot / 2;
        job_mar = job_pot / 2;

        if (job_exp > 3000) job_exp = 3000;
        if (job_pot > 1500) job_pot = 1500;
        if( query_temp("warquest/guard", me) )
        {
                job_exp += 1000;
                job_pot += 500;
                addn_temp("warquest/reward", 500, me);
        }

        reward=query_temp("guo_shoucheng/killed_mgb", me)/10+1;

/*
#ifdef DB_SAVE
                if (MEMBER_D->is_double_reward(me))
                {
                        job_exp *= 2;
                        job_pot *= 2;
                        job_mar *= 2;
                        job_sco *= 2;
                        reward  *= 2;
                }
#endif

        tell_object(me, HIW "�㱻������" + chinese_number(job_exp) + "�㾭��ֵ��" +
                        chinese_number(job_pot) + "��Ǳ�ܺ�" + chinese_number(job_sco) + "����������һЩ������ᡣ\n" NOR);
*/

        GIFT_D->bonus(me, ([ "exp" : job_exp, "pot" : job_pot, "mar" : job_mar, "score" : job_sco, "weiwang" : 5 ]));

        me->apply_condition("guojob2_busy", 2);

/*
        addn("combat_exp", job_exp, me);
        addn("potential", job_pot, me);
        addn("weiwang", 5, me);
        addn("score", job_sco, me);
        addn("experience", job_mar, me);
*/

        //addn("guo_shoucheng/reward_exp", job_exp, me);
        //addn("guo_shoucheng/reward_potential", job_pot, me);
        addn("jungong", reward, me);

        delete_temp("guo_shoucheng", me);

        return "��" + RANK_D->query_respect(me) + "��Ϊ��ɱ�У����µ��ȣ����Ǿ���" HIY +
                chinese_number(reward) + NOR + CYN "�ߣ�������\n" NOR;
}

string ask_chetui()
{
        object me;

        me = this_player();

        if( !query_temp("guo_shoucheng/start_job", me )
                 && !query_temp("guo_shoucheng/mark_jianlou", me )
                 && !query_temp("guo_shoucheng/mark_shadi", me) )
                return "��û��������,������Ϲ����ʲ�᣿";

        me->apply_condition("jobshadi_limit", 0);
        me->apply_condition("jobjianlou_limit", 0);
        addn("combat_exp", -100+random(20), me);
        me->apply_condition("jobshadi_failed", 4);
        delete_temp("guo_shoucheng", me);

        return "û��ϵ���´μ���Ŭ�� ��";
}

string ask_lianzhu()
{
        object me = this_player(), ob = this_object();

        if( query("guo_shoucheng/reward", me)>100 )
        {
                message_sort(HIC "$N������Ц�����������������(lianzhu-arrow)�Ҿ�" +
                             "�������ˣ��������ɱ�У�����ս������Ҳ�޺��ˣ�\n" NOR, ob);
                return "ʱ����ȣ����ھͿ�ʼѧ��(qingjiao lianzhu-arrow)��\n";
        } else
        {
                message_sort(HIC "$N΢΢��ͷ�����������������(lianzhu-arrow)���ҵ�" +
                             "������Ѫ֮����\n���������ഫ����\n" NOR, ob);
                return "���������з���ɱ�У����Ҵ���֮�ģ��պ�ؿ������ͣ�\n";
        }
}

int do_study(string arg)
{
        string skill;
        object me = this_player(), ob = this_object();

        if (! arg || arg != "lianzhu-arrow")
                return notify_fail("��Ҫ��������(qingjiao)ʲô��\n");

        if (me->query_skill("lianzhu-arrow", 1) > me->query_skill("arrow", 1))
                return notify_fail("��Ļ�������̫���ˣ��޷�����ѧϰ���������\n");

        if (me->query_skill("lianzhu-arrow", 1) * me->query_skill("lianzhu-arrow", 1) > query("jungong", me)*50 )
                return notify_fail("����سǾ��������࣬������Ը���������ˣ�\n");

        if( query("learned_points", me) >= query("potential", me) )
                return notify_fail("���Ǳ�ܲ����ˣ�\n");

        if( query("jing", me)<100 || query("qi", me)<100 )
                return notify_fail("������̫���ˣ�����Ϣһ�°ɣ�\n");

        me->receive_damage("qi", 10 + random(40));
        me->receive_damage("jing", 10 + random(40));
        addn("learned_points", 1, me);
        message_vision(HIC "$Nָ����$nһЩ�й�" HIW "�����������" HIC "�����⣬" +
                       "$n�ƺ���Щ�ĵá�\n" NOR, ob, me);

        me->improve_skill("lianzhu-arrow", random(me->query_skill("arrow", 1)));

        return 1;
}

int ask_degree()
{
        int lv;
        object ob = this_player();

        if( query_temp("degree_jungong", ob) )
        {
                command("say " + RANK_D->query_respect(ob) + "�԰����꣬" +
                        "���Ѿ�����ǰ������ˣ�\n");
                return 1;
        }
        
        lv=query("degree_jungong", ob);
        if (lv >= sizeof(degree_desc))
        {
                command("say �������Ϊ������⣬����������ǰ�����٣�ǰ;�Բ�������\n");
                return 1;
        }
                
        if( query("degree_jungong", ob) < 0 )
                delete("degree_jungong", ob);

        if( query("jungong", ob)>
            (100*(1+query("degree_jungong", ob))*(1+query("degree_jungong", ob))) )
                lv=query("degree_jungong", ob)+1;

        if( lv <= query("degree_jungong", ob) )
        {
                command("say"+query("name", ob)+"��Ҫ��ø��ߵĲ߷⣬������������ſ��԰���\n");
                return 1;
        }

        command("say " + RANK_D->query_respect(ob) + "���Ժ��Ҽ�������ǰ������Ϊ" +
                RANK_D->query_respect(ob) + "��⣡\n");

        call_out("add_degree", 10, ob, lv);
        set_temp("degree_jungong", 1, ob);
        message("channel:rumor", MAG "������������" + CHINESE_D->chinese_date((time()-14*365*24*60*60)) +
                "��һƥ���������������ֱ�����ξ��ǣ�\n" NOR, users());

        return 1;
}

int add_degree(object ob,int lv)
{
        string degree, old_degree;
        degree = degree_desc[lv-1];

        if( query("degree", ob) )
                old_degree=query("degree", ob);
        else old_degree = "";

        message("channel:rumor", HIY "�����ξ��ǡ�����������ʵ�گԻ��" +
                "�߷�"+old_degree+""+HIW+query("name", ob)+
                HIY " Ϊ���� " NOR + degree + HIY "���մˣ�\n" NOR, users());

        delete_temp("degree_jungong", ob);

        if( query("degree", ob) )
        {
                if( query("degree_ask", ob) )
                        degree=HIM " �� " NOR+clear_degree(query("degree", ob))+
                                 HIM " �� " NOR + degree + HIM " �� " NOR;
                else
                        degree=HIM " �� " NOR+clear_degree(query("degree", ob))+
                                 degree + HIM " �� " NOR;
        } else
                degree = HIM " �� " NOR + degree + HIM " �� " NOR;

        set("degree_jungong", lv, ob);
        set("degree", degree, ob);
        addn("weiwang", lv*200, ob);
        return 1;
}

string clear_degree(string arg)
{
        if ((strsrch(arg, BLU "ʿ��" NOR) >= 0) ||
            (strsrch(arg, BLU "�λ�" NOR) >= 0) ||
            (strsrch(arg, HIC "�ν�" NOR) >= 0) ||
            (strsrch(arg, HIC "�Խ�" NOR) >= 0) ||
            (strsrch(arg, HIY "����" NOR) >= 0) ||
            (strsrch(arg, HIY "����" NOR) >= 0) ||
            (strsrch(arg, HIR "����" NOR) >= 0) ||
            (strsrch(arg, HIR "�ᶽ" NOR) >= 0) ||
            (strsrch(arg, HIM " �� " NOR) >= 0))
        {
                arg = replace_string(arg, BLU "ʿ��" NOR,"");
                arg = replace_string(arg, BLU "�λ�" NOR,"");
                arg = replace_string(arg, HIC "�ν�" NOR,"");
                arg = replace_string(arg, HIC "�Խ�" NOR,"");
                arg = replace_string(arg, HIY "����" NOR,"");
                arg = replace_string(arg, HIY "����" NOR,"");
                arg = replace_string(arg, HIR "����" NOR,"");
                arg = replace_string(arg, HIR "�ᶽ" NOR,"");
                arg = replace_string(arg, HIM " �� " NOR,"");
        }
        return arg;
}

string ask_canjun(string arg)
{
        object me = this_player();
        return WAR_D->join_kingwar(me);
}

int recognize_apprentice(object ob, string skill)
{
        if( !query("can_learn/3skills/guojing", ob) )
        {
                command("say �����ɹ���Χ�������������������ڿΰ���");
                command("say ���㽫����ʦ֮����ʦ����Ȼ����㣬�����ļ���");
                return -1;
        }

        if( query("combat_exp", ob)>50000 )
        {
                command("say �㾭��Ҳ�����ˣ�Ӧ�ö��ȥ����������������������\n");
                return -1;
        }

        if (skill != "force"
           && skill != "guoshi-xinfa"
	   && skill != "dodge"
           && skill != "feiyan-zoubi"
           && skill != "unarmed"
           && skill != "changquan")
        {
                command("shake");
                command("say ����ഫ���㼸���Ϊ���������⼼�ܣ��������������ˡ�");
                command("say ����Ը���ѧ�����ķ��������߱ڡ�̫�泤ȭ��һЩ�������ܡ�\n");
                return -1;
        }

        if( !query_temp("can_learn/guojing", ob) )
        {
                command("nod2");
                command("say �����ڷܿ̿࣬�ұ㴫����һЩ���ܣ���Ҫ����Ǻ��ˡ�");
                set_temp("can_learn/guojing", 1, ob);
        }
        return 1;
}

void unconcious()
{
        full_self();
        return;
}

varargs void die(object killer)
{
        full_self();
        return;
}
