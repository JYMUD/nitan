// This program is a part of NITAN MudLIB
// shengang.c ���������������

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        object weapon;
        string msg;
        int d_count, count, qi, maxqi, skill;

        weapon=query_temp("weapon", me);

        if( !query("can_exert/huntian-qigong/shengang", me) )
                return notify_fail(HIG "�㻹û���ܵ�ĳ�˵�ָ�㣬������ʹ�����ֹ���\n" NOR);

        if( query_temp("shield", me) )
                return notify_fail(HIG "���Ѿ����˻�Ԫ����ˡ�\n" NOR);

        if( query("neili", me)<200 )
                return notify_fail("���������������\n");

        if ((int)me->query_skill("huntian-qigong", 1) < 150)
                return notify_fail("��Ļ�����������Ϊ����������ʹ�û�Ԫ���! \n");

        msg = WHT "$Nʹ������������ѧ����Ԫ�����һ�ɰ����Զ������跢ɢ���£�ȫ�������ڰ�ɫ�����У�\n" NOR;

        qi=query("qi", me);
        maxqi=query("max_qi", me);
        skill = (int) (me->query_skill("huntian-qigong", 1) / 6);
        count = me->query_str();
        d_count = (int)me->query_dex() / 2;

        if (qi > (maxqi * 0.4))
        {
                message_combatd(msg, me, target);
                addn_temp("apply/damage", skill*20, me);
                addn_temp("apply/unarmed_damage", skill*20, me);
                addn_temp("apply/attack", skill*2, me);
                addn_temp("apply/defense", skill*2, me);
                addn_temp("apply/dex", skill, me);
                set_temp("shield", 1, me);
                me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill * 2 :), skill);

                addn("neili", -150, me);
        } else
        {
                msg = HIR "$Nƴ�����������������Ԫ������Լ�����̫�أ�û�ܳɹ�!\n" NOR;
                message_combatd(msg, me, target);
        }
        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("shield", me) )
        {
                message_combatd("��ɫ�ı�����ɢȥ��$N�����β����ֱ�������ɼ���\n", me);
                addn_temp("apply/damage", -amount*10, me);
                addn_temp("apply/unarmed_damage", -amount*10, me);
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/dex", -amount/2, me);
                addn_temp("apply/defense", -amount, me);

                delete_temp("shield", me);
                tell_object(me, HIY "��Ļ�Ԫ���������ϣ��������ջص��\n" NOR);
        }
}
