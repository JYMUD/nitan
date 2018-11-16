// This program is a part of NT MudLIB
// sanjiao.c ���������

#include <ansi.h>

inherit F_SSERVER;

string name() { return HIR "���������"; }

int perform(object me,object target)
{
        string msg;
        object weapon;
        int skill, ap, dp, neili_wound, qi_wound;
        int flag;
        int damage;
        string fskill,bskill,pskill,sskill;


        if( !objectp(target) )
        {
                flag =1;
                target = offensive_target(me);
        }

        if( !target || !target->is_character() || target == me ||
            !me->is_fighting(target) ||
            !living(target) )
                return notify_fail(name()+"ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if (objectp(weapon = query_temp("weapon", me)))
                return notify_fail("�������ֲ���ʹ�á��������������\n");

        fskill = "jiuyang-shengong";
        sskill = "qishang-quan";
        bskill = "cuff";

        if( (int)me->query_skill(fskill, 1) < 200 )
                return notify_fail("���"+to_chinese(fskill)+"��Ϊ���㣬�������ʹ��"+name()+"��\n");

        if( (int)me->query_skill(sskill, 1) < 200 )
                return notify_fail("���"+to_chinese(sskill)+"����Ϊ���������ܹ����"+name()+"��\n");

        if( (int)me->query_skill(bskill, 1) < 200 )
                return notify_fail("���"+to_chinese(bskill)+"�������ң��޷���������ȭ��"+name()+"��\n");

        if( (int)query("neili", me) < 2000 )
                return notify_fail("��������������ߣ�\n");

        skill = me->query_skill(bskill,1) + me->query_skill("force",1);

        msg = HIY"$N����������ͼʹ������ȭ�ܾ��еġ�" HIR "���������" HIY "�������з�����������\n"NOR;

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "force");

        if( ap /2 + random(ap) > dp || !living(target))
        {
                addn("neili", -500, me);

                msg += HIG "$nֻ������ǰһ���ʹ�����ۡ���һ�����һ����Ѫ��\n"NOR;
                neili_wound = damage_power(me, "cuff");
                damage+= query("jiali", me);
                qi_wound = neili_wound ;
                if(qi_wound > query("qi", target))
                        qi_wound = query("qi", target);
                target->receive_wound("qi", qi_wound,me);

                if(neili_wound > query("neili", target))
                        neili_wound = query("neili", target);
                addn("neili", -neili_wound, target);
                if( !target->is_busy() )
                        target->start_busy(2);
                me->start_busy(random(3));
        }
        else
        {
                msg+=HIG "ֻ��$n���Ų�æ������һ���������$N�ı�ɱһ����\n"NOR;
                addn("neili", -200, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        if(!target->is_fighting(me)) target->fight_ob(me);
        return 1;
}

