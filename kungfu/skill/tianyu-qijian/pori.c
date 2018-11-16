// This program is a part of NITAN MudLIB
// pori.c �Ż�����

#include <ansi.h>
#include <combat.h>
inherit F_SSERVER;

string name() { return "�Ż�����"; }

int perform(object me, object target)
{
        object weapon;
        int damage, p, i, wadd;
        string msg;
        int ap, dp;

        weapon=query_temp("weapon", me);

        if ( ! target )
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if ( ! target || ! me->is_fighting(target) )
                return notify_fail("���Ż����ա�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( !weapon || query("skill_type", weapon) != "sword" )
                return notify_fail("������û�н����޷�ʹ�á��Ż����ա�������\n");

        if ( me->query_skill_mapped("sword") != "tianyu-qijian"
                || me->query_skill_mapped("parry") != "tianyu-qijian" )
                return notify_fail("��û���������潣����ôʩչ���Ż����ա�������\n");

        if( query("unique", weapon) )
                return notify_fail("����������һ���������޷����������飡\n");

        if ( me->query_skill("tianyu-qijian", 1) < 160 )
                return notify_fail("��������潣����㣬ʹ�������Ż����ա�������\n");

        if ( me->query_skill("sword", 1) < 140 )
                return notify_fail("��Ļ���������������죬ʹ�������Ż����ա�������\n");

        if( query("09g/ring", me) == "li" )
        {
                if ( me->query_skill("xiaowuxiang", 1) < 140 )
                        return notify_fail("���С���๦��Ϊ���㣬ʹ�������Ż����ա�������\n");
                if ( me->query_skill_mapped("force") != "bahuang-gong" )
                        return notify_fail("��û��ʹ��С���๦���޷�ʹ�á��Ż����ա�������\n");
        }

        else
        {
                if ( me->query_skill("bahuang-gong", 1) < 140 )
                        return notify_fail("��İ˻�����Ω�Ҷ�����Ϊ���㣬ʹ�������Ż����ա�������\n");
                if ( me->query_skill_mapped("force") != "bahuang-gong" )
                        return notify_fail("��û��ʹ�ð˻�����Ω�Ҷ��𹦣��޷�ʹ�á��Ż����ա�������\n");
        }

        if ( me->query_str() < 28 )
                return notify_fail("�������������ǿ����ʹ�������Ż����ա�������\n");

        if ( me->query_dex() < 30 )
                return notify_fail("��������������飬�޷�ʩչ���Ż����ա�������\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ���㣬�޷�ʹ�á��Ż����ա�������\n");

        if( query("neili", me)<1000 )
                return notify_fail("��������������޷��������г�����\n");


        msg = HIY"\n$N����һ��������"+weapon->name()+HIY"��ʱ��������ϣ�������Ƭ�����㼤����$n��\n"NOR;

        //Damage is also decided by how many times the player used this perform
        i=query("09g/pori", me);

        if ( i > me->query_skill("tianyu-qijian") )
                i = me->query_skill("tianyu-qijian");

        i-=query("age", me);

        ap = attack_power(me, "sword");
        dp = defense_power(target, "force");
        if( ap / 2 + random(ap) > dp )
        {
                me->start_busy(2);
                if( !target->is_busy() )
                        target->start_busy(1);
                addn("neili", -300, me);
                damage = damage_power(me, "sword");
                damage+= query("jiali", me);
                damage+= i*20;

                //Damage is also decided by how strong the weapon is
                wadd=(query("weapon_prop/damage", weapon)+1);
                damage = damage+(random(wadd)+wadd)*2;

                if( query("neili", me)>query("neili", target)*2 )
                        damage += random(damage);

                if ( damage > 2000 )
                        damage = damage+random(me->query_skill("sword", 1));

                if ( damage < 200 )
                        damage = damage-random(target->query_skill("dodge", 1)/2);

                target->receive_damage("qi", damage);
                target->receive_wound("qi", damage/3);

                msg += HIR"\n���$N���������"+weapon->name()+
                       HIR"��Ƭ����������$n���ϣ�һ������Ѫ���˿ڴ�ӿ����\n"NOR;

                p=query("qi", target)*100/query("max_qi", target);
                msg = replace_string(msg, "$w", "��Ƭ");
                msg = replace_string(msg, "$l", "����ദ");

                if ( me->query_skill("tianyu-qijian", 1) > 140
                && me->query_skill("sword") > 140 )
                        call_out("perform2", 0, me, target);
        }

        else
        {
                addn("neili", -100, me);

                me->start_busy(3);
                msg += HIC"\n$n�ۼ�"+weapon->name()+
                       HIC"��Ƭ��������ǰ��ֻ���������գ��˾��������佫��Ƭ���˿���\n"NOR;
        }

        message_combatd(msg, me, target);

        weapon->unequip();
        weapon->move(environment(me));
        set("name", "���ѵ�"+query("name", weapon), weapon);
        set("value", 1, weapon);
        set("weapon_prop", 0, weapon);
        me->reset_action();
        addn("09g/pfm_pori", 1, me);

        return 1;
}

//If possible, also busy target
int perform2(object me, object target)
{
        string msg;

        if ( !me || !target || !living(target) )
                return 0;

        msg = MAG "\n���ϣ�$N�������Ƭ������������������������$n������ҪѨ��\n\n"NOR;

        if( query("max_neili", me)>query("max_neili", target)*2/3 && random(10)<4 )
        {
                msg += HIR "���$nֻ���˴���Ѫ�����������Ѿ��޷���ת����ʱ����һ��������\n" NOR;
                me->start_busy(3);
                target->start_busy(me->query_skill("force",1)/10);
                addn("neili", -(me->query_skill("force",1)/5), me);
        }

        else
        {
                addn("neili", -10, me);
                addn("neili", -10, target);
                me->start_busy(3);
                msg += HIC "\n$pֻ����Ƭ����������������������Ѩ�������Ҷ�����׼����û���ϵ���\n" NOR;
        }

        message_combatd(msg, me, target);

        return 1;
}

int help(object me)
{
        write(WHT"\n���Ż����ա�\n\n"CYN+
                 " ������һʽ�Ż��������������潣��������ʽ��ϵ������ڹ������Լ���\n"+
                 " �������������컨����ַ�������ˣ�ʵ������������Ȼ��������������\n"+
                 " ���ڹ��������������൱�Ľ���������ܵ���ʩչ��Ҳ�������Ͼ�������\n"+
                 " ���գ������һ�е��������������迿"HIY"������ʹ��"CYN"����ߣ���ʽ��������\n"+
                 " ��ʹ�õ���������Ҳ�кܴ��ϵ��������ˣ�������������ﵽһ������\n"+
                 " ֮ʱ�������"HIG"���ӹ�Ч"CYN"��\n\n"+

              WHT" Ҫ�󣺰˻�����Ψ�Ҷ��𹦡�"HIR"140"WHT" ��\n"+
              WHT" ������С���๦          ��"HIR"140"WHT" ��\n"+
              WHT" �����������潣  ����������"HIR"160"WHT" ��\n"+
              WHT" ��������������������������"HIR"140"WHT" ��\n"+
              WHT" ����������ķ�  ����������"HIR" 80"WHT" ��\n"+
              WHT" ��������������  ��������  "HIR" 28"WHT" ��\n"+
              WHT" ������������  ��������  "HIR" 30"WHT" ��\n"+
              WHT" ��������ǰ����  �������� "HIR" 200"WHT" ��\n"+
              WHT" ��������ǰ����  �������� "HIR"1000"WHT" ��\n"+
              WHT" ����������������������� "HIR"2000"WHT" ��\n\n"+

              WHT" ս����ʹ�á�\n"NOR);

        return 1;
}
