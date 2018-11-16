#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "������"; }

int perform(object me, object target)
{
        string msg;
        int ap, dp;
        int damage, skill;
        int n;

        if (! target) target = offensive_target(me);

        if( !query("reborn/times", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if( query("family/family_name", me) != "���ϻ���" 
         && member_array("���ϻ���", query("reborn/fams", me)) == -1 ) 
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( me->is_busy() )
                return notify_fail("����æ���ء�\n");

        if (me->query_skill_prepared("finger") != "six-finger")
                return notify_fail("��û��׼��ʹ�������񽣣��޷�ʩչ" + name() + "��\n");

        skill = me->query_skill("six-finger", 1);

        if (skill < 800)
                return notify_fail("�����������Ϊ���ޣ��޷�ʹ��" + name() + "��\n");

        if (me->query_skill("force", 1) < 1000)
                return notify_fail("����ڹ���򲻹�������ʩչ" + name() + "��\n");

        if( query("max_neili", me)<12000 )
                return notify_fail("���������Ϊ����,�޷�ʩչ" + name() + "��\n");

        if( query("neili", me)<1000 )
                return notify_fail("������������������޷�ʩչ" + name() + "��\n");

        if( query_temp("weapon", me) )
                return notify_fail("������ǿ��ֲ���ʩչ" + name() + "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");


        msg = HIM "$N" HIM "һ����Х��������ָ�׵����پ�����������ӿ����ͷ������"
              "�˷������಻����\n��ʱ�����籼�������޾������������Ȼ����$n" HIM
              "��\n" NOR;

        ap = attack_power(me, "finger");
        dp = defense_power(target, "force");

        // ���20%
        ap = ap + ap / 5 + me->query_skill("martial-cognize", 1) + me->query_skill("jingluo-xue", 1);

        // ��20%����ʩչ��BUSY
        if (random(5) != 1) me->start_busy(2 + random(3));

        if ((int)target->query_skill("martial-cognize", 1) >= 2000
            && target->query_skill("dodge", 1) >= me->query_skill("six-finger", 1)
            && random (10) == 1 )
        {
                addn("neili", -2000, me);
                msg += HIY "����$n" HIY "����һЦ��������䣬���׵Ķ����һ�У�\n"NOR;
        } else
        if (ap + random(ap) > dp)
        {
                damage = damage_power(me, "finger") + me->query_skill("martial-cognize", 1) + me->query_skill("jingluo-xue", 1);
                damage *= 3;
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        damage += damage*n*15/100;
                        msg += HIM"$N"HIM"����������ת�ĸ�����ʹ���������˺���ǿ��\n"NOR;
                }

                addn("neili", -1800, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300 + random(200),
                                           HIR "ֻ��$n" HIR "һ���ҽУ����������"
                                           "͸��������˿ڴ���Ѫ��ʱ��ӿ��ʹ���ѵ���\n" NOR);
                target->set_weak(5);
                if( !target->is_busy() ) target->start_busy(8);
        } else
        {
                addn("neili", -400, me);
                msg += CYN "$n" CYN "��$N" CYN "������ӿ����������"
                       "�мܣ���æ����Ծ����\n" NOR;
        }

        msg += HIG "\n�����ţ�$N" HIG "һ����Х��������ָ�׵����پ�����������ӿ����ͷ������"
              "�˷������಻����\n��ʱ�����籼�������޾������������Ȼ����$n" HIG
              "��\n" NOR;

        // �ٷ�һ��
        if ((int)target->query_skill("martial-cognize", 1) >= 2000
            && target->query_skill("dodge", 1) >= me->query_skill("six-finger", 1)
            && random (10) == 1 )
        {
                addn("neili", -600, me);
                msg += HIY "����$n" HIY "����һЦ��������䣬���׵Ķ����һ�У�\n"NOR;
        } else
        if (ap + random(ap) > dp)
        {
                damage = damage_power(me, "finger") * 3;
                if( (n = me->query_skill("qimai-liuzhuan", 1) / 100) >= 1 )
                {
                        damage += damage*n*15/100;
                        msg += HIM"$N"HIM"����������ת�ĸ�����ʹ���������˺���ǿ��\n"NOR;
                }

                addn("neili", -800, me);
                msg += COMBAT_D->do_damage(me, target, REMOTE_ATTACK, damage, 300 + random(200),
                                           HIR "ֻ��$n" HIR "һ���ҽУ����������"
                                           "͸��������˿ڴ���Ѫ��ʱ��ӿ��ʹ���ѵ���\n" NOR);
                target->set_weak(5);
                if( !target->is_busy() ) target->start_busy(8);
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
