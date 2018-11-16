#include <ansi.h>
#include <combat.h>

string name() { return HIR "�����" NOR; }

inherit F_SSERVER;

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
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("������ǿ��ֲ���ʹ��" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "tianchan-zhang")
                return notify_fail("��û�м�������Ʒ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "tianchan-zhang")
                return notify_fail("��û��׼��ʹ������Ʒ�������ʩչ" + name() + "��\n");

        lvl = me->query_skill("tianchan-zhang", 1);

        if (lvl < 120)
                return notify_fail("������Ʒ��������죬����ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 150)
                return notify_fail("����ڹ����̫�ͣ�������ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�������������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIR "$N" HIR "һ����Ц���������ƣ�����һԾ����һ��"
                  "Я���綾�ġ�����ơ�����$n" HIR "������£�\n"NOR;

        ap = attack_power(me, "strike") + lvl;
        dp = defense_power(target, "parry");

        if ( ap / 2 + random(ap) > dp )
        {
                addn("neili", -200, me);
                damage = damage_power(me, "strike");
                target->affect_by("tianchan_zhang", ([
                        "level":query("jiali", me)+random(query("jiali", me)),
                        "id":query("id", me),
                        "duration" : lvl / 60 + random(lvl / 30)
                ]));
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 70,
                        HIR "ֻ��$n" HIR "�ҽ�һ������$N" HIR "��һ��"
                        "�ĸ����ţ���ʱ�������ģ����ۡ������һ�����Ѫ��\n" NOR);

                me->start_busy(2);
        } else
        {
                msg += HIY "$p" HIY "��$P" HIY "������ӿ����æ����һԾ���𣬶�"
                       "������һ����\n" NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}