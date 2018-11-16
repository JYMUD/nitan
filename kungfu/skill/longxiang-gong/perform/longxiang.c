// This program is a part of NITAN MudLIB

#include <ansi.h>
#include <combat.h>

string name() { return HIW "ʮ��ʮ��" NOR; }

inherit F_SSERVER;

string final1(object me, object target, int damage, object weapon, int lvl);
string final2(object me, object target, int damage);
string final3(object me, object target, int damage, object weapon, int lvl);
string final4(object me, object target, int ap);
void tian_end(object me, object target);

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;
        
        if( !query("reborn/times", me) ) 
                return notify_fail("����ʹ�õ��⹦��û��������ܡ�\n"); 

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name()+ "ֻ�ܶ�ս���еĶ���ʹ�á�\n");
        
        if( me->is_busy() )
                return notify_fail("����æ���أ�\n");
                
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) ) 
                return notify_fail(name() + "ֻ�ܿ���ʹ�á�\n"); 

        if ((int)me->query_skill("force", 1) < 1000)
                return notify_fail("���ڹ���Ϊ����������ʩչ" +name()+ "��\n");

        if( query("max_neili", me)<100000 )
                return notify_fail("��������Ϊ����������ʩչ" +name()+ "��\n");

        lvl = (int)me->query_skill("longxiang-gong", 1);
        if (lvl < 1000)
                return notify_fail("�������������򲻹�������ʩչ" +name()+ "��\n");

        if( query("neili", me)<10000 )
                return notify_fail("��������������������ʩչ" +name()+ "��\n");

        if (me->query_skill("martial-cognize", 1) < 400)
                return notify_fail("����ѧ�������㣬����ʩչ" +name()+ "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        message_combatd(HIM "\n$N" HIM "����ʮ��ʮ��֮������ʱ����ת���������ȫ��\n"
                        HIM "$N" HIM "������Х������������ӿ��ȥ������ʯ���쾪�������ޱȣ�Ϯ��$n" HIM "��\n" NOR, me, target);

        message_combatd(HIM "ʮ��ʮ��֮һ��һ��\n" NOR, me, target);
        
        me->addn("neili", -10000);
        
        // ��һ�У��ж϶Է�����
        ap = attack_power(me, "unarmed") + me->query_str()*10;
        dp = defense_power(target, "parry") + target->query_str()*10;
        
        damage = damage_power(me, "unarmed");
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                                         (: final1, me, target, damage, lvl :));
        } else
        {
                msg = HIC "$n" HIC "����˫�ۣ������Զԣ�����$N" HIC "֮��жȥ��\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "ʮ��ʮ��֮��������\n" NOR, me, target);
        
        ap = attack_power(me, "unarmed") + me->query_int()*10;
        // �ڶ��У��ж϶Է�����
        dp=defense_power(target,"parry")+target->query_int()*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                                          HIY "$n" HIY "��Цһ��������$N" HIY "���з�ǳ֮������"
                                          "�������мܣ���Ȼ�䣬�����͡���һ����˫��"
                                          HIY "�Ѵ�͸$n" HIY "�����ţ���Ѫ����ӿ����\n" NOR, me , target);
        } else
        {
                msg = HIC "$n" HIC "����һЦ������$N" HIC "�����е�����������ʩ�о������л�ȥ��\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "ʮ��ʮ��֮��������\n" NOR, me, target);
        
        ap = attack_power(me, "unarmed") + me->query_con()*10;
        // �����У��ж϶Է�����
        dp = defense_power(target, "force") + target->query_con()*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                                           (: final2, me, target, damage :));
        } else
        {
                msg = HIC "$n" HIC "Ĭ���ڹ����ھ�����ȫ�������ֵ�ס$N" HIC "���С�\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "ʮ��ʮ��֮��������\n" NOR, me, target);

        // �����У��ж϶Է���

        ap = attack_power(me, "unarmed") + me->query_dex()*10;
        dp = defense_power(target, "dodge") + target->query_dex()*10;

        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                                          (: final3, me, target, damage, lvl :));
        } else
        {
                msg = HIC "$n" HIC "�������������ͣ����μ��ˣ�˲��Ʈ����"
                      "�ɣ����Ŷ��$N" HIC "���С�\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "ʮ��ʮ��֮��������\n" NOR, me, target);

        // �����У��ж϶Է�����

        if( query("max_neili", me)>query("max_neili", target)*2 )
        {
                 msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                        HIY "$n" HIY "˼��δ����$N" HIY "���ھ���������룬"
                            "$n" HIY "�ܴ��ػ������һ��Ż������" HIR "��Ѫ" HIY "��\n" NOR, me, target);
        } else
        {
                msg = CYN "$n" CYN "֪��$N�����޿ɵֵ���"
                       CYN "��������Ծ����������������\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "ʮ��ʮ��֮��������\n" NOR, me, target);

        // �����У��ж϶Է���������

        if( query("score", me)>query("score", target)*2 )
        {
                 msg = COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 80 + random(15),
                                          (: final4, me, target, damage :));
        } else
        {
                msg = CYN "$n" CYN "����һЦ��һ�л�����ǽ���ģ�����������ȥ��\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "ʮ��ʮ��֮��������\n" NOR, me, target);
        
        // �����У��ж϶Է������ڹ�
        
        ap = attack_power(me, "unarmed") + me->query_skill("force", 1);
        dp = defense_power(target, "parry") + target->query_skill("force", 1);
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                        HIY "$n" HIY "˼��δ����$N" HIY "���ھ���������룬"
                            "$n" HIY "�ܴ��ػ������һ��Ż������" HIR "��Ѫ" HIY "��\n" NOR, me, target);
        } else
        {
                msg = CYN "$n" CYN "���$N" CYN "����ɽ�������ƣ���ȫ"
                                          CYN "�޷��ֵ���Ψ���˺󼸲�������Ӧ�ԡ�\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "ʮ��ʮ��֮��������\n" NOR, me, target);
        
        // �ڰ��У��ж϶Է������м�
        
        ap = attack_power(me, "unarmed") + me->query_skill("parry", 1);
        dp = defense_power(target, "parry") + target->query_skill("parry", 1);
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                        HIY "$n" HIY "��Ų���㣬�߾�ȫ����Ҳû�취�㿪�����������˸����ţ�\n" NOR, me, target);
        } else
        {
                msg = HIC "$n" HIC "�������������ͣ����μ��ˣ�˲��Ʈ����"
                      "�ɣ����Ŷ��$N" HIC "���С�\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "ʮ��ʮ��֮��������\n" NOR, me, target);
        
        // �ھ��У��ж϶Է������Ṧ
        
        ap = attack_power(me, "unarmed") + me->query_skill("dodge", 1);
        dp = defense_power(target, "parry") + target->query_skill("dodge", 1);
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80 + random(10),
                                          HIY "$n�������ʮ��ս�������ﻹ�ֵܵ���ס��"
                                          HIY "������Ϣ֮�䣬�Ѿ��������У�\n" NOR, me , target);
        } else
        {
               msg = CYN "$n���һ������æ�˺󣬾�Ȼ"
                      CYN "���Ҷ㿪����һ�У�\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);
        message_combatd(HIM "ʮ��ʮ��֮ʮ��ʮ��\n" NOR, me, target);
        
        // ��ʮ�У��ж϶Է���ѧ����
        
        ap = attack_power(me, "unarmed") + me->query_skill("martial-cognize", 1);
        dp = defense_power(target, "parry") + target->query_skill("martial-cognize", 1);
        
        if (ap / 2 + random(ap) > dp)
        {
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 100 + random(10),
                        HIY "$n" HIY "����������ǿ���һ�У������޷��мܣ������ػ��У�\n"
                        HIY "�����������ڲ��ݣ�����" HIR "��Ѫ" HIY "����������\n" NOR, me, target);
        } else
        {
                msg = CYN "$n����߲��²���ھ�����$N" CYN "�����Ĺ��ƾ����ֵ���\n" NOR;
        }
                     
        me->start_busy(6 + random(5));
        return 1;
}

