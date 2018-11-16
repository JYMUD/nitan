// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return WHT "��ʬ��" NOR; }

inherit F_SSERVER;


string final(object me, object target, int damage);

int perform(object me, object target)
{
        object *corpse;
        int lvl, lvp, damage;
        int ap, dp;
        string name, msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( userp(me) && (query_temp("weapon", me )
            || query_temp("secondary_weapon", me)) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        lvl = me->query_skill("chousui-zhang", 1);
        lvp = me->query_skill("poison");

        if (lvl < 140)
                return notify_fail("��ĳ����Ʋ�����죬����ʩչ" + name() + "��\n");

        if (lvp < 200)
                return notify_fail("��Զ������˽ⲻ��������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("throwing") < 180)
                return notify_fail("�㰵���ַ���򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "chousui-zhang")
                return notify_fail("��û�м��������ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang")
                return notify_fail("��û��׼�������ƣ�����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ���Ϣ���㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        /*
        corpse = filter_array(all_inventory(environment(me)),
                             (: base_name($1) == CORPSE_OB
                              && (query("defeated_by", $1) == this_player( )
                              || !query("defeated_by", $1)):));

        if (userp(me) && sizeof(corpse) < 1)
                return notify_fail("�㸽��û�к��ʵ�ʬ�壬����ʩչ" + name() + "��\n");

        // ����ȼ� 250 ���ϵ����� NPC ʩչ����
        if (! userp(me) && lvl < 250 && sizeof(corpse) < 1)
                return notify_fail("�㸽��û�к��ʵ�ʬ�壬����ʩչ" + name() + "��\n");

        if (sizeof(corpse) >= 1)
                name = corpse[0]->name();
        else
        */
                name = "·�ߵ�����";

        msg = WHT "$N" WHT "����ץ��" + name + WHT "������"
              HIR "��ʬ��" NOR + WHT"�������������ϣ���$n"
              WHT "������ȥ��\n" NOR;

        ap = attack_power(me, "strike") +
             me->query_skill("poison", 1);

        // ������NPC��������֣��ټ������״��
        if (userp(me))
                dp = defense_power(target, "dodge") +
                     target->query_skill("martial-cognize")/2;
        else
                dp = defense_power(target, "dodge") +
                     target->query_skill("parry", 1)/2;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "strike");
                damage+= query("jiali", me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
                                          (: final, me, target, damage :));
                me->start_busy(2);
                addn("neili", -300, me);
        } else
        {
                msg += CYN "����$n" CYN "���Ʋ����æ��Ų���Σ���"
                       "�ڱܿ���$N" CYN "������ʬ�塣\n" NOR;
                me->start_busy(3);
                addn("neili", -200, me);
        }
        message_combatd(msg, me, target);

        /*
        if (sizeof(corpse) >= 1)
                destruct(corpse[0]);
        */

        return 1;
}

string final(object me, object target, int damage)
{
        int lvp = me->query_skill("poison");

        target->affect_by("corpse_poison",
                ([ "level"    : lvp * 10 + random(lvp * 15),
                   "id":query("id", me),
                   "duration" : 20 + random(lvp / 20) ]));

        target->receive_damage("jing", damage, me);
        target->receive_wound("jing", damage / 2, me);

        return  HIR "$n" HIR "ֻ��һ�ɶ����������֮��������"
                "�ܣ��ٱ�ʬ��������С�\n" NOR;
}