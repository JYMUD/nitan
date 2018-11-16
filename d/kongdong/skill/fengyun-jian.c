// liuyun-jian.c
// 	nerd     Dec 9,1996 create

inherit SKILL;

mapping	* action=({
	([	"action":
        "$Nʹһ�С����˹��֡�������$w��һ���������$n��$l",
        "lian" :
        "$Nʹһ�С����˹��֡�������$w��һ�����������ǰ��......",
                "jibie":7,
                "zhaoshi":"�����˹��֡�",
                "sen"  :8  ,
		"dodge":		20  ,
		"damage":		40   ,
		"damage_type":	"����"
	]),
	([	"action":
        "$Nһ�С����»Ի͡�������Ʈ�����ߣ�����$wն��$n��$l",
                "lian":
        "$Nһ�С����»Ի͡�������Ʈ�����ߣ�����$w�󿪴��ڣ�����Ʈ��......",
                "jiebie":30,
                "zhaoshi":"�����»Ի͡�",
                "sen" : 10,
		"dodge":		30,
		"damage":		50 ,
		"damage_type":	"����"
	]),
	([	"action":
        "$N����$w�й�ֱ����һʽ���������š���׼$n�ļ羮Ѩ�̳�һ��",
                "lian":
        "$N����$w�й�ֱ����һʽ���������š���׼��ǰ��б��һ��......",
                "jibie":40,
                "limb":"��ͷ",
                "zhaoshi":"��������",
                "sen": 12,
		"dodge":30 ,
                "damage":50,
		"damage_type":	"����"
	]),
	([	"action":
        "$N��$wƾ��һָ��һ�С�����ָ�ϡ���$w�����Ŵ���$n�ľ���.......",
                "lian":
        "$N��$wƾ��һָ��һ�С�����ָ�ϡ���$w�����Ŵ����Ϸ�.......",
                "jibie":62,
                "zhaoshi":"������ָ�ϡ�",
                "sen": 10,
                "limb":"����",
		"dodge":		20,
		"damage":		70,
		"damage_type":	"����"
	]),
    ([  "action":"$N�������˸�����������һ�С����ɵ�ɽ��������$w��׼$nһ��",
        "lian"  :"$N�������˸�����������һ�С����ɵ�ɽ��������$w����һ�㡣",
        "sen"   :4,
        "jibie" :20,
        "dodge" :40,
        "parry" :30,
        "zhaoshi":"�����ɵ�ɽ��",
        "damage":5,
        "damage_type":"����"    ]),
    ([  "action":"ֻ��$N������ǰ��˫�ֽ���$w��һ�С����չ������$n��ͷ�����¶���һ��",
        "lian"  :"$Nһ��������ʹ��һ�С����չ��������$w����һ�á�",
        "sen"   :5,
        "jibie" :30,
        "dodge" :30,
        "parry" :30,
        "zhaoshi":"�����չ��",
        "damage":50,
        "damage_type":"����"    ]),
    ([  "action":"$N����$w��һ�С��ͻ���β������$n��$l����һ��",
        "lian"  :"$N����$w��һ�С��ͻ���β�������ٻ�����",
        "sen"   :5,
        "jibie" :40,
        "dodge" :10,
        "parry" :10,
        "zhaoshi":"���ͻ���β��",
        "damage":60,
        "damage_type":"����"    ]),
});

string *parry_msg = ({
    "$nʹ��һ�С�˳��ɨҶ�������е�$v����һ�����磬�Ŀ���$N��$w��\n",
    "$nʹ��һ�С�������¯�������е�$v��������ѩӰ��������$N��$w��\n",
    "$n���е�$vһ����һ�С���ȸ�ɿա�����$N��$w��������ȥ��\n",
    "$nʹ��һ�С������˻�����$wֱ��$N��˫�֡�\n",
});

string *unarmed_parry_msg = ({
    "$n˫������ܲ�͸�磬ʹ����˳��ɨҶ������ס��$N�Ĺ��ơ�\n",
    "$n����һ�С�������¯������ܿ���$N����һ�С�\n",
    "$nʹ��һ�С���ȸ�ɿա�����ס��$N�Ĺ��ơ�\n",
    "����$nһ�С������˻������ȵ�$N�������ˡ�\n",
});

int valid_learn(object me)
{
    return 1;
}

int valid_lian( object me )
{   
    object ob = me->query_temp("weapon");
    if ( !ob || (string)ob->query("weapon_type") != "sword" )
    {   
        write("���������һ�ѽ�������������\n");
        return 0;
    }
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
    if ( weapon )
        return parry_msg[random(sizeof(parry_msg))];
    else
        return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
}

string query_xiuwei_type() { return "sword"; }      
string query_weapon_type() { return "sword"; }

int query_dengji() { return 2; }

int query_youxiao_jibie() { return 9; }

int query_parry_ratio() { return 12; }
