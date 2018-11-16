#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "��������"; }

int perform(object me)
{
        string msg;
        object weapon, target;
        int skill, ap, dp;
        int damage, lvl;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("������ǿ��ֲ���ʹ�ö������ģ�\n");

        lvl = me->query_skill("cuixin-zhang", 1);

        if (lvl < 120)
                return notify_fail("��Ĵ����ƻ��������죡\n");

        if (me->query_skill("force") < 120)
                return notify_fail("����ڹ����̫�ͣ��޷�ʹ���������ġ�\n");

        if( query("neili", me)<800 )
                return notify_fail("��������������޷�ʹ���������ġ�\n");

        msg = HIR "$N" HIR "�������ƣ�����һ����Х��ɲ�Ǽ�˫�ƽ���һ��"
                  "���������ġ����������ھ�ֱ��$n" HIR "��\n"NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "parry");


        if ( ap / 2 + random(ap) > dp )
        {
                addn("neili", -300, me);
                damage = damage_power(me, "strike");
                target->affect_by("cuixin_zhang",
                        (["level":query("jiali", me)+random(query("jiali", me)),
                             "id":query("id", me),
                      "duration" : lvl / 50 + random(lvl / 20) ]));

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50,
                        HIR "ֻ��$n" HIR "�ҽ�һ����ֻ��������"
                        "����Ŀ��������һ�����Ѫ������̱����\n" NOR);

                me->start_busy(2);
        } else
        {
                msg += HIY "$p��$P������ӿ����æ����һԾ���𣬶㿪����������һ����\n" NOR;
                addn("neili", -300, me);
                me->start_busy(3);
        }

        message_combatd(msg, me, target);

        return 1;
}