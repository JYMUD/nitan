
// wushen-jian.c ��ɽ����
// �ɺ�ɽ���ϸǽ�����ܽ�ؽ�����ʯ�޽�����ף�ڽ�����������
// ����һ������B+����е��ѧ��

#include <ansi.h>
inherit SKILL;

mapping *action = ({
([      
        "action" : "$N��ת����$w�������Ŀ������" HIR "ף�ڽ���" NOR
                   "�����ӵ����쾡�£����������$n",
        "force" : 430,
        "attack": 147,
        "dodge" : 96,
        "parry" : 128,
        "damage": 190,
        "damage_type" : "����",
]),
([ 
        "action" : "$N���н���ͻ�֣���ʱ���Ⱪ�����ѽ���" HIM "ܽ�ؽ�"
                   "��" NOR "��ʹ����ֱ��$n��$l",
        "force" : 420,
        "attack": 154,
        "dodge" : 118,
        "parry" : 120,
        "damage": 210,
        "damage_type" : "����",
]),
([
        "action" : "$N��$wһ�ӣ���Хһ���ڿն���һʽ��" HIY "������"
                   "��" NOR "����$w��ָ��$n$l",
        "force" : 420,
        "attack": 156,
        "dodge" : 100,
        "parry" : 120,
        "damage": 223,
        "damage_type" : "����",
]),
([
        "action" : "$N��Хһ��������$w���$n���ۣ�ͻȻ����ת������" HIG 
                   "ʯ�޽���" NOR "���ľ��跢�ӵ��˼���",
        "force" : 430,
        "attack": 160,
        "dodge" : 120,
        "parry" : 140,
        "damage": 248,
        "damage_type" : "����",
]),
([
        "action" : "$N����$w��·����������������֣�һ����" HIW "��������"
                   NOR "����������Ʈ���ʹ�˳���",
        "force" : 480,
        "attack": 180,
        "dodge" : 140,
        "parry" : 160,
        "damage": 260,
        "damage_type" : "����",
]),
});

string main_skill()
{
        return "wushen-jian";
}

