
#include <ansi.h>

inherit F_SSERVER;

string name() { return "ǧ��һ��"; }

int perform(object me, object target)
{
        object weapon;
        int skill, skill1;
        int myskill;
        int damageone;
        int damagesub;
        int damage;
        string msg;
        mixed ap,dp;
        int status_flag=0;

        if( !target ) target = offensive_target(me);
        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail("ǧ��һ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) )
                return notify_fail("��δ������������ʹ��ǧ��һ����\n");

        if( me->query_skill("force") < 300 )
                return notify_fail("����ڹ����δ�����޷�ʩչǧ��һ����\n");

        if( me->query_skill("sword") < 300 )
                return notify_fail("��Ľ������δ�����޷�ʩչǧ��һ����\n");

        if( query("max_neili", me) <= 3000 )
                return notify_fail("�����������ʩչǧ��һ����\n");

        if( query("neili", me) <= 1000 )
                return notify_fail("�����������ʩչǧ��һ����\n");

        if( query("jingli", me) <= 1000 )
                return notify_fail("��ľ�������ʩչǧ��һ����\n");

        msg=HIW"\n\n$N������б�����ֳ��������"+query("name", weapon)+"��˳��һ�С�ǧ��һ����!\n"NOR;

        ap=attack_power(me, "sword");
        dp=defense_power(target, "force");
        damage=damage_power(me, "sword");
        damage+= query("jiali", me);

        if ( ap/2 + random(ap) > dp )
        {
                msg+=HIB"$N����ʹ�ü���,ͦ���ͳ���$n���������ȴ���벻�����ƾ���������ң��ۼ����ܲ�����\n"
                        "ֻ�����һ�����죬��ʱ������������������ǿ�ô�վ������ʱ�����ֽ��\n"NOR;
                target->receive_damage("qi", damage,  me);
                target->receive_wound("qi", random(damage/2)+damage/2, me);
                me->start_busy(1+random(2));
                status_flag=1;
        }

        else if( query("int", me)>random(query("int", target)*2) )
        {
                msg+=HIB"$Nһ�����������ֳ���˳�Ʒ�ȥ��$n��̼�ֻ�������������Ʒ�ת�ˣ�վ�ڵ��أ��Ȳ���������\n"
                        "Ҳ�����ƶ��벽�����罩��һ�㡣\n"NOR;
                if (! target->is_busy())
                        target->start_busy(3+random(4));
                me->start_busy(2+random(2));
                status_flag=1;
        }
        else if (query("str", me)>random(query("str", target)*2) )
        {
                msg+=HIC"$Nֻ���Է���ײ�����ľ������಻����Խ��Խǿ,�˳������������һ����\n" NOR;
                addn("neili", -300, me);
                addn("neili", -300, target);
                me->start_busy(1+random(2));
                if (! target->is_busy())
                        target->start_busy(1+random(2));
                status_flag=1;
        }
        else
        {
                msg += HIG"$n��շ�Ծ�����μ�����ʹ�������Ṧ��������������һ�࣬$N�ķ�����������ա�\n"NOR;
                me->start_busy(2+random(2));
        }
        addn("neili", -200, me);

        message_combatd(msg+"\n", me, target);
        if (status_flag==1) COMBAT_D->report_status(target);
        return 1;
}