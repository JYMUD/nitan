// hun.c Ϧ����

#include <ansi.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg,str;
        object weapon;
        int n;
        int skill, ap, dp, damage;

        me->clean_up_enemy();
        if (! target) target = me->select_opponent();

        skill = me->query_skill("luorishenquan-cuff", 1);

        if (! me->is_fighting(target))
                return notify_fail("Ϧ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("cuff") != "luorishenquan-cuff") 
                return notify_fail("��û����������ȭ���޷�ʹ�á�Ϧ���졹���У�\n");

        if (me->query_skill_prepared("cuff") != "luorishenquan-cuff")
                return notify_fail("��û��׼��ʹ��������ȭ���޷�ʩչ��Ϧ���졹���С�\n");

        if (skill < 100)
                return notify_fail("���������ȭ�ȼ�������������������\n");

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

        msg = HIW "\n$N" HIW "Ĭ������������ȭ����" HIC "Ϧ����" HIW "�����ĳ�Хһ����˫ȭ����������\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIW "\n$N" HIW "����һ����������һȭ��ʵ�޻�����$n" HIW "ӭ���ȥ��\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIW "$n" HIW "�����������ҽ�һ�������ű����˸����š�\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIC "$n" HIC "���Ʋ���͵����һԾ���㿪�������һȭ��\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        if(!userp(target) && !target->is_killing(query("id",me)) ) target->kill_ob(me); 
        addn("neili", -damage/3, me);
        return 1;
}

