// honglian.c ���浶  ������

#include <ansi.h>
inherit F_SSERVER;

string name() { return "������"; }

void remove_effect(object me, int amount);

int perform(object me)
{
        int count, skill;
        skill = me->query_skill("longxiang-gong");

        /*
        if( !me->is_fighting() )
                return notify_fail("��������ֻ����ս���е�ʹ�á�\n");
        */

        if( objectp(query_temp("weapon", me)) )
                return notify_fail("�������ֲ������á������𡹣�\n");

        if( query_temp("honglian", me) )
                return notify_fail("������ʹ�á������𡹡�\n");

        if( (int)me->query_skill("huoyan-dao", 1) < 180 )
                return notify_fail("��Ļ��浶������죬��������ᡸ������֮���ϡ�\n");

        if ( me->query_skill_mapped("strike") != "huoyan-dao")
                return notify_fail("�����ʹ�û��浶��ʩչ�������𡹡�\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("���������Ϊ̫����ʹ�����������𡹡�\n");

        if( query("neili", me)<800 )
                return notify_fail("����������������ʹ�����������𡹡�\n");

        if( userp(me) && (int)me->query_skill("longxiang-gong", 1) < 100 )
                return notify_fail("�����������񹦵ȼ������ߣ�ʹ�����������𡹡�\n");

        if( me->query_skill_mapped("force") != "longxiang-gong" && me->query_skill_mapped("force") != "xiaowuxiang")
                return notify_fail("����ʹ�ڹ��ڻ��浶�ķ�������ʹ�����������𡹡�\n");

        if( userp(me) && (int)me->query_skill("lamaism", 1) < 150 )
                return notify_fail("��������ķ������򲻹����޷�ʹ�á������𡹡�\n");

        me->receive_damage("qi", 0);
        message_combatd(RED"\n$N" RED "������浶֮�������𡹾����������������ʺ�ɫ����ӿ��������ǰ����֮��\n"
                        RED "Ʈ���޶����������ڰ�գ�������翣�����׽����\n"NOR,me);
        count = skill / 2;


        addn("neili", -300, me);
        addn("jing", -50, me);
        addn_temp("apply/attack", count, me);
        addn_temp("apply/strike", count/2, me);
        set_temp("honglian", 1, me);
        me->start_call_out( (: call_other,  __FILE__, "remove_effect", me, count :), skill/3 );

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("honglian", me) )
        {
                addn_temp("apply/attack", -amount, me);
                addn_temp("apply/strike", -amount/2, me);
                delete_temp("honglian", me);
                tell_object(me,HIR "����ǰƮ���޶��Ļ���������ȥ��\n"NOR);
        }
}
