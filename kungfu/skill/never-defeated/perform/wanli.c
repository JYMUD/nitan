// wanli.c �������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object  weapon;
        int     damage;
        string  msg;
        string  pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("�������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)me->query_skill("never-defeated", 1) < 120)
                return notify_fail("��Ĳ����񹦻�������죬����ʹ��������\n");
                                
        if( query("neili", me)<200 )
                return notify_fail("����������̫��������ʹ��������\n");
                        
        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("������ֱֳ��в���ʩչ������\n");
                
        if (me->query_skill_mapped("sword") != "never-defeated") 
                return notify_fail("������û�м���������Ϊ����������ʩչ������\n"); 
                
        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "����" + weapon->name() + HIC "��һ"
              "ȦȦ�Ļ���$n" HIC "����$p" HIC "���ڵ��У�\n" NOR;
        addn("neili", -20, me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -180, me);

                damage = damage_power(me, "sword");

                if( arrayp(limbs=query("limbs", target)) )
                        limb = limbs[random(sizeof(limbs))];
                else
                        limb = "Ҫ��";
                pmsg = HIR "$n��æ��Ų������Ȼ�������ꡱһ����" + weapon->name() +
                       HIR "���û���$p" HIR "��" + limb + "��$p"
                       HIR "һ���ҽУ�����������\n" NOR;
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 90, pmsg);
        } else 
        {
                me->start_busy(2);
                msg += CYN "����$p" CYN "������$P"
                       CYN "�ı仯�����в��У�û���ܵ��κ��˺���\n"NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}
