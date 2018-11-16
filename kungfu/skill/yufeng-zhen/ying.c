#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIY "��Ӱ��" NOR; }

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i;
        int n;
        int my_exp, ob_exp, p, damage;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me)) ||
            query("skill_type", weapon) != "throwing" )
                return notify_fail("���������в�û�������룬��ôʩչ" + name() + "��\n");

        if (weapon->query_amount() < 1)
                return notify_fail("������û���룬�޷�ʩչ" + name() + "��\n");

        if ((skill = me->query_skill("yufeng-zhen", 1)) < 100)
                return notify_fail("���������ַ�������죬����ʹ��" + name() + "��\n");

        if (me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹����޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("throwing") != "yufeng-zhen")
                return notify_fail("��û�м�������룬����ʹ��" + name() + "��\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������޷�ʩչ" + name() + "\n");

        if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -80, me);
        weapon->add_amount(-1);

        msg = HIY "$N" HIY "���ţ��㲻�ƣ�����ֻ������һ����ֻ��"
             "һ�㺮������������������$n" HIY "��\n" NOR;

        me->start_busy(2);

        my_exp = attack_power(me, "throwing");

        ob_exp = defense_power(target, "dodge");

        if (my_exp / 2 + random(my_exp) > ob_exp)
        {
                damage = damage_power(me, "throwing");
                msg += HIR "���$p" HIR "��Ӧ����������$P" + HIR "һ" +
                       query("base_unit", weapon)+weapon->name()+
                       HIR "��\n" NOR;
                target->receive_wound("qi", damage/3, me);

                COMBAT_D->clear_ahinfo();
                weapon->hit_ob(me,target,query("jiali", me)+100);

                p=query("qi", target)*100/query("max_qi", target);

                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;

                msg += "( $n" + eff_status_msg(p) + " )\n";

                message_combatd(msg, me, target);
        } else
        {
                msg += HIG "����$p" HIG "���ݲ��ȣ����ɵ�������$P" HIG "������" +
                       weapon->name() + HIG "��\n" NOR;
                message_combatd(msg, me, target);
        }

        me->reset_action();
        return 1;
}