string final1(object me, object target, int damage, int lvl)
{
        addn("neili", -(lvl+random(lvl)), target);

        return  HIY "$n" HIY "ȴ��$N" HIY "�������ƻֺ룬�������������ֵ�������������"
                "���������ˣ�$n" HIY "�ƺ�һ�������˼������پ���Ϣ��ɢ����"
                "������Ⱦ����Ѫ��\n" NOR;
}

string final2(object me, object target, int damage)
{
        target->receive_damage("jing", damage / 2, me);
        target->receive_wound("jing", damage / 4, me);
        return  HIY "$n" HIY "����һ��������$N" HIY "�⼸�������ޱȣ���ʽ�仯Ī�⣬"
                "������ȴ��Ȼ����������ԥ�䣬$n" HIY "ȴ�����У��ٸо������ã���"
                "��������\n" NOR;
}

string final3(object me, object target, int damage, int lvl)
{
   
        target->start_busy(4 + random(3));
  
        return  HIY "$N" HIY "�Ʒ������ޱȣ�˫��ʱ������������ʱ��"
                "�������裬���Ǽ�$n" HIY "�ѱ������ˣ�$N" HIY "��Ȼ��˫ȭһ"
                "ת��ȭ�ƶ�Ȼ�ӿ죬��$n" HIY "����Χס������һ˿��϶��\n" NOR;

}

void tian_end(object me, object target)
{
        if( target && query_temp("no_perform", target) )
        {
                if (living(target))
                {
                        message_combatd(HIC "$N" HIC "��������һ��"
                                        "������ɫ�ɰ�ת�죬��������"
                                        "���ˡ�\n" NOR, target);

                        tell_object(target, HIY "��е������ҵ�����"
                                            "����ƽ����������\n" NOR);
                }
        addn_temp("apply/avoid_busy", 90, target);
        addn_temp("apply/reduce_busy", 36, target);
        addn_temp("apply/avoid_weak", 90, target);
        addn_temp("apply/avoid_forget", 90, target);
        tell_object(target, HIR "��ĺ�������������æ�ҡ����Ӿ����䶳�������ڽ����ӡ��\n" NOR);
                delete_temp("no_perform", target);
        }
        return;
}

string final4(object me, object target, int ap)
{
        addn_temp("apply/avoid_busy", -90, target);
        addn_temp("apply/reduce_busy", -36, target);
        addn_temp("apply/avoid_weak", -90, target);
        addn_temp("apply/avoid_forget", -90, target);
        set_temp("no_perform", 1, target);
        remove_call_out("tian_end");
        call_out("tian_end", 10 + random(ap / 50), me, target);
        return HIY "$n" HIY "˿���������а��һ�����񣬵��������ش���\n" NOR +
               WHT "$n" WHT "�е�����ĺ�������������æ�ҡ����Ӿ����䶳��������ӡ��\n" NOR;
}