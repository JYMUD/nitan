// wuji.c ��Ԫ�޼�

#include <ansi.h>
#include <combat.h>

string name() { return HIW "��Ԫ�޼�" NOR; }

inherit F_SSERVER;

int perform(object me, object target)
{
        string msg;
        object weapon;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        skill = me->query_skill("hunyuan-zhang", 1);

        if (skill < 120)
                return notify_fail("��Ļ�Ԫ�Ƶȼ�����, ����ʩչ" + name() + "��\n");

        if (me->query_skill("force", 1) < 120)
                return notify_fail("���ڹ���Ϊ�������޷�ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1400 )
                return notify_fail("��������Ϊ���㣬�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<240 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "hunyuan-zhang")
                return notify_fail("��û��׼��ʹ�û�Ԫ�ƣ��޷�ʩչ" + name() + "��\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIC "$N" HIC "ŭ��һ����Ǳ�ˡ�" HIW "��Ԫ�޼�" HIC "����˫ȭЮ"
              "�������ķ���֮����$n" HIC "��ȥ��\n" NOR;

        ap = attack_power(me, "strike");
        dp = defense_power(target, "force");
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -220, me);
                damage = damage_power(me, "strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           HIR "$n" HIR "ֻ������ǰһ���ʹ�����ۡ���һ"
                                           "�����һ����Ѫ��\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                addn("neili", -120, me);
                msg += CYN "ֻ��$n" CYN "���Ų�æ������һ�������"
                       "��$N" CYN "�ı�ɱһ����\n" NOR;
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}