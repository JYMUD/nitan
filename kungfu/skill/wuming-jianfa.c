// ��������

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      "action":HIB"\n$NĬ�� ���ġ�,�����ݺ�ֱֱָ��$n��$l"NOR,
        "force" : 160,
        "lvl" : 0,
"skill_name" : "���ġ��־�",
        "damage_type":        "����"
]),
([      "action":HIR"\n$NĬ�� �ֺޡ�,�����ݺ�ֱֱָ��$n��$l"NOR,
        "force" : 240,
        "lvl" : 50,
"skill_name" : "��ޡ��־�",
        "damage_type":        "����"
]),
([      "action":HIY"\n$NĬ�� ��Թ��,�����ݺ�ֱֱָ��$n��$l"NOR,
        "force" : 280,
        "lvl" : 75,
"skill_name" : "��Թ���־�",
        "damage_type":        "����"
]),
([      "action":HIM"\n$NĬ�� �ְ���,�����ݺ�ֱֱָ��$n��$l"NOR,
        "force" : 320,
        "lvl" : 120,
"skill_name" : "�ﰮ���־�",
        "damage_type":        "����"
]),
([      "action":HIC"\n$NĬ�� ��˼��,�����ݺ�ֱֱָ��$n��$l"NOR,
        "force" : 380,
        "lvl" : 230,
"skill_name" : "��˼���־�",
        "damage_type":        "����"
]),
([      "action":HIG"\n$NĬ�� �����,�����ݺ�ֱֱָ��$n��$l"NOR,
        "force" : 420,
        "lvl" : 250,
"skill_name" : "������־�",
        "damage_type":        "����"
]),
([      "action":CYN"\n$NĬ�� �ֶ���,�����ݺ�ֱֱָ��$n��$l"NOR,
        "force" : 450,
        "lvl" : 330,
"skill_name" : "������־�",
        "damage_type":        "����"
]),
([      "action":HIR"\n$NĬ�� �ֳ��,�����ݺ�ֱֱָ��$n��$l"NOR,
        "force" : 480,
        "lvl" : 380,
"skill_name" : "�����־�",
        "damage_type":        "����"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("�������������\n");
//           if ((int)me->query_skill("wudu-shengong", 1) < 20)
//                  return notify_fail("����嶾�񹦻��̫ǳ��\n");
        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("��Ļ����ڹ����̫ǳ��\n");
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        mapping a_action;
        int i, level;
level   = (int) me->query_skill("wuming-jianfa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"]){
                        a_action=action[NewRandom(i, 20, level/5)];
                       break;
                 }
    a_action["dodge"]  = 0-level/2;
    a_action["parry"]  = 0-level/2;
    a_action["damage"] = level/2;
    return a_action;
}


int practice_skill(object me)
{
        object weapon;

        return notify_fail("��������������޷�������ͨ����ϰ������\n");

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("��ʹ�õ��������ԡ�\n");
        if((int)me->query_skill("wuming-jianfa",1) < 300)
                return notify_fail("��������ϰ��������,����û���κν�����\n");
        if( query("qi", me)<40 )
                return notify_fail("�����������������������\n");
        me->receive_damage("qi", 20);
        return 1;
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
  if( random(damage_bonus/2) > victim->query_con() ) {
                victim->receive_wound("qi", damage_bonus/ 3 );
        }
/*
  if( query("family/family_name", victim) != "�嶾��" && me->query_skill("wudu-shengong",1)>80){
         switch( random(5) ) {
                case 0:
            victim->apply_condition("snake_poison", (me->query_skill("wudu-shengong"))/10 +
                        victim->query_condition("snake_poison"));
                        break;
                case 1:
            victim->apply_condition("zhizhu_poison", (me->query_skill("wudu-shengong"))/10 +
                        victim->query_condition("zhizhu_poison"));
                        break;
                case 2:
            victim->apply_condition("wugong_poison", (me->query_skill("wudu-shengong"))/10 +
                        victim->query_condition("wugong_poison"));
                        break;
                case 3:
            victim->apply_condition("xiezi_poison", (me->query_skill("wudu-shengong"))/10 +
                        victim->query_condition("xiezi_poison"));
                        break;
                case 4:
            victim->apply_condition("chanchu_poison", (me->query_skill("wudu-shengong"))/10 +
                        victim->query_condition("chanchu_poison"));
                        break;
        }
        return HIR "$nֻ�����˴�һ���飬�ƺ��ж��ˡ�\n" NOR;
*/
   }
string perform_action_file(string action)
{
        return __DIR__"wuming-jianfa/" + action;
}

void skill_improved(object me)
{
        int lvl, i;

        i=query("int", me)/3;
        lvl = me->query_skill("wuming-jianfa", 1);

        if (lvl > 200
        &&  query("can_perform/wuming-jianfa/moming", me) <= 100 )
        {
                if( me->add("can_perform/wuming-jianfa/moming",random(i))<100 )
                {
                        tell_object(me, HIC "�������������" HIW "����Ī��"
                                        HIC "�������µ�����\n" NOR);
                } else
                {
                        tell_object(me, HIC "��ͨ��������������" HIW "��"
                                        "��Ī��" HIC "���İ��ء�\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }

}
