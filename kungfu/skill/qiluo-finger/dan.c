// dan.c ˫��ָ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        object weapon,weapon2;
        int damage,i;
        string msg,str;
        int ap, dp;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }
        
        if (! target || ! me->is_fighting(target))
                return notify_fail("��˫��ָ��ֻ�ܶ�ս���еĶ���ʹ�á�\n");
 
        if(me->query_skill_mapped("finger") != "qiluo-finger") 
                return notify_fail("��û��������������޷�ʹ�á�˫��ָ�����У�\n");

        if (me->query_skill_prepared("finger") != "qiluo-finger")
                return notify_fail("��û��׼��ʹ������������޷�ʩչ��˫��ָ�����С�\n");

        if( objectp(weapon=query_temp("weapon", me)) || 
            objectp(weapon=query_temp("handing", me)) )
                return notify_fail("��������˫�ֲ���ʹ��ָ�����С�\n");

        if ((int)me->query_skill("qiluo-finger", 1) < 200)
                return notify_fail("����������������죬����ʹ�á�˫��ָ����\n");
                                
        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���Ϊ�����ߡ�\n");
                        
        if( query("neili", me)<800 )
                return notify_fail("����������̫��������ʹ�á�˫��ָ����\n");
                        
        msg = HIB "\n$N" HIB "����Ĭ��������˵���飬��Ȼ��ʽһ���������ˣ�������������֮�⡣\n"
              HIB "$n" HIB "��$N" HIB "���в��̣���Ҫ������ȴ��$N" HIB "�Ӵ����ŷ���˫�ֽ��ۣ�˫ָ��ת��ңָ$n�� \n"
              HIB "$n" HIB "һʱ������ţ���֪$N" HIB "�������У���ͷһ����㯡�\n"
              HIW " �� �� �� �� !\n"
              HIB "�����л�����ǿ����" HIB + to_chinese(me->query_skill_mapped("force"))+ HIB "��$n" HIB "����������ң�\n"
              HIB "ֻ�е��Է��˳�������ǧ�������������ϲ���������˷�ӿ������ʹЭ��˫�����Ǳ��޿ɱܣ�\n\n" NOR;

        ap = me->query_skill("finger") + me->query_skill("force");
        ap+=query("jiali", me);
        ap+=query("jianu", me);
        
        damage = ap*2 + random(ap);
        damage+=query("jiali", me);

        if (living(target))
                dp = target->query_skill("dodge",1) + target->query_skill("parry",1);
        else
                dp = 0;

        dp = dp*3/2;

        weapon2=query_temp("weapon", target);
        
        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -damage/2, me);
                if (weapon2)
                {
                        msg += HIM "\n$n" HIM "��$N" HIM "�������ͣ���������ֵ�������" + weapon2->name() + HIM "�����Ӱ������ˮй��ͨ\n"
                               HIM "$N" HIM "�����������ţ�" HIW "��������" HIM "�Ծ����಻����$n" HIM "����" + weapon2->name() + HIM "����������֮�£�\n"
                               HIM "��Ϊ����Ķ���ʮ�أ����ϰ�գ��������ڹ⣡\n" NOR;
                                damage -= damage/3;
                                weapon2->set_name("���ѵ�"+query("name", weapon2));
                                weapon2->move(environment(target));
                                set("value", 0, weapon2);
                                set("weapon_prop", 0, weapon2);
                                target->reset_action();
                } else
                        msg += HIM "\n$n" HIM "��$N" HIM "�������ͣ���������ֵ����������˫�Ʒ������$N��\n"
                               "$N" HIM "�����������ţ�" HIW "��������" HIM "�Ծ����಻����$n" HIM "�޿��κ�֮�£���ײ����Ѫ������\n" NOR;

                target->receive_damage("qi",damage,me);
                target->receive_wound("qi",damage/2 + random(damage/2),me);
                str=COMBAT_D->status_msg(query("qi", target)*100/query("max_qi", target));
                msg += "($n"+str+")\n";
                
                target->start_busy(1+random(2));
                me->start_busy(3+random(2));
        } else 
        {
                if (weapon2)
                        msg += HIM "\n$n" HIM "��$N" HIM "�������ͣ���������ֵ�������" + weapon2->name() + HIM "�����Ӱ������ˮй��ͨ\n"
                               "$N" HIM "������һ����" HIW "��������" HIM "��Ȼ���\n" NOR;
                else
                        msg += HIM "\n$n" HIM "��$N" HIM "�������ͣ���������ֵ����������˫�Ʒ������$N��\n"
                               HIM "$N" HIM "������һ����" HIW "��������" MAG "��Ȼ��գ���$n" HIM "Ҳ��$N" HIM "ײ����Ѫ��ӿ��\n" NOR;

                addn("neili", -100, me);
                me->start_busy(3);
                if (target->is_busy())
                        target->start_busy(1);
        }
        message_combatd(msg, me, target);

        return 1;
}