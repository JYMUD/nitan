// powerup.c ���ߴ�
// Last Modified by winder on Mar. 10 2000
//modified by sega 12/28/1999
//�������ӹ����뽵�Ͳ��ȺͲ���������bug

#include <ansi.h>

inherit F_CLEAN_UP;

void remove_effect(object me, int amount);

int exert(object me, object target)
{
        int skill;

/*
  if ( userp(me) && !wizardp(me) && 
  !query("perform/powerup", me) && 
  !query("can_perform/wudu-shengong/powerup", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("����ʹ�õ��ڹ���û�����ֹ��ܡ�");
*/

        if( target != me )
                return notify_fail("��ֻ�����嶾�������Լ���ս������\n");
        if( query("neili", me)<100 )
                return notify_fail("�������������\n");
        if( query_temp("powerup", me) )
                return notify_fail("���Ѿ����˹����ˡ�\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        message_combatd(BLU"$N�����嶾�񹦣�ͷ���������ڣ�ȫ���������ɫ���ۼף�˫Ŀ�׹����䣡\n" NOR, me);

        addn_temp("apply/armor", skill, me);
        addn_temp("apply/hand", skill/3, me);
        addn_temp("apply/attack", skill/3, me);
        set_temp("powerup", 1, me);

        me->start_call_out( (: call_other, __FILE__, "remove_effect", me, skill:), skill);

        if( me->is_fighting() ) me->start_busy(2);

        return 1;
}

void remove_effect(object me, int amount)
{
        if( query_temp("powerup", me) )
        {
                addn_temp("apply/hand", -amount/3, me);
                addn_temp("apply/attack", -amount/3, me);
                addn_temp("apply/armor", -amount, me);
                delete_temp("powerup", me);
                tell_object(me, "����嶾��������ϣ������𽥻ָ�������\n");
        }
}
int help(object me)
{
        write(WHT"\n�嶾��֮���ߴ󷨣�"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                �����Լ��Ĺ�����������

        ����Ҫ��
                ����100
HELP
        );
        return 1;
}
