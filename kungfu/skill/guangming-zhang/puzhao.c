// ʥ������

#include <ansi.h>

inherit F_SSERVER;

string name() { return "ʥ������"; }

int perform(object me, object target)
{
        int damage;
        int ap,dp;
        string msg,str;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʩչʥ�����ա�\n");

        if (query_temp("weapon", me))
                return notify_fail("��ֻ�п��ֲ���ʹ�ù������ơ�\n");

        if (!(me->query_skill_mapped("strike") == "guangming-zhang"))
                return notify_fail("�㲢û�м����������ƣ������ʥ�����գ�\n");

        if (!(me->query_skill_prepared("strike") == "guangming-zhang"))
                return notify_fail("�㲢û��׼���������ƣ������ʥ�����գ�\n");

        if ((int)me->query_skill("guangming-zhang", 1) < 80)
                return notify_fail("��Ĺ������ƻ�򲻹���\n");

        if ((int)query("max_neili", me) < 500)
                return notify_fail("���������Ϊ���㣬�޷�������ʩչʥ�����ա�\n");

        if ((int)query("neili", me) < 200)
                return notify_fail("��������Ϣ���㣬�޷�������ʩչʥ������      ��\n");

        msg = HIR "ֻ��$N" HIR "��ɫ��ׯ����ϲ��ŭ���޴��ޱ��������૲������������ʢ��\n\n"
              "$N" HIR "˫�ƻ���̧������ҫ�۵�Ѫɫ��â���������ƣ�������������ף�\n\n"
              "��Ȼ�䣬$N" HIR "������Х��˫��Ѹ���Ƴ�����ɫ��â���Ź������˽�$n������Χ������\n\n"NOR;

        me->start_busy(1 + random(2));
        addn("neili", -50, me);


        damage = damage_power(me, "strike");

        ap = attack_power(me, "strike") + me->query_str()*10;
        ap = defense_power(target, "dodge") + target->query_dex()*10;

        if (ap < dp)
        {
                msg += HIY "$n" HIY "�������񣬲������ۺ�â������"
                       "�����μ�����������$N" HIY "����������Ŀ���һ�ơ�\n\n";
        } else
        {
                msg += HIR "$n" HIR "ֻ������ǰ���һƬ����Ҳ������$N�����Σ�"
                               "��ʧɫ�£������Ѿ�ϯ���ֹ�������ؿڸ�����ӡ��һ�ƣ�������Ѫ���磡\n\n" NOR;
                        target->receive_damage("qi", damage, me );
                        target->receive_wound("qi", random(damage/2), me);
                        if (! target->is_busy())
                        target->start_busy(2);
                        str = COMBAT_D->status_msg((int)query("qi", target) * 100 /(int)query("max_qi", target));
                        msg += "($n"+str+")\n";
        }

        message_combatd(msg, me, target);
        //me->want_kill(target);
        //if (! target->is_killing(me)) target->kill_ob(me);
        return 1;
}