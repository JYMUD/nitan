#include <ansi.h>

string name() { return HIW "����" NOR; } 

inherit F_SSERVER; 

int perform(object me, object target)
{
        int skill;
        object ob;
        object weapon;
        
        if( query("neili", me)<8000 )
                return notify_fail("�������������\n");

        if ((int)me->query_skill("badao", 1) < 1500)
                return notify_fail("��İԵ���Ϊ������\n");

        if (me->query_skill_mapped("blade") != "badao")
                return notify_fail("�㻹û�м����Ե��ء�\n");
                
        if (find_living(query("id", me) + "-daohun"))
                return notify_fail("��ĵ��껹û����ʧ����ʱ����ʩչ���С�\n");

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("��ʹ�õ��������ԣ�\n");

        skill = me->query_skill("badao", 1);
        addn("neili", -8000, me);

        message_combatd(HIY "\n$N" HIY "��������" + weapon->name() + HIY "��ɲ�Ǽ仪������һ��"
                        "��Ӱ��" + weapon->name() + HIY "�лû����� ����\n\n" NOR, me);

        // ���õ���
        ob = new("/kungfu/class/misc/daohun");
        ob->init_npc(me);
        ob->move(environment(me));

        me->start_busy(3);
        
        return 1;
}
