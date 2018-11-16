// This program is a part of NITAN MudLIB
// jingsng.c ���ȭ ������ͨ

#include <ansi.h>

inherit F_SSERVER;

void remove_effect(object me, int aamount, int damount);

int perform(object me, object target)
{
        object weapon;
        string msg;
        int d_count, count, qi, maxqi, skill;

        if( query_temp("jingang", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ͨ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query("neili", me)<500 )
                return notify_fail("��������������޷�ʩչ��������ͨ����\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("����ڹ���Ϊ����������ʹ�ô�����ͨ��\n");

        if ((int)me->query_skill("cuff") < 150)
                return notify_fail("���ȭ���������ң��޷�ʹ�ô�����ͨ��\n");

        if (me->query_skill_mapped("cuff") != "jingang-quan")
                return notify_fail("��û�м������ȭ���޷�ʹ�ô�����ͨ��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "ʹ������ȭ�ľ�����������ͨ����������Ȼ���ӣ�\n" NOR;

        qi=query("qi", me);
        maxqi=query("max_qi", me);
        skill = (int) (me->query_skill("jingang-quan", 1) / 3);
        count = me->query_str();
        d_count = (int)me->query_dex() / 2;

        if (qi > (maxqi * 0.4))
        {
                message_combatd(msg, me, target);

                addn_temp("apply/str", count*2, me);
                addn_temp("apply/dex", -d_count, me);
                set_temp("jingang", 1, me);
                me->start_call_out((: call_other, __FILE__, "remove_effect", me, count * 2, d_count :), skill);

                addn("neili", -150, me);
        } else
        {
                msg = HIR "$N" HIR "ƴ����������ʹ���˴���ȭ����"
                      "������, ȫ�����һ����, ����$n" HIR "ͬ���ھ���\n" NOR;
                message_combatd(msg, me, target);
                addn_temp("apply/str", count*9, me);
                set_temp("jingang", 1, me);

                COMBAT_D->do_attack(me,target,query_temp("weapon", me),0);
                set("neili", 0, me);
                addn("max_neili", -10, me);

                msg = HIR "$N" HIR "�þ������һ������, ���һ����Ѫ, һͷ�Ե��ڵأ�\n" NOR;
                message_combatd(msg, me, target);
                addn_temp("apply/str", -(count*9), me);
                delete_temp("jingang", me);
                me->unconcious();
        }
        return 1;
}

void remove_effect(object me, int aamount, int damount)
{
        if( query_temp("jingang", me) )
        {
                addn_temp("apply/str", -aamount, me);
                addn_temp("apply/dex", damount, me);
                delete_temp("jingang", me);
                tell_object(me, "��Ĵ�����ͨ������ϣ��������ջص��\n");
        }
}
