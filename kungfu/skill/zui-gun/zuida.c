// This program is a part of NITAN MudLIB
// zuida.c ������� �������

#include <ansi.h>

inherit F_SSERVER;

string name() { return "�������"; }
void remove_effect(object me, int amount, int amount1);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int count, count1, cnt, skill;

        if (! me->is_fighting())
                return notify_fail("���������ֻ����ս����ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "club" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if( query_temp("zg_zuida", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ������ڹ������ˣ�û�и��������ʹ�ð������\n");

        if ((int)me->query_str() < 25)
                return notify_fail("�����ڵı���������Ŀǰ����ʹ�ô˾�����\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���򲻹�������ʩչ���������\n");

        if ((int)me->query_skill("club") < 100)
                return notify_fail("��Ĺ�����Ϊ����������ʹ�ô��������\n");

        if( query("neili", me)<500 )
                return notify_fail("����������㣡\n");

        msg = HIY "$N" HIY "ʹ����������ľ�����������򡹣���"
              "����Ȼ����, ����Ȼ�ӿ죡\n" NOR;

        message_combatd(msg, me, target);
        skill = me->query_skill("zui-gun",1);
        cnt =(int)( (int)me->query_condition("drunk") / 30);
        if( cnt > 50 ) cnt = 50;
        count=query("str", me)*random(cnt+2);
        count1=query("dex", me)*random(cnt+2);

        addn_temp("apply/str", count, me);
        addn_temp("apply/dex", count1, me);
        set_temp("zg_zuida", 1, me);

        me->start_call_out((: call_other, __FILE__, "remove_effect",
                           me, count, count1 :), skill / 3);
        me->start_busy(2);

        addn("neili", -150, me);
        return 1;
}

void remove_effect(object me, int amount, int amount1)
{
        if( query_temp("zg_zuida", me) )
        {
                addn_temp("apply/str", -amount, me);
                addn_temp("apply/dex", -amount1, me);
                delete_temp("zg_zuida", me);
                tell_object(me, "��İ�������˹���ϣ��������ջص��\n");
        }
}
