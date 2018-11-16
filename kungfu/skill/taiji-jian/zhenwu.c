// zhenwu.c �����а

#include <ansi.h>
#include <combat.h>

string name() { return "�����а"; }

inherit F_SSERVER;

string final(object me, object target, int damage);
int perform(object me, object target)
{
        object weapon;
        int damage;
        string msg;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        if (! target || ! me->is_fighting(target))
                return notify_fail("��" + name() + "��ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");

        if ((int)me->query_skill("taiji-jian", 1) < 250)
                return notify_fail("���̫������������죬����ʹ�á�" + name() + "����\n");

        if ((int)me->query_skill("force", 1) < 250)
                return notify_fail("����ڹ���Ϊ�����ߣ��������á�" + name() + "����\n");

        if ((int)me->query_skill("taiji-shengong", 1) < 250)
                return notify_fail("���̫������Ϊ�����ߣ��������á�" + name() + "����\n");

        if( query("neili", me)<2000 )
                return notify_fail("��������������������ʹ�á�" + name() + "����\n");

        if (me->query_skill_mapped("sword") != "taiji-jian")
                return notify_fail("��û�м���̫������������ʹ�á�" + name() + "����\n");

        msg = HIY "$N" HIY "��Ŀ���������ת��һ�г���̫������ġ�" HIW + name() +
              HIY "������ʹ�������з��ӹ��棬����ƽ�����棬\nʵ��㼯�����֮���������"
              HIY "������" + weapon->name()+ "�û�������̫����Ȧ������ǵص�ѹ��$n��\n" NOR;

        ap = attack_power(me, "sword");
        dp = defense_power(target, "parry");


        if( query("id", weapon) == "zhenwu jian") ap+=ap*(20+random(10))/100;
        if (target->is_bad()) ap += ap / 2;

        /*
        if (me->is_not_good()) ap = ap / 2;
        if (me->is_bad()) ap = ap / 3;
        if (target->is_good()) ap = ap * 4 / 5;
        */

        if( wizardp(me) && query("env/combat_test", me) )
        {
                tell_object(me, HIY "AP: " + ap + ". DP: " + dp + ".\n" NOR);
        }
        if (ap / 2 + random(ap*4/3) > dp)
        {
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);

                addn("neili", -500, me);
                //tell_object(me, HIC "DAMAGE: " + damage + ".\n" NOR);
                //msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 285,
                //                           HIR "\n$p" HIR "��$P���������壬��Ȼ�ŵù˲����мܣ�"
                //                           "��һ�����ؿ���С���Ữ������\n��ʱ��Ѫ�ɽ���\n" NOR);
                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 285,
                                           (: final, me, target, damage :));
                me->start_busy(2);
        } else
        {
                msg += HIG "����$p" HIG "������$P" HIG "����ͼ����"
                       "����㣬ȫ��Ӧ�����硣\n" NOR;
                addn("neili", -50, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}

string final(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 3, me);
        target->receive_wound("jing", damage / 6, me);
        return  HIY "���$p" HIY "û�а����������ϣ���"
                "��Ӧ��һ�У�ȴ��$P" HIY "���ƺ�Ȼһ��"
                "��\n������ǧ���������������߷緶��\n"
                HIR "$p" HIR "����ʧ�룬���ڵ�������$P"
                HIR "��һ������Ҫ������Ѫ�������Ҳ��̶ã�\n" NOR;
}
