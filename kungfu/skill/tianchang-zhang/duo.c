// duo.c ���ֶ����

#include <ansi.h>

inherit F_SSERVER;

string name() { return "���ֶ����"; }

int perform(object me, object target)
{
        string msg;
        object weapon, weapon2;
        int skill;
        int comb1,comb2;
        mixed exp1, exp2;
        int skill1,skill2,neili1,neili2,str1,str2;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("tianchang-zhang",1);

        if( !(me->is_fighting() ))
                return notify_fail("���ֶ����ֻ�ܶ�ս���еĶ���ʹ�á�\n");

        if( objectp(weapon2=query_temp("weapon", me)) )
                return notify_fail("�������֡�\n");

        if( !objectp(weapon=query_temp("weapon", target)) )
                return notify_fail("�Է�û�б��У��㲻�õ��ġ�\n");

        if( skill < 100)
                return notify_fail("����쳤�Ʒ��ȼ�����, ����ʹ�ÿ��ֶ���У�\n");

        if ((int)me->query_skill("lengyue-shengong", 1)<100)
                return notify_fail("��������񹦻�򲻹���\n");

        if ( me->query_skill_mapped("force") != "lengyue-shengong")
                return notify_fail("��û�����������񹦣�\n");

        if( query("neili", me)<300 )
                return notify_fail("��������������޷�ʹ�ÿ�����÷��\n");

        if( !living(target))
                return notify_fail("�Է����Ѿ������ˣ�����ʲô��ȥ����ˣ�\n");

        message_combatd(CYN"\n$N�����������֣���׼$n�书����֮����ץ��$n���е�"+query("name", weapon)+CYN"��\n\n"NOR,me,target);

        exp1=query("combat_exp", me);
        exp2=query("combat_exp", target);
        skill1 = me->query_skill("tianchang-zhang");
        skill2 = target->query_skill("parry");
        neili1=query("neili", me);
        neili2=query("neili", target);
        str1 = me->query_str();
        str2 = target->query_str();

        if (exp1 < exp2/3)
        {
                message_combatd("˭֪$n¶�������������յУ�һ�����з�����$N�͹�������\n",me,target);
                me->start_busy(1+random(3));
                addn("neili", -50, me);
                COMBAT_D->do_attack(target,me,query_temp("weapon", me));
                return 1;
        }

        if (exp1/ 100 > random(exp2/ 100))
        {
                message_combatd(HIR"$n�۾�һ��������"+query("name", weapon)+HIR"�ѱ�$N����ץ����\n\n"NOR,me,target);
                comb1 = str1*neili1*skill1;
                comb2 = str2*neili2*skill2;

                if (comb1 > comb2 * 3/5 )
                {
                        message_combatd(HIW"$nֻ��һ�ɺ�����"+query("name", weapon)+HIW"���˹����������ֱ�һ�����������"+query("name", weapon)+HIW"���ֶ�����\n"NOR,me,target);
                        weapon->unequip();
                        weapon->move(me);
                        addn("neili", -50, me);
                        return 1;
                }
                message_combatd(HIW"$NĬ�����º������߶���������ע��"+query("name", weapon)+HIW"��$n��״�Ͻ��߶��������������࿹��\n\n"NOR,me,target);
                message_combatd(HIG"$Nֻ��$n���е�"+query("name", weapon)+HIG"����һ�����ȵ����������Լ������º������������Σ�ֻ�÷��֣�Ʈ���˿���\n"NOR,me,target);
                me->start_busy(1+random(2));
                addn("neili", -150, me);
                return 1;

        }
        message_combatd("����$n�Ŀ�����$N����ͼ�����̲�ȡ���ƣ�Ʈ��㿪$N�Ĺ�����\n",me,target);
        addn("neili", -50, me);
        me->start_busy(1+random(2));
        return 1;
}