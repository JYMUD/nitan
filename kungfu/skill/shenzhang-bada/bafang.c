// This program is a part of NITAN MudLIB
// bafang.c ����˷�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����˷�"; }

int perform(object me, object target)
{
        object weapon;
        string msg;
        int ap, dp;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("������˷���ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("�������ֲ���ʹ�á�����˷�����\n");

        if (me->query_skill("force") < 300)
                return notify_fail("����ڹ�����Ϊ����������ʹ����һ������\n");

        if (me->query_skill("shenzhang-bada", 1) < 200)
                return notify_fail("������ư˴���Ϊ������Ŀǰ����ʹ�á�����˷�����\n");

        if( query("neili", me)<700 )
                return notify_fail("��������������޷�ʹ�á�����˷�����\n");

        if (me->query_skill_mapped("strike") != "shenzhang-bada")
                return notify_fail("��û�м������ư˴򣬲���ʹ�á�����˷�����\n");

        msg = HIY "$N" HIY "���������һ���������һ����ȫ�������޷��Թģ�"
                   HIY "Ȼ����������һ�ݣ��Ӹ����£�˫�Ʒ������£�ɲ�Ǽ䣬�ھ����������"
                   "����$n" + HIY "��\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*20;
        dp=defense_power(target,"parry")+target->query_dex()*20;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                addn("neili", -350, me);

                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 50);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -100, me);
                me->start_busy(3);
                msg += CYN "����$p" CYN "������$N" CYN "����ͼ������"
                       CYN "���Ʈ�����ɣ��������һ������һ����\n"NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}