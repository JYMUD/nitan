// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "��ɨǧ��" NOR; }

string final(object me, object target, int ap, int dp);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((int)me->query_skill("baisheng-daofa", 1) < 150)
                return notify_fail("���ʤ�����������ң�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "baisheng-daofa")
                return notify_fail("��û�м�����ʤ����������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        ap = attack_power(me, "blade") + me->query_str()*10;
        if( query("character", me) == "��������" || query("character", me) == "������˫" )
        {
                msg = HIR "$N" HIR "��Ŀ��ȣ�ɱ����Ȼ�����ֳ�" + weapon->name() +
                      HIR "���޷��˵���Ȼ��ɨ$n" HIR "��ȫȻ����������������Ȼ��\n" NOR;
                ap += ap * 1 / 4;
        } else
                msg = HIR "$N" HIR "�����ھ�����ȫ��������ע��" + weapon->name() +
                      HIR "֮�ϼ�ն��������ৡ���һ��ɨ��$n" HIR "��ȥ��\n" NOR;

        dp = defense_power(target, "force")  + target->query_str()*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                addn("neili", -350, me);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                           (: final, me, target, ap, dp :));
                me->start_busy(2);
        } else
        {
                msg += HIC "$n" HIC "�����мܣ�Ӳ�����ĵ�ס���������ʧɫ֮��ɱһ����\n" NOR;
                addn("neili", -150, me);
                me->start_busy(2);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int ap, int dp)
{
        object weapon;
        string msg;

        msg = HIR "$n" HIR "��æ�ֵ���ȴ�����мܵ�ס��������"
              "����һ����÷������Զ��ƽɳ��";
        if (ap / 3 > dp)
        {
                msg += "�ʹ˱�����\n" NOR;
                call_out("char_killed", 0, target, me);
        } else
        if( (ap/2>dp) && objectp(weapon=query_temp("weapon", target)) )
        {
                msg += "���е�" + weapon->name() + HIR "��Ҳ����ס��Ӧ��������\n" NOR;
                weapon->unequip();
                weapon->move(environment(me));
        } else
                msg += "\n" NOR;
        return msg;
}

void char_killed(object ob, object me)
{
        if (objectp(ob) && objectp(me) && me->is_fighting(ob) &&
            environment(ob) == environment(me))
                ob->die(me);
}