mapping sub_skills = ([
        "zigai-jian"   : 180,
        "furong-jian"  : 180,
        "shilin-jian"  : 180,
        "zhurong-jian" : 180,
        "tianzhu-jian" : 180,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;
        me = this_player();

        if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
        {
                tell_object(me, "��������˰��죬����������ý�ʵ������������\n");
                return 0;
        }

        if( query("int", me)<30 )
        {
                tell_object(me, "��������ϣ�ֻ�����ֽ�������ǣ���������������"
                                "�ԣ��޷������һ��\n");
                return 0;
        }

        if( query("dex", me)<28 )
        {
                tell_object(me, "��������ϣ�ֻ�����Լ������鶯�ԣ������޷���"
                                "���ֽ�����һ��\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 150)
        {
                tell_object(me, "��������ϣ������Լ�����ѧ�����д���ߣ�������"
                                "�������ֽ�����һ��\n");
                return 0;
        }

        if( query("max_neili", me)<3200 )
        {
                tell_object(me, "��ͻȻ�����������̣��������Լ���������Ϊ���޷�"
                                "�����ֽ�����һ��\n");
                return 0;
        }

        if (random(20) < 17)
        {
                tell_object(me, "������������򣬻���������һ�ξ����ڻ��ͨ����"
                                "���ֽ�����һ��\n");
                return 0;
        }

        tell_object(me, HIY "\nһ�󷲳�����ӿ����ͷ���㼸��������̾�����Ǽ��ɽ"
                        "�����ֽ���������\n����Ժ��ｻ�����֣���������ڻ��ͨ"
                        "����Ϊһ�塣������ͨ���˺�ɽ\n���񽣵ľ��ϡ�\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword" )
                return notify_fail("���������һ�������ܹ���ϰ��\n");

        if( query("int", me)<30 )
                return notify_fail("����������Բ��㣬û�а취����ɽ���񽣡�\n");

        if( query("dex", me)<28 )
                return notify_fail("���������������û�а취����ɽ���񽣡�\n");

        if (me->query_skill("martial-cognize", 1) < 180)
                return notify_fail("����ú�ɽ���񽣼�����£������Լ�����ѧ����"
                                   "������⡣\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("���������Ϊ������û�а취����ɽ���񽣡�\n");

        if ((int)me->query_skill("sword", 1) < 200)
                return notify_fail("��Ļ�������̫�û�а취����ɽ���񽣡�\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("wushen-jian", 1))
                return notify_fail("��Ļ�������������ޣ��޷���������ĺ�ɽ���񽣡�\n");

        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}

int practice_skill(object me)
{
        int cost;

        if( query("qi", me)<100 )
                return notify_fail("�������̫���ˡ�\n");

        cost = me->query_skill("wushen-jian", 1) / 2 + 60;

        if( query("neili", me)<cost )
                return notify_fail("���������������ɽ���񽣡�\n");

        me->receive_damage("qi", 60);
        addn("neili", -cost, me);
        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}
void skill_improved(object me)
{
        int i,lvl;
        string *sub_skillnames;

        lvl = me->query_skill("wushen-jian", 1);
           if( lvl > 180 &&
            !query("can_perform/wushen-jian/hui", me) ) 
        {
                tell_object(me, WHT "��ͨ���˺�ɽ���񽣡�" HIC "�ط�������" WHT "���İ��ء�\n" NOR);    
                set("can_perform/wushen-jian/hui", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
            if( lvl > 200 &&
            !query("can_perform/wushen-jian/qian", me) ) 
        {
                tell_object(me, WHT "��ͨ���˺�ɽ���񽣡�" HIC "ǧ���ݺ���" WHT "���İ��ء�\n" NOR);    
                set("can_perform/wushen-jian/qian", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
            if( lvl > 240 &&
            !query("can_perform/wushen-jian/shen", me) ) 
        {
                tell_object(me, WHT "��ͨ���˺�ɽ���񽣡�" HIC "����Ԫ��" WHT "���İ��ء�\n" NOR);    
                set("can_perform/wushen-jian/shen", 1, me);
                me->improve_skill("martial-cognize", 1500000);  
                me->improve_skill("martial-cognize", 1500000); 
                me->improve_skill("martial-cognize", 1500000);  
        }
        sub_skillnames = keys(sub_skills);

        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        object weapon;
        int i;

        lvl = me->query_skill("wushen-jian", 1);

        if (damage_bonus < 135
            || query("neili", me)<300
           || me->query_skill_mapped("sword") != "wushen-jian"
           || random(3) != 1)
                     return 0;

        if( !query_temp("weapon", me))return 0;
        switch(random(4))
        {
           case 1:
              if (damage_bonus / 5 > victim->query_con())
              {
                  addn("neili", -100, me);
                  victim->receive_wound("qi", (damage_bonus - 54) / 2, me);
                  
                  return random(2) ? HIW "$N" HIW "һ��������ɲ�Ǽ佣����ɣ�$n" HIW
                                     "���϶�ʱ��Ѫ��ӿ��\n" NOR:
                                     HIW "$N" HIW "����һת��һ��ƽƽ����$n" HIW "Ҫ��"
                                     "��������ͨ��һ������ȴ�̲��ż����ɱ�š�\n" NOR;
             }
             break;

          case 2:
             if (random(me->query_skill("sword") / 2) + me->query_skill("sword")
                 > victim->query_skill("dodge"))
             {
                  weapon=query_temp("weapon", me);
                  if (!victim->is_busy())
                  victim->start_busy(2 + random(lvl / 60));
                  return   HIC "$N" HIC "������Ȼ��죬����" + weapon->name() + HIC "�����Ŀ��"
                           "��$n" HIC "�����ڽ���֮�С�\n" NOR;
             }
             break;

          case 3:
             if (lvl > 220 && random(lvl / 2) + lvl > victim->query_skill("parry", 1)
                  && random(2) == 1 && !query_temp("perform_wushenjian/qian", me) )
             {
                weapon=query_temp("weapon", me);
                message_sort(HIM "\n$N" HIM "��Хһ�����ڿն���" + weapon->name() + "��"
                             "�������һ����������̼佣����ɢ������������������"
                             "������Ӱ������$n" HIM "ȫ��\n" NOR, me, victim);

                for (i = 0; i < 5; i++)
                {
                    if (! me->is_fighting(victim))
                            break;
                   
                    if (! victim->is_busy() && random(2) == 1)
                            victim->start_busy(1);

                    COMBAT_D->do_attack(me, victim, weapon, 0);
                }                
                
             }
             break;                        

          default:
                return 0;
       }
}

int difficult_level()
{
        return 700;
}

string perform_action_file(string action)
{
        return __DIR__"wushen-jian/" + action; 
}
