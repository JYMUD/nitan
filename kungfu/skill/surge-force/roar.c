// roar.c ��Ȼ��

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if (me->query_skill("surge-force", 1) < 100)
                return notify_fail("����Ȼһ����̾����������˼�ֻ����\n");

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ�ܹ�������! \n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 10);

        me->start_busy(5);
        message_combatd(HIR "$N" HIR "���쳤Х������һ��һ���ĵ���"
                        "ȥ�����˷����������������ԣ�\n" NOR, me);

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character() || ob[i] == me)
                        continue;

                if( skill/2+random(skill/2)<query("con", ob[i])*2 )
                        continue;

                if ((int)ob[i]->query_condition("die_guard"))
                        continue;

                me->want_kill(ob[i]);
                me->fight_ob(ob[i]);
                ob[i]->kill_ob(me);
                
                damage=skill-(query("max_neili", ob[i])/10);
                if (damage > 0)
                {
                        ob[i]->receive_damage("jing", damage * 2, me);
                        if( query("neili", ob[i])<skill*2 )
                                ob[i]->receive_wound("jing", damage, me);
                        tell_object(ob[i], "���������Ӻ��һ��......\n");
                }
        }
        return 1;
}