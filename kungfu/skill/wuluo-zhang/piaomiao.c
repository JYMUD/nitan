// snowyu piaomiao

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int dam,int attack);
void checking(object me,int dam,int attack);
void checking2(object me,int dam,int attack,int old_dam,int old_att);

string name() { return "����Ʈ��"; }

int perform(object me, object target)
{
        object weapon=query_temp("weapon", me);
        int lv, attack, dam,old_att,old_dam;

        old_att=query_temp("apply/attack", me);
        old_dam=query_temp("apply/unarmed_damage", me);
        lv = (int)me->query_skill("wuluo-zhang", 1);
        attack = lv/4+ random(lv/2);
        dam = lv/2 + random(lv/4);

        if( !target ) target = offensive_target(me);
        else set_temp("offensive_target", target, me);

        if( query("family/family_name", me) != "���ϻ���" && !wizardp(me) )
                return notify_fail(HIW "��Ǵ�������޷�ʩչ������Ʈ�졹��\n" NOR);

        if( !target || !target->is_character() || !me->is_fighting(target) )
                return notify_fail(HIW "����Ʈ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("piaomiao", me) )
                return notify_fail(HIW "������ʹ������Ʈ�죡\n");

        if( me->query_skill("force") < 200 )
                return notify_fail(HIW "����ڹ����δ����\n");

        if( me->query_skill("wuluo-zhang", 1) < 150 )
                return notify_fail(HIW "��Ļ���������������δ���죬�޷�ʩչ����Ʈ�죡\n");

        if( me->query_skill("strike", 1) < 150 )
                return notify_fail(HIW "��Ļ����Ʒ���δ���죬�޷�ʩչ����Ʈ�죡\n");

        if( me->query_skill_mapped("force") != "kurong-changong")
                return notify_fail(HIW "�����õ��ڹ��ķ����ǿ����������޷��ۼ�������\n");

        if( query("max_neili", me) <= 2000 )
                return notify_fail(HIW "���������Ϊ���㣬�޷���������Ʈ�죡\n" NOR);

        if( query("neili", me)<800 )
                return notify_fail(HIW "��������������ھ�������ʩչ����Ʈ�죡\n" NOR);

        if(me->is_busy()) return notify_fail(HIW "����æ����,û�취ʩչ����Ʈ�죡\n" NOR);

        message_vision(HIB"$N�����ڹ��ķ��������������������ƣ���ʱ$N���Ʒ��ף����з���һ��"NOR HIW"����"NOR HIB"��\n" NOR, me);

        addn("neili", -200, me);

        set_temp("piaomiao", 1, me);
        addn_temp("apply/attack", attack, me);
        addn_temp("apply/unarmed_damage", dam, me);

        COMBAT_D->do_attack(me,target,query_temp("weapon", me));

        set_temp("piaomiao", 2, me);
        me->start_call_out( (: call_other, __FILE__, "checking2", me,dam,attack,old_dam,old_att :), 12);
        me->start_call_out( (: call_other, __FILE__, "checking", me,dam,attack :), 1);
        return 1;
}

void checking(object me, int dam, int attack)
{
        int pm, limit;
        object weapon, target;

        weapon=query_temp("weapon", me);
        target=query_temp("offensive_target", me);

        pm=query_temp("piaomiao", me);
        limit = 1 + (int)me->query_skill("wuluo-zhang", 1)/100;

        if( !target || !me->is_fighting(target) ) target = offensive_target(me);

        if( pm > limit || pm > 6 ) {
                message_vision(BLU "\n$N����һ���������ھ��ջص��\n"NOR, me);
                remove_effect(me, dam, attack);
                me->start_busy(1);
                return;
        }

        if( !living(me) || me->is_ghost()  )
        {
                remove_effect(me, dam, attack);
                return;
        }

        if( !me->is_fighting() )
        {
                message_vision(HIM "\n$N�������һԾ�������˾�����ھ���\n"NOR, me);
                remove_effect(me, dam, attack);
                tell_object(me, MAG "\n�㽫��Ϣ������ԭ����״̬��\n\n"NOR);

                return;
        }

        me->start_call_out( (: call_other, __FILE__, "checking", me,dam,attack :), 1);
        return;
}

void remove_effect(object me, int dam, int attack)
{
        if (!me) return;
        addn_temp("apply/attack", -attack, me);
        addn_temp("apply/unarmed_damage", -dam, me);
        delete_temp("piaomiao", me);
        me->start_busy(1);
}

void checking2(object me,int dam,int attack,int old_dam,int old_att)
{
        if( query_temp("piaomiao", me) )
        {
                message_vision(BLU "\n$N����һ���������ھ��ջص��\n"NOR, me);
                me->start_busy(1);
                tell_object(me, MAG "\n�㽫��Ϣ������ԭ����״̬��\n\n"NOR);
                addn_temp("apply/attack", -attack, me);
                addn_temp("apply/unarmed_damage", -dam, me);
                delete_temp("piaomiao", me);
        }

        if( query_temp("apply/attack", me) != old_att )
        {
                set_temp("apply/attack", old_att, me);
        }
        if( query_temp("apply/unarmed_damage", me) != old_dam )
        {
                set_temp("apply/unarmed_damage", old_dam, me);
        }
}
