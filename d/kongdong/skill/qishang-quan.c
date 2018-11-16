// qishang-quan

inherit SKILL;

mapping *action = ({
    ([  "action":"$N������ȭ���أ�����ʹ��һ�С��������¡�����������$n��$l",
        "lian"  :"$N������ȭ���أ�����ʹ��һ�С��������¡����������������ζ��",
        "zhaoshi":"���������¡�",
        "jibie" : 5,
        "sen" : 5,
        "damage" : 5,
        "damage_type":  "����"
    ]),
    ([  "action":"$N������Σ�ʹ��һ�С�����ʵӦ�������ƻ���Ϊʵ����$n��$l",
        "lian"  :"$N������Σ�ʹ��һ�С�����ʵӦ�������ƻ���Ϊʵ������������",
        "zhaoshi" : "������ʵӦ��",
        "jibie" : 10,
        "sen"  : 10,
        "damage" : 10,
        "damage_type":  "����"
    ]),
    ([  "action":"$Nʹ������ȭ����������ˮ����������ǰ��˫��ͬʱ����$n��$l",
        "lian" : "$Nʹ������ȭ����������ˮ����������ǰ��˫�������һ�ġ�",
        "zhaoshi" : "��������ˮ��",
        "jibie" : 20,
        "sen" : 15,
        "damage" : 15,
        "damage_type":  "����"
    ]),
    ([  "action":"$Nʹ��һ�С�����ī���������ڿ�Ծ�𣬶�׼$n��$l�����ĳ�����",
        "lian"  :"$Nʹ��һ�С�����ī���������ڿ�Ծ�𣬶��ſ�������һͨ��",
        "zhaoshi" : "������ī��",
        "jibie" : 30,
        "sen" : 20,
        "damage" : 20,
        "damage_type":  "����"
    ]),
    ([  "action":"$N��������������ָһ��һ����һ�С�������������$n��$l",
        "lian"  :"$N��������������ָһ��һ����ʹ��һ�С��������������������Ӭ��",
        "zhaoshi" : "����������",
        "jibie" : 35,
        "sen" : 30,
        "damage" : 30,
        "damage_type":  "����"
    ]),
    ([  "action":"$N���η��裬һ�С���̽Ѱ����˫��ͬʱ��$n��$l���ƹ���",
        "lian" : "$N���η��裬ʹ��һ�С���̽Ѱ����˫��һ�����أ��������硣",
        "zhaoshi" : "����̽Ѱ��",
        "jibie" : 40,
        "sen" : 40,
        "damage" : 50,
        "damage_type":  "����"
    ]),
    ([  "action":"$N���һ����һ�С���ɽ���롹���������£��Ʒ�����$nȫ��",
        "lian" : "$N���һ����һ�С���ɽ���롹���������£�����һ���Ʒ磬���Կ�����ʯ��",
        "zhaoshi" : "����ɽ���롹",
        "jibie" : 50,
        "sen" : 50,
        "damage" : 60,
        "damage_type":  "����"
    ]),
});

string *parry_msg = ({
    "$n˫����㣬һ�С����Ƽ��ա�������׾ٵĵ�����$N��һ����\n",
    "ֻ��$n�㲻��أ�һ�С�˳ˮ���ۡ�����$N�Ĺ��ƻ������Ρ�\n",
    "����$n���˷�����˫��һ�ʹ��һ�С�Ҷ��ժ���������̻���Ϊ�ġ�\n",
});
    
int valid_lian(object me)
{   
    if (me->query_temp("weapon"))
        return notify_fail("������ȭ������֡�\n");
    if ( me->query("str") < 18 )
        return notify_fail("������̫�����޷�������ȭ��\n");
    if ( me->query("force") < 5 )
        return notify_fail("���������㣬һ����������Σ�ա�\n");
    me->receive_damage("kee",5);
    me->add("force",-5);
    return 1;
}

int valid_learn(object me)
{
    if ( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
            return notify_fail("ʦ��˵���������Ȱ����б������¡���\n");
    if ( (int)me->query("max_force") < 100 )
            return notify_fail("�������̫����������ȭ���߻���ħ��\n");
    return 1;
}

mapping query_action(int jibie)
{ 	
    int i, size;
	size = sizeof( action );
	for ( i = 0; i < sizeof( action ); i++ )
		if ( action[ i ][ "jibie" ] > jibie )
		{
			size = i;
			break;
		}
    return action[ random( size ) ];
}

string query_parry_msg(object weapon)
{   
    return parry_msg[random(sizeof(parry_msg))];
}

string perform_action_file(string action)
{   
    return SKILL_D("qishang-quan/") + action;
}

string query_xiuwei_type() { return "unarmed"; }

int query_dengji() { return 5; }

string query_zhaoshi( int jibie )
{
    int i;
    for ( i = 0; i < sizeof(action); i++ )
    {
        if ( action[ i ][ "jibie" ] >= jibie )
            return action[ i ][ "zhaoshi" ];
    }
    return "";
}
