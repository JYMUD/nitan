#include <ansi.h>
#include <combat.h>

string name() { return HIY "�𹳶���" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon, weapon2;
        int damage;
        string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ��޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "jinwu-goufa")
                return notify_fail("��û�м������ڹ������޷�ʩչ" + name() + "��\n");

        if ((int)me->query_skill("jinwu-goufa", 1) < 160)
                return notify_fail("��Ľ��ڹ�����������죬�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "ͻȻ$N" HIY "һ����ߣ�����" + weapon->name() +
              NOR + HIY "�ӳ����ڿ��л����������Ļ��ߣ�ֱ��$n" HIY
              "��ҪѨ��\n" NOR;
        addn("neili", -50, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        //me->want_kill(target);
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2 + random(2));
                addn("neili", -200, me);
                damage = 0;

                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIR "ֻ��$N" HIR "��һ�����ƺÿ죬����һ"
                               "����������$n" HIR "���ʺ�$n" HIR "һ��"
                               "�ҽУ��������̱����ȥ��\n" NOR "( $n" RED
                               "���˹��أ��Ѿ�������в�����ʱ�����ܶ�"
                               "����" NOR ")\n";
                        damage = -1;
                } else
                if( objectp(weapon2=query_temp("weapon", target)) &&
                    me->query_skill("sword") > target->query_skill("parry"))
                {
                        // if(userp(me))
                        msg += HIR "ֻ����������һ����$n" HIR "����"
                              "�������У�����" + weapon2->name() + NOR
                              + HIR "��Ҳ׽�ò�ס�����ֶ��ɣ�\n" NOR;
                        //me->start_busy(2 + random(2));
                        if( !target->is_busy() )
                                target->start_busy(2);
                        weapon2->move(environment(target));
                } else
                {
                        damage = damage_power(me, "sword");

                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "Ҫ��";
                        pmsg = HIR "$n" HIR "���������Ȼ��ֻ����������"
                               "һ����$N" HIR "��" + weapon->name()+ NOR
                               + HIR "������$n" HIR + limb + "�ϣ���ʱ��"
                               "Ѫ�񽦶�����\n" NOR;
                        msg += COMBAT_D->do_damage(me, target,
                               WEAPON_ATTACK, damage, 40, pmsg);
                }
        } else
        {
                me->start_busy(4);
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ���ܿ�����һ�С�\n"NOR;
        }

        message_combatd(msg, me, target);
        if (damage < 0) target->die(me);

        return 1;
}
