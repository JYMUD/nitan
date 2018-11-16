#include <combat.h>
#include  <ansi.h>

#define HUI "��" HIW "����" HIR "���" NOR "��"

string final1(object me, object target, int damage);
string final2(object me, object target, int damage);

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, lvl;
        object weapon;
         int attack_type;

        if( userp(me) && !query("can_perform/kuihua-mogong/hui", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("kuihua-mogong", 1) < 320)
                return notify_fail("�����ħ����Ϊ����������ʩչ" HUI "��\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("��������Ϊ����������ʩչ" HUI "��\n");

        if (me->query_skill_mapped("force") != "kuihua-mogong")
                return notify_fail("��û�м�������ħ��Ϊ�ڹ����޷�ʩչ" HUI "��\n");

        if( weapon=query_temp("weapon", me) )
        {
                if( query("skill_type", weapon) != "sword" && 
                    query("skill_type", weapon) != "pin" )
                        return notify_fail("��ʹ�õ��������ԣ�\n");

                attack_type = WEAPON_ATTACK;
        } else
        {
                if (me->query_skill_prepared("unarmed") != "kuihua-mogong")
                        return notify_fail("�㲢û��׼��ʹ�ÿ���ħ�����޷�ʩչ" HUI "��\n");

                attack_type = UNARMED_ATTACK;
        }

        
        if( query("neili", me)<800 )
                return notify_fail("��������������������ʩչ" HUI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        lvl = me->query_skill("kuihua-mogong", 1);

        message_vision("\n\t\t" + BBLU + HIR "��    ��    " HIW "��    ��\n" NOR, me);

        // ��һʽ-----����
        ap = me->query_skill("force") + me->query_skill("dodge");
        dp=target->query_skill("force")+query("dodge", target);

        message_combatd(sort_msg(HIW "\n��Ȼ��$N" HIW "������ת��ɲʱ����糱�����Ʊ�"
                     "�գ����Ϊ֮��ɫ�������ǡ��������䡷�����ؾ�ѧ��" HIR "����"
                     "ʽ" HIW "����ת�ۼ�$N" HIW "�Ѳ�������Ӱ��ֻ����һ����Х��һ"
                     "���׹������½�$n" HIW "���֣�" NOR), me, target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, attack_type, damage, 130,
                                           (: final1, me, target, damage :));

                if( !query("can_perform/kuihua-mogong/hui2", me) )
                {
                       addn("can_perform/kuihua-mogong/hui1", 1, me);
                       if( query("can_perform/kuihua-mogong/hui1", me) >= 200 )
                       {
                            tell_object(me, HIR "��ġ�����ʽ���Ѿ����õ÷ǳ������ˣ�\n" NOR);
                       }
                }
        } else
        {
                msg = HIC "$p" HIC "������죬��������һ������������С���\n" NOR;
        }
        message_combatd(msg, me, target);

        if( query("can_perform/kuihua-mogong/hui2", me) )
        {
        // �ڶ�ʽ-----���ʽ        
        message_combatd(sort_msg(HIM "\n������$N" HIM "����һ�Σ���û���ټ���ɲ�Ǽ䣬$n" HIM "ֻ���õض�"
                     "ɽҡ��������ӿ������ԥ�䣬$N" HIM "�Ѵ���$n" HIM "���һ��"
                     "��" HIR "��ؾ�" HIM "��ʹ�� ����\n" NOR), me, target);

        ap = me->query_skill("force") + me->query_skill("dodge");
        dp=target->query_skill("force")+query("dodge", target);

        if (ap * 4 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, attack_type, damage, 130,
                                          (: final2, me, target, damage :));

                                           
        } else
        {
                msg = HIC "$p" HIC "ֻ���������������͵�����Ծ������������С�\n" NOR;
        }
        message_combatd(msg, me, target);
        }

        me->start_busy(2 + random(3));
        addn("neili", -200-random(300), me);
        return 1;
}

string final1(object me, object target, int damage)
{
        target->receive_wound("qi", damage / 16, me);

        return HIR "$n" HIR "���д󾪣�ֻ��$N" HIR "һ��"
               "ҫ�۰׹�һ�����ѻ����Լ���ǰ����������������"
               "�����С�\n:����@?";

}
string final2(object me, object target, int damage)
{
        target->receive_wound("jing", damage / 20, me);
        target->receive_wound("qi", damage / 20, me);
        return  HIR "ֻ��$n" HIR "һ���Һ�����$N" HIR
                "���б��ģ������꿦�ꡱ�߹�����ϡ�\n:����@?";
}