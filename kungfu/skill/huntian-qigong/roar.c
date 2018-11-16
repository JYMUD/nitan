// This program is a part of NT MudLIB
// roar.c ��Х

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if( query("neili", me)<600 )
                return notify_fail("�������������\n");

        if( query("no_fight", environment(me)) )
                return notify_fail("�����ﲻ�ܹ������ˡ�\n");

        skill = me->query_skill("force");

        addn("neili", -150, me);
        me->receive_damage("qi", 10);

        me->start_busy(5);
        message_combatd(HIY "$N" HIY "����һ��������������������һ��"
                        "��Х�����������������\n" NOR, me);

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! living(ob[i]) || ob[i] == me) continue;
                if (skill / 2 + random(skill / 2) < (int)ob[i]->query_con() * 2)
                        continue;

                if (userp(ob[i]) && !ob[i]->die_protect(me))
                        continue;

                damage=skill-(query("max_neili", ob[i])/10);
                if (damage > 0)
                {
                        ob[i]->receive_damage("jing", damage * 2, me);
                        if( query("neili", ob[i])<skill*2 )
                                ob[i]->receive_wound("jing", damage, me);
                        tell_object(ob[i], "�������ǰһ�������ð������ʹ������Ҫ�ѿ�һ����\n");
                }

                me->want_kill(ob[i]);
                me->fight_ob(ob[i]);
                ob[i]->kill_ob(me);
        }

        return 1;
}