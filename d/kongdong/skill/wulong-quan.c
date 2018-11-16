// wulong-quan.c
// ����ȭ

inherit SKILL;

mapping *action = ({
([	"action"    :"$N��������������һȭ������һ������ȭ�еġ�������ˮ��",
    "lian"      :"$N��������������һ�С�������ˮ����ȴ�ܾ�����Щ����Ҫ��",
    "jibie"     :8,
    "zhaoshi":"��������ˮ��",
    "sen"       :1,
	"dodge"     :0,
    "parry"     :0,
    "damage"     :10,
	"damage_type":	"����"
]),
([	"action"    :"$N˫��һ��ʹ�����������项����׼$n��$l�����ĳ�����",
    "lian"      :"$N˫��һ��ʹ�����������项�������ĳ����ƣ�������ְ����ִ������",
    "jibie"     :16,      
    "zhaoshi":"���������项",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"����"
]),
([	"action"    :"$N����������һ�С�������ˮ����˫�ֱ�$n��ͷ����ȥ",
    "lian"      :"$Nһ�С�������ˮ����˫��������еĵ��˵�ͷ����ȥ",
    "jibie"     :24,
    "zhaoshi":"��������ˮ��",
    "limb":"ͷ��",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :20,
	"damage_type":	"����"
]),
([	"action"    :"$Nһ�С��������ơ�,������$n$l��ȥ...",
    "lian"      :"$Nһ�С��������ơ���������ǰ��ȥ...",
    "jibie"     :32,    
    "zhaoshi":"���������ơ�",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :10,
	"damage_type":	"����"
]),
([	"action"    :"$N����һ���������Ƴ���һ�С���������������$n$l",
    "lian"      :"$N���������Ƴ�������һ����������Ƶı仯�����˸�������������..",
    "jibie"     :40,
    "zhaoshi":"������������",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :25,
	"damage_type":	"����"
]),
([	"action"    :"$Nʹ��һ�С�������β�����Ų����ǲ���һȭ��$n$l��ȥ",
    "lian"      :"$N����ʹ��һ�С�������β������ϸ��Ħÿһ���仯",
    "jibie"     :48,
    "zhaoshi":"��������β��",
    "sen"       :1,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :15,
	"damage_type":	"����"
]),
([	"action"    :"$Nʹ��һ�С������붴���������鰴����ȭ�»���ֱ��$n��$l��ȥ",
    "lian"      :"$N�����鰴����ȭ�»�����ᡸ�����붴��������",
    "jibie"     :56,  
    "zhaoshi":"�������붴��",
    "sen"       :2,
	"dodge"     :0,
	"parry"     :0,
	"damage"     :20,
	"damage_type":	"����"
]),
});

string * parry_msg = ({
    "$nһ�С��������ơ���˫�Ʒ��裬$N��ǰһ����ʧȥ��$n����Ӱ��\n",
    "$n������ȭ��һ�С�������β��������$N��һ����\n",
    "����$nһ�С�����������������һ��������������$N�Ĺ��ơ�\n",
});
    
int valid_learn(object me)
{
    if ( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
    {    
        write("������ȭ������֡�\n");
        return 0;
    }
    if ( me->query("max_force") < 300 )
    {   
        write("�������̫�����޷�������ȭ��\n");
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

int query_dengji() { return 4; }
  
string query_parry_msg(object weapon)
{
    return parry_msg[random(sizeof(parry_msg))];
}

int query_youxiao_jibie() { return 12; }

int query_parry_ratio() { return 9; }
