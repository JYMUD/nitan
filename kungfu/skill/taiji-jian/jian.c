// ̫�O����

#include <ansi.h>
#include <combat.h>

string name() { return HIM "̫�O����" NOR; }

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);

int perform(object me, object target)
{
        int damage;
        string msg;
        object weapon;
        int ap, dp, fp;
        int xy;

        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ��̫�O���⣡\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( me->is_busy() )
                return notify_fail("����æ���ء�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�\n");

        if ((int)me->query_skill("taiji-jian", 1) < 1000)
                return notify_fail("��̫������������죬�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<2000 )
                return notify_fail("�����������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("��û�м���̫���������޷�ʹ��" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -1000, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "dodge");
        fp = defense_power(target, "parry");

        xy = me->query_skill("tianwei-zhengqi", 1);

        ap = ap + ap*(xy/100<10?10:xy/100)/100;

        damage = damage_power(me, "sword");
        damage = damage + damage*(xy/50<10?10:xy/50)/100;
        damage *= 3;

        //target->start_busy(10);

        message_combatd(sort_msg(HIY "\n$N" HIY "����һת������" + weapon->name() + HIY "��������������"
                     "�������������������̬Ʈ������֮�����ľ�" HIC "̫�O" HIY "֮��" HIY "����\n" NOR), me);

        msg = HIM "$N" HIM "�����������ڽ��ϣ�����һ�������������������̡�\n" NOR;
        if (ap + random(ap / 2) < dp)
                msg += CYN "$n" CYN "�����ֿ죬б��������\n" NOR;
        else
        {

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200 + (xy / 2 + random(xy / 2)>500?500:xy / 2 + random(xy / 2)),
                                           (: attack1, me, target, damage :));
        }

        msg += HIM "\n$N" HIM "��ҡ" + weapon->name() + HIM "����ʱ�������ݺᣬ����է�֣�����Ŀ��Ͼ�ӡ�\n" NOR;
        if (ap + random(ap / 2) < fp)
                msg += CYN "$n" CYN "����һ������������һ�����Ǳ��ض�����С�\n" NOR;
        else
        {
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200 + (xy / 2 + random(xy / 2)>500?500:xy / 2 + random(xy / 2)),
                                           (: attack2, me, target, damage :));
        }

        me->start_busy(2 + random(3));
        message_combatd(msg, me, target);

        return 1;
}


string attack1(object me, object target, int damage)
{
        string msg;

        msg = HIR "$N" HIR "����Ʈ���ޱȣ���$n" HIR "���޷�Ӧ��"
              "���������������ز�����\n" NOR;

        // if( random(2) != 1 ) return msg;
        //if( target->query_condition("no_perform") ) return msg;

        target->apply_condition("no_perform", 5);

        msg += WHT "$n" WHT "�е���������ȫ���������ƻ�ɢ��һ�㣬ȫȻ�޷����ơ�\n" NOR;

        return msg;
}

void remove_effect(object target)
{
        if( !objectp(target) ) return;

        addn_temp("apply/avoid_busy", 90, target);
        addn_temp("apply/reduce_busy", 36, target);
        addn_temp("apply/avoid_weak", 90, target);
        addn_temp("apply/avoid_locked", 90, target);
        tell_object(target, HIR "��ĺ�������������æ�ҡ����Ӿ����䶳�������ڽ����ӡ��\n" NOR);
}

string attack2(object me, object target, int damage)
{
        string msg;

        msg = HIR "$N" HIR "����Խ����������$n" HIR "�Ƶý������ˣ�"
              "����һ������$n" HIR "��Ҳ�޴Ӷ�ܡ�\n" NOR;

        if( random(2) != 1 ) return msg;

        addn_temp("apply/avoid_busy", -90, target);
        addn_temp("apply/reduce_busy", -36, target);
        addn_temp("apply/avoid_weak", -90, target);
        addn_temp("apply/avoid_locked", -90, target);
        call_out("remove_effect", 30, target);

        msg += WHT "$n" WHT "�е�����ĺ�������������æ�ҡ����Ӿ����䶳��������ӡ��\n" NOR;

        return msg;
}
