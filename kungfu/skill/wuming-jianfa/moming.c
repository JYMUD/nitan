// ����Ī��

#include <ansi.h>
#include <combat.h>

inherit F_SSERVER;

string name() { return "����Ī��"; }
int perform(object me, object target)
{
        object weapon, ob;
        string msg;
        int i,j,times,n;

        i = me->query_skill("wuming-jianfa", 1)/60;
        j = me->query_skill("sword")/60;

        if (! target) 
        {
                me->clean_up_enemy(); 
                target = me->select_opponent(); 
        }
        if (! target || ! me->is_fighting(target)) 
                return notify_fail("��ֻ�ܶ�ս���еĶ���ʹ�þ��С�����Ī������\n"); 
        if( !objectp(weapon=query_temp("weapon", me)))return notify_fail("�����ʹ����������ʹ�á�����Ī������\n");
        //if ( base_name(weapon)!="/clone/weapon/yuenv" ) return notify_fail("������ֳ�ԽŮ����������ʹ�á�����Ī������\n");
        if ( (int)me->query_str() < 35 ) return notify_fail("��ı�������, ������ʹ���������! \n");
        if ( (int)me->query_skill("sword",1) < 600 ) return notify_fail("��Ļ��������Ļ�򻹲�����, ����ʹ����һ���� !\n");
        if ( (int)me->query_skill("wuming-jianfa", 1) < 500 ) return notify_fail("������������Ļ�򻹲�����, ����ʹ����һ���� !\n");
        if( query("neili", me)<50000)return notify_fail("�������������\n");
        if( query("max_neili", me)<50000)return notify_fail("���������Ϊ������\n");
        if ( me->is_busy() ) return notify_fail("����һ��������û����ɣ�\n");

        msg = MAG "\n$N������˼,�����糱ӿ����ͷ,���н�����бָһ��Թ���ӽ���ɢ������������\n" NOR;
        message_combatd(msg, me);
        ob = target;
        addn_temp("apply/str", i, me);
        addn_temp("apply/attack", j, me);
        times = (int)(me->query_skill("wuming-jianfa", 1)/50) - 1;
        if( times > 12 ) times = 12;
        for ( n=0; n<times; n++ )
        {
                if ( !ob ) break;
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me),1);
        }
        addn_temp("apply/str", -i, me);
        addn_temp("apply/attack", -j, me);
        addn("neili", -random(5000)-5000, me);
        me->start_busy(random(2)+2);
        if ( ob && !ob->is_busy() ) ob->start_busy(random(2)+1);
        return 1;
}
