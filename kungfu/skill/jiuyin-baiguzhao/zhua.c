// zhua.c �����׹�צ - ������ץ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIG "������צ" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        string pmsg;
        string *limbs;
        string  limb;
        int ap, dp;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�þ�����ץ��\n");

        if ((int)me->query_skill("jiuyin-baiguzhao", 1) < 120)
                return notify_fail("��ľ����׹�צ��������죬����ʹ��"+name()+"��\n");

        if (me->query_skill_prepared("claw") != "jiuyin-baiguzhao")
                return notify_fail("��û��׼�������׹�צ���޷�ʹ��"+name()+"��\n");

        if( query("neili", me)<240 )
                return notify_fail("����������̫��������ʹ�þ�����ץ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "��Цһ������¶�׹⣬���ֳ�צ��������������"
              "ʵʵ����$n" HIR "��ͷ��ץ��������\n" NOR;

        addn("neili", -50, me);

        me->want_kill(target);
        ap = attack_power(me, "claw");
        dp = defense_power(target, "dodge");
        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                addn("neili", -180, me);
                damage = 0;

                if( query("max_neili", me)<query("max_neili", target)*4/5 &&
                    me->query_skill("force") < target->query_skill("force"))
                        msg += HIY "��ž����һ��$N" HIY "��ץ��$n" HIY "��������ϣ�"
                               "�����á����ۡ��ֽ���������\n" NOR;
                else
                if( query("max_neili", me)>query("max_neili", target)*2 )
                {
                        msg += HIY "�����ꡱһ����$N" HIY "��ָ������$n" HIY "������"
                               "�ǣ�$n" HIY "һ���ҽУ��������̱����ȥ��\n" NOR;
                        damage = -1;
                } else
                {
                        if (!target->is_busy())
                        target->start_busy(1 + random(3));

                        damage = damage_power(me, "claw");

                        if( arrayp(limbs=query("limbs", target)) )
                                limb = limbs[random(sizeof(limbs))];
                        else
                                limb = "Ҫ��";
                        pmsg = HIC "$n��æ��Ų������Ȼ�������ꡱһ����$N"
                               HIC "��ָ������$n" HIC "��" + limb + "��$n"
                               HIC "һ���ҽУ�Ѫ���岽��\n" NOR;
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 95, pmsg);
                }
        } else
        {
                me->start_busy(2);
                msg += CYN "����$p" CYN "������$P"
                       CYN "����ͼ�����μ������㿪����һץ��\n" NOR;
        }

        message_combatd(msg, me, target);

        if (damage < 0)
                target->die(me);
        else
        if (! target->is_killing(me))
                target->kill_ob(me);

        return 1;
}
