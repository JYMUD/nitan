// This program is a part of NITAN MudLIB
// guizhao.c  �����צ

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return HIB "�����צ" NOR; }

int perform(object me, object target)
{
        int skill, ap, dp, damage;
        string msg, pmsg;

        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("�������צ��ֻ����ս����ʹ�á�\n");

        if( query("gender", me) != "Ů��" )
                return notify_fail("����Ϊ���ӣ�������ᡸ�����צ�����еİ��\n");

        if( query("shen", me)>0 )
                return notify_fail("�����������ʿ���������á������צ�����������书��\n");

        if ((int)me->query_skill("youming-guizhao", 1) < 180)
                return notify_fail("�����ڤ��צ�ȼ�����������ʹ�á������צ����\n");

        if ((int)me->query_skill("claw", 1) < 180)
                return notify_fail("��Ļ���צ����������죬����ʹ�á������צ����\n");

        if ((int)me->query_skill("force", 1) < 180)
                return notify_fail("��Ļ����ڹ���򲻹���ǿ��ʹ�á������צ���������Լ��ľ�����\n");

        /*
        if ((int)me->query_skill("xiaowuxiang", 1) < 180
                && (int)me->query_skill("bahuang-gong", 1) < 180
                && (int)me->query_skill("beiming-shengong", 1) < 180)
                return notify_fail("�����ң���ڹ���򲻹���\n");

        if (me->query_skill_mapped("force") != "xiaowuxiang"
                || me->query_skill_mapped("force") != "bahuang-gong"
                || me->query_skill_mapped("force") != "beiming-shengong")
                return notify_fail("��û��������ң���ڹ���\n");
        */

        if( query("neili", me)<800 )
                return notify_fail("����������̫��������ʹ�á������צ����\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("����������̫��������ʹ�á������צ����\n");

        if( query_temp("gz_pfmed", me) == 1 )
                return notify_fail("���ʹ����һ�У����ܾۼ��㹻��Ԫ����\n");

        if( !query("jiali", me) )
                return notify_fail("��צ�ϴ������㣬����ʹ�á������צ����\n");

        skill = (int)me->query_skill("youming-guizhao", 1);

        message_combatd(HIB "\nͻȻ$N" HIB "��˫�Ʊ�צ������ǰ����糵�㼱ת��Ȧ������˫צ����һ��\n"
                        "����$n" HIB "��ת��Ȧ�������ָ����$n����ֱ�²��䡣\n\n" NOR, me, target);

        addn("neili", -400, me);
        set_temp("gz_pfmed", 1, me);

        call_out("recover", 1800 / skill, me);


        ap = attack_power(me, "claw");
        dp = defense_power(target, "dodge");

        if (ap / 2 + random(ap) > dp)
        {
                addn("neili", -100, me);
                damage = damage_power(me, "claw");
                damage+= query("jiali", me);
                pmsg = HIR "$n" HIR "ֻ����ͷ��һ��������$N"
                       HIR "����צ����$n" HIR "ͷ������������������ָ����\n" NOR;
                msg = COMBAT_D->do_damage(me, target, UNARMED_ATTACK, damage, 80, pmsg);
                me->start_busy(2);
        } else
        {
                msg = CYN "����$p" CYN"��������������������ͷ������㣬���ǿ����ܹ�$P"
                      CYN "�Ĺ��������Ѿ�����һ���亹��\n\n" NOR;
                me->start_busy(3);
        }

        message_combatd(msg, me, target);

        if (userp(target))
                target->fight_ob(me);
        else
        if (! target->is_killing(me))
                target->kill_ob(me);
        return 1;
}

int recover(object me)
{
        if (! me) return 0;

        delete_temp("gz_pfmed", me);
        return 1;
}
