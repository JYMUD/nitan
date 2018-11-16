// This program is a part of NT MudLIB
// qiong.c ��¥����

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;
string name() { return "��¥����"; }

int perform(object me, object target)
{
        int bonus, hits;
        object weapon;


        if (! target)
        {
                me->clean_up_enemy();
                target = me->select_opponent();
        }

        if (! target || ! me->is_fighting(target))
                return notify_fail("����¥���ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( query_temp("weapon", me) )
                return notify_fail("���ֲ���ʩչ����¥�����\n");

        if (! living(target))
                return notify_fail("�Է����Ѿ������ˣ��ò�����ô�����ɣ�\n");

        if( query("neili", me)<400 )
                return notify_fail("���������ʣ�޼����޷�ʩչ����¥�����\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("���������Ϊ���㣬�޷�ʩչ����¥�����\n");

        if ( me->query_skill("mingyu-gong", 1) < 200 )
                return notify_fail("��������񹦲�����죬����ʹ�á���¥�����\n");

        if ( me->query_skill("unarmed", 1) < 200 )
                return notify_fail("��Ļ���ȭ�Ų�����죬����ʹ�á���¥�����\n");

        if( query("jiali", me)<1 )
                return notify_fail("�����̫�٣��޷�ʹ�á����������\n");

        if ( me->query_skill_mapped("force") != "mingyu-gong" )
                return notify_fail("����ڹ�û��ʹ�����񹦣��޷�ʹ�á���¥���������\n");
        if ( me->query_skill_mapped("parry") != "mingyu-gong" )
                return notify_fail("����м�û��ʹ�����񹦣��޷�ʹ�á���¥���������\n");
        if ( me->query_skill_mapped("unarmed") != "mingyu-gong" )
                return notify_fail("���ȭ��û��ʹ�����񹦣��޷�ʹ�á���¥���������\n");
        if ( me->query_skill_mapped("dodge") != "mingyu-gong" )
                return notify_fail("����Ṧû��ʹ�����񹦣��޷�ʹ�á���¥���������\n");
        if( query("gender", me) != "Ů��" )
                return notify_fail("�㲢�Ǵ���֮�壬�޷�ʹ�á���¥���������\n");
        if( query_temp("mingyu_pfm/qiong", me) )
                return notify_fail("������ʹ�á���¥�����\n");

        if( query_temp("mingyu_pfm/qiong_over", me) )
                return notify_fail("��ո�ʹ�ù�����¥�������ʱ��Ѫ���������ǵ�һ�����ðɡ�\n");

        bonus = me->query_skill("mingyu-gong", 1) / 3;
        bonus += me->query_skill("unarmed", 1) /3;
        bonus += me->query_skill("force", 1) /3;

        addn_temp("apply/attack", bonus, me);
        addn_temp("apply/unarmed_damage", bonus, me);
        addn_temp("apply/defense", bonus*2, me);

         message_combatd(WHT"��"HIY"��¥����"WHT"��\n\n"HIG"ֻ��$N�ֹ⾢���ٶ�������������������չ�ᣬ
����һ�Ź�â����â��Ȼ����������һƬ���꣬��������$n������\n" NOR, me, target);

        set_temp("mingyu_pfm/qiong", bonus, me);
        addn("neili", -200, me);

        // call_out("check_fight", 1, me, target, bonus);
         me->start_call_out((: call_other, __FILE__, "remove_effect",
                              me, bonus :), bonus/4);

        return 1;
}

void remove_effect(object me, int bonus)
{
        addn_temp("apply/attack", -bonus, me);
        addn_temp("apply/unarmed_damage", -bonus, me);
        addn_temp("apply/defense", -bonus*2, me);
        delete_temp("mingyu_pfm/qiong", me);
        set_temp("mingyu_pfm/qiong_over", 1, me);
        if ( me->is_fighting() && !me->is_busy() )
                me->start_busy(3);

        me->start_call_out((: call_other, __FILE__, "qiong_done", me : ), 3);
}

void qiong_done(object me)
{
        if ( !me )
                return;

        tell_object(me, HIY"����һ��ʱ�����Ϣ�����ֿ���ʹ�á���¥����ˣ�\n"NOR);

        delete_temp("mingyu_pfm/qiong_over", me);
}

void check_fight(object me, object target, int bonus)
{
        if ( !me )
                return;

        if( !me->is_fighting() || !query_temp("mingyu_pfm/qiong", me) || query_temp("mingyu_pfm/qiong", me)<1
             || !target || ! (living(target)) )
        {
                message_combatd(WHT"\n$N������һ���������е����ξ���Ҳ�Բ�����ǰһ�������ˡ�\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( query("neili", me)<300 )
        {
                message_combatd(HIR"\n$N��ͷð�����������������棬���ϵľ���һ����ʧ�����ˡ�\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if ( me->query_skill_mapped("unarmed") != "mingyu-gong" )
        {
                message_combatd(HIR"\n$N��Ȼ��ʽһ�ߣ����ϵľ�����ʱ��ʧ����Ӱ���١�\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        if( query_temp("weapon", me) )
        {
                tell_object(me, HIR"\n��װ���ϱ������޷�����ʹ�á���¥����ˡ�\n"NOR, me);
                remove_effect(me, bonus);
                return;
        }

        remove_call_out("check_fight");
        call_out("check_fight", 1, me, target, bonus);
}


