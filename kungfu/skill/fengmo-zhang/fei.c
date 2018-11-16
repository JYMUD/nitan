// lianhuan.c  ��ħ�ȷ�֮��ħ����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��ħ����"; }
void check_fight(object me, object target, object weapon);
private int remove_attack(object me, object weapon);

int perform(object me, object target)
{
        object weapon;
        int skill;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ħ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("fengmo", me) )
                return notify_fail("������ʹ�÷�ħ�����ˣ�\n");

        weapon=query_temp("weapon", me);
        if( !objectp(weapon) || query("skill_type", weapon) != "staff" )
                return notify_fail("���������ȣ�����ܹ�ʩչ��ħ���ȣ�\n");

        if( me->query_skill_mapped("force") != "huntian-qigong" )
                return notify_fail("�����õĲ��ǻ����������޷�����ȷ�ʩչ��ħ���ȣ�\n");

        if( me->query_skill("force") < 100 )
                return notify_fail("��Ļ����������δ�����޷�����ȷ�ʩչ��ħ���ȣ�\n");

        if( me->query_skill("staff") < 100 )
                return notify_fail("���ħ�ȷ���Ϊ���㣬������ʹ�÷�ħ���ȣ�\n");

        if( query("neili", me) <= 300 )
                return notify_fail("�����������ʩչ��ħ���ȣ�\n");
        if( query("jingli", me) <= 200 )
                return notify_fail("��ľ�������ʩչ��ħ���ȣ�\n");

        skill = me->query_skill("staff");

        message_combatd(HIR "\n$N���һ�������м�ת�ŵ�"+weapon->name()+"�����������ڿ��иߵ����һ�����\n\n" NOR,
                        me, target);

        set_temp("fengmo", 1, me);
        set_temp("location", file_name(environment(me)), me);
        addn("neili", -200, me);
        addn("jingli", -100, me);
        me->start_busy(3);
        weapon->unequip();

        set("no_clean_up", 1, weapon);
        me->reset_action();
        call_out("check_fight", 0, me, target, weapon);

        return 1;
}

void check_fight(object me, object target, object weapon)
{
        string msg;
        int damage;

        if ( !objectp( me ) ) return;
                me->reset_action();

        if( query_temp("fengmo", me) >= me->query_skill("fengmo-zhang",1)/100 )
        {
                call_out("remove_attack", 1, me, weapon);
        }
        else if( me->is_fighting() && query_temp("fengmo", me) )
        {

                msg = HIM "\nͻȻ��" + weapon->name() + HIM "������$n��Ȼ��ײ��ȥ��\n" NOR;

                if( random(query("level", me))>query("level", target)/2 )
                {
                        damage = 60 + random(me->query_skill("fengmo-zhang", 1) / 4);
                        target->receive_damage("qi", damage, me);
                        msg += HIR "$nֻ��һ�ɴ�������ǵذ�ѹ��,��ʱ��ǰһ������������,�۵����һ����Ѫ����\n" NOR;


                } else
                {
                        msg += YEL "$n���÷���������һ�ã��ܹ���" + weapon->name() + YEL "��\n" NOR;
                }
                message_combatd(msg, me, target);
                message_combatd(HIR "\n$N����һ������Ʈ�����$n��������βһ�ƣ����������ڰ�շ�����\n\n" NOR,
                                me, weapon);

                addn_temp("fengmo", 1, me);
                call_out("check_fight", 1, me, target, weapon);
        } else
        {
                call_out("remove_attack", 1, me, weapon);

        }
}

int remove_attack(object me, object weapon)
{
        remove_call_out("check_fight");
        if ( !objectp( me ) ) return 1;
        delete_temp("fengmo", me);

        if( file_name(environment(me)) == query_temp("location", me) && living(me) )
        {
                weapon->move(me);
                set("no_clean_up", 0, weapon);
                weapon->wield();
                message_combatd(YEL "\n$N������ǰ����������$n�ջء�\n\n" NOR, me, weapon);
        } else
        {
                weapon->move(query_temp("location", me));
                message("vision", "ֻ�����ϵ�һ����"+weapon->name()+"�����ɰ�յ��䡣\n",
                        environment(weapon), ({weapon}) );
        }

        delete_temp("location", me);

        return 1;
}
