// super-strike �����Ʒ�
// 2006-2-26
inherit SKILL;
#include <ansi.h>

string *parry_msg = ({
"$N˫��һ������$n�����ƾ�����ȥ��$n��������������һƬճ��֮���м�һ�㡣\n",
"$N�Ҽ�б����������ָƾ�ջ��˼���Ȧ�ӣ�������΢��������$nǧ�������\n",
"$N�ۼ�$n����������ʹ��һ�С����޵�������˫���ܲ�͸�硣\n",
"����$N˫��һȦ��һ���ۻ��ޱȵ����������һ�����У�ֻ����$n��ԭ�ؼ�ת�߰��¡�\n",
"$N��������˫�ֳ�Բ�λ�������ʱ���׵�$n����ײײ�������������㲻�ȡ�\n",
"$Nʹ��һ�С������֡������ָߣ����ֵͣ�һ������ѽ�$n�𿪡�\n",
"$N��һ����������������ת�����ƻӳ���һ��һӭ����$n�������������˻�ȥ��\n",
"$N˫��һ����ʹ��һ�С������֡���˫���ᵽ�˼������������飬��$n�ļ���������ȥ��\n",
"��������ʯ���һ˲֮�䣬$N����һ����$n�ľ�����ʱ��ա�\n",
});

string  *msgc = ({
"$N�°����ҽ�Ʋ����ǰ��˫�ֻ��ƣ���ǰ˫���ϻ�$n��$l",
"$N������ǰ�����˫���ȱ��������ᣬ����ǰ��˫����ֱ�ƶ���",
"$Nȫ��ԭ����ת���������ҵ��������˳�ƻ��磬ץ��$n��$l",
"$Nһʽ[�İ����ơ���ȫ��΢����������������֮�ƣ������֣����ֻ�����ǰֱѹ����",
"$N��ǰһ�С�˫��̽צ����˫�ֱ���Ϊצ����������������$n��$l����",
"$N���ֻ��ƣ������ֳ崷����ǰȦ�ɶ�������˳���������֣�����ȭ��$n����",
"$N����һ������һ�С��ƴ����¡��������Բ����������򣬵�ʱ��$n��������б������һ�ӣ�����$p$l",
"$Nʹһ�С���ˮ���������ұ�ͻ��ץ��$n�����ƶ�Ȼ�����쳤���ұۣ��ɿ��һ��������ն��$n��$l",
"$NͻȻʹһʽ�����ƻ��衹��˫��������һ��һ����裬����һ����ת�����ˣ�����һ�ƣ�ѹ��$n",
"$Nһ�С�����Ǭ������һ���ĳ��Ժ��͵ز���������ұ��������¼���������Ĵ������ָ��Ȧ�͵�$n��$l",
"$Nһ�С����ո��¡�������һ��һ�գ�һ����˿��������һ��֮�䣬һ�������ޱȵ������Ŷ�Ȼ����",
"$Nһ�С����޵����������ƴ�Ȧ����������СȦ�������������������һ��֮�£��޴���ھ�ѹ��$n��$l",
"$Nһ�С���ָ��ɽ������һ�����������������ţ���һ��ȴ��Ѹ���ޱȵ�һ�Ƽ��գ�˫����һ��ȥ���绢",
"$N���һ����˫�ƽ����������ޣ�Ʈ���һ�С��������á����Ʒ缱������$n��$l",
"$Nһ�С�б���廨��΢����ת���ɶ�����վ����ͬʱ���ֻ�����$n̽ץ",
"$N�����������Ϸ�ֱ�����������С������֡�ֱ��$n��$l",
"$N�����������Ϸ�ֱ��������һ�С��Ҵ����֡�����$n��$l",
"$N�ɶ��ֲ������䲽�̻��� ��ȭ�������Ϸ��������������ջ����ƣ����»���",
"$N��һ�С�����ƽ�ơ���ȫ������ת�������ֻ����֣������Ժ�������$nֱ�ж���",
"$Nһ�С������Ю����������ͬʱ�Դ�������$n������������ʽ",
"$Nһʽ��������ޡ���������ǰ�߳�˫���ȣ�ͬʱ���ֻع�������ǰ������$n",
"$N����Ȧ����ػ�ס�Ҽ磬һ�С��������ء���������ȭ��$n�������",
"$N������ǰ��Сɨ����ǰɨ����˫����ȭ��̩ɽѹ����ֱѹ��$n��$l",
"$N�����ز�˫�С�������������˫��ͬʱ��ǰ˫�����ϣ�����$n��$l",
"$N�������㣬һ�С�����廨�������Ʋ��������������·�����$n$l",
"$Nһʽ������˫�硹��˫����˫������ǰ���ж��������ǰӲ������������",
"$N����ֲ����������ջ���ǰ��������˳����ɽ����������$nֱ�ƶ���",
"$N�ջ�˫�֣���ʮ���ַ�ס��ǰ�����ֲ����硹����˫����$nƽ�Ŷ���",
"$Nһʽ���߻���ǹ����˫����˦�����ֻ��磬���ּ�����˦��ֱ������"
});

