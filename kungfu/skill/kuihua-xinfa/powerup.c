// powerup.c
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
inherit F_CLEAN_UP;
void remove_effect(object me, int amount);
int exert(object me, object target)
{
        int skill;
/*
  if ( userp(me) && !wizardp(me) && 
  !query("perform/powerup", me) && 
  !query("can_perform/kuihua-xinfa/powerup", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("����ʹ�õ��ڹ���û�����ֹ��ܡ�");
*/

        if( target != me )
                return notify_fail("��ֻ���ÿ����ķ������Լ���ս������\n");
        if( query("neili", me)<100 )
                return notify_fail("�������������\n");
        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi",0);

        message_combatd(MAG"$N�ſ�һ��������Х����������ķ�����ͻȻ���Ʈ����ȣ���ȥ��磡\n" NOR, me);

        addn_temp("apply/attack", skill/3, me);
        addn_temp("apply/dodge", skill/3, me);
        set_temp("powerup", 1, me);
        me->start_call_out((:call_other,__FILE__,"remove_effect",me,skill/3:),skill);
        if( me->is_fighting() ) me->start_busy(3);
        return 1;
}

void remove_effect(object me, int amount)
{
        addn_temp("apply/attack", -amount, me);
        addn_temp("apply/dodge", -amount, me);
        delete_temp("powerup", me);
        tell_object(me, "��Ŀ����ķ�������ϣ��������ջص��\n");
}

int help(object me)
{
        write(WHT"\n�����ķ�֮������"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                �����Լ��Ĺ�����������

        ����Ҫ��
                ����100
HELP
        );
        return 1;
}
