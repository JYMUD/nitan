#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail("��ڤ�޼�ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ����ڤ�޼���\n");         

        if ((int)me->query_skill("xuanming-shengong", 1) < 150)
                return notify_fail("�����ڤ�񹦻�򲻹���ʹ������ڤ�޼���\n");

        if ((int)me->query_skill("xuanming-zhang", 1) < 150)
                return notify_fail("�����ڤ���Ʋ�������������ʹ����ڤ�޼���\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ���㣬�޷�ʹ����ڤ�޼���\n");

        if( query("neili", me)<500 )
                return notify_fail("��������������޷�ʹ����ڤ�޼���\n");

        msg = MAG "$N������ڤ�񹦣�ȫ���ֳ�һ����������Ȼ��˫�Ʒ��ڣ�ʩչ��������ڤ\n�޼���Я���������������֮�����ƾ��ѹ���$n��\n"NOR;  

        lvl = me->query_skill("xuanming-zhang", 1);
        ap=attack_power(me,"strike")+query("str", me)*10;
        dp=defense_power(target,"dodge")+query("dex", target)*10;
        me->start_busy(4);
        if (ap / 2 + random(ap) > dp)
        { 
                damage = damage_power(me, "strike");
                addn("neili", -400, me);
                target->affect_by("xuanming_poison",
                               (["level":query("jiali", me)+random(query("jiali", me)),
                                  "id":query("id", me),
                                  "duration" : lvl / 50 + random(lvl / 20) ]));
                                  msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 70,
               MAG "$nֻ����ǰ��Ӱ�ζ���ͻȻ���ؿ�һ����֪���Ʋ��ֻ���ؿڴ�һ��\n�������𣬾�������������\n" NOR);
        } else
        {
                msg += HIY "$n����$N������ӿ����æ����Ծ����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}