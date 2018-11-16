#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIR "����" + HIY + "��" + HIR "����" NOR; }

int perform(object me, object target)
{
        string type1, type2, msg;
        object weapon1, weapon2;
        int ap, dp, damage;
        int fmsk = me->query_skill("daojian-xiaotianwai", 1);
        int da_add;
        int i, count;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        
        if( me->is_busy() )
                return notify_fail("����æ���ء�\n");

        if( !query("reborn/times", me) ) 
                return notify_fail("����δת���������޷�ʹ��" + name() + "��\n"); 
                
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

        if (me->query_skill("daojian-guizhen", 1) < 1000)
                return notify_fail("��Ľ�����ȼ�����������ʩչ" + name() + "��\n");

        if (query("neili", me) < 2000)
                return notify_fail("�����ڵ���������������ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        fmsk = me->query_skill("daojian-xiaotianwai", 1);
        ap = attack_power(me, "blade") + me->query_skill("sword-cognize", 1);
        dp = defense_power(target, "force");

        damage = damage_power(me, "blade");
        damage+= damage_power(me, "sword");
        damage+= query("jiali", me);

        msg = HIY "$N" HIY "��" + weapon1->name() + HIY "��" +
              weapon2->name() + HIY "��������ǰ����ת��" + name() + HIY "�������ھ��纣Х�㱬����\n" NOR;

        msg += HIY "�������ƶ�����˰���ɫ���������������һ��һľ��ɢ������������������" HIY "$N" HIY "ǿ���ɱ�������ꡢ���⣬\n"
                   "��˲��ȫ����������һ����������" + weapon1->name() + HIY "��" + weapon2->name() + HIY "�Ĺ����������赲��\n"
                   HIY"$N" HIY "��ǰ�Ķ���������ȫ����һ˲�䱻���飬�ȿ���������գ��ƺ���ն�������룬ͱ����һ��������\n"
                   "��һ�ˡ�һ����һ����������ģ��ݺݵķ�����"HIY "$n"HIY"��\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIR "$n" HIR "�������$N" HIR "���������ƣ��������书��������"
                       "�����⣬�мܶ�ʱɢ�ң�ȫȻ��������\n" NOR;

                target->receive_damage("jing", damage / 2);
                target->receive_wound("jing", damage / 3);

                msg += COMBAT_D->do_damage(me, target, SPECIAL_ATTACK, damage, 100,
                                           HIR "$n" HIR "ʧ�����ǣ� һʱ����֪�ֵ�"
                                           "����$N" HIR "һ������Ҫ������Ѫ�Ľ���"
                                           "�˲��ᡣ\n" NOR);
                ap += ap / 5;
                damage += damage / 3;
        } else
        {
                msg += HIG "$n" HIG "��$N" HIG "ɱ�����ǣ�˿����"
                       "�Ҵ��⣬��æ��������Ŭ�����ܸ��š�\n" NOR;
        }

        msg += HIW "\nͻȻ��$N" HIW "����һչ������" + weapon1->name() +
               HIW "����һ����վ��һ���뻡��ֱ��$n" HIW "��ȥ��\n" NOR;

        if (me->query_skill("zuoyou-hubo", 1) > 200)
        {
                damage = damage + damage / 3;
                da_add = (80 + fmsk / 15) + (80 + fmsk / 15) / 3;
        }

        if (ap / 2 + random(ap) > dp)
        {

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, da_add,
                                           HIR "$n" HIR "�����ֵ���ȴ�����мܵ�ס"
                                           "����$N" HIR "һ�л���Ҫ������Ѫ�Ĵ���"
                                           "����\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "��֪��һ�е���������æ����"
                       "������С�Ĳ��У�˿������\n" NOR;
        }

        msg += HIW "\n����$N" HIW "�ֽ�����" + weapon2->name() +
               HIW "��$n" HIW "ƽƽ�ݳ�����ʽ���Ƽ򵥣�ȴ�̲���"
               "�����ɱ�š�\n" NOR;

        if (ap / 2 + random(ap) > dp)
        {
                /*
                weapon1->move(me, 1);
                weapon2->wield();
                */

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, da_add,
                                           HIR "$n" HIR "ֻ���ۻ����ң�ȫȻ�޷���"
                                           "���Ȼ���$N" HIR "һ�����У����һ����"
                                           "Ѫ��\n" NOR);
                /*
                weapon2->move(me, 1);
                weapon1->wield();
                set_temp("handing", weapon2, me);
                */
        } else
        {
                msg += CYN "$n" CYN "��֪��һ�е���������æ����"
                       "������С�Ĳ��У�˿������\n" NOR;
        }

        if( fmsk >= 100 && query("neili", me)>1000 )
        {
                msg += HIC "\n====================" HIY" ��" HIR "  ��" HIG "  Х" HIW "  ��  ��" HIC " ====================" NOR;
                msg += HIC "\n��Ȼ�䣬$N" HIC "����" + weapon1->name() + HIC "��" + weapon2->name() + HIC +
                           "���������ĳ�Х�������������⻪������ʣ���������ͻ�䣬\nת�ۼ䣬����������߻���������$n" HIC "��\n" NOR;

                if (ap / 2 + random(ap)  + fmsk / 2 > dp)
                {
                        damage *= 2;
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 350,
                                           HIR "$n" HIR "ɲ�Ǽ�Ŀ�ɿڴ���ȫȻ�޷�����"
                                           "��ǰ֮����$N" HIR "һ�����У����������"
                                           "Ѫ��\n" NOR);
                        addn("neili", -500, me);
                        
                        count = me->query_skill("martial-cognize", 1) + me->query_skill("sword-cognize", 1);
                        count /= 1000;
                        if (! target->is_busy())
                                target->start_busy(8 + random(count));
                        
                        target->set_weak(3 + random(count));
                } else
                {
                        msg += CYN "$n" CYN "˿��������ǰ������Ӱ�죬�������㣬�ܿ���һ�С�\n" NOR;
                }
        }
        
        count = 0;
        ap = attack_power(me, "blade");
        dp = defense_power(target, "parry");

        if (ap / 2 + random(ap) > dp)
        {
                msg += HIW "$n" HIW "ֻ���������⽣Ӱ���Լ���"
                       "�����ٸ��ۻ����ң��ĵ׺�����Ȼ������\n" NOR;
                count = ap / 15;
                set_temp("daojian-guizhen/max_pfm", 1, me);
        } else
        {
                msg += HIG "$n" HIG "ͻȻ�����Լ����ܽԱ�����"
                       "��Ӱ����Χ����֪�����æС���мܡ�\n" NOR;
                count = ap / 30;
        }
        message_combatd(msg, me, target);
        
        addn("neili", -500, me);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/damage", count*2/3, me);
        addn_temp("apply/avoid_locked", 50, me);
        for (i = 0; i < 12; i++)
        {
                if (! me->is_fighting(target))
                        break;

                COMBAT_D->do_attack(me, target, (random(2) ? weapon1:weapon2), 100);
        }
        addn_temp("apply/attack", -count, me);
        addn_temp("apply/damage", -count*2/3, me);
        addn_temp("apply/avoid_locked", -50, me);
        delete_temp("daojian-guizhen/max_pfm", me); 
        me->start_busy(3 + random(2));
        
        message_combatd(msg, me, target);
        return 1;
}
