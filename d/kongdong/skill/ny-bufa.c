// ny-bufa.c

inherit SKILL;

mapping *action = ({
    ([ "action":"$n����һԾ��һ�������ӷ�����������˿�ȥ��",
       "lian"  :"$N�������أ��ո���磬һ�������ӷ������߸�Ծ��",
       "jibie" :5,
       "sen"   :2, ]),
    ([ "action":"$n�͵�һ����������β��������������ߡ�",
       "lian"  :"$N����һ�ţ�һ����������β�������ȥ����ЩŤ�������ס�",
       "jibie" :10,
       "sen"   :2, ]),
    ([ "action":"$n˫����㣬һ�����׺׳��졹���������ϴ������ߡ�",
       "lian"  :"$N˫��һ�㣬һ�����׺׳��졹�������������ߡ�",
       "jibie" :20,
       "sen"   :2, ]),
    ([ "action":"$n��ƮƮ�����Ա�һ����$N���������ƾ��������˿��",
       "lian"  :"$N����ס�����ƽ�⣬�������ȵ����������Ա�һԾ��",
       "jibie" :30,
       "sen"   :3, ]),
    ([ "action":"$n��߿���һ����Ծ��������ߡ�",
       "lian"  :"$N��߿���һ����Ծ��������ߡ�",
       "jibie" :40,
        "sen"  :3, ]),
    ([ "action":"$nԾ����У�һ�С����ѵ�ˮ������$Nͷ��Ծ�˹�ȥ��",
       "lian"  :"$NԾ����ߣ�һ�С����ѵ�ˮ�����������µ�����",
       "jibie" :50,
       "sen"   :3, ]),
//    ([ "action":"$n��ͷ��������һ�ݣ����Ա�Ծ���߳ߡ�",
//       "lian"  :"$N��ͷ��������һ�ݣ����Ա�Ծ���߳ߡ�",
//       "jibie" :60,
//       "sen"   :4, ]),
});

int valid_learn(object me)
{
	return 1;
}

int valid_lian(object me)
{
//    int encu;
//    encu = me->query_encumbrance() * 100 / me->query_max_encumbrance();
//    if ( encu < 10 )
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

// ������·�书�ĵȼ�, ��һ�ȷ��� 1, ��ʮ�ȷ��� 10.
int query_dengji()
{
	return 2;
}

