#include <ansi.h>
#include <combat.h>

string name() { return HIW "���ĵ�" NOR; }

inherit F_SSERVER;

string final(object me, object target, int damage);

int perform(object me, object target)
{
        object du;
        int lvl, lvp, damage, pos;
        int an, dn, ap, dp;
        string name, fire, msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        lvl = me->query_skill("chousui-zhang", 1);
        lvp = me->query_skill("poison");

        if (lvl < 120)
                return notify_fail("��ĳ����Ʋ�����죬����ʩչ" + name() + "��\n");

        if (lvp < 180)
                return notify_fail("��Զ������˽ⲻ��������ʩչ" + name() + "��\n");

        if ((int)me->query_skill("throwing") < 150)
                return notify_fail("�㰵���ַ���򲻹�������ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("strike") != "chousui-zhang")
                return notify_fail("��û�м��������ƣ�����ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("strike") != "chousui-zhang")
                return notify_fail("��û��׼�������ƣ�����ʩչ" + name() + "��\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if( query("neili", me)<300 )
                return notify_fail("�����ڵ���Ϣ���㣬����ʩչ" + name() + "��\n");

        // ����NPC����ֱ��ʩչ
        if( userp(me) && !objectp(du=query_temp("handing", me)) )
                return notify_fail("���������(hand)Щ��ҩ����ʩչ" + name() + "��\n");

        if (objectp(du) && ! mapp(query("poison", du))) 
                return notify_fail("���������õ�" + du->name() + NOR "��"
                                   "�Ƕ�ҩ������ʩչ" + name() + "��\n");

        if( objectp(du) && query("no_shot", du) )
                return notify_fail("��" + du->name() + NOR "�����ȥ����"
                                   "����̫�ðɡ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        // ���ݳ����ƺͶ����Ĳ�ͬ�����費ͬ����Ϣ
        if (lvl >= 200 && lvp >= 270)
        {
                pos = 600 + random(lvp * 4 / 3);
                fire = "һ��Ө��ɫ��" HIG "����" HIR;
        } else
        if (lvl >= 180 && lvp >= 240)
        {
                pos = 400 + random(lvp * 3 / 4);
                fire = "һ�����ɫ�Ļ���";
        } else
        if (lvl >= 150 && lvp >= 210)
        {
                pos = 200 + random(lvp * 2 / 3);
                fire = "�������ɫ��" NOR + RED "����" HIR;
        } else
        {
                pos = 100 + random(lvp / 2);
                fire = "һ�㰵��ɫ��" NOR + RED "����" HIR;
        }

        if (objectp(du))
                name = du->name();
        else
                name = NOR + RED "����";

        msg = HIR "$N" HIR "����һ����ʩ�������ɾ�����" HIW "���ĵ�"
              HIR "����������" + name + HIR "��ಡ��ĵ����˳�ȥ��\n"
              "ȴ����" + name + HIR "������;������ر��ѿ�������" +
              fire + "ƮȻϮ��$n" HIR "��\n" NOR;

        an=query("max_neili", me)+query("neili", me)/4;
        dn=query("max_neili", target)+query("neili", target)/4;

        // �����ж�����������Է�������������Ч
        if (an / 2 + random(an) < dn * 2 / 3)
        {
                msg += WHT "Ȼ��$n" WHT "ȫȻ���������ϣ�����һ�����ѽ�$N"
                       WHT "�����Ļ�������\n" NOR;
                me->start_busy(3);
                addn("neili", -150, me);
        } else
        {
                ap = attack_power(me, "strike") +
                     me->query_skill("poison");

                // ������NPC��������֣��ټ������״��
                if (userp(me))
                        dp = defense_power(target, "dodge") +
                             target->query_skill("martial-cognize")/2;
                else
                        dp = defense_power(target, "dodge") +
                             target->query_skill("parry")/2;

                damage = damage_power(me, "strike") + pos;
                damage+= query("jiali", me);

                if (ap / 2 + random(ap) > dp)
                {
                        msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80,
                                                  (: final, me, target, damage :));
                        me->start_busy(2);
                        addn("neili", -200, me);
                } else
                {
                        msg += CYN "����$n" CYN "���Ʋ����æ��Ų���Σ���"
                               "�ڱܿ���$N" CYN "�����Ļ��档\n" NOR;
                        me->start_busy(3);
                        addn("neili", -100, me);
                }
        }
        message_combatd(msg, me, target);

        // ���Ķ�ҩ����
        if (objectp(du))
        {
                if (du->query_amount())
                {
                        du->add_amount(-1);

                        if (du->query_amount() < 1)
                                destruct(du);
                } else
                        destruct(du);
        }
        return 1;
}

string final(object me, object target, int damage)
{
        object cloth;
        string name;
        int lvp = me->query_skill("poison");

        if( objectp(cloth=query_temp("armor/cloth", target)) )
        {
                if( query("stable", cloth)<100 )
                {
                        addn("consistence", -1-random(10), cloth);

                        if( query("consistence", cloth)<0 )
                                set("consistence", 0, cloth);
                }
                name = cloth->name();
        } else
        if( objectp(cloth=query_temp("armor/armor", target)) )
        {
                if( query("stable", cloth)<100 )
                {
                        addn("consistence", -1-random(10), cloth);

                        if( query("consistence", cloth)<0 )
                                set("consistence", 0, cloth);
                }
                name = cloth->name();
        } else
                name = "����";

        target->affect_by("fire_poison",
                ([ "level"    : lvp * 2 + random(lvp * 3),
                   "id":query("id", me),
                   "duration" : 6 + random(lvp / 30) ]));

        target->receive_damage("jing", damage, me);
        target->receive_wound("jing", damage * 2 / 3, me);
        if( !target->is_busy() )
                target->start_busy(1);

        return  HIR "$n" HIR "һ�����������Ƕ�ʱ����" + name +
                HIR "֮�ϣ�����ȼ��������Ƥ���յ��������졣\n" NOR;
}
