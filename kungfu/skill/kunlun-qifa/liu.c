// liu.c

#include <ansi.h>
#include "/kungfu/skill/eff_msg.h";

#define LIU "��" HIY "���ǵ���" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int skill, i, p;
        int n;
        int my_exp, ob_exp;
        string pmsg;
        string msg;
        object weapon;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/kunlun-qifa/liu", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(LIU "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("handing", me)) || 
            query("skill_type", weapon) != "throwing" )
                return notify_fail("���������в�û�����Ű������޷�ʩչ" LIU "��\n");

        if (weapon->query_amount() < 20)
                return notify_fail("����Ҫ�ж�ʮö���������ʩչ" LIU "��\n");

        if ((skill = me->query_skill("kunlun-qifa", 1)) < 120)
                return notify_fail("������������в���죬����ʩչ" LIU "��\n");

        if ((int)me->query_skill("force") < 200)
                return notify_fail("����ڹ���򲻹�������ʩչ" LIU "��\n");

        if( query("neili", me)<150 )
                return notify_fail("����������������ʩչ" LIU "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg= HIY "$N" HIY "һ����Ц������Ծ�𣬰����ʮָ��Ȼ���ţ����е�"
             + weapon->name() + HIY "��������һ����$n" HIY "��ȥ��\n";

        p=query("qi", target)*100/query("max_qi", target);
        my_exp=query("combat_exp", me)/100+skill*skill/1000*skill;
        ob_exp=query("combat_exp", target)/100;

        if (random(my_exp) > ob_exp)
        {
                n = 5 + random(5);
                if (random(my_exp) > ob_exp) n += 5 + random(5);
                if (random(my_exp / 2) > ob_exp) n += 5 + random(5);
                if (random(my_exp / 4) > ob_exp) n += 5 + random(10);
                if (weapon->query_amount() < n) n = weapon->query_amount();

                msg += "$p" HIY "ֻ����ǰ����һ����������Ӧ��������������$P"
                       HIY+chinese_number(n)+query("base_unit", weapon)+
                       weapon->name() + HIY "��\n" NOR;
                target->receive_wound("qi", skill / 3 + random(skill / 2), me);
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
                msg += NOR + CYN "����$p" CYN "�����ֿ죬�����$P" CYN "����"
                       "������" + weapon->name() + CYN "��\n" NOR;
                message_combatd(msg, me, target);
        }

        weapon->set_amount(0);
        addn("neili", -100, me);
        me->start_busy(2);
        me->reset_action();
        return 1;
}