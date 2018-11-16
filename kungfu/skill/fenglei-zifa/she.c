#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

#define SHE "��" HIR "���վ�" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i;
        int n, p;
        mixed my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if( userp(me) && !query("can_perform/fenglei-zifa/she", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHE "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" || 
            weapon->query_amount() < 1)
                return notify_fail("���������в�û�����Ű������޷�ʩչ��" SHE "��\n");

        if ((skill = me->query_skill("fenglei-zifa", 1)) < 100)
                return notify_fail("��ķ����ӷ�������죬�޷�ʩչ" SHE "��\n");

        if( query("neili", me)<100 )
                return notify_fail("���������㣬�޷�ʩչ" SHE "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -80, me);
        weapon->add_amount(-1);

        msg = HIR "$N" HIR "����΢΢һչ������һ�Σ�ֻ����쬡���һ����һ" +
             query("base_unit", weapon)+weapon->name()+HIR"�������"+
             "����$n" HIR "��ȥ��\n" NOR;

        me->start_busy(2);
        my_exp=query("combat_exp", me)+skill*skill/10*skill;
        my_exp /= 100;
        ob_exp=query("combat_exp", target)/100;
        p=query("qi", target)*100/query("max_qi", target);
        if (random(my_exp) > ob_exp * 2 / 3)
        {
                msg += HIR "$n" HIR "���ܲ�������ʱ�����д��˸�Ѫ��ģ��"
                       "�Ŀ������������۵ü�����Ҫɢ�ܡ�\n" NOR;
                target->receive_wound("qi", skill / 2 + random(skill / 2), me);
                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+150);
                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;
                        msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "����$p" CYN "����һ�ݣ���������$P" CYN "������" +
                       weapon->name() + CYN "��\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}