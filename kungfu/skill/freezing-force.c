// freezing-force.c ���� ���Ϻ���
// Feb.21 1998 by Java

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage)
{
        return usage == "force";
}

int valid_force(string force)
{
        return 1;
        return force == "guixi-gong";
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("freezing-force", 1);
        return lvl * lvl * 22 * 18 / 100 / 200;
}

int valid_learn(object me)
{
        if( (!me->query_family() || 
            me->query_family() != "������") && (!query("reborn/times", me) || member_array("������", query("reborn/fams", me)) == -1) ) 
                return notify_fail("�㲻�����������ˣ��޷�ѧϰ���񹦡�\n");

        if (me->query_skill("force", 1) < 50)
                return notify_fail("��Ļ����ڹ���򲻹������Զ������Ϻ�����\n");

/*
        if (me->query_skill("yijinjing", 1))
                me->delete_skill("yijinjing");
*/

        if (me->query_skill("force", 1) < me->query_skill("freezing-force", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���������Զ��������ı��Ϻ�����\n");

        return ::valid_learn(me);
}

int practice_skill(object me)
{
        return notify_fail("���Ϻ����޷�ͨ���򵥵���ϰ�����������ȡ�\n");
}

// hit effect called by combatd
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        mixed result;
        int lvl;
        int flvl;

        result = ::hit_ob(me, victim, damage_bonus, factor);
        if (intp(result) && result > 0)
        {
                lvl  = me->query_skill("freezing-force", 1);
                flvl=query("jiali", me);
                if (lvl < 80 || flvl < 10)
                        return;

                if (flvl * 2 + random(lvl) > victim->query_skill("force"))
                {
                        victim->affect_by("freezing",
                                ([ "level" : flvl * 3 / 2 + random(flvl / 2),
                                   "id":query("id", me),
                                   "duration" : lvl / 40 + random(lvl / 20) ]));

                        return ([ "damage" : result * 2,
                                  "msg" : HIW "��ʱ$n" HIW "ֻ���ú���Ϯ"
                                          "�壬����˵���������ܡ�\n" NOR ]);
                }
        }

        return result;
}

string exert_function_file(string func)
{
        return __DIR__"freezing-force/" + func;
}

string *fanzhen_msg = ({
        "ֻ���$N���ڸ��У���������һ�뷭ת��\n",
        "���ȷ��𣬽�$N��������ֽ��ȫ��Ѫɫ��\n",
        "���$N�ķ����ѣ�����������������\n",
        "�����Ѳ���ȫ����$N�����������ȥ��\n",
        "���$N������ת�������������߰˲���\n",
        "��$Nһײ��ֻ���$p�ؿ���Ѫ��ӿ��\n",
        "$N����ײ��һ���޻����棬����Ϊ��ĺ�ǽ��һ�㣬����������\n",
        "$N������$p��ͻȻ����һ�𣬵�ʱ���˳�ȥ��\n",
});
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        string msg;
        int ap, dp;
        int jiali;
        object weapon1;
        
        if ((int) me->query_skill("freezing-force", 1) < 200 ||
            ! living(me))
                return;                      

        if( (jiali=query("jiali", ob))<1 )
                return;

        ap=ob->query_skill("force")+query("neili", ob)+
             ob->query_skill("count", 1);
        dp=me->query_skill("force")+query("neili", me);

        if (ap / 2 + random(ap) < dp)
        {
                if( !objectp(weapon1=query_temp("weapon", ob)) )
                {
                        result = ([ "damage" : -damage ]);
                        
                        msg = random(2) ? HIR "$n��������һ�ɷ���֮����" : HIR "$n���ϱ��Ϻ������Ķ���";   
                              
                        msg += fanzhen_msg[random(sizeof(fanzhen_msg))] + NOR;             
                
                        ob->receive_damage("qi", damage, me);
                        ob->receive_wound("qi", damage / 2, me);      
                        
                        result += ([ "msg" : msg ]);
                        
                        return result;
                } else
                {
                        result = ([ "damage" : -damage ]);

                        switch (random(5))
                        {
                        case 0:  
                        case 1:
                        case 2:
                        case 3:                                                
                                result += ([ "msg" : HIR "������һ�����ε�ǽ��$n��ǰ�赲�ţ����"
                                                     "$N" HIR "һ���ӱ����������$N" 
                                                     HIR "�ֱ۷��飡\n" NOR ]);
                                break;
                        default:
                                result += ([ "msg" : HIR "���$n��������һ�ɷ���֮����$Nֻ������һ�ȣ�" + 
                                                     weapon1->name() + HIR "��ʱ���ֶ������ɳ����⣡\n" NOR]);
                                weapon1->unequip();
                                weapon1->move(environment(ob));
                                ob->reset_action();
                                if (! ob->is_busy())
                                        ob->start_busy(1);
                                break;
                        }

                        return result;
                }
        }
}
