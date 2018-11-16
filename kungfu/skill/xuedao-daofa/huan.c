// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIR "�ұػ�֮" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp, damage;
        int per;

        /*
        if( query("family/family_name", me) != "Ѫ����" )
                return notify_fail("�㲻��Ѫ���ŵ��ӣ��޷�ʹ��" + name() + "��\n");
        */

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ��" + name() + "��\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if( me->is_busy() )
                return notify_fail("����æ���ء�\n");

        if ((int)me->query_skill("force") < 1200)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("xuedao-daofa", 1) < 1000)
                return notify_fail("���Ѫ���󷨻������ң�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "xuedao-daofa")
                return notify_fail("��û�м���Ѫ����Ϊ����������ʩչ" + name() + "��\n");

        if( query("qi", me)<100 )
                return notify_fail("��Ŀǰ��Ѫ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<800 )
                return notify_fail("��Ŀǰ�������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        msg = HIR "$N" HIR "����" + weapon->name() + "ֱָ$n" HIR"�����к������������ʲô���Ծ��ǲ�֪�����������ң��ұػ�֮����\n"
              HIR "ֻ��" + weapon->name() + "����Ũ��Ѫ�⡢��ζ�̱ǣ�ӳ������ֱ��ŨѪ������\n";

        if (ap / 2 + random(ap) > dp)
        {
                target->set_weak(5);
                per=query("eff_qi", me)*100/query("max_qi", me);
                if (per > 60)
                {
                        damage = damage_power(me, "blade");
                        damage+= query("jiali", me);
                }
                else
                if (per < 20)
                        damage = -1;
                else
                        damage=query("max_qi", target)*per/100;

                addn("neili", -150, me);
                me->start_busy(2);

                if (damage > 0)
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 300,
                                           HIR "��$n" HIR "���У�" + weapon->name() + "�ĵ���Խ��Խ��ѹ���Լ�����͸��������"
                                           HIR "ֱ����ȻһŻѪ��ȴ����" + weapon->name() + "�Ѿ����Լ��������������Ĺ켣��\n" NOR);
                else
                {
                        msg += HIR "��$n" HIR "���У�" + weapon->name() + "�ĵ���Խ��Խ��ѹ���Լ�����͸��������"
                               HIR "ֱ����ȻһŻѪ��ȴ����" + weapon->name() + "�Ѿ����Լ��������������Ĺ켣��\n" NOR;
                        target->die(me);
                }
        } else
        {
                me->start_busy(2);
                msg += CYN "�����⵶Ҫ����$n" CYN "���ϣ�$N" CYN "����һ����Ѫ�������$n" CYN "˳�ƹ���һ�ԣ����ǲ����з��������$N"
                       CYN "�ı�ɱһ����\n"NOR;
                addn("neili", -100, me);
        }

        message_combatd(msg, me, target);
        return 1;
}

