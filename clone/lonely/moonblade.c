// moonblade.c Բ���䵶

#include <weapon.h>
#include <ansi.h>

//inherit F_OBSAVE;
inherit BLADE;

string do_wield();
string do_unwield();

void create()
{
        set_name(HIW "Բ���䵶" NOR, ({ "moon blade", "blade", "moon" }));
        set_weight(1500);
        if (clonep())
                destruct(this_object());
        else {
                set("long", HIW "�˵���ħ�����֮���������ޱȣ�Բ�µ������"
                                "�����¹���ʹ����ͨ��֮�ܡ�\n" NOR );
                set("unit", "��");
                set("value", 800000);
                set("no_sell", 1);
                set("no_store", 1);
                set("material", "steel");
                set("wield_msg", (: do_wield() :));
                set("unwield_msg", (: do_unwield() :));
                set("stable", 80);
        }
        init_blade(500);
        setup();
        //restore();
}

string do_wield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        call_out("check_npc", 0, me, environment(me));
        if( query("shen", me)<-100000 )
        {
                addn_temp("apply/attack", me->query_skill("blade",1)/4, me);
                addn_temp("apply/defense", me->query_skill("parry",1)/4, me);
                return HIW "$N�����ͺ𣬻����γ�$n" HIW "��ֻ�е�һ���¹⵱��������\n" NOR;
        } else
        if( query("shen", me) <= 0 )
        {
                addn_temp("apply/attack", me->query_skill("blade",1)/4, me);
                addn_temp("apply/defense", me->query_skill("parry",1)/4, me);
                return HIC "$N���ְ�$n" HIW "������ʡ�\n" NOR;
        } else
        if( query("shen", me)>100000 )
        {
                addn_temp("apply/attack", me->query_skill("blade",1)/4, me);
                addn_temp("apply/defense", me->query_skill("parry",1)/4, me);
                return HIB "$Nսս�����İγ�һ��$n" HIB "��\n" NOR;
        } else
        {
                addn_temp("apply/attack", me->query_skill("blade",1)/4, me);
                addn_temp("apply/defense", me->query_skill("parry",1)/4, me);
                return HIB "$N�����һ��ͺ𣬡�ৡ���һ��������$n" HIB "��\n" NOR;
        }
}

string do_unwield()
{
        object me;

        me = this_player();
        remove_call_out("check_npc");
        addn_temp("apply/attack",-me->query_skill("blade",1)/4, me);
        addn_temp("apply/defense",-me->query_skill("parry",1)/4, me);
        if( query("shen", me) <= 0 )
                return HIC "$N���ֽ�Բ���䵶��ص��ʡ�\n" NOR;
        else
        if( query("shen", me)>100000 )
                return HIG "$N��$n" HIG "�����������о���������ȫ�����ѡ�\n" NOR;
        else
                return HIG "$Nһɹ����$n" HIG "��ص��ʡ�\n" NOR;
}

