#include <ansi.h>
#include <combat.h>

#define BING "��" HIW "�������" NOR "��"

inherit F_SSERVER;

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int lvl;

        if (! target) target = offensive_target(me);

        if( userp(me) && !query("can_perform/xuantian-zhi/bing", me) )
                return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

        if (! target || ! me->is_fighting(target))
                return notify_fail(BING "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ��" BING "��\n");         

        if (me->query_skill_mapped("finger") != "xuantian-zhi")
                return notify_fail("��û�м�������ָ������ʹ��" BING "��\n");

        if (me->query_skill_prepared("finger") != "xuantian-zhi")
                return notify_fail("������û��׼��ʹ������ָ���޷�ʹ��" BING "��\n");

        if ((int)me->query_skill("xuantian-wujigong", 1) < 180)
                return notify_fail("��������޼�����򲻹���ʹ����" BING "��\n");

        if ((int)me->query_skill("xuantian-zhi", 1) < 180)
                return notify_fail("�������ָ��������������ʹ��" BING "��\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("���������Ϊ���㣬�޷�ʹ��" BING "��\n");

        if( query("neili", me)<500 )
                return notify_fail("��������������޷�ʹ��" BING "��\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIW "$N" HIW "Ĭ�������޼�������ʱһ�㺮˪����ȫ��һ����"
              "Ц��������ָ��ֱ��$n" HIW "ҪѨ��\n"NOR;  

        lvl = me->query_skill("xuantian-zhi", 1);

        ap=me->query_skill("finger")+query("con", me)*5;
        dp=target->query_skill("force")+query("con", target)*5;

        me->start_busy(4);
        if (ap / 2 + random(ap) > dp)
        { 
                damage = ap + random(ap / 2);
                addn("neili", -400, me);
                target->affect_by("xuantian_zhi",
                               (["level":query("jiali", me)+random(query("jiali", me)),
                                  "id":query("id", me),
                                  "duration" : lvl / 50 + random(lvl / 20) ]));
                                  msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK,
                                         damage, 70, HIW "$n" HIW "�Բ������ѱ�$P" HIW
                                         "һָ���У�����֮����ʱ��������������\n" NOR);
        } else
        {
                msg += CYN "$n" CYN "��$N" CYN "������ӿ����æ����Ծ����\n" NOR;
        }
        message_combatd(msg, me, target);

        return 1;
}