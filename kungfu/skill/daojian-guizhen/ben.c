#include <combat.h>
#include  <ansi.h>

string name() { return HIM "������" NOR; }

string final1(object me, object target, int damage);

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, type1, type2;
        int ap, dp, lvl;
        object weapon1, weapon2;
        int attack_type;
        mapping prepare;
        int i;
        string* key_pre;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if ((int)query("max_neili", me) < 100000)
                return notify_fail("��������Ϊ����������ʩչ" + name() + "��\n");

        if ((lvl = me->query_skill("daojian-guizhen", 1)) < 200)
                return notify_fail("�㵶��������Ϊ����200�����޷�ʩչ" + name() + "��\n");

        weapon1 = query_temp("weapon", me);
        weapon2 = query_temp("secondary_weapon", me) || query_temp("handing", me);

        if (! objectp(weapon1) || ! objectp(weapon2))
                return notify_fail("��û��ͬʱװ������������ʩչ" + name() + "��\n");

        if (query("consistence", weapon2) <= 0)
                return notify_fail("���" + weapon2->name() + "�Ѿ�����"
                                   "�𻵣��޷�����ʹ���ˡ�\n");

        type1 = query("skill_type", weapon1);
        type2 = query("skill_type", weapon2);

        if ((type1 != "sword" && type1 != "blade")
           || (type2 != "sword" && type2 != "blade"))
                return notify_fail("����ʹ�õ��������ԣ�����ʩչ" + name() + "��\n");

        if ((type1 == "sword" && type2 != "blade")
           || (type1 == "blade" && type2 != "sword"))
                return notify_fail("��û��ͬʱװ������������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("sword") != "daojian-guizhen"
           || me->query_skill_mapped("blade") != "daojian-guizhen")
                return notify_fail("��û�м����������棬����ʩչ" + name() + "��\n");

        if (query("neili", me) < 30000)
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        addn("neili", -30000, me);

        ap = attack_power(me, "blade") +
             me->query_skill("sword", 1) + me->query_skill("blade", 1);
        dp = defense_power(target, "parry") + target->query_skill("sword", 1) +
             target->query_skill("blade", 1);

        message_combatd(HIY "$N" HIY "˫Ŀ΢�գ������޷�����ɲ�Ǽ䣬ɱ����� ����\n"
                     HIC "һ�����⣬" HIM "һ����Ӱ��" HIY "һ�С������ڡ��������׵�ʹ�������⽣���������\n"
                     "�������غ�Х��������$n" HIY "���֡���\n" NOR, me, target);

        if (ap / 2 + random(ap / 2) > dp)
        {
                damage = damage_power(me, "blade");
                damage += damage_power(me, "sword");
                damage+=query("jiali", me);

                message_combatd(HIC "$N" HIC "�������ɳ۶�����ǿ�������ţ�����˼������أ�ֻ��ƴ���ֿ�����\n" NOR, target);

                msg = COMBAT_D->do_damage(me, target, attack_type, damage, 500 + 200 * (userp(me)?0:1),
                                          (: final1, me, target, damage :));
                message_combatd(msg, me, target);
        }
        else
        {
                message_combatd(HIM "$N" HIM "�������ѣ�ȴӲ��ͷƤʩչ�Ṧ���ܣ�������������С�\n" NOR, target);
        }

        // 20%������BUSY
        if (random(5) < 4) me->start_busy(3);
        target->start_busy(3);

        return 1;
}

string final1(object me, object target, int damage)
{
       if (! query_temp("daojian_cimu", target))
       {
               set_temp("block_msg/all", 1, target);
               target->apply_condition("no_perform", 5);
               set_temp("daojian_cimu", 1, target);
               call_out("cimu_end", 20 + random(31), me, target);
               return HIR "$n" HIR "ֻ��˫Ŀ��һ��ǿ���Թ�����ǰһ�ڣ���ʲô"
                       "Ҳ�������ˣ��������޿־塣\n" NOR;
        }
        else
                return "";
}

void cimu_end(object me, object target)
{
        if (target && query_temp("daojian_cimu", target))
        {
                if (living(target))
                {
                        tell_object(target, HIR "��Ȼ�䣬��ǰ�����������������ܿ����ˡ�\n" NOR);
                }
                delete_temp("block_msg/all", target);
               target->clear_condition("no_perform");
                delete_temp("daojian_cimu", target);
        }
        return;
}
