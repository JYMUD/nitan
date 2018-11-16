// qianzhu-wandushou.c ǧ����
#include <ansi.h>

inherit F_SSERVER;

string name() { return "ǧ����"; }

int perform(object me, object target)
{
        string msg;
        int ap, dp, damage;

        if( !target ) target = offensive_target(me);

        if( !target
        ||        !target->is_character()
        ||        !me->is_fighting(target) )
                return notify_fail("ǧ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if((int)me->query_skill("poison",1) < 100)
                return notify_fail("�㶾��̫��,����ʹ����һ����!\n");

        if((int)me->query_skill("wudu-shengong",1) < 80)
                return notify_fail("���嶾�񹦵Ĺ�����������ʹ��ǧ����!\n");

        if((int)me->query_skill("qianzhu-wandushou",1) < 100)
                return notify_fail("���ǧ��������Ϊ����,������ʹ��ǧ���򶾵ľ���!\n");

        if( query("max_neili", me)<700 )
                return notify_fail("��������Ϊ����, ����ʹ��ǧ����! \n");

        if( query("neili", me)<200 )
                return notify_fail("����������, ����ʹ��ǧ����! \n");

        if( query_temp("qzwd_used", me) )
                return notify_fail("���ʹ�ù�ǧ���򶾣��޷��ڶ�ʱ������۶���! \n");

        msg = HIR "$Nһ����Ц�����������һָ��$n��ü�ĵ�ȥ��\n";
        message_combatd(msg, me, target);

        ap = attack_power(me, "hand");
        dp = defense_power(target, "dodge");

        damage = damage_power(me, "hand") + me->query_skill("poison");
        damage+= query("jiali", me);

        if( ap / 2 + random(ap) > dp )
        {
                msg = HIR"ֻ��һ�ƺ�����$N��ָ��͸����ֻһ����û��$n��ü�ģ�\n" NOR;
                message_combatd(msg, me, target);
                if(target->query_skill("hunyuan-yiqi",1)>me->query_skill("qianzhu-wandushou",1)*12/10&&random(2)==0)
                {
                        msg = RED"$N��Ȼ����ָ����һ�����εľ��������ţ�������ֻ��\n"
                              "$nһ����ȣ�$N��ʱ��һ�����ݰ㱻����Զ����\n" NOR;
                        message_combatd(msg, me, target);

                        msg = RED"$Pֻ����һ����ɽ�ľ���˳ָ���͹�������ֻ����ȫ������ܡ�\n��Ȼ�ؿ�һʹ�����ɡ��ۡ���һ���³�һ�ں�Ѫ��\n" NOR;
                        message_combatd(msg, me);

                        target->receive_wound( "qi",damage, me);
                        addn("neili", -100, me);
                        me->start_busy(2);
              }
              else
              {
                        msg = HIR"$n����һ���Һ�ˤ���ڵأ�������ʹ���������һ�ţ�\n" NOR;
                        message_combatd(msg, me, target);

                        target->receive_wound( "qi",damage, me);
                        target->apply_condition("snake_poison",
                                (int)target->query_condition("snake_poison") + 50 );
                        target->apply_condition("wugong_poison",
                                (int)target->query_condition("wugong_poison") + 50 );
                        target->apply_condition("zhizhu_poison",
                                (int)target->query_condition("zhizhu_poison") + 50 );
                        target->apply_condition("xiezi_poison",
                                (int)target->query_condition("xiezi_poison") + 50 );
                        target->apply_condition("chanchu_poison",
                                (int)target->query_condition("chanchu_poison") + 50 );
                        addn("neili", -100, me);
                        if( !target->is_busy() )
                                target->start_busy(4);
                }
        }
        else
        {
                msg = HIG "����$n����׼����һ����¿����������������һ�С�\n" NOR;
                me->start_busy(4);
                message_combatd(msg, me, target);
                addn("neili", -100, me);
        }

        set_temp("qzwd_used", 1, me);
        remove_call_out ("qzwd_used");
        call_out ("qzwd_used", 6,me);
        return 1;
}
void qzwd_used(object me)
{
        if( !me ) return;
        delete_temp("qzwd_used", me);
}