void check_npc(object me, object env)
{
        object *ob;
        int i;

        if (! objectp(me) || ! living(me))
                return;

        if (environment(me) != env)
                return;

        ob = all_inventory(env);
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character() || ob[i] == me ||                    
                    !living(ob[i]) || query("not_living", ob[i]) || 
                    query("id", ob[i]) == "qing qing" )
                        continue;

                if (me->is_good())
                {
                        if (userp(ob[i]))
                                continue;

                        if( query("shen", ob[i])<-100000 )
                        {
                                message_vision("$N��ŭ�ȵ��������" + RANK_D->query_rude(me) +
                                               "����Ȼ�ҵ���Բ���䵶��\n", ob[i]);
                                if( !query("no_fight", env) )
                                        ob[i]->kill_ob(me);
                        } else
                        if (ob[i]->is_good())
                        {
                                message_vision(random(2) ? "$N������Ц����$n�����ɵ�Ư������֮"
                                                           "���ߣ�Ҳ������̨������\n" :
                                                           "$Nƴ�����ƣ���$n�����벻��ħ����"
                                                           "����̨�������֮��ѽ��",
                                               ob[i], me);
                        }
                        continue;
                }

                if (me->is_not_bad())
                        continue;

                if( query("shen", ob[i])<-100000 && !userp(ob[i]) )
                {
                        message_vision(random(2) ? "$N�޵����õ����õ���\n" :
                                                   "$N̾����Ҳ��֪ħ�̽������ϼһﵽ����û������\n",
                                       ob[i]);
                } else
                if( query("shen", ob[i])>10 && !userp(ob[i]) )
                {
                        mixed ob_exp, my_exp;
                        ob_exp=query("combat_exp", ob[i]);
                        my_exp=query("combat_exp", me);
                        if (count_gt(ob_exp, count_mul(my_exp * 2)) || count_gt(ob_exp, 1500000))
                        {
                                message_vision(random(2) ? "$N��$n���������������������ǰ��Ū��\n" :
                                                           "$Nһ����Ц����$n��������Ϊ����˭��ħ�̽���"
                                                           "�ǣ�����������\n",
                                               ob[i], me);
                        } else
                        if (count_gt(ob_exp, 20000))
                        {
                                message_vision(random(2) ? "$N��ɫ��Щ���Ծ���\n" :
                                                           "$N¶�����µ���ɫ��\n",
                                               ob[i]);
                                if( query("no_fight", env) )
                                        continue;
                                message_vision(random(2) ? "$Nŭ��һ��������Ҷ���Ҫ���ˣ���\n" :
                                                           "$Nһ�Բ�������������$n�����μ��졣\n",
                                               ob[i], me);
                                ob[i]->kill_ob(me);
                        } else
                        {
                                message_vision(random(2) ? "$N��ͨһ����̱���ڵأ�˫�ּ�ҡ"
                                                           "�����������ң���Ĳ����ң���\n" :
                                                           "$Nһ�����£����Ͱ͵�ʲôҲ˵"
                                                           "��������\n",
                                               ob[i], me);
                                if( !query("no_fight", env) )
                                        ob[i]->unconcious();
                        }
                }
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int n;
//        int my_exp, ob_exp;

        if (me->is_good() || victim->is_bad())
                return - damage_bonus / 2;

        if (me->is_not_bad() || victim->is_not_good())
                return 0;

        if (me->query_skill_mapped("blade") != "moon-blade" ||
            me->query_skill("moon-blade", 1) < 100)
                // only increase damage
                return damage_bonus / 2;

        switch (random(4))
        {
        case 0:
                if (! victim->is_busy())
                        victim->start_busy(me->query_skill("blade") / 10 + 2);
                return HIB "$N��ǰһ�������е�" NOR+HIW "Բ���䵶" NOR+HIB "�����벻����"
                       "�Ƕ���$n��ȥ��$nֻ����������������������\n"
                       "��֪��εֵ���ֻ���������ˡ�\n" NOR;

        case 1:
                n = me->query_skill("blade");
                victim->receive_damage("qi", n, me);
                victim->receive_wound("qi", n, me);
                n=query("eff_jing", victim);
                n /= 2;
                victim->receive_damage("jing", n, me);
                victim->receive_wound("jing", n / 2, me);
                return random(2) ? HIB "$N����ͺ����е�Բ���䵶���������⣬��ৡ���ɨ��$n��\n" NOR:
                                   HIB "$NͻȻ�����ȵ�����ʲô�������ɣ�����������������Բ���䵶"
                                   HIB "����һ����$n��ʱ������ǰ����ǧ�򵶹ⲻͣ������\n" NOR;
        }

        // double effect
        return damage_bonus;
}

void start_borrowing()
{
        remove_call_out("return_to_laozu");
        call_out("return_to_laozu", 14400 + random(1800));
}

void return_to_laozu()
{
        object me;

        me = environment();
        if (! objectp(me))
                return;

        while (objectp(environment(me)) && ! playerp(me))
                me = environment(me);
 
        if (playerp(me))
        {
                if (me->is_fight())
                {
                        call_out("return_to_laozu", 1);
                        return;
                }

                message_vision("��Ȼһ��ħ�̵ĵ������˹���������$N��æ�к�����������˵"
                               "��ѵ����ܶ��ˣ����������ϲ�����ģ������������û�Բ���䵶�������ڲ�����ô����\n"
                               "$N���������ˣ����ˣ�����û�ȥ�ɡ���\n"
                               "$N���񵶽���ħ�̵��Ӵ��ߡ�\n", me);
        } else
        {
                message("vision", "��Ȼһ��ħ�̵������˹���������Բ���䵶��̾�˿�����ҡҡ"
                                  "ͷ���ˡ�\n", me);
        }

        destruct(this_object());
}
