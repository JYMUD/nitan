// by rcwiz for yhonline
// ������

#include <ansi.h>

inherit FORCE;

string *dodge_msg = ({
        HIW "$n" HIW "�������һ�Σ�$N" HIW "��Ȼ�޷�������ֻ���Ա���\n" NOR,
        HIW "ֻ��$n" HIW "��������ζ���$N" HIW "��ǰ��ʱ������������$n" HIW
        "�Ļ�Ӱ����$N" HIW "��ȫ�޷������ʵ��\n" NOR,
        HIW "$n" HIW "���Ա�����бб������һ����ȴǡ����$N" HIW "�Ĺ���ʧ֮"
        "���塣\n" NOR,
        HIW "$N" HIW "��һ�����ĺÿ죬Ȼ��$n" HIW "һ�����ƺ����Ѱ��������"
        "ȴ��$N" HIW "��һ�иպñܿ���\n" NOR,
        HIW "����$n" HIW "����һԾ���Ѳ�������Ӱ��$N" HIW "���д󺧣�ȴ�ּ�"
        "$n" HIW "���籼��������֮���ɣ���������˼�����ǡ�\n" NOR,
});

string *parry_msg = ({
        HIW "$N" HIW "һ�л���$n" HIW "���ϣ���������ʧ����Ӱ���٣�\n" NOR,
        HIW "$n����һ����$N" HIW "�����Լ������ػ��������ŵ������˼�����\n" NOR,
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bagua-shengong", 1);
        return lvl * lvl * 15 * 40 / 100 / 200;
}

mapping *action = ({
([
        "action": HIW "$N" HIW "����һ�ӣ�ɲ�Ǽ������� ���˲���������" NOR,
        "attack": 999,
        "dodge" : 999,
        "parry" : 999,
        "damage": 999,
        "force" : 999,
        "damage_type":  "����"
]),
([
        "action": HIG "$N" HIG "����΢�䣬��Ȼ���籩�꣬��ɫ��䡣" NOR,
        "attack": 999,
        "dodge" : 999,
        "parry" : 999,
        "damage": 999,
        "force" : 999,
        "damage_type":  "����"
]),
});

string *usage_skills = ({ "unarmed", "strike", "claw", "hand", "cuff", "finger",
                          "sword", "blade", "hammer", "throwing", "club", "whip",
                          "staff", "dodge", "dagger", "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force)
{
        return 1;
}

int double_attack()
{
        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        object ob;
        int lvl;
        
        lvl = me->query_skill("force");
        
        if( query_temp("baguazhen", victim) >= 3 )
        {
                if (lvl / 2 + random(lvl) > victim->query_skill("force") )
                {
                      if (random(2))
                      {
                           victim->receive_wound("qi", 300);
                           addn("jing", -50, victim);
                      }
                      else 
                      {
                           message_vision(HIR "$N" HIR "����$n" HIR "��㼸�£�$n" HIR 
                                          "���޷������ˡ�\n" NOR, me, victim);
                                     
                           victim->start_busy(20 + random(20));                                            
                      }
                }
                return;
        }

        if (random(20) == 1)
        {
                message_vision(NOR + HIG "��Ȼ��һ������Ʈ�����������"
                               "��������Ӱ�� ����\n", me, victim);               

                victim->move("/kungfu/class/sky/bagua");

                return;                
        }

        victim->receive_wound("qi", 500);
        addn("jing", -30, victim);

        return;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;

        if (random(10) == 0)
        {
                result = ([ "damage": -damage ]);

                result += (["msg" : HIW "$n" HIW "�����㼸�£���Ȼ�䲻������Ӱ��\n" NOR]);

                return result;
        }
}


