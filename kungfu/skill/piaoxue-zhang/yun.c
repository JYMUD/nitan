#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIW "�ƺ�����" NOR; }

int perform(object me, object target)
{
        object weapon;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս���жԶ���ʹ�á�\n");

        if( query_temp("weapon", me) ||
            query_temp("secondary_weapon", me) )
                return notify_fail("�������ֲ���ʩչ" + name() + "��\n");

        if (me->query_skill("force") < 200)
                return notify_fail("����ڹ�����Ϊ�������޷�ʩչ" + name() + "��\n");

        if (me->query_skill("piaoxue-zhang", 1) < 150)
                return notify_fail("���Ʈѩ��������Ϊ�������޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<200 || query("max_neili", me)<2000 )
                return notify_fail("��������������޷�ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "piaoxue-zhang")
                return notify_fail("��û�м���Ʈѩ�����ƣ��޷�ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "piaoxue-zhang")
                return notify_fail("��û��׼��ʹ��Ʈѩ�����ƣ��޷�ʩչ" + name() + "��\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "һ�����ȣ���Ȼʩ��Ʈѩ�����ƾ������ƺ����ơ���˲"
              "�������������С�\n" NOR;
        message_combatd(msg, me);

        addn("neili", -100, me);

        // ��һ��
        addn_temp("apply/attack", 300, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // �ڶ���
        addn_temp("apply/attack", 600, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // ������
        addn_temp("apply/attack", 900, me);
        COMBAT_D->do_attack(me, target, weapon, 0);

        // ������������
        addn_temp("apply/attack", -1800, me);

        me->start_busy(1 + random(3));

        return 1;
}
