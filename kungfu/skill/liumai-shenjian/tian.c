#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

#define ZONG "��" HIR "������" NOR "��"

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill;

        if (! target) target = offensive_target(me);

        if( !query("scborn/ok", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");
                
        if (! target || ! me->is_fighting(target))
                return notify_fail(ZONG "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (me->query_skill_prepared("finger") != "liumai-shenjian")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ" ZONG "��\n");

        skill = me->query_skill("liumai-shenjian", 1);

        if (skill < 800)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" ZONG "��\n");

        if (me->query_skill("force", 1) < 1000)
                return notify_fail("����ڹ���򲻹�������ʩչ" ZONG "��\n");

        if( query("max_neili", me)<12000 )
                return notify_fail("���������Ϊ����,�޷�ʩչ" ZONG "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("������������������޷�ʩչ" ZONG "��\n");

        if( query_temp("weapon", me) )
                return notify_fail("������ǿ��ֲ���ʩչ" ZONG "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        msg = HIM "$N" HIM "һ����Х������ʮָ�׵����پ�����������ӿ����ͷ������"
              "�˷������಻����\n��ʱ�����籼�������޾������������Ȼ����$n" HIM 
              "��\n" NOR;

        ap = me->query_skill("martial-cognize", 1) + me->query_skill("force");
        dp = target->query_skill("martial-cognize", 1) + target->query_skill("force");
        
        // ���20%
        ap = ap + ap / 5;
        
        // ��20%����ʩչ��BUSY
        if (random(5) != 1)me->start_busy(5 + random(3));

        if ((int)target->query_skill("jingluo-xue", 1) >= 200 
            && target->query_skill("dodge", 1) >= me->query_skill("liumai-shenjian", 1)
            && random (10) == 1 )
        {
                addn("neili", -2000, me);
                if (random(5) != 1)me->start_busy(5);
                msg += HIY "����$n" HIY "����һЦ��������䣬���׵Ķ����һ�У�\n"NOR;
        } else
        if (ap + random(ap) > dp)
        { 
                damage = ap * 3 + random(ap);                 
                
                addn("neili", -1800, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300 + random(200),
                                           HIR "ֻ��$n" HIR "һ���ҽУ����������"
                                           "͸��������˿ڴ���Ѫ��ʱ��ӿ��ʹ���ѵ���\n" NOR);
        } else
        {
                addn("neili", -400, me);
                if (random(5) != 1)me->start_busy(5);
                msg += CYN "$n" CYN "��$N" CYN "������ӿ����������"
                       "�мܣ���æ����Ծ����\n" NOR;
        }
        
        msg += HIG "\n�����ţ�$N" HIG "һ����Х������ʮָ�׵����پ�����������ӿ����ͷ������"
              "�˷������಻����\n��ʱ�����籼�������޾������������Ȼ����$n" HIG
              "��\n" NOR;
              
        // �ٷ�һ��
        if ((int)target->query_skill("jingluo-xue", 1) >= 200 
            && target->query_skill("dodge", 1) >= me->query_skill("liumai-shenjian", 1)
            && random (10) == 1 )
        {
                addn("neili", -600, me);
                if (random(5) != 1)me->start_busy(5);
                msg += HIY "����$n" HIY "����һЦ��������䣬���׵Ķ����һ�У�\n"NOR;
        } else        
        if (ap + random(ap) > dp)
        { 
                damage = ap * 3 + random(ap);                 
                
                addn("neili", -800, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300 + random(200),
                                           HIR "ֻ��$n" HIR "һ���ҽУ����������"
                                           "͸��������˿ڴ���Ѫ��ʱ��ӿ��ʹ���ѵ���\n" NOR);
        } else
        {
                addn("neili", -400, me);
                if (random(5) != 1)me->start_busy(5);
                msg += CYN "$n" CYN "��$N" CYN "������ӿ����������"
                       "�мܣ���æ����Ծ����\n" NOR;
        }
        message_combatd(msg, me, target);
        
        
        return 1;
}
