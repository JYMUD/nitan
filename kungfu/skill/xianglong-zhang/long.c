#include <ansi.h>
#include <combat.h>

#define HUI "��" HIR "���[����" NOR "��"
#define HUIP "��" HIR "�����л�" HIW "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp, i;
        object weapon;

        if( userp(me) && !query("can_perform/xianglong-zhang/long", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(HUI "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail(HUI "ֻ�ܿ���ʹ�á�\n");

        if ((int)me->query_skill("force", 1) < 1000)
                return notify_fail("���ڹ���Ϊ����������ʩչ" HUI "��\n");

        if( query("max_neili", me)<10000 )
                return notify_fail("��������Ϊ����������ʩչ" HUI "��\n");

        if ((int)me->query_skill("xianglong-zhang", 1) < 1000)
                return notify_fail("�㽵��ʮ���ƻ�򲻹�������ʩչ" HUI "��\n");

        if (me->query_skill_mapped("strike") != "xianglong-zhang")
                return notify_fail("��û�м�������ʮ���ƣ�����ʩչ" HUI "��\n");

        if (me->query_skill_prepared("strike") != "xianglong-zhang")
                return notify_fail("��û��׼������ʮ���ƣ�����ʩչ" HUI "��\n");

        if( query("neili", me)<3000 )
                return notify_fail("��������������������ʩչ" HUI "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        message_combatd(sort_msg(HIG "\n$N" HIG "�����������̬��Ȼ�������黮�����ֻ�ת����������ǰ���͵�˫"
                         "���Ƴ���ɲ�Ǽ䣬һ�б�Ϊ���У�ͬʱʹ�������ǽ���ʮ���ơ�" HIR "���[����" HIG "����"
                         "���ƻֺ룬�Ʋ��ɵ� ����\n" NOR), me, target);        

        // ��һ��
        ap=me->query_skill("strike")+query("str", me)*5;
        dp=target->query_skill("dodge")+query("dex", target)*5;
        ap *= 2;
        
        message_combatd(sort_msg(HIW "��Ȼ$N" HIW "���μ���������һ�������ֺ���һ��"
                     "����$n" HIW "����������֮��"
                     "˵���㵽������ɽ����֮����$n" HIW "��ӿ��ȥ������ʯ"
                     "���쾪�������ޱȡ�\n" NOR), me, target);

        if (ap * 3 / 5 + random(ap) > dp)
        {
                damage = ap + random(ap / 2) + me->query_skill("force");
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                          HIR "$P����һ�������ѻ���$p��ǰ��$p��"
                                          "���������ٱ��������С�\n" NOR);
        } else
        {
                msg = HIC "ȴ��$p����˫�ۣ�����Ӧ�ԣ�$P��"
                      "������ţ�뺣������жȥ��\n" NOR;
        }
        message_combatd(msg, me, target);

        // �ڶ���
        ap=me->query_skill("strike")+query("str", me)*5;
        dp=target->query_skill("parry")+query("int", target)*5;
        ap *= 2;

        message_sort(HIW "$N" HIW "һ�Ƽȳ���������Ȼ������$n" HIW "��"
                     "����֮�⣬������ǰ�������������ϲ�����������ŭ����"
                     "ӿ���Ʋ��ɵ�����ʱ$p�����Ϣ��"
                     "�ͣ����㲻�ȡ�\n" NOR, me, target);

        if (ap * 2 / 3 + random(ap) > dp)
        {
                damage = ap + random(ap / 2) + me->query_skill("force");
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                          HIR "$pһ���Һ�����$P��һ�ƻ�����ǰ��"
                                          "���꿦����˼����߹ǡ�\n" NOR);
        } else
        {
                msg = HIC "����$pȫ���ֵ��мܣ�����������"
                      "�࣬��$P������ж�����Ρ�\n" NOR;
        }
        message_combatd(msg, me, target);

        // ������
        ap=me->query_skill("strike")+query("str", me)*5+me->query_skill("force");
        dp=target->query_skill("force")+query("con", target)*5;
        ap *= 2;
        
        message_combatd(sort_msg(HIW "������$N" HIW "����б�ӣ�ǰ������δ����������"
                     "���ֵ�����Ȼ�ֹ���һ�У��Ƽз��ƣ���������"
                     "����һ��������ǽ����ǰ�����ȥ��$n" HIW "ֻ����Ѫ��"
                     "ӿ����Ϣ���ǡ�\n" NOR), me, target);

        if (ap *11 / 20 + random(ap) > dp)
        {
                damage = ap + random(ap);
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                          HIR "���$p����������$P�ƾ���ʱ���ض�"
                                          "������ʱ������Ѫ���硣\n" NOR);
        } else
        {
                msg = HIC "$p�ۼ��������ͣ����μ��ˣ�˲��"
                      "Ʈ�����ɣ��ѳ�����֮�⡣\n" NOR;
        }              
        message_combatd(msg, me, target);
        
        message_combatd(sort_msg(HIY "$N" HIY "����ͣ�٣�˫�Ʒ���������һ�����������ھ���֮��"
                        "��\n" NOR), me, target);
                
        addn_temp("apply/attack", 100000, me);
        addn_temp("apply/damage", 5000, me);
        for (i = 0; i < 6; i++)
        {
                if (! me->is_fighting(target))
                        break;

                if (random(2) && ! target->is_busy())
                        target->start_busy(1);

                COMBAT_D->do_attack(me, target, 0, 0);
        }
        addn_temp("apply/attack", -100000, me);
        addn_temp("apply/damage", -5000, me);
                
        weapon=query_temp("weapon", target);
        if (objectp(weapon) && base_name(environment(me)) != "/d/city/biwu_dating")
        {
                message_combatd(sort_msg(HIG "\n$N" HIG "����һ����ȫ���ھ��ŷ��������ұ۷����⳶����ͼ��$n"
                                HIW "��" + weapon->name() + HIW "�������С�\n" NOR), me, target);
        
                ap=me->query_skill("strike")+query("str", me)*10;
                dp=target->query_skill("parry")+query("dex", target)*10;
                ap = ap + ap / 2;
                                    
                if (ap / 3 + random(ap) > dp)
                {
                        addn("neili", -300, me);
                        msg = HIR "$n" HIR "ֻ����Χ����ӿ��������" + weapon->name()
                               + HIR "��Ȼ����ס����$N" HIR "�������ַ�ȥ��\n" NOR;
                        weapon->move(me, 1);
                } else
                {
                        addn("neili", -200, me);
                        msg = CYN "$n" CYN "ֻ����Χ����ӿ������æ����������"
                               + weapon->name() + CYN "������ܲ�͸�磬ʹ��$N"
                               CYN "�޴����֡�\n" NOR;
                }
                message_combatd(msg, me, target);
        }
        
        if (random(5) == 1)
        {
                message_combatd(HIG "$N" HIG "��ƽ��δ������������ֺ����ʽ������Ū�ò�֪���롣\n" NOR, 
                                target);
                target->start_busy(5 + random(6));
        }

        me->start_busy(3 + random(4));
        addn("neili", -3000, me);
        return 1;
}