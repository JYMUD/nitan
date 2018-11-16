// hun.c ��������

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;
        string *limbs,limb;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("feilong-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("cuff") != "feilong-cuff") 
                return notify_fail("��û���÷�����ȭ���޷�ʹ�á��������졹���У�\n");

        if (me->query_skill_prepared("cuff") != "feilong-cuff")
                return notify_fail("��û��׼��ʹ�÷�����ȭ���޷�ʩչ���������졹���С�\n");

        if (skill < 100)
                return notify_fail("��ķ�����ȭ�ȼ�������������������\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("��������˫�ֲ���ʹ��ȭ�����С�\n");

        if( query("neili", me)<500 )
                return notify_fail("�������������\n");
        
        ap = me->query_skill("cuff") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIW "\n$N" HIW "Ĭ�����������ȭ��" HIC "��������" HIW "�����ĳ�Хһ����˫ȭ����������\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIR "\n$N" HIR "˫ȭ�����������޵���ʽ�����л���$n" HIR "�Ĺؽ�Ҫ����\n\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                limbs=query("limbs", target);
                limb = limbs[random(sizeof(limbs))];
                msg += HIB "$n" HIB "��ʧɫ���������У�����$N" HIB "����" + limb + "��\n"NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIY "$n" HIY "���˷���������һȦһ����$N" HIY "���ݲ�����ȥ��\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        addn("neili", -damage/3, me);
        return 1;
}

