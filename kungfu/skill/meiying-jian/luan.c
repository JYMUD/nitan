

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        object weapon;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�á���Ӱ������\n");

        if (! objectp(weapon = me->query_temp("weapon")) ||
            (string)weapon->query("skill_type") != "sword")
                return notify_fail("��ʹ�õ��������ԣ�\n");
                
        if (me->query_skill_mapped("sword") != "meiying-jian")
                return notify_fail("��û�м�����Ӱ�������޷�ʩչ��\n"); 

        if ((int)me->query_skill("meiying-jian", 1) < 200)
                return notify_fail("��Ŀǰ������ʹ��������Ӱ������\n");

        if ((int)me->query("neili") < 300)
                return notify_fail("�������������\n");

        if (! living(target))
               return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        me->add("neili", -200);
        msg = HIM "\n$N" HIM "¶�������Ц�ݣ���Ȼ����Ȼ�ӿ죬������ȫ��Ӱ����ת��"
              "����$N" HIM "��Ӱ�㼤�������$n" HIW "ֻ����ӰΧ�ƣ���Ϣ֮����\n" NOR;

        if (random(10) < 2)
        {
                if (random(10) < 7)me->start_busy(1);
                else
                {
                        me->start_busy(2);
                }               
        }
        
        ap = me->query_skill("dodge") + me->query_skill("force");
        dp = target->query_skill("dodge") + target->query_skill("force");
        
        if (ap * 3 / 4 + random(ap) > dp)
        {
                if (random(3) == 1)target->start_busy(2);
                damage = ap * 2 + random(ap);

                msg += COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 100, 
                                           HIR "ֻ��$n" HIR "�ѱ�$N" HIR
                                           "�̵����������Ѫ�������ȫ�����������\n" NOR);
        } else
        {
                msg += HIC "����$p" HIC "��æ����㿪��ʹ$P"
                       HIC "����û�еóѡ�\n" NOR;
        }
        message_combatd(sort_msg(msg), me, target);

        return 1;
}

