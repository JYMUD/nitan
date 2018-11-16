// hun.c Ⱥħ����

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

        skill = me->query_skill("diyushajie-strike", 1);

        if (! me->is_fighting(target))
                return notify_fail("Ⱥħ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if(me->query_skill_mapped("strike") != "diyushajie-strike") 
                return notify_fail("��û���õ���ɱ���Ʒ����޷�ʹ�á�Ⱥħ���衹���У�\n");

        if (me->query_skill_prepared("strike") != "diyushajie-strike")
                return notify_fail("��û��׼��ʹ�õ���ɱ���Ʒ����޷�ʩչ��Ⱥħ���衹���С�\n");

        if (skill < 100)
                return notify_fail("��ĵ���ɱ���Ʒ��ȼ�������������������\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("��������˫�ֲ���ʹ���Ʒ����С�\n");

        if( query("neili", me)<500 )
                return notify_fail("�������������\n");
        
        ap = me->query_skill("strike") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);

        damage = ap + random(ap);
                
        dp = target->query_skill("parry",1) + target->query_skill("dodge",1);
        dp = dp*3/2;

        msg = HIG "$N" HIG "˫�ֺϽᡰ" HIY "ʮ�˲�����ֻ�ӡ" HIG "����"
              "��̤����������,��Բʮ��Ⱥħ���衣\n" HIG "������������������������"
              "��$n" HIG "���񲻶��������㱡�\n"
              "ͻȻ��һȦȦ��âΧ��$n" HIG "�����$n" HIR "��Ѫ" HIG "������\n" NOR;

        message_combatd(msg, me, target);

        n=query("tianmo_jieti/times", me);
        
        while (n-- && me->is_fighting(target))
        {
                if (! target->is_busy() && random(3))
                        target->start_busy(1);
                COMBAT_D->do_attack(me, target, 0, 0);
        }

        msg = HIG "\n$n" HIG "��δ�ع����񣬽�����ֱ���" HIY "ʮ�˲�����ֻ�ɱ��" HIG "����ǿ��ħ���������ڣ��Ǹк���������\n"
              "�˴�������$N" HIG "ʮ�˹ɼ����������ͬ��ɽ����һ�㱼��$n" HIG "���������������ɰ��ʯ��\n\n" NOR;

        if (ap / 2 + random(ap) > dp || !living(target))
        {
                msg += HIM "$n" HIM "��Ҳ�ֵ���ס�����ӱ��߸����𣬿���" HIR "��Ѫ" HIM "���磬����������\n" NOR;
                target->receive_damage("qi", damage, me);
                target->receive_wound("qi", damage/2, me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                target->start_busy(1);
        } else
        {
                msg += HIM "$n" HIM "ƴ�������Ծ�����ձܹ�������һ����������¡�\n" NOR;
        }

        me->start_busy(2 + random(2));
        message_vision(msg, me, target);
        addn("neili", -damage/3, me);
        return 1;
}

