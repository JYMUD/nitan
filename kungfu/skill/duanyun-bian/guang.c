// wuguang.c ���Ʊ޷��������޹⡹

#include <ansi.h>

inherit F_SSERVER;

string name() { return "�����޹�"; }
int perform(object me, object target)
{
        int damage, power;
        string msg;
        object weapon;
        int ap, dp;

        if( !objectp(target) ) {target = offensive_target(me);}

        if( !target || !target->is_character() || target == me ||
                  !me->is_fighting(target) ||
          !living(target) || query_temp("noliving", target) )
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "whip" )
                return notify_fail(HIR"װ���޲���ʹ�á������޹⡹��\n"NOR);

        if( me->query_skill("duanyun-bian", 1) < 150 )
                return notify_fail("��Ķ��Ʊ޷���򲻹���ʹ����"+name()+"��\n");

        if( me->query_skill("whip",1) < 150 )
                return notify_fail("��ı޷��Ļ���������ʵ��\n");

        if( query("max_neili", me)<600 )
                return notify_fail(RED"��������Ϊ���㣬�޷�����������\n"NOR);

        if( query("neili", me)<600 )
                return notify_fail(HIC"����������������û�ܽ�"+name()+"ʹ�꣡\n"NOR);

        msg=HIC"$N"HIC"һ����ȣ�����һ������"+query("name", weapon)+HIC"���ַɳ���ֻ�������Ӱ���������ƣ��ڱ����գ���ͷ������$n"HIC"������ȥ��\n"NOR;
        ap = attack_power(me, "whip");
        dp = defense_power(target, "force");
        if( ap / 2 + random(ap) > dp )
        {
                if( query("shen", me)>1000000 )
                        power = 1000000;
                else if( query("shen", me)>0 )
                        power=query("shen", me);
                else power = 3000;
                if( query("shen", target)<0 )
                        power=power*2;
                damage = damage_power(me, "whip") + random((int)(power/1000))+(int)(power/3000);
                addn("neili", -600, me);
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(random(3));
                target->receive_damage("qi", damage,me);
                target->receive_wound("qi", damage/2,me);
                target->receive_damage("jing", damage/4,me);
                msg += HIR"$n��æ�����Ծ�������Ƽ��������������Ӱ��ѹ��֮�ƶ�����ȫ������"
                       "�׻���һʱ��֪���˶��ٱޣ���������������\n"NOR;
        } else
        {
                me->start_busy(2);
                msg += HIY"����$n"HIY"һ�����ɣ�һ�¾�Ծ����$N�ı�Ӱ��\n"NOR;
                addn("neili", -200, me);
        }
        msg+=HIC+query("name", weapon)+HIC+"���£������ڵ��ϣ�����ȻŪ�����졣\n"NOR;
        weapon->move(environment(me));
        message_combatd(msg, me, target);

        return 1;
}