string *super_msg = ({
"$N���б���һʽ������Ϊ������˫�ƺ���г�����Ե�ŵݳ������غ�Х֮������������֮�����ɴ˶���",
"$NͻȻ���һ�������м��ɶ���˫�Ʒ��ɣ���������������$nֱ�˶��£������б������ء���һ���̶���Х��",
"$N����˫�ƣ�˳�Ƴ�ǰ��ȥ����Ȼ����һֻ�޴�����ƣ�ֱ��$n$l",
"$N˫��˳��һ�ڣ�һ������ƿն���",
});
int valid_enable(string usage)
{
        return usage== "strike" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        int level;
        string msg;
        level = (int)me->query_skill("super-strike",1);
        
        if(me->query_temp("tz/heyi")){
           	switch(me->query_temp("tz/heyi")){
            		case 2: msg = HIG"������$N����һת������$n���ԣ�����˳���ĳ�����һ�п���ƽ�ͣ�ʵ���ں�����������ޱȣ�"NOR;break;
            		case 1: msg = CYN"$NͻȻ����һ�Σ��۽�$n������һ�����������������������$p����ֱ�Ķ��£�"NOR; break;
           	}  
           	me->add_temp("tz/heyi", -1);
           	return ([
                        "action":msg, 
                        "force" :level + me->query("jiali"),
                        "dodge": random(30)+random(30),
                        "damage": level/2,
                        "parry": 20+random(20),
                        "damage_type" : "����",
        	]);
        }
    	
    	if( level > 350
        && me->query_skill_prepared("strike") == "super-strike" 
        && me->query_skill_mapped("strike") == "super-strike"
	&& random(7)>4
)
    		return ([  
                	"action" : WHT +super_msg[random(sizeof(super_msg))]+NOR,
                	"force" :  level * 2,
                	"dodge":   level,
                	"parry":   level,
                	"weapon": "���",
     "damage": level * 2,
        	"damage_type" :random(2)==1?"����":"����",
        	]);
        if (!weapon)
       	 	return ([
                	"action":CYN +msgc[random(sizeof(msgc))]+NOR,
                	"damage_type":"����",
       "damage": random(level/3),
         	"dodge":random(me->query_dex() * 2),
                	"force":me->query_skill("force") + me->query_str() * 2 + me->query("jiali") * 2,
 "parry": random(me->query_con() * 2),
"weapon" : "���",
       	]);
}

int practice_skill(object me)
{
        if (!me->query("sg/tzjj"))
             return notify_fail("��û�еõ��Ϲٰ�����ɣ���ô��͵ѧ�����Ʒ���\n");        
        if (!me->query_skill("force", 1))
                if((int)me->query_skill("force", 1) < 100)
                        return notify_fail("����ڹ���򲻹����޷��������Ʒ���\n");
        if ((int)me->query("jingli") < 70)
                return notify_fail("�������̫���ˡ�\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("������������������Ʒ���\n");                         
        me->receive_damage("jingli", 40);
        me->receive_damage("neili", 10+random(10));
        return 1;
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("�������Ʒ�������֡�\n");
        if (!me->query("sg/tzjj"))
             return notify_fail("��û�еõ��Ϲٰ�����ɣ���ô��͵ѧ�����Ʒ���\n");
        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("����ڹ���򲻹����޷�ѧ�����Ʒ���\n");
        if ((int)me->query("max_neili") < 3000)
                return notify_fail("�������̫�����޷��������Ʒ���\n");
        return 1;
}


int ob_hit(object ob, object me, int damage)
{
        string msg;
        int i, neili,p,j,skill, neili1;
        skill = me->query_skill("super-strike", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");

        if(!living(ob)) return damage;
        if(neili < 300) return damage; 
           msg = parry_msg[random(sizeof(parry_msg))];
             if(neili >= random(neili1)+damage){
              msg += "���������ж����$n��������\n";              
              j = -(damage+skill);
              }
           else{
              j = damage/2+random(damage/2); 
              if(j<damage/2) msg += "���ж����һЩ$n��������\n";
              else msg += "���ж����$nһ���������\n";
              j = -j;
            }           
           message_vision(msg, me, ob);
           return j;
          
     
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
        if(random(me->query_skill("super-strike", 1)) > 100 &&
            me->query_skill("poison", 1) > 60) {                
            victim->apply_condition("tz_poison", random(6) + 
                    (me->query_skill("poison", 1)/10) +
                    victim->query_condition("tz_poison"));
        }
}

string perform_action_file(string action)
{
        return __DIR__"super-strike/" + action;
}
