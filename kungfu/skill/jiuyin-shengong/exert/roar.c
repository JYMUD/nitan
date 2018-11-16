// roar.c ��������

#include <ansi.h>

inherit F_CLEAN_UP;

int exert(object me, object target)
{
        object *ob;
        int i, skill, damage;

        if( query("neili", me)<100 )
                return notify_fail("�������������\n");

        skill = me->query_skill("force");

        addn("neili", -100, me);
        me->receive_damage("qi", 10);

        if( query("no_fight", environment(me)) )
                return notify_fail("���ﲻ�ܹ�������! \n");

        me->start_busy(5);
        message_combatd(HIY "$N" HIY "���������Ȼһ���Ϻȣ�һ����"
                        "ƽ���͵�����ԶԶ�Ĵ��˿�ȥ��������ֹ��\n" NOR, me);

        ob = all_inventory(environment(me));
        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character() || ob[i] == me)
                        continue;

                if( skill/2+random(skill/2)<query("con", ob[i])*2 )
                        continue;

                me->want_kill(ob[i]);
                me->fight_ob(ob[i]);
                ob[i]->kill_ob(me);
                
                damage=skill-(query("max_neili", ob[i])/10);
                if (damage > 0)
                {
                        set("last_damage_from", me, ob[i]);
                        ob[i]->receive_damage("jing", damage * 2, me);
                        if( query("neili", ob[i])<skill*2 )
                                ob[i]->receive_wound("jing", damage, me);
                        tell_object(ob[i], "��ֻ������ǰһƬģ��������"
                                    "����ǰ�ƺ��������ǹ���˸......\n");
                }
        }
        return 1;
}