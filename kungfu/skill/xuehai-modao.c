// Ѫ��ħ��
#include <ansi.h>
inherit SKILL;
#include "/kungfu/skill/eff_msg.h";;

mapping *action = ({
([      "action" : CYN"$Nһ�С�"HIR"ĥ��˱Ѫ"CYN"������$w"CYN"���������$n�߽��ˣ�ͻȻ������ץס������˳��һ�ӣ�����$p$l"NOR,
        "skill_name" : "ĥ��˱Ѫ",
        "force" : 200,
        "dodge" : 15,
        "lvl" : 0,
        "damage" : 150,
        "damage_type" : "����",
]),
([      "action" : CYN"$N�ٺ�һЦ��һʽ��"MAG"��ֽ����"CYN"����һ��������ȥ��$nֻ����ǰ���������$l��΢΢һ��"NOR,
        "skill_name" : "��ֽ����",
        "force" : 240,
        "dodge" : 25,
        "lvl" : 20,
        "damage" : 175,
        "damage_type" : "����",
]),
([      "action" : CYN"$N��$w"CYN"�ڿڣ�������$n���Դ�����ȥ����������ִӿ��г����������"HIR"Ѫ��ãã"CYN"��һ��֮�£�����ֱ��$p$l"NOR,
        "skill_name" : "Ѫ��ãã",
        "force" : 280,
        "dodge" : 30,
        "lvl" : 30,
        "damage" : 160,
        "damage_type" : "����",
]),
([      "action" : CYN"$N�ٺ���Ц���У�һ�С�"HIR"Ѫϴ���"CYN"����ͻ����$w"HIR"��Ӱ"CYN"������ӭͷ��ת������һ�����һ��������������ͷ����$n$l"NOR,
        "skill_name" : "Ѫϴ���",
        "force" : 320,
        "dodge" : 55,
        "lvl" : 50,
        "damage" : 190,
        "damage_type" : "����",
]),
([      "action" : CYN"$N������ǰһ̽��һ�С�"HIR"Ѫ�����"CYN"����$w"CYN"���������б���һ��������һ�㣬Ѹ�����׵���$n�������ж������漴�յ����ʣ�������Ц"NOR,
        "skill_name" : "Ѫ�����",
        "force" : 350,
        "dodge" : 75,
        "lvl" : 70,
        "damage" : 200,
        "damage_type" : "����",
]),
([      "action" : CYN"$N�ͺ�һ������Ȼ������������$w"CYN"�������ã�һʽ��"HIR"Ѫ������"CYN"��������ƬƬ����ն��$n��$l"NOR,
        "skill_name" : "Ѫ������",
        "force" : 380,
        "dodge" : 60,
        "lvl" : 90,
        "damage" : 260,
        "damage_type" : "����",
]),
([      "action" : CYN"$N��͸���⣬����̹Ǻ��磬һ�С�"BLU"Ѫ��̹�"CYN"����ǰֱ�����£�һ����������������$n��$l"NOR,
        "skill_name" : "Ѫ��̹�",
        "force" : 500,
        "dodge" : 55,
        "lvl" : 100,
        "damage" : 380,
        "damage_type" : "����",
]),
([      "action" : CYN"$Nһʽ��"HIR"Ѫ�����"CYN"����һ��$w"CYN"ԽʹԽ�죬һ���ź�Ӱ������ȫ����$n��������������ֻ�����أ���������������"NOR,
        "skill_name" : "Ѫ�����",
        "force" : 620,
        "dodge" : 10,
        "lvl" : 120,
        "damage" : 320,
        "damage_type" : "����",
]),
([      "action" : CYN"$N���Բ���һ�С�"MAG"նͷʽ"CYN"�����ִӱ��������һ����ֱ��$n�����\n  "NOR,
        "skill_name" : "նͷʽ",
        "force" : 200,
        "dodge" : 5,
        "parry" : 5,
        "lvl" : 0,
        "damage" : 130,
        "damage_type" : "����",
]),
([      "action" : CYN"$NͻȻ�����ڵأ�$nĿ�ɿڴ�֮�ʣ�һ�С�"GRN"���ŵ�"CYN"��������$w"CYN"���¶���ֱ��$n��С����  "NOR,
        "skill_name" : "���ŵ�",
        "force" : 240,
        "dodge" : 5,
        "parry" : 15,
        "lvl" : 8,
        "damage" : 150,
        "damage_type" : "����",
]),
([      "action" : CYN"$N���һ�㣬һ������ͷ���ŵأ�һ�С�"YEL"ȥ���"CYN"����$w"CYN"һ����������ң����ҵ�������ʮ����  "NOR,
        "skill_name" : "ȥ���",
        "force" : 280,
        "dodge" : 10,
        "parry" : 15,
        "lvl" : 16,
        "damage" : 165,
        "damage_type" : "����",
]),
([      "action" : CYN"$N�ֽ�һ�������ڿ��У�һ�С�"BLU"���Ǿ���"CYN"��������$w"CYN"���ֶ���������$n��$l  "NOR,
        "skill_name" : "���Ǿ���",
        "force" : 320,
        "dodge" : 0,
        "parry" : 5,
        "lvl" : 23,
        "damage" : 170,
        "damage_type" : "����",
]),
([      "action" : CYN"$N��ɫ���죬���С�"BLU"�Ǻ�"CYN"���ͺ�һ�С�"YEL"����"CYN"����$w"CYN"�鶯�쳣����$n��$l���߹�ȥ  "NOR,
        "skill_name" : "����",
        "force" : 350,
        "dodge" : 35,
        "parry" : 25,
        "lvl" : 30,
        "damage" : 180,
        "damage_type" : "����",
]),
([      "action" : CYN"$Nһ�С�"HIW"������"CYN"��������$w"CYN"΢΢һ������"HIW"������"CYN"���������죬��$nͷ���ء�������������  "NOR,
        "skill_name" : "������",
        "force" : 320,
        "dodge" : 10,
        "parry" : 25,
        "lvl" : 40,
        "damage" : 210,
        "damage_type" : "����",
]),
([      "action" : CYN"$Nը�װ���һ����һʽ��"HIR"ħ����"CYN"��$w"CYN"��$n§�����б���������������ͣ��Ʋ��ɵ���  "NOR,
        "skill_name" : "ħ����",
        "force" : 500,
        "dodge" : 15,
        "parry" : 10,
        "lvl" : 60,
        "damage" : 230,
        "damage_type" : "����",
]),
([      "action": CYN"$N�߸�Ծ�𣬻��������е�$w"CYN"һ�С�"BLU"һ������"CYN"������һ����������$n��ͷֱ�����"NOR,
        "dodge": 10,
        "force": 310,
        "damage" : 250,
        "lvl" : 0,
        "damage_type": "����"
]),

([  "action": CYN"$Nһ�����ȡ�"YEL"��ɨǧ��"CYN"������$w"CYN"��������һ�ã�˫����ס$w��ת���͵ú�ɨ����$n��$l"NOR,
        "dodge": 15,
        "force": 350,
        "lvl" : 0,
        "damage": 260,
        "damage_type": "����"
]),
([      "action": CYN"$N��Ȼ����һ�䣬ʹ����"HIC"���߳���"CYN"���������Ե�����֮��������$w"CYN"����������Ӱ����$n"NOR,
        "dodge": 50,
        "force": 400,
        "lvl" : 29,
        "damage": 330,
        "damage_type": "����"
]),
([  "action": CYN"$N�Ե�������$w"CYN"�й�ֱ��������һ����̳�������$n��$l�������С�"HIB"���߻���"CYN"��"NOR,
        "dodge": 15,
        "force": 400,
        "lvl" : 59,
        "damage": 370,
        "damage_type": "����"
]),
([  "action": CYN"$Nһʽ��"HIW"һ������"CYN"������ͷһ$w"CYN"������������ͷδ����һ�ɷ��ѽ�$n�Ƶ����Դ���"NOR,
        "dodge": 50,
        "force": 440,
        "lvl" : 79,
        "damage": 380,
        "damage_type": "����"
]),
([  "action": CYN"$N���С�"HIR"Ⱥħ����"CYN"����$w"CYN"ɨ��һ������Ӱ������˷�Χ��$n��Ҫ��$n��û��ʳ"NOR,
        "dodge": 100,
        "force": 540,
        "lvl" : 89,
        "damage": 390,
        "damage_type": "����"
]),
});

