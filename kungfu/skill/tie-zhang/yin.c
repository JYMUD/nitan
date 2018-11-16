#include <ansi.h>
#include <combat.h>

string name() { return HIR "����ĥ" NOR; }

inherit F_SSERVER;

string finala(object me, object target, int damage);
string finalb(object me, object target, int damage);

int perform(object me, object target)
{
        string msg;
        int ap, dp, dd;
        int damage;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("tie-zhang", 1) < 220)
                return notify_fail("�������Ʒ���򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "tie-zhang")
                return notify_fail("��û�м��������Ʒ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "tie-zhang")
                return notify_fail("��û��׼�������Ʒ�������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("���������Ϊ����������ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "ʩ�����ƾ�����" HIR "����ĥ"
              HIW "�������Ʋ��Ű��������Я����������$n"
              HIW "��ȥ��\n" NOR;

        ap=attack_power(me,"strike")+me->query_str()*15;
        dp=defense_power(target,"parry")+target->query_con()*15;
        dd=defense_power(target,"dodge")+target->query_dex()*15;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me,"strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 75,
                                           (: finala, me, target :));
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "�Ƴ���磬��֪"
                       "���к��ż�������������б��������\n" NOR;
        }

        msg += HIR "\n������$N" HIR "����һ���Ʒ��������ϯ"
               "����һ�����ˣ���$n" HIR "��ǰ��Ȼ���䡣\n" NOR;

        if (ap / 2 + random(ap) > dd)
        {
                damage = damage_power(me,"strike");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                           (: finalb, me, target :));
        } else
        {
                msg += CYN "$n" CYN "���ź�Х���������ۼ�$N" CYN
                       "������磬��æ��Ծ��ܿ�����\n" NOR;
        }
        me->start_busy(2 + random(2));
        addn("neili", -400, me);
        message_combatd(msg, me, target);
        return 1;
}

string finala(object me, object target, int damage)
{
        int lvl;
        lvl = me->query_skill("strike");

        target->affect_by("tiezhang_yin",
                       (["level":query("jiali", me)+random(query("jiali", me)/2),
                          "id":query("id", me),
                          "duration" : lvl / 50 + random(lvl / 50) ]));

        return HIW "���Ǽ�$n" HIW "�ѱ�$N" HIW "�����ƾ�����Ҫ"
               "�������ɵû���һ��������֮����\n" NOR;
}

string finalb(object me, object target, int damage)
{
        int lvl;
        lvl = me->query_skill("strike");

        target->affect_by("tiezhang_yang",
                       (["level":query("jiali", me)+random(query("jiali", me)/2),
                          "id":query("id", me),
                          "duration" : lvl / 50 + random(lvl / 50) ]));

        return HIR "ֻ���͵�һ����$N" HIR "��������ܸ����"
               "$n" HIR "�ؿڣ�����������߹ǡ�\n" NOR;
}