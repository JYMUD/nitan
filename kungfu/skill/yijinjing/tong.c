// shield.c �׽ һ��ͨ����

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill, qi, maxqi;


        if( query("family/family_name", me) != "������" )
                return notify_fail("�㲻�����ֵ��ӣ��޷�ʹ���׽������\n");

        if (target != me)
                return notify_fail("��ֻ�����׽������һ��ͨ���� \n");

        if ((skill = (int)me->query_skill("yijinjing", 1)) < 100)
                return notify_fail("����׽�ȼ�������\n");

        if( query("eff_qi", me)*100/query("max_qi", me)>80 )
                return notify_fail("�����ƺ��ᣬ�޷������׽���߾�ѧ��\n");

        if( query("eff_qi", me)*100/query("max_qi", me)<10 )
                return notify_fail("������̫�أ��޷������׽���߾�ѧ��\n");

        if( query("neili", me)<skill*5 || 
            query("max_neili", me)<500 )
                return notify_fail("�������������\n");

        addn("neili", -skill*5, me);
        me->receive_damage("qi", 0);

        message_combatd(HIM "$N" HIM "Ĭ���׽�Ŀھ�: "
                            "Ԫ��,��������,�����⡣"
                            "�׽�,�л���Ϣ,����֧....\n"
                        HIW "һ����͵İ�ɫ�����ͷ��Ѹ��"
                        HIW "�α�" HIW "$N" HIW "���澭������\n"
                        HIR "�������ɲ�Ǽ��Ϊ��ת����\n" NOR, me);

        addn("max_neili", -skill/5, me);

        addn("eff_qi", skill*5, me);
        if( query("eff_qi", me)>query("max_qi", me) )
                set("eff_qi",query("max_qi",  me), me);
        set("qi",query("eff_qi",  me), me);

        if (me->is_fighting()) me->start_busy(5+random(5));

        return 1;
}