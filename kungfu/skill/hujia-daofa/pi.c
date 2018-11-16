// pi.c ����ٵ�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����ٵ�"; }

int perform(object me, object target)
{
        object weapon,weapon2;
        int damage,i;
        string msg,str;
        int ap, dp;
        int n;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("������ٵء�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("���á��������ء����б����е���\n");

        if ((int)me->query_skill("hujia-daofa", 1) < 600)
                return notify_fail("��ĺ��ҵ���������죬����ʹ�á�����ٵء���\n");

        if ((int)me->query_skill("force") < 650)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");

        if( query("neili", me)<800 )
                return notify_fail("����������̫��������ʹ�á��������ء���\n");

        msg = HIC "$N" HIC "һ����Ц��˫�ֽ���" + weapon->name() +
              HIC "����������һ������ȫ����$n" HIC "Ѹ����ȥ��\n\n"NOR;

        //if( query_temp("hu/freeze", me) )
        if (query_temp("lengyue-shengong_freeze", target))
        {
                msg += HIW + weapon->name() +
                HIW "�������ˣ�����˺�ѿ�����ƬƬѩ��Ʈ�䣬��δ�����ȼ���$n" HIW "üë�������˱�����˪��\n\n"NOR;
        }

        ap = attack_power(me, "blade") + me->query_skill("force");
        if (living(target))
                 dp = target->query_skill("force") + defense_power(target, "parry");
        else     dp = 0;

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "blade");
                damage+=query("jiali", me);
                addn("neili", -damage/2, me);
                if( !objectp(weapon2=query_temp("weapon", target)) )
                {
                        /*
                        target->receive_damage("qi",damage,me);
                        target->receive_wound("qi",damage/2 + random(damage/2),me);
                        msg += HIR "ֻ��$n" HIR "һ���ҽУ��ؿڸ�"
                                "����һ���޴�Ŀ��ӣ���Ѫ��ӿ�����\n"NOR;
                        if( query_temp("hu/freeze", me) )
                        {
                                damage /= 3;
                                target->receive_damage("qi",damage,me);
                                target->receive_wound("qi",damage/2 + random(damage/2),me);
                                msg += HIR "\n$n" HIR "����ҡ�μ䣬�о���"
                                        + weapon->name() + HIR +
                                        "��һ��̹ǵĺ����������ڣ��������һ����Ѫ��\n" NOR;
                        }
                        */
                        msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                                       HIR "ֻ��$n" HIR "һ���ҽУ��ؿڸ�"
                                                       "����һ���޴�Ŀ��ӣ���Ѫ��ӿ�����\n" NOR);

                        if (query_temp("lengyue-shengong_freeze", target))
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 33,
                                                           HIB "\n$n" HIB "����ҡ�μ䣬�о���"
                                                           + weapon->name() + HIB +
                                                           "��һ��̹ǵĺ����������ڣ��������"
                                                           "һ����Ѫ��\n" NOR);
                } else
                {
                        /*
                        msg += HIR "$n" HIR "��״�����æ����" + weapon2->name() + HIR +
                                "�ֵ�����$N������ޱߵ�һ���£�" + weapon2->name() + HIR +
                                "�������Ƭ��\n" NOR;
                        for (i = 0;i < 2 + random(5);i++)
                        {
                                msg += HIB "��Ƭ��ɢ�ɽ���������$n�����壡\n" NOR;
                                target->receive_damage("qi",damage/7,me);
                                        target->receive_wound("qi",damage/15 + random(damage/15),me);
                        }
                        msg += HIR + weapon->name() + HIR "����δ������������$n" + HIR +
                                "���ؿڣ�$n����ش�����Ѫ���������\n" NOR;

                        if( !weapon2->is_item_make() )
                        {
                                weapon2->set_name("���ѵ�"+query("name", weapon2));
                                weapon2->move(environment(target));
                                set("value", 0, weapon2);
                                set("weapon_prop", 0, weapon2);
                        }
                        else
                                weapon2->move(environment(target));
                        */
                        if (weapon2->is_item_make() || weapon2->query("damage") > 800 ||
                            weapon2->query("skill_type") == "hammer")
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80,
                                                           HIG "$p" HIG "���" + weapon2->name() + HIG "��ͼ�мܣ�"
                                                           HIG "�����⵶�����Ϭ����͸��" + weapon2->name() +
                                                           HIG "ֱ���$p" HIG "������Ѫ������������Ҫ��ת������\n\n" NOR);
                        else
                        {
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 50,
                                                           HIR "$n" HIR "��״�����æ����" +
                                                           weapon2->name() + HIR + "�ֵ�����$N" HIR
                                                           "�������˫��һ���£�" + weapon2->name() +
                                                           HIR "�������Ƭ��\n\n" NOR);
                                n = 2 + random(5);
                                for (i = 0; i < n; i++)
                                {
                                        msg += (random(2) ? HIB : HIC) + "��Ƭ��ɢ�ɽ���������$n�����壡\n" NOR;

                                        target->receive_damage("qi", damage / 7, me);
                                                target->receive_wound("qi",damage / 15 + random(damage / 15), me);
                                }

                                msg += "\n" + HIY + weapon->name() + HIY "����δ������������$n" + HIY +
                                        "���ؿڣ�$n����ش�����Ѫ���������\n" NOR;

                                weapon2->set_name("���ѵ�" + weapon2->query("name"));
                                weapon2->move(environment(target));
                                weapon2->set("value", 0);
                                weapon2->set("weapon_prop", 0);
                        }
                        target->reset_action();
                        target->receive_damage("qi",damage/2,me);
                                        target->receive_wound("qi",damage/4 + random(damage/4),me);

                        /*
                        if( query_temp("hu/freeze", me) )
                        {
                                damage /= 4;
                                target->receive_damage("qi",damage,me);
                                target->receive_wound("qi",random(damage),me);
                                msg += HIR "\n$n" HIR "����ҡ�μ䣬�о���"
                                        + weapon->name() + HIR +
                                        "��һ��̹ǵĺ����������ڣ��������һ����Ѫ��\n" NOR;
                        }
                        */
                        if (target->query_temp("lengyue-shengong_freeze"))
                                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 200,
                                                           HIB "\n$n" HIB "����ҡ�μ䣬�о���"
                                                           + weapon->name() + HIB +
                                                           "��һ��̹ǵĺ����������ڣ��������"
                                                           "һ����Ѫ��\n" NOR);
                }
                /*
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "( $n"+str+" )\n";
                */
                me->start_busy(3);
                if (! target->is_busy()) target->start_busy(1 + random(2));
        } else
        {
                msg += HIY "$n" HIY "���Ʋ�������ˣ����ձܹ�$N"
                       HIY "����ǿ���ٵأ����������У������ѿ���һ������ӣ�\n"NOR;
                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}
