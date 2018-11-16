// This program is a part of NT MudLIB
// qi.c ���ν���

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "���ν���" NOR; }

int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;
        int n;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("force") < 420)
                return notify_fail("����ڹ���򲻹���ʹ����" + name() + "��\n");

        if( query("max_neili", me) < 5000 )
                return notify_fail("���������Ϊ��������ʹ�����Ϭ����" + name() + "��\n");

        if( query("neili", me) < 500 )
                return notify_fail("��������������޷�ʹ��" + name() + "��\n");

        if (me->query_skill("six-finger", 1) < 200)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" + name() + "��\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("��û��׼�������񽣣��޷�ʹ��" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIG "$N" HIG "��ָһ����һ���������׵����ν���ֱ��$n" HIG "��ǰ��ȥ��\n" NOR;

        ap = attack_power(me, "finger")+me->query_skill("force");
        dp = defense_power(target, "dodge") + target->query_skill("force");
        weapon=query_temp("weapon", target);
        me->start_busy(3);
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "finger");
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        msg += HIM"$N"HIM"����������ת�ĸ�����ʹ�����ν����˺���ǿ��\n"NOR;
                        damage += damage*n*15/100;
                }
                addn("neili", -400, me);
                if( !objectp(weapon) || query("skill_type", weapon) == "pin" )
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 120,
                                                   HIR "$n" HIR "ֻ������ǰһ���ʹ����Ѫ"
                                                   "�Դ��ڼ����������ǰ��ʱһ�ڣ�\n" NOR);
                else
                if( weapon->is_item_make() || query("damage", weapon)>180 ||
                    query("skill_type", weapon) == "hammer" )
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 100,
                                                   HIR "$n" HIR "��" + weapon->name() + HIR "��ͼ�мܣ�"
                                                   HIR "������ɽ������Ϭ����͸��" + weapon->name() +
                                                   HIR "ֱ���$n" HIR "������Ѫ������������Ҫ��ת������\n" NOR);
                else
                {
                        msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80,
                                                   HIR "$n" HIR "��ת" + weapon->name() + HIR "��������"
                                                   "ǰ��ֻ��ž��һ����" + weapon->name() +
                                                   HIR "������أ��������죡\n$n" HIR "����"
                                                   "���������ۡ�������һ����Ѫ����ɫ��ĲҰס�\n" NOR);
                        weapon->move(environment(me));
                        set("no_wield", weapon->name()+"�Ѿ�����ˣ�û��װ���ˡ�\n", weapon);
                        weapon->set_name("�����" + weapon->name());
                        set("value", 0, weapon);
                }
        } else
        {
                msg += CYN "����$p" CYN "�ڹ���Ϊ������Ὣ����������������Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}