string *parry_msg = ({
"$n����һ�̣�$w��һ�����ߣ�ֱ��$N������.",
"$n������һ�������е�$w˳�ƻ��£�����$N�յ���ָ��\n",
"$n����һ�䣬�����е�$w����һ��,��$N�Ĺ�����ƫ��ȥ.",
});
int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
	if ((int)me->query_skill("xiangfu-lun") > 100)
		return notify_fail("����ѩɽ��ɽ��ʦ�Ĺ���?\n");
	if ((int)me->query_skill("longxiang-boruo", 1) < 150)
		return notify_fail("��Ҫ�е��������������������,��������Ѫ��ħ����\n");
          return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me)
{
        object target, weapon; 
        int i, level, lvl;     
        
        target = offensive_target(me);    
        if (target->query_temp("weapon"))
             weapon = target->query_temp("weapon");
    
        lvl = random((int)me->query_skill("xuehai-modao",1));
      
        if (me->query_skill("xuehai-modao",1) > 100 &&
            me->query("neili") > 1000 && random(5) > 3 &&
            random(me->query("combat_exp")) > (int)target->query("combat_exp")/2){
            me->add("neili", -20);            
//            COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 0);
            return ([
                "action": HIC"������ʽ���ϣ�$N������$w˳��һ�Σ�����ֱ�����£�����һ����������$n��"NOR,
                "force" : 600,
                "dodge" : 200,
                "damage": 510,
                "damage_type":  "����"]);  
           } 
            

        level   = (int) me->query_skill("xuehai-modao",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
	object weapon;

	if (!objectp(weapon = me->query_temp("weapon"))
	|| (string)weapon->query("skill_type") != "blade")
		return notify_fail("��ʹ�õ��������ԡ�\n");
	if ((int)me->query_skill("xiangfu-lun") > 100)
		return notify_fail("����ѩɽ��ɽ��ʦ�Ĺ���?\n");
	
	if ((int)me->query("jingli") < 60)
		return notify_fail("��ľ���������Ѫ��ħ����\n");
	me->receive_damage("jingli", 50);
	return 1;
}

int double_attack(object me)
{	
   	if ( me->query_skill("xuehai-modao", 1) >= 80
     	&& me->query_skill_mapped("blade") == "xuehai-modao"
     	&& me->query("zhou/hubo"))
             	return 1;
}
string perform_action_file(string action)
{
        return __DIR__"xuehai-modao/" + action;
}
