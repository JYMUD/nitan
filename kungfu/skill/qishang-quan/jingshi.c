// jingshi.c ��ʧ��

#include <ansi.h>

inherit F_SSERVER;

string name() { return "��ʧ��"; }

int perform(object me)
{
        string msg,str;
        object target;
        int skill, jing_wound, eff_jing_wound, neili_wound;
        mixed ap, dp;

        me->clean_up_enemy();
        target = me->select_opponent();

        skill = me->query_skill("qishang-quan",1) + me->query_skill("force",1);

        if( !me->is_fighting() )
                return notify_fail("����ʧ����ֻ����ս����ʹ�á�\n");

        if( (int)query("neili", me) < 900 )
                return notify_fail("��������������ߣ�\n");

        if( (int)me->query_skill("cuff") < 250 )
                return notify_fail("���ȭ���������ң��޷���������ȭ�ĸ����ܾ���\n");

        if( (int)me->query_skill("qishang-quan", 1) < 250)
                return notify_fail("������ȭ����Ϊ���������ܹ���ᾫʧ��! \n");

        if( (int)me->query_skill("force", 1) < 250)
                return notify_fail(HIM "��Ļ����ڹ���Ϊ���㣬�������ʹ�þ�ʧ��! \n" NOR);

        if( me->query_skill_mapped("cuff") != "qishang-quan")
                return notify_fail("��û�м�������ȭ���޷����þ�ʧ����\n");

        if( me->query_skill_prepared("cuff") != "qishang-quan" )
                return notify_fail("��û��׼��ʹ������ȭ���޷�ʩչ����ʧ������\n");

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ���ʹ�ô��У�\n");


        msg = HIY "$N��������ʹ������ȭ�ܾ��еġ�" HIR "��ʧ��" HIY "����˫ȭ������������$n��ȥ��\n"NOR;
        message_vision(msg, me, target);

        ap = attack_power(me, "cuff");
        dp = defense_power(target, "dodge");

        if( ap / 2 + random(ap) > dp || !living(target) )
        {
                addn("neili", -300, me);

                msg = HIG "$N��ȭֻ�������������$n����$N����������һ˲����������$n���ڣ�\n$nֻ�����е�ƣ��������\n"NOR;
                neili_wound = damage_power(me, "cuff");
                neili_wound += query("jiali", me);
                if(neili_wound > query("neili", target))
                        neili_wound = query("neili", target);

                jing_wound = random((int)skill);
                jing_wound += query("jiali", me);
                eff_jing_wound = random((int)skill / 3);
                eff_jing_wound += (int)query("jiali", me)/2;
                target->receive_damage("jing", jing_wound, me);
                target->receive_wound("jing", eff_jing_wound, me);
                str = COMBAT_D->status_msg((int)query("qi", target) * 100 /(int)query("max_qi", target));
                msg += "($n"+str+")\n";
                me->start_busy(2);
                if (! target->is_busy())
                        target->start_busy(1 + random(2));
        }
        else
        {
                msg = HIG "ֻ��$n���Ų�æ������һ���������$N�ı�ɱһ����\n"NOR;

                addn("neili", -100, me);
                me->start_busy(3);
        }
        message_combatd(msg, me, target);

        return 1;
}