#include <ansi.h>
#include <combat.h>

string name() { return HIR "ȼľ����" NOR; }

inherit F_SSERVER;

void remove_effect(object me, int skill);

int perform(object me, object target)
{
        object weapon;
        int skill;
        string msg;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail(name() + "������õ���ʩչ��\n");

        if( query_temp("zhen_yan", me) )
                return notify_fail(name() + "�޷�����ʩչ��\n");

        if ((int)me->query_skill("ranmu-daofa", 1) < 180)
                return notify_fail("���ȼľ������Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("blade") != "ranmu-daofa")
                return notify_fail("��û�м���ȼľ����Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");


        msg = HIY "$N" HIY "˫�ֳֵ���������������ʩ����ȼľ������ѧ��"
              HIR "ȼľ����" HIY "������ʱ��Х������������һ�������ޱȵ��"

              "��$N" HIY "����ӿ�����ƹ���$N" HIY "��ȥ��\n" NOR;
        message_combatd(sort_msg(msg), me);
        if (me->is_fighting())
                me->start_busy(2);
        skill = me->query_skill("ranmu-daofa",1);
        set_temp("zhen_yan", 1, me);
        addn_temp("apply/attack", skill*2/5, me);
        addn_temp("apply/defense", skill*2/5, me);
        addn_temp("apply/weapon_damage", skill/4, me);
        addn("neili", -400, me);
        me->start_call_out((: call_other, __FILE__, "remove_effect", me, skill :), skill);
        return 1;
}

void remove_effect(object me, int skill)
{
        if( query_temp("zhen_yan", me) )
        {
                addn_temp("apply/attack", -(skill*2/5), me);
                addn_temp("apply/defense", -(skill*2/5), me);
                addn_temp("apply/weapon_damage", -(skill/4), me);
                delete_temp("zhen_yan", me);

                tell_object(me, "�㾭��������Ϣ���ֿ��Լ���ʩչ��" HIR "ȼľ����" NOR "���ˡ�\n");
        }
}

