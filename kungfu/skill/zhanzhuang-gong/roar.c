// roar.c ����ʨ�Ӻ�
// Last Modified by winder on May. 29 2001

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

  if ( userp(me) && !wizardp(me) && 
  !query("perform/roar", me) && 
  !query("can_perform/zhanzhuang-gong/roar", me) && 
  !query_temp("murong/xingyi", me) )
   return notify_fail("����ʹ�õ��ڹ���û�����ֹ��ܡ�");
        if( (query("neili", me)<600) || 
                (query("max_neili", me)<600) || 
                ((int)me->query_skill("zhanzhuang-gong",1) < 100) )
                return notify_fail("����������������ĺ���һ��, ��������˼�ֻ����\n");
        if( query("no_fight", environment(me)) )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        skill = me->query_skill("force");
        addn("neili", -150, me);
        me->receive_damage("qi", 10);

        me->start_busy(5);
        message_combatd(HIY"$N�������һ�����������ŷ�������һ�����춯�صľ޺�\n" NOR, me);

        ob = all_inventory(environment(me));
        for(i=0; i<sizeof(ob); i++)
        {
                if( !living(ob[i]) || query_temp("noliving", ob[i]) || ob[i] == me)continue;

                if( skill/2+random(skill/2)<query("con", ob[i])*2)continue;

                if (!userp(ob[i]) && !ob[i]->accept_hit(me)) continue;

                damage=skill-(query("max_neili", ob[i])/10);

                if( damage > 0 )
                {
                        ob[i]->receive_damage("jing", damage * 2 );
                        if( query("neili", ob[i])<skill*2 )
                                ob[i]->receive_wound("jing", damage);
                tell_object(ob[i], "�������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n");
                }

                if( userp(ob[i]) ) ob[i]->fight_ob(me);
                else if( !ob[i]->is_killing(me) ) ob[i]->kill_ob(me);
        }

        return 1;
}

int help(object me)
{
        write(WHT"\nվ׮��֮����ʨ�Ӻ�"NOR"\n");
        write(@HELP

        ʹ�ù�Ч��
                �˺��Լ���Χ����������ľ���

        ����Ҫ��
                վ׮��100��
                ����600
HELP
        );
        return 1;
}