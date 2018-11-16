#include <ansi.h>
#include <combat.h>

#define HUAN "��" HIR "�öݺ���" NOR "��"

inherit F_SSERVER;

#include "/kungfu/skill/eff_msg.h";

int perform(object me, object target)
{
        int skill, i, p;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/pidi-shenzhen/huan", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUAN "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("���������в�û�����Ű�����\n");

        if (weapon->query_amount() < 20)
                return notify_fail("����Ҫ�ж�ʮö��������ʩչ" HUAN "��\n");

        if ((skill = me->query_skill("pidi-shenzhen", 1)) < 140)
                return notify_fail("��ıٵ����벻����죬����ʩչ" HUAN "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�������ʩչ" HUAN "��\n");

        if( query("neili", me)<150 )
                return notify_fail("�������������㣬����ʩչ" HUAN "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "ֻ��$N" HIR "һ����Ц�����弱����ת����ʱ���������е�"
              + weapon->name() + HIR "��������˷����˳�ȥ��\n" NOR;

        my_exp=query("combat_exp", me)/100+skill*skill/1000*skill;
        ob_exp=(query("combat_exp", target)/100);

        if (random(my_exp) > ob_exp)
        {
                n = 4 + random(4);
                if (random(my_exp) > ob_exp) n += 4 + random(4);
                if (random(my_exp / 2) > ob_exp) n += 4 + random(4);
                if (random(my_exp / 4) > ob_exp) n += 4 + random(8);
                if (weapon->query_amount() < n) n = weapon->query_amount();

                msg += HIR "$n" HIR "��ʱֻ��������â��������Լ�Ϯ������"
                       "����������������$P" HIR + chinese_number(n) +
                       query("base_unit", weapon)+weapon->name()+HIR
                       "��\n" NOR;
                target->receive_damage("qi", skill + random(skill), me);
                target->receive_wound("qi", skill / 2 + random(skill / 2), me);
                p=query("qi", target)*100/query("max_qi", target);
                while (n--)
                {
                        COMBAT_D->clear_ahinfo();
                        weapon->hit_ob(me, target,
                                       query("jiali", me)+100+n*15);
                }

                if (stringp(pmsg = COMBAT_D->query_ahinfo()))
                        msg += pmsg;

                msg += "( $n" + eff_status_msg(p) + " )\n";
                message_combatd(msg, me, target);
        } else
        {
                msg += CYN "$p" CYN "����$P" CYN "�������أ����Ҵ��⣬��"
                       "������㿪������" + weapon->name() + CYN "��\n" NOR;
                message_combatd(msg, me, target);
        }

        weapon->set_amount(0);
        addn("neili", -100, me);
        me->start_busy(2);
        me->reset_action();
        return 1;
}