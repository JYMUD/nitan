// �����ʽ    luofeng.c
//   created by qyz on Feb 4, 1997

inherit SKILL;

mapping *action = ({
        ([     
                "action":               
"ֻ��$n������ת��һ�С������޶�����ٿ����һ��Ų�������ߣ��ܹ���$N��һ�С�",
                "lian" :
"$N������ת��һ�С������޶�����ٿ����һ��Ų�������ߡ�",
                "jibie":          8,
                "sen"  :      5,
                "dodge":                0,
                "parry":                0,
                "damage":                15,
                "damage_type":  "����"
        ]),
        ([      "action":
"$nʹ��һ�С����۷��¡�����һ��ƮȻ�ݳ��������ŵء�",
                "lian" :
"$Nʹ��һ�С����۷��¡�����һ��ƮȻ�ݳ��������ŵء�",
                "jibie":15,
                "sen"  :5,
                "dodge":                0,
                "parry":                0,
                "damage":                20,
                "damage_type":  "����"
        ]),
        ([      
                "action":               
"$n����΢�Σ�һ�С����ո��ơ����о����յرܿ���$N��һ�С�",
                "lian" :
"$N����΢�Σ�һ�С����ո��ơ�����һ����ȥ��",
                "jibie":25,
                "sen"  : 5,
                "dodge":                0,
                "parry":                0,
                "damage":                15,
                "damage_type":  "����"
        ]),
        ([    
                "action":               
"$n�������ĵ�����һ��������ɳ�������պñܹ�$N���������ơ�",
                "lian" :
"$N�������ĵ�����һ��������ɳ����Ʈ�˹�ȥ��",
                "jibie":33,
                "sen"  : 5,
                "dodge":                0,
                "parry":                0,
                "damage":                20,
                "damage_type":  "����"
        ]),
        ([      
                "action":               
"$n�������һ�ݣ�ʹ��һ�С���Ҷ��硹���ܹ���$N�Ĺ�����",
                "lian" :
"$N�������һ�ݣ�ʹ��һ�С���Ҷ��硹���˺����š�",
                "jibie":40,
                "sen"  : 6,
                "dodge":                0,
                "parry":         0,
                "damage":                15,
                "damage_type":  "����"
        ]),
        ([      
                "action":               
"����$nʹһ�С���Ʈ���ա�����������Ʈ�˿�ȥ��",
                "lian" :
"$Nʹһ�С���Ʈ���ա��������������Ʈ�˿�ȥ��",
                "jibie":50,
                "sen"  : 6,
                "dodge":                0,
                "parry":         0,
                "damage":                15,
                "damage_type":  "����"
        ]),
});
/*
string *parry_msg = ({
        "$nһ�С��̹ſ��졹���������㣬˫�Ʊ�צ���ܿ���$N��\n",
        "$n��ȭȫ����������ʹ$N���ò�����������\n",
        "$n�ܿ���$N�Ĺ��ơ�\n",
});
*/
int valid_learn(object me)
{
    return 1;
}

int valid_lian( object me )
{
//        int encu;
//        encu=me->query_encumbrance() * 100 / me->query_max_encumbrance();
//        if( encu < 10 )
//        return notify_fail("�Ṧ���븺����ϰ��\n");

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

string query_xiuwei_type()
{
	return "dodge";
}

// ������·�书�ĵȼ�, ��ʮ�ȷ���0, ��һ�ȷ���9.
int query_dengji()
{
	return 3;
}
/*
string query_parry_msg(object weapon)
{   
    if(!weapon)
        return parry_msg[random(sizeof(parry_msg))];
}
*/
int effective_level(){  return 10; }

string *query_lian()
{
	string *lian_msg;
	mapping lian_act;

	lian_msg = allocate( sizeof( action ) );
	for ( int i = 0; i < sizeof( action ); i++ )
	{
		lian_act = action[ i ];
		lian_msg[ i ] = (string)lian_act[ "lian" ];
	}
	return lian_msg;
}

