// shizi-zhan.c
// ʮ��ս

inherit SKILL;

mapping *action = ({
([	"action"    :"$N��������������һȭ������һ�С���Ԫ�֡�..",
    "lian"      :"$N��������������һȭ����Ԫ�֡���ȴ�ܾ�����Щ����Ҫ��",
    "jibie"     :8,
    "zhaoshi":"����Ԫ�֡�",
    "sen"       :1,
	"dodge"     :0,
    "parry"     :0,
    "damage"     :10,
	"damage_type":	"����"
]),
([	"action"    :"$N˫��һ��ʹ������ʽ�����ڡ�����׼$n��$l�����ĳ�����",
    "lian"      :"$N˫��һ��ʹ������ʽ�����ڡ��������ĳ����ƣ�������ְ����ִ������",
    "jibie"     :16,      
    "zhaoshi":"����ʽ�����ڡ�",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"����"
]),
([	"action"    :"$N����������һ�С�ʨ�Ӵ��ſڡ�˫�ֱ�$n��ͷ����ȥ",
    "lian"      :"$Nһ�С�ʨ�Ӵ��ſڡ���˫��������еĵ��˵�ͷ����ȥ",
    "jibie"     :24,
    "zhaoshi":"��ʨ�Ӵ��ſڡ�",
    "limb":"ͷ��",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :20,
	"damage_type":	"����"
]),
([	"action"    :"$Nһ�С���ȭ���ȡ�,������$n$l��ȥ...",
    "lian"      :"$Nһ�С���ȭ���ȡ���������ǰ��ȥ...",
    "jibie"     :32,    
    "zhaoshi":"����ȭ���ȡ�",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :10,
	"damage_type":	"����"
]),
([	"action"    :"$N����һ���������Ƴ���һ��������������$n$l",
    "lian"      :"$N���������Ƴ�������һ����������Ƶı仯",
    "jibie"     :40,
    "zhaoshi":"��������",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :25,
	"damage_type":	"����"
]),
([	"action"    :"$Nʹ��һ�С����ȡ����Ų����ǲ���һȭ��$n$l��ȥ",
    "lian"      :"$N����ʹ��һ�С����ȡ�����ϸ��Ħÿһ���仯",
    "jibie"     :48,
    "zhaoshi":"�����ȡ�",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"����"
]),
});

string * parry_msg = ({
    "$nһ�С��ϲ��崸����˫�Ʒ��裬$N��ǰһ����ʧȥ��$n����Ӱ��\n",
    "$n������ȭ��һ�С���Ԫ�֡�������$N��һ����\n",
    "����$nһ�С���ȭ���ȡ�������һ����������$N�Ĺ��ơ�\n",
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

int query_dengji() { return 2; }
  
string query_parry_msg(object weapon)
{
    return parry_msg[random(sizeof(parry_msg))];
}

int query_youxiao_jibie() { return 12; }

int query_parry_ratio() { return 9; }
