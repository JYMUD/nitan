// This program is a part of NITAN MudLIB
// tuo.c
// �����ս���ַ���ʱ��ʩչ�ľ���ʤ����һ�С�

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIM "�����ˮ" NOR; }

int perform(object me, object target)
{
        int damage;
        string msg;
        int ap, dp;
        int effqi, maxqi;
        string couple;
        object cob;

        if (! target) target = offensive_target(me);

        if (! target || ! me->is_fighting(target))
                return notify_fail(name() + "ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query("static/marry", me)>1 )
                return notify_fail("��������Ѳ��������ﻹ�����Ե�������Ȼ����ĸо���\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("����ڹ���򲻹���ʹ����" + name() + "��\n");

        if ((int)me->query_skill("sad-strike", 1) < 180)
                return notify_fail("�����Ȼ�����Ʋ�������������ʹ��" + name() + "��\n");

        if( query("neili", me)<500 )
                return notify_fail("��������������޷�ʹ��" + name() + "��\n");

        if (me->query_skill_mapped("unarmed") != "sad-strike")
                return notify_fail("��û�м�����Ȼ�����ƣ��޷�ʹ��" + name() + "��\n");

        if( !stringp(couple=query("couple/couple_id", me)) )
                return notify_fail("��û�����ӣ���᲻�����������ҵĸо���\n");
        /*
        if (! objectp(cob = find_player(couple)))
                return notify_fail("���Ų��ڰ���������˭����\n");
        */
        if( time()-query_temp("last_perform/sad-strike/tuo", me)<60 )
                return notify_fail("��ո�ʩչ�������ˮ����������û����ô�����ˡ�\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        effqi=query("eff_qi", me);
        maxqi=query("max_qi", me);

        ap = attack_power(me, "unarmed") +
             me->query_skill("force");

        dp = defense_power(target, "parry") +
             target->query_skill("force");

        me->start_busy(2);

        if (effqi < maxqi / 3)
        {
                msg = HIR "$N" HIR "���������ң���Ȼ������"
                      HIR "����һ�ۣ������������ˣ����Լ����ء���\n"
                      "����ʧ�����ǣ�����һ�У�ǡ��ʹ������Ȼ��������"
                      "�ġ������ˮ����\n" NOR;
                ap += ap  / 5;
        } else
        {
                msg = HIM "ֻ��$N" HIM "û����ɵĻ��������ĳ�һ�ƣ�����"
                      "��Ȼ�������еġ������ˮ����\n"NOR;
        }
        if (ap / 2 + random(ap) > dp)
        {
                damage = damage_power(me, "unarmed");
                damage+= query("jiali", me);
                addn("neili", -300, me);
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 200,
                                           HIR "ֻ��$n" HIR "һ���ƺߣ����ۡ���һ"
                                           "������һ�����û���$p" HIR "��ͷ�� \n"
                                           NOR);
                set_temp("last_perform/sad-strike/tuo", 1, me);
        } else
        {
                addn("neili", -100, me);
                msg += HIC "����$p" HIC "С��Ӧ���������мܣ���������һ�С�\n"
                       NOR;
        }
        message_combatd(msg, me, target);
        return 1;
}