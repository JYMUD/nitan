#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "��ɱ" NOR; }

string final(object me, object targer, int lvl);

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ����ս����ʹ�á�\n");

        if ((int)me->query_skill("yinfeng-dao", 1) < 140)
                return notify_fail("������絶��������죬�޷�ʩչ" + name() + "������\n");

        if ((int)me->query_skill("force") < 260)
                return notify_fail("���ڹ���򲻹�������ʩչ" + name() + "������\n");

        if ((int)query("max_neili", me) < 2400)
                return notify_fail("��������������޷�ʩչ" + name() + "��������\n");

        if ((int)query("neili", me) < 400)
                return notify_fail("��������������޷�ʩչ" + name() + "��������\n");

        if (me->query_skill_mapped("strike") != "yinfeng-dao")
                return notify_fail("��û�м������絶���޷�ʹ��" + name() + "������\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "ʹ�����絶��" HIR "�� ɱ" HIW"���������ƾ��ó�һƬƬ�йǺ�"
              "����쫷�����$nȫ��\n" NOR;

        lvl = me->query_skill("yinfeng-dao", 1);

        ap = attack_power(me, "strike") + me->query_skill("force");
        dp = defense_power(target, "parry") + me->query_skill("dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");

                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 50,
                                           (: final, me, target, lvl :));

                addn("neili", -350, me);
                me->start_busy(1);
        } else
        {
                msg += CYN "����$n��æ��������������㿪����һ����\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int lvl)
{
       target->affect_by("yinfeng_dao",
                       ([ "level"    : query("jiali", me) + random(query("jiali", me)),
                          "id"       : query("id", me),
                          "duration" : lvl / 50 + random(lvl / 20) ]));

       return HIR "���ֻ��$nһ���Һ���ȫ����ҪѨͬʱ�����纮�����У������ιǣ���Ѫ��й������\n" NOR;
}
