// dahong.c
// ���ȭ

inherit SKILL;

mapping *action = ({
([	"action"    :"$N˫��һ��ʹ����ʮָ���������׼$n��$l�����ĳ�����",
    "lian"      :"$N˫��һ��ʹ����ʮָ�������������ְ����ִ������",
    "jibie"     :16,      
    "zhaoshi":"��ʮָ�����",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"����"
]),
([	"action"    :"$Nʹ��һ�С��ؽ���ӡ�����Ų����ǲ���һȭ��$n$l��ȥ",
    "lian"      :"$N����ʹ��һ�С��ؽ���ӡ������ϸ��Ħÿһ���仯",
    "jibie"     :48,
    "zhaoshi":"���ؽ���ӡ��",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"����"
]),
([	"action"    :"$Nʹ��һ�С����������������鰴����ȭ�»���ֱ��$n��$l��ȥ",
    "lian"      :"$N�����鰴����ȭ�»�����ᡸ���������ĸо�..",
    "jibie"     :56,  
    "zhaoshi":"����������",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :20,
	"damage_type":	"����"
]),
([	"action"    :"$Nʹ�����ƴ����¡����󲽿�ǰ������ȭ������ȭ��$n��$l��ȥ",
    "lian"      :"$N�󲽿�ǰ������ȭ������ȭ��Ѱ�ҡ��ƴ����¡��ĸо�",
    "jibie"     :64, 
    "zhaoshi":"���ƴ����¡�",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :30,
	"damage_type":	"����"
]),
    ([   "action"  :"$Nʹ��һ�С��ڷ������������ֱ�������ƴ�������$n��$l",
         "lian"    :"$Nʹ��һ�С��ڷ������������ֱ����������ǰ������",
         "zhaoshi" : "���ڷ������",
         "sen"   : 6,
         "parry" : 20,
         "dodge" : 15,
         "jibie" : 0,
         "damage": 5,
         "damage_type":  "����"
    ]),
    ([   "action"  :"$Nһ�С��ڷ�ɨ�ء������ƻ���Ϊʵ����$n��$l",
         "lian"    :"$Nһ�С��ڷ�ɨ�ء�����������ʵʵ������",
         "zhaoshi" : "���ڷ�ɨ�ء�",
         "damage" : 20,
         "sen"    : 8,
         "parry"  : 20,
         "dodge"  : 20,
         "jibie"  : 5,   
         "damage_type":  "����"
    ]),
    ([   "action": "$N˫��һ��ʹ����ӥצ׽ʳ�������η��𣬶�׼$n��$l�����ĳ�",
         "lian"  :"$N˫��һ��ʹ����ӥצ׽ʳ�������η������ߡ�",
         "zhaoshi" : "��ӥצ׽ʳ��",
         "damage":  20,
         "sen"  :  8,
         "parry" : 60,
         "dodge" : 60,
         "jibie":    20,
         "damage_type":  "����"
    ]),
    ([   "action": "$N������������Ƴ���һ�С����ֶ㲽������$n$l",
         "lian"  : "$N������������Ƴ���һ�С����ֶ㲽�������ĳ���",
         "zhaoshi" : "�����ֶ㲽��",
         "sen"  : 6,
         "jibie": 30,
         "parry" : 50,
         "dodge" : 40,
         "damage": 60,
         "damage_type":  "����"
    ]),
});

string * parry_msg = ({
    "$nһ�С�˫���ġ���˫�Ʒ��裬$N��ǰһ����ʧȥ��$n����Ӱ��\n",
    "$n������ȭ��һ�С������ġ�������$N��һ����\n",
    "����$nһ�С�Ϭţ�׽ǡ�������һ����������$N�Ĺ��ơ�\n",
});
    
int valid_learn(object me)
{
    if ( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
    {    
        write("��ȭ������֡�\n");
        return 0;
    }
    return 1;
}

int valid_lian( object me )
{   
    return valid_learn(me);
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

string query_xiuwei_type() { return "unarmed"; }

int query_dengji() { return 3; }
  
string query_parry_msg(object weapon)
{
    return parry_msg[random(sizeof(parry_msg))];
}

int query_youxiao_jibie() { return 12; }

int query_parry_ratio() { return 9; }
