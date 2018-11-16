// kongling-jian.c
//  ���齣��
inherit SKILL;

mapping *action = ({
    ([  "action":"$Nһ�С�����֮�项���߾�����$w����$nӭͷһ��",
        "lian"  :"$Nһ�С�����֮�项������$w���һ����",
        "sen"   :3,
        "jibie" :5,
        "dodge" :20,
        "parry" :30,
        "zhaoshi":"������֮�项",
        "damage":20,
        "damage_type":"����"    ]),
    ([  "action":"$N����һ�С��˻�֮΢��������$w��$n��$lһĨ",
        "lian"  :"$N����$w��ʹ��һ�С��˻�֮΢����ǰ˳��һĨ��",
        "sen"   :10,
        "jibie" :10,
        "dodge" :10,
        "parry" :0,
        "zhaoshi":"���˻�֮΢��",
        "damage":40,
        "damage_type":"����" ]),
    ([  "action":"ֻ��$N������ǰ��˫�ֽ���$w��һ�С���ɽ��ľ������$n��ͷ�����¶���һ��",
        "lian"  :"$Nһ��������ʹ��һ�С���ɽ��ľ��������$w����һ�á�",
        "sen"   :5,
        "jibie" :30,
        "dodge" :30,
        "parry" :30,
        "zhaoshi":"����ɽ��ľ��",
        "damage":50,
        "damage_type":"����"    ]),
    ([  "action":"$N����$w��һ�С���̦���͡�����$n��$l����һ��",
        "lian"  :"$N����$w��һ�С���̦���͡������ٻ�����",
        "sen"   :5,
        "jibie" :40,
        "dodge" :10,
        "parry" :10,
        "zhaoshi":"����̦���͡�",
        "damage":60,
        "damage_type":"����"    ]),
	([	"action":
"$Nʹ���������项��$w���ӽ������ն��$n��$l",
                "lian" :
"$Nʹ���������项��$w���ӣ�ֻ�����������ɷ�Ǿ���......",
                "zhaoshi":"�������项",
                "jibie":20,
                "sen" :12,
		"dodge":		30    ,
		"damage":		30,
		"damage_type":	"����"
	]),
	([	"action":
"$Nһ�С���֮˼֮��������Ʈ�����ߣ�����$wն��$n��$l",
                "lian":
"$Nһ�С���֮˼֮��������Ʈ�����ߣ�����$w�󿪴��ڣ�����Ʈ��......",
                "jiebie":30,
                "zhaoshi":"����֮˼֮��",
                "sen" : 10,
		"dodge":		30,
		"damage":		50 ,
		"damage_type":	"����"
	]),
	([	"action":
"$N����һԾ������$wһ�С�������Υ������׼$n������бб�̳�һ��",
                "lian" :
"$N����һԾ������$wһ�С�������Υ����бб�������·���ȥ......",
                "jibie":50,
                "zhaoshi":"��������Υ��",
                "sen"  :13,
		"dodge":40,
                "limb":"С��",
                "damage":80,
		"damage_type":	"����",
	]),
});

string *parry_msg = ({
        "$nʹ��һ�С��罫���ơ������е�$v��������ѩӰ����ס��ȫ����\n",
        "$nʹ�������֡��������ΰ���$w���ִ̳�����ʱ�߽���$N�Ĺ��ơ���\n",
        "$nʹ��һ�С���ñ��ʫ�������е�$vƮ���������ճ���㽣�����ε�$N�������۾�����\n",
        "$n���е�$vһ����һ�С���֪��ĺ������$N����練����ȥ��\n",
});

string *unarmed_parry_msg = ({
        "$nʹ��һ�С��罫���ơ�����ס��$N�Ĺ��ơ�\n",
        "$n����һ�С���ñ��ʫ���������˻���һ�Ż�Ӱ��\n",
        "$nʹ��һ�С���֪��ĺ��������Ϊ��������$N��硣��\n",
        "$n˫��һ�ӣ������Ƴ����ȵ�$N�������ˡ�\n",
});

int valid_learn(object me)
{
	object ob;

	if( (int)me->query("max_force") < 50 )
		return notify_fail("�������������û�а취�����齣����\n");
	return 1;
}

int valid_lian( object me )
{
	object weapon;

	weapon = me->query_temp( "weapon" );
    if ( !weapon || weapon->query("weapon_type") != "sword" )
        return notify_fail("���������һ�ѽ�������ϰ������\n");

	return 1;
}
string query_xiuwei_type() { return "sword";}      
string query_weapon_type() { return "sword"; }

int query_dengji() { return 3; } //1~~ 10

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
    if ( weapon )
        return parry_msg[random(sizeof(parry_msg))];
    else
        return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
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

int query_youxiao_jibie() { return 12;}

int query_parry_ratio() { return 12; }
