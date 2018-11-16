// This program is a part of NITAN MudLIB
// chumo.c ������ħ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "������ħ"; }

int perform(object me)
{
        string msg;
        object target;
        int skill, ap, dp, damage;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("��������ħ��ֻ����ս���жԶ���ʹ�á�\n");

        skill = me->query_skill("yingzhua-gong", 1);

        if (skill < 135)
                return notify_fail("���ӥצ���ȼ�����������ʹ�á�������ħ����\n");

        if( query("neili", me)<250 )
                return notify_fail("��������������޷����á�������ħ����\n");

        if (me->query_skill_mapped("claw") != "yingzhua-gong")
                return notify_fail("��û�м���ӥצ�����޷�ʹ�á�������ħ����\n");

       if (! living(target))
              return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        msg = HIY "$N" HIY "΢΢һЦ��˫�ƻ�������$n" HIY "ץ��������"
              "����ȥҲƽƽ���棬���޶��پ���仯��\n" NOR;

        ap = attack_power(me, "claw") + me->query_skill("force");
        dp = defense_power(target, "dodge") + me->query_skill("parry");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -200, me);
                damage = damage_power(me, "claw");
                msg += COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 55,
                                           HIR "��֪��ô�ģ�$p" HIR "ȴƫƫ�㲻��$P"
                                           HIR "��һץ�������ץ�˸����У����ɵ���"
                                           "��һ�������˼�����\n" NOR);
                me->start_busy(1 + random(2));
        } else
        {
                msg += CYN "����$p" CYN "û������$P" CYN
                       "��һץ����æ�мܣ�˳��Ծ����û�б�$P"
                       CYN "���֡�\n" NOR;
                addn("neili", -40, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}