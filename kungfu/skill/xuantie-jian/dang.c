// This program is a part of NITAN MudLIB
// ����Ⱥħ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return RED"����Ⱥħ"NOR; }

int perform(object me, object target)
{
        int damage, ap, dp;
        object weapon;
        string msg, pmsg;

        if (! target) target = offensive_target(me);

        if (! target
        ||  ! target->is_character()
        ||  ! me->is_fighting(target))
                return notify_fail(
                        "��"RED"����Ⱥħ"NOR"��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if (target->is_busy())
                return notify_fail(target->name() + "Ŀǰ���Թ˲�Ͼ���ӽ������ɢ�\n");

        if((int)me->query_skill("xuantie-jian", 1) < 120)
                return notify_fail(
                        "�����������������죬����ʹ�á�"RED"����Ⱥħ"NOR"����\n");

        if ((int)me->query_skill("surge-force", 1) < 120
        &&  (int)me->query_skill("surge-force", 1) < 120)
                return notify_fail(
                        "��Ĺ�Ĺ�ڹ���Ϊ̫ǳ������ʹ�á�"RED"����Ⱥħ"NOR"����\n");

        if (me->query_str() < 40)
                return notify_fail(
                        "��ı���������ʹ�á�"RED"����Ⱥħ"NOR"�����ڼ��ѡ�\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������\n");

        msg=HIB"��Ȼ�䣬$N����"NOR+query("name", weapon)+HIB"����һ�����������¡¡"+
              "�ķ���֮����Ю�������֮�ƣ�\nһʽ��"NOR+BLINK+RED"����Ⱥħ"NOR+HIB"����" +
              "����"NOR+query("name", weapon)+HIB"��$n��ͷֱѹ��ȥ��\n";

        ap = attack_power(me, "sword") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_str()*10;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                addn("neili", -200, me);

                pmsg = HIR "$n�����мܣ���ʱ��$N�������ѹ����Ѫ���ڣ�����ס���ۡ����³�һ����Ѫ��\n" NOR;
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80, pmsg);
                me->start_busy(1);
                if( !target->is_busy() )
                        target->start_busy(2);
        } else
        {
                addn("neili", -100, me);
                msg += HIW"$p��æȫ��һ�������项��һ�����죬$P������о�Ȼ��$p����������\n" NOR;
                me->start_busy(2);
        }

        message_combatd(msg, me, target);

        return 1;
}

