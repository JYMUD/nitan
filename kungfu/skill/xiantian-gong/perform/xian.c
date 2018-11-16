// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIY "�������" NOR; }

inherit F_SSERVER;

string attack1(object me, object target, int damage);
string attack2(object me, object target, int damage);

int perform(object me, object target)
{
        object weapon;
        int ap, dp, damage;
        string msg;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        
        if( !query("reborn/times", me) )
                return notify_fail("����δת���������޷�ʹ��" + name() + "��\n"); 

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(name() + "ֻ�ܿ���ʩչ��\n");

        if ((int)me->query_skill("xiantian-gong", 1) < 1000)
                return notify_fail("������칦��Ϊ����������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("���������Ϊ���㣬����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "xiantian-gong")
                return notify_fail("��û�м������칦Ϊȭ�ţ�����ʩչ" + name() + "��\n");

        if (me->query_skill_mapped("force") != "xiantian-gong")
                return notify_fail("��û�м������칦Ϊ�ڹ�������ʩչ" + name() + "��\n");

        if (me->query_skill_prepared("unarmed") != "xiantian-gong")
                return notify_fail("��û��׼��ʹ�����칦������ʩչ" + name() + "��\n");

        if( query("neili", me)<2000 )
                return notify_fail("�����ڵ��������㣬����ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "\n$N" HIW "ʩ�������������ʱ����Բʮ�����֮����������"
              "��������˫�����ƴ�������һ�ӣ�������ӿ��$n" HIW "��\n" NOR;

        addn_temp("apply/ap_power", 30, me);
        ap=attack_power(me,"unarmed")+me->query_con()*20;
        dp=defense_power(target,"parry")+target->query_dex()*20;
        
        damage = damage_power(me, "unarmed");
        damage+= query("jiali", me);
        damage *= 3;
        
        if (ap / 2 + random(ap) > dp)
        {
                if( !target->is_busy() )
                        target->start_busy(2);
                
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100,
                                                    (: attack1, me, target, damage :));
        } else
        {
                msg += CYN "$n" CYN "����һ������������һ�����Ǳ��ض�����С�\n" NOR; 
        }
        
        message_combatd(msg, me, target); 
        msg = HIW "�����ţ�$N" HIW "һ����Х����������$n"HIW"���£��Ӵ�����֮����ӿ��ѹ��$n" HIW "��\n" NOR;
        if (ap / 2 + random(ap) > dp)
        {
                if( !target->is_busy() )
                        target->start_busy(2);
                        
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 500,
                                                   (: attack2, me, target, damage :));
        } else
        {
                msg += CYN "$n" CYN "����һ������������һ�����Ǳ��ض�����С�\n" NOR; 
        }
        
        message_combatd(msg, me, target);
        addn_temp("apply/ap_power", -30, me);
        addn("neili", -1000, me);
       
        me->start_busy(3 + random(2));

        return 1;
}

string attack1(object me, object target, int damage)
{
        string msg;

        target->receive_damage("jing", damage);
        target->receive_wound("jing", damage / 2);
                
        msg = HIR "���$N" HIR "��������$n" HIR "��"
              "�ڣ����������ʱ���Զ��룬���������"
              "����Ѫ��\n" NOR;
        
        //if (random(2) != 1) return msg;

        set("neili", 0, target);

        msg += WHT "$n" WHT "ֻ�е��ؿ�һʹ��ȫ������������˿�������ޱȡ�\n" NOR;

        return msg;
}

void clear_no_exert(object target)
{
        if( !objectp(target) ) return;

        target->clear_condition("no_exert");
}

string attack2(object me, object target, int damage)
{
        string msg;

        msg = HIR "���$N" HIR "��������$n" HIR "��"
              "�ڣ����������ʱ������룬���������"
              "����Ѫ��\n" NOR;

        //if (random(2) != 1) return msg;
        //if( target->query_condition("no_exert") ) return msg;

        target->apply_condition("no_exert", 10);
        call_out("clear_no_exert", 25, target);
        
        msg += WHT "$n" WHT "�е�����������Ϣ���ң�˵������ʹ�ࡣ\n" NOR;

        return msg;
}
