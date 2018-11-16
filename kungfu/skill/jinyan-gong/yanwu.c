// This program is a part of NITAN MudLIB

#include <combat.h>
#include <ansi.h>

inherit F_SSERVER;

string name() { return "ӥ������"; }

void remove_effect(object me, object target, int lvl1, int lvl2);
void check(object me, object target, int lvl1, int lvl2);

int perform(object me, object target)
{
        string msg;
        int lvl1, lvl2, amount;

        if( !target ) target = offensive_target(me);

        if( !target
        ||      !target->is_character()
        ||      !me->is_fighting(target) )
                return notify_fail("��ӥ�����衹�Ṧ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("jyg-yanwu", me) )
                return notify_fail("���������á�ӥ�����衹�Ṧ������\n");

        /*
        if( me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("�����õ��ڹ��롸ӥ�����衹�Ṧ����������ʽ��㣣�\n");
        */

        if( me->query_skill_mapped("dodge") != "jinyan-gong")
                return notify_fail("�����õ����롸ӥ�����衹��ʽ��ͬ���޷�ʹ�ã�\n");

        if( me->query_skill("dodge") < 134 )
                return notify_fail("�������Ϊ���������޷�ʩչ��ӥ�����衹�Ṧ������\n");

        if( me->query_skill("force") < 59 )
                return notify_fail("����ڹ���Ϊ���δ�����޷�ʩչ��ӥ�����衹�Ṧ������\n");

        if( query("neili", me)<600 )
                return notify_fail("�����������������������ʩչ��ӥ�����衹�Ṧ������\n");

        msg = HIC "$N��Хһ��������Ȼ�ӿ졣$N����Ӱʱ��ӥ�����ա�ʱ��Ⱥ����裬�����ۻ����ң�ɷ�Ǻÿ���\n\n" NOR;

        lvl1 = (int)me->query_skill("dodge");
        lvl2 = (int)me->query_skill("force");

        addn_temp("apply/dex", lvl1/5, me);
        addn_temp("apply/defense", lvl1/2, me);

        addn("neili", -(lvl1+lvl2)/3, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, target, lvl1, lvl2:), (lvl1+lvl2)/15);
        message_combatd(msg, me);
        call_out("check", 1, me, target, lvl1, lvl2);
        set_temp("jyg-yanwu", 1, me);
        return 1;
}

void remove_effect(object me, object target, int lvl1, int lvl2)
{
        if( !me || !query_temp("jyg-yanwu", me))return ;
        if( me->is_fighting())
                message_combatd(HIY "\n$N����һ�������ջء�ӥ�����衹�Ṧ������$n��ʱ�е�ѹ�������˲��١�\n" NOR, me, target);
        else message_combatd(HIY "\n$N���ν�ͣ������һ�������ջ��ˡ�ӥ�����衹�Ṧ������\n" NOR, me, target);
        delete_temp("jyg-yanwu", me);
        addn_temp("apply/dex", -lvl1/5, me);
        addn_temp("apply/defense", -lvl1/2, me);
}

void check(object me, object target, int lvl1, int lvl2)
{
        if (!me) return;
        else if( !me->is_fighting()){
                remove_effect(me, target, lvl1, lvl2);
                return;
            } /*
        }else if( me->query_skill_mapped("dodge") != "jinyangong"){
                message_vision(HIY "\n$N���Ṧ�Ѿ������ǽ��㹦����ӥ�����衹�Ṧ������ʱ��ʧ��\n" NOR, me, target);
                remove_effect(me, target, lvl1, lvl2);
                return;
        }
            */
        call_out("check", 1, me, target, lvl1, lvl2);
}


