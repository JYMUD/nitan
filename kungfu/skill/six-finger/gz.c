#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��������"; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap,dp;
        int n;

        if( !target ) target = offensive_target(me);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_mapped("finger") != "six-finger")
                return notify_fail("��û�м��������񽣣��޷�ʩչ���������ڡ���\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ���������ڣ�\n");

        if( (int)me->query_skill("six-finger", 1) < 200 )
                return notify_fail("��������񽣲�����죬����ʹ���������ڡ�\n");

        if( query("max_neili", me)<8000 )
                return notify_fail("����������������񣬲���ʹ�������뷢��\n");

        if( query("neili", me)<1500 )
                return notify_fail("����������̫��������ʹ���������ڣ�\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ���������ڡ���\n");

        if( !living(target) )
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY"$Nʹ����������ǿ�������������ڡ����������˾Ŵ����죬������ӿ���ȣ�\n"
              HIR"ɲʱ�����ɳ��ȸ��͵Ľ�����ָ�������������Ѹ�׼����໥��ײ��֮�ʣ�\n"
              HIW"��Ȼ�㼯��һ��������ƥ�Ľ���������һ����ɫ����,����㼲����$n������\n"NOR,

        ap = attack_power(me, "finger") + me->query_skill("force") + me->query_str()*10;;
        ap+= random(1+query("jiali", me)/2);

        dp = defense_power(target, "dodge") + target->query_skill("force") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                me->start_busy(2);
                if (! target->is_busy())
                        target->start_busy(2 + random(2));

                damage = damage_power(me, "finger");
                damage+=query("jiali", me)*2;
                damage+=query("jianu", me)*(10+random(20));
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        msg += HIM"$N"HIM"����������ת�ĸ�����ʹ�����������˺���ǿ��\n"NOR;
                        damage += damage*n*15/100;
                }

                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                target->receive_damage("jing", damage,me);
                target->receive_wound("jing", damage/2,me);
                addn("neili", -1000, me);

                if( damage < 20 ) msg += HIY"���$n�ܵ�$N�Ľ������У��ƺ�һ����\n"NOR;
                else if( damage < 40 ) msg += HIY"���$n��$N�Ľ������У����١���һ������������\n"NOR;
                else if( damage < 80 ) msg += RED"���$n��$N�Ľ������У��ؿ������ܵ�һ���ش�����������������\n"NOR;
                else msg += HIR"���$n��$N�Ľ������У�����[��]���³�һ����Ѫ�������絾����һ�����ɳ�������\n"NOR;

        } else
        {
                me->start_busy(3);
                msg += CYN"����$p������$P����ʽ������΢΢һ���Ѿ��ܿ���$P�ġ��������ڡ���\n"NOR;
        }
        message_vision(msg, me, target);

        return 1;
}

