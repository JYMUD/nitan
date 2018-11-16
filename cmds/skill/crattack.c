// crattack.c

#include <ansi.h>

inherit F_CLEAN_UP;

void hate_attack(object me, object target);
void shout_message(string msg);

int main(object me, string arg)
{
        object target;
        int craze;
        string msg;
        int attack;
        int damage;

        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ��ս����\n");

        if (me->is_busy())
                return notify_fail("( ����һ��������û����ɣ�����ʩ�÷�ŭһ����)\n");

        if (! arg)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        } else
                target = present(arg, environment(me));

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ŭһ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (! living(target))
                return notify_fail("�˼Ҷ��Ѿ���������ˣ���"
                                   "���õ�����ô������ô��\n");

        if ((craze = me->query_craze()) < 500)
                return notify_fail("��������ƽ���ͣ�̸����ʲô��ŭ��\n");

        if (craze < 1000)
                return notify_fail("�����ڻ�������ŭ���޷�ʩչ��ŭ��ɱ������\n");

        if( query("qi", me)*100/query("max_qi", me)<50 )
                return notify_fail("����������̫�������޷�ʩչ��ŭ��ɱ������\n");

        if( query("qi", me)<200 )
                return notify_fail("��������Ϣ����ǿ������ʩչ���ҵķ�ŭ��ɱ������\n");

        me->receive_damage("qi",random(query("max_qi", me)/4));

        if (me->is_most_craze())
        {
                int second;

                if( me->is_hating(query("id", target)) )
                {
                        hate_attack(me, target);
                        return 1;
                }

                if( query("gender", me) == "Ů��" )
                        msg = HIR "$N" HIR "�����������У������ɨ��$n"
                              HIR "�������������˸���ս��ֻ��$P������"
                              "������" + RANK_D->query_rude(target) +
                              "����ȥ���ɣ���\n" NOR;
                else
                        msg = HIR "$N" HIR "�������ף������񣬶�$n"
                              HIR "��ȵ�����" + RANK_D->query_rude(target) +
                              "���㻹���������������\n" NOR;
                message_combatd(msg, me, target);

                // first attack
                attack = craze / 50;
                damage = craze / 20;
                if (attack > me->query_skill("force") + 10)
                        attack = me->query_skill("force") + 10;
                if (damage > me->query_str() * 8)
                        damage = me->query_str() * 8;
                addn_temp("apply/attack", attack, me);
                addn_temp("apply/damage", damage, me);
                addn_temp("apply/unarmed_damage", damage, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                msg = HIR "\n$N" HIR "һ�й������������ݣ��漴������������һ�У�\n" NOR;
                if (! me->is_fighting(target) && living(target))
                {
                        msg += HIY "$n" HIY "��$N" HIY "����������ȫȻ"
                               "�����Լ��Ѿ��������գ����ɴ��һ������"
                               "æ�ֵ���\n" NOR;
                }
                message_combatd(msg, me, target);

                // second attack
                second=query("str", me);
                attack += second;
                damage += second;
                addn_temp("apply/attack", second, me);
                addn_temp("apply/damage", second, me);
                addn_temp("apply/unarmed_damage", second, me);
                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                addn_temp("apply/attack", -attack, me);
                addn_temp("apply/damage", -damage, me);
                addn_temp("apply/unarmed_damage", -damage, me);
                me->cost_craze(craze / 4 + random(craze / 2));
                me->start_busy(2);
                return 1;
        }

        if( query("gender", me) == "Ů��" )
                msg = HIR "$N" HIR "һ��������ңָ$n" HIR "�ȵ�����" +
                      RANK_D->query_rude(target) + "�����У���\n" NOR;
        else
                msg = HIR "$N" HIR "һ�������ͬ�����������$n" HIR
                      HIR "���ȵ�����" + RANK_D->query_rude(target) +
                      "���㻹�������������\n" NOR;

        message_combatd(msg, me, target);
        attack = craze / 60;
        damage = craze / 30;
        if (attack > me->query_skill("force") + 10)
                attack = me->query_skill("force") + 10;
        if (damage > me->query_str() * 8)
                damage = me->query_str() * 8;

        addn_temp("apply/attack", attack, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/uanrmed_damage", damage, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        addn_temp("apply/attack", -attack, me);
        addn_temp("apply/damage", -damage, me);
        addn_temp("apply/uanrmed_damage", -damage, me);
        me->cost_craze(craze / 4 + random(craze / 2));
        me->start_busy(1);
        return 1;
}

void hate_attack(object me, object target)
{
        int craze;
        int attack;
        int damage;

        craze = me->query_craze();
        attack = craze / 40;
        damage = craze / 18;
        if (attack > me->query_skill("force") + 10)
                attack = me->query_skill("force") + 10;
        if (damage > me->query_str() * 8)
                damage = me->query_str() * 8;

        if (random(2))
                shout_message(me->name(1) + "��" + target->name() + HIR "�����ȵ���" +
                              RANK_D->query_rude(target) + "������" +
                              RANK_D->query_self(me) + "Ҫ��ѪծѪ�������У�");
        else
                shout_message(me->name(1) + "��" + target->name() + HIR "ŭ�ȵ���" +
                              RANK_D->query_rude(target) + "���Թ�ɱ�˳�����" +
                              "�����Ҿ�Ҫ��Ĺ��������ɣ�");

        me->want_kill(target);
        me->kill_ob(target);
        addn_temp("apply/attack", attack, me);
        addn_temp("apply/damage", damage, me);
        addn_temp("apply/unarmed_damage", damage, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "�е���" + target->name() +
                       "�����ٿ�����һ�У�\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "�е���" + RANK_D->query_rude(target) +
                      "�����ٿ�����һ�У�\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "�е����ã����ٽ�����һ�У�\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "�е������ߣ����ٽ�����һ�У�\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "�е�����������⵱�д���һ�У�\n" NOR, me);
        damage+=query("str", me);
        attack+=query("str", me);
        addn_temp("apply/attack",query("str",  me), me);
        addn_temp("apply/damage",query("str",  me), me);
        addn_temp("apply/unarmed_damage",query("str",  me), me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);

        message_combatd(HIR "\n$N" HIR "�е�����û�꣬�������һ�У�����\n" NOR, me);
        COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
        addn_temp("apply/attack", -attack, me);
        addn_temp("apply/damage", -damage, me);
        addn_temp("apply/unarmed_damage", -damage, me);

        if( query("qi", target) >= 0 && 
            query("jing", target) >= 0 )
        {
                if (random(2))
                        shout_message(target->name(1) + "�ǺǴ�Ц������λ" +
                                      RANK_D->query_respect(me) + "�����"
                                      "���������������������ҺΣ�");
                else
                        shout_message(target->name(1) + "������Ц�������" +
                                      "���ƺ��װ�����ϧ����̫�Ҳ�գ�Ҳ�գ�������");

                tell_object(me, HIR "��Ŀ�����ѣ�����ȼ�������ŭ��˿��û�м�����\n" NOR);
        } else
        {
                if (random(2))
                        shout_message(target->name(1) + "�ҽе����ҵ��죡");
                else
                        shout_message(target->name(1) + "�������ţ��찡����Ӧ���úÿ죡");

                me->cost_craze(craze);
                me->craze_defeated(query("id", target));
                tell_object(me, HIC "�㳤��һ����������ƽ������ࡣ\n" NOR);
        }
        me->start_busy(2);
}

void shout_message(string msg)
{
        message("channel:chat", HIR "������" HIW "ѩ" HIR "�ޡ�" +
                                msg + "\n" NOR,
                                all_interactive());
}

int help (object me)
{
        write(@HELP
ָ���ʽ��crattack <����>

����㴦�ڷ�ŭ״̬���Ϳ��������Լ��ķ�ŭ��ַ����Լ���������
�������ڽ��ֵĶ��ֳ��صĴ������Ȼ�㻹��ʹ�ø��ͻ���ɱ������
���书�����յ����õ�Ч�������ŭ���ﵽ�˶����ʱ����������
��ͬ���졣

����㱻�˴��λ���ɱ������������ɱ������˽���Ϊ�����޵Ķ�
�󣬵����ŭ�ﵽ������ʱ�򣬾Ϳ��Զ������޵Ķ���ʩչ��������
ɱ������ֻ�ܶ�һ�����޵Ķ�������һ�Ρ�

HELP );
        return 1;
}