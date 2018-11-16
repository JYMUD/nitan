// piaoyi-bu.c

inherit SHAOLIN_SKILL;

string *dodge_msg = 
        ({
        "$nһ�������ضɺ�����Ծ�����ߣ������$N��һ�С�\n",
        "$n�������һ�ݣ�ʹ��һ�С������䳾�����ܹ���$N�Ĺ�����\n",
        "$nʹ��������ɳ����ǡ�ö����$N�Ĺ��ơ�\n",
        "$nһ�С�����öݡ�����̬����ض��˿�ȥ��\n"
        "$nʹ��һ�С����ഩ�ơ�����Ȼ�������࣬���$N���˸��ա�\n",
        "$n����һҡ���ó�������Ӱ��һ�С�������ˮ�������$N�Ĺ��ơ�\n",
        "$n��һҡ����һ�Σ�һ�С�������ૡ�������������\n",
        "$nһ�С�����Ͷ�֡�����Ծ��ٿ��������$N���\n",
        });

int valid_enable(string usage)
{
        return (usage == "dodge");
}


int valid_learn(object me)
{

        if ((int)me->query_skill("force") < 100)
                return notify_fail("����ڹ���򲻹����޷�ѧƮ�ݲ���\n");

        if( query("max_neili", me)<1500 )
                return notify_fail("�������̫�����޷���Ʈ�ݲ���\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("piaoyi-bu", 1))
                return notify_fail("������Ṧ��򲻹����޷����������Ʈ�ݲ���\n");
        
        if ((int)me->query_skill("dodge", 1) < 80)
                return notify_fail("������Ṧ��򲻹����޷��������Ʈ�ݲ���\n");

        return 1;
}


string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{       
        int ci;
        if( query("qi", me)<100 )
                return notify_fail("�������̫���ˣ�������Ʈ�ݲ�����\n");
        if (me->query_skill("piaoyi-bu", 1) < 100)
                me->receive_damage("qi", 30);
        else if (me->query_skill("piaoyi-bu", 1) > 100)
        {    
             if( query("neili", me)<170 )
                     return notify_fail("�������������Ʈ�ݲ�����\n");

                me->receive_damage("qi", ci);
        }
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"piaoyi-bu/" + action;
}
