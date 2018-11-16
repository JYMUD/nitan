#include <ansi.h>
#include <combat.h>

#define SHEN "��" HIM "����Ԫ��" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg, wn;
        object weapon;
        int ap, dp;
        me = this_player();

        if( userp(me) && !query("can_perform/wushen-jian/shen", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(SHEN "ֻ����ս���жԶ���ʹ�á�\n");

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԣ�����ʩչ" SHEN "��\n");

        if ((int)me->query_skill("wushen-jian", 1) < 240)
                return notify_fail("���ɽ���񽣲�����죬����ʩչ" SHEN "��\n");

        if (me->query_skill_mapped("sword") != "wushen-jian")
                return notify_fail("��û�м�����ɽ���񽣣�����ʩչ" SHEN "��\n");

        if ((int)me->query_skill("force", 1) < 220)
                return notify_fail("����ڹ���򲻹�������ʩչ" SHEN "��\n");

        if ((int)me->query_skill("dodge", 1) < 200)
                return notify_fail("����Ṧ��򲻹�������ʩչ" SHEN "��\n");  

        if( query("max_neili", me)<5500 )
                return notify_fail("���������Ϊ���㣬����ʩչ" SHEN "��\n");

        if( query("neili", me)<500 )
                return notify_fail("�����ڵ���������������ʩչ" SHEN "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        wn = weapon->name();

        msg = HIM "\n$N" HIM "һ��ŭ�ȣ��ھ����ǣ�����" + wn +
              HIM "�����ǧ�����Ǽ仯��������̰�������⣬��"
              "����$P����ر�죬���Ž���ͬʱ����" HIR
              "ף��" HIM "������" HIY "�ϸ�" HIM "������" NOR
              WHT "ʯ��" HIM "������" HIG "ܽ��" HIM "������"
              HIW "����" HIM "�����׽�������ʹ��������ʯ��"
              "��Ϯ��$n" HIM "ȫ��" NOR;

        message_sort(msg, me, target);
        
        ap = attack_power(me, "sword");

        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "sword");

                // ���֮һ�ļ��ʿɱ��м�
                if (random(10) <= 1 && ap / 2 < dp)
                {
                        damage = damage / 3;

                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 60,
                                                  HIG "\n$n" HIG "��$N" HIG "������⽣��"
                                                  "���ˣ���æ������������мܡ���֪$P��"
                                                  "�������Ƿ���$pһ���ƺߣ����˼�������"
                                                  "��һ����Ѫ��\n" NOR);
                        addn("neili", -200, me);
                        me->start_busy(3 + random(2));
                } else 
                {
                        msg = COMBAT_D->do_damage(me, target, WEAPON_ATTACK, damage, 80 + random(10),
                                                  HIR "\n$n" HIR "��$N" HIR "��������ͷ�"
                                                  "���䣬�����ݺᣬ��Х�����Լ�Ϯ������"
                                                  "�ײ��ɴ󾪣���ʱ���á����͡�һ������"
                                                  "��͸�������\n" NOR);
                        addn("neili", -300, me);
                        me->start_busy(3 + random(3));
                }
        } else
        {
                msg = CYN "\nȻ��$n" CYN "�Կ�Կ죬����һ��"
                      "��Ȼ���$N" CYN "��һ�С�\n" NOR;
                addn("neili", -150, me);
                me->start_busy(3);
        }
        message_sort(msg, me, target);
        return 1;
}