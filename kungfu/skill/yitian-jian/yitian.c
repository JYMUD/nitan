// yitian.c ���콣��

#include <ansi.h>
#include <weapon.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "���콣��"; }

int perform(object me, object target)
{
        object weapon, ob;
        int extra,i,time;
        string msg;

        i = me->query_skill("yitian-jian", 1) + me->query_skill("linji-zhuang", 1);
        time = 5;
        if( !target ) target = offensive_target(me);

        if( !me->is_fighting() )
                return notify_fail("�����콣����ֻ����ս����ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("�����콣���������ý�����ʹ�ã�\n");

        if (me->query_skill_mapped("sword") != "yitian-jian")
                return notify_fail("��û�м������콣������ôʹ�á����콣��������\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("����ڹ���Ϊ������\n");
        if( query("neili", me)<500 )
                return notify_fail("�������������\n");

        if( (int)me->query_skill("yitian-jian",1) < 120 )
                return notify_fail("������콣���������ң��޷�ʹ�á����콣������\n");

        if( !living(target) )
                return notify_fail("�Է��Ѿ������ˣ�����Ҫ��ô�����ɣ���\n");

        msg =HIY "$N" HIY "��Хһ����\n" HIR "�������𡢱����������������£�Ī�Ҳ��ӡ����첻����˭������? \n"
             HIR "��ʱ���Ʊ�ɫ��" HIR "$N" HIR "����������콣��........ \n" NOR;

        message_combatd(msg, me);
        addn_temp("apply/attack", i, me);
        addn_temp("apply/damage", i*2, me);
        {
                msg =  HIC "-----���Ƽ���!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);
                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N�������콣��������Ȼ�ӿ죡\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }

                if( !living(target) ) return 1;
                        msg =  BLU "-----�Ǻ�����!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N�������콣��������Ȼ�ӿ죡\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }
                if( !living(target) ) return 1;
                msg =  HIY "-----���첻��!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N�������콣��������Ȼ�ӿ죡\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }
                if( !living(target) ) return 1;
                msg =  HIR "-----˭������!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);

                if (! me->is_fighting(target))
                {
                        addn_temp("apply/attack", -i, me);
                        addn_temp("apply/damage", -i*2, me);
                        addn("neili", -200, me);
                        msg =HIY "$N�������콣��������Ȼ�ӿ죡\n" NOR;
                        message_combatd(msg, me);
                        me->start_busy(1+random(2));
                        return 1;
                }
                if( !living(target) ) return 1;
                msg =  HIM "-----��������!----- \n"NOR;
                message_combatd(msg,me,target);
                COMBAT_D->do_attack(me,target,weapon,TYPE_REGULAR,msg);
        }
        addn_temp("apply/attack", -i, me);
        addn_temp("apply/damage", -i*2, me);
        addn("neili", -200, me);
        msg =HIY "$N�������콣��������Ȼ�ӿ죡\n" NOR;
        message_combatd(msg, me);
        me->start_busy(1+random(2));
        return 1;
}
