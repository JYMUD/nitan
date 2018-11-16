// This program is a part of NT MudLIB
// luoying-shenfa ��Ӣ��

#include <combat.h>
#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$n��ͷһ�ͣ�˫�����䣬������ǰ���Ƽ�����$N������ȥ������һ�С�����������$N��֮�£���������ͳͳ����$n��󣬾�����ա�\n",
        "dodge"  : 10,
        "skill_name" : "������"
]),
([      "action" : "$n���μ�����ʹ��һ�С������ڿա���������ͬΪ�������������Ʈ��һ�����࣬�ܹ�$N������\n",
        "dodge"  : 20,
        "skill_name" : "�����ڿ�"
]),
([      "action" : "$n����һ�ݣ�Ծ�ڰ�գ��ո����أ�һ�С��������㡱���ڿ�����������һ������������Ϣ������$N���\n",
        "dodge"  : 30,
        "skill_name" : "��������"
]),
([      "action" : "$n�ۼ����й�����ίʵ���޿ɱܣ���Ȼһ�С���Ͽ�ƶϡ������һ�������ţ�ȫ����ϥ�����ϣ�ƽƽ�۶ϣ�$N������ʱʧ��׼ͷ��ȫ�����ڿմ���\n",
        "dodge"  : 40,
        "skill_name" : "��Ͽ�ƶ�"
]),
([      "action" : "$n����������ʹ��һ�С�����������˫��չ���������������裬��̬Ʈ�ݣ�����$N������\n",
        "dodge"  : 50,
        "skill_name" : "��������"
]),
([      "action" : "$n��һ�䣬һʽ��������衱������$N���ƣ��������󣬵������ң�$N�俴�ƴ�ռ�Ϸ磬ȴ��һ���ܹ����С�\n",
        "dodge"  : 60,
        "skill_name" : "�������"
]),
([      "action" : "$nһ����Х�����ΰεض�������һ�С��������������ڿ���һ������ת�ۣ���ҡֱ�ϣ�Ѹ���������������������$N������\n",
        "dodge"  : 70,
        "skill_name" : "��������"
]),
([      "action" : "$n����������¼��Ⱥ�����Է�λ��һʽ����ȥ���⡱����������֮��ǰ�������ں�$N��æ���ң����ֵ����������ܣ������ỹ�ַ����ˡ�\n",
        "dodge"  : 80,
        "skill_name" : "��ȥ����"
])
});

mapping query_action(object me, object weapon)
{
        int zhaoshu, level;

        zhaoshu = sizeof(action);
        level   = (int) me->query_skill("luoying-shenfa");

        if (level < 60 )
                zhaoshu--;

        if (level < 50 )
                zhaoshu--;

        if (level < 40 )
                zhaoshu--;

        return action[random(zhaoshu)];
}

int valid_enable(string usage)
{
        return usage == "dodge" || usage == "move";
}

int valid_learn(object me)
{
        return 1;
}

string query_dodge_msg(string limb)
{
        return action[random(sizeof(action))]["action"];
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("�����Ѫ̫���ˣ���������Ӣ����\n");
        me->receive_damage("qi", 30);
        return 1;
}

mixed valid_damage(object me, object victim, int damage, object weapon)
{
        mapping prepare,action;
        string msg,result,attack_skill;
        object w,w2;
        int ap, dp;
        w=query_temp("weapon", victim);
        w2=query_temp("weapon", me);

        if( !query_temp("wuzhuan", victim))return ;

        if( !living(victim) ) return;

        if( query("neili", victim)<300)return ;

        if( objectp(w2) )
                attack_skill=query("skill_type", w2);
        else {
                prepare = me->query_skill_prepare();
                if (!prepare) prepare = ([]);
                else if ( sizeof(prepare) == 0)        attack_skill = "unarmed";
                else if ( sizeof(prepare) == 1)        attack_skill = (keys(prepare))[0];
                else if ( sizeof(prepare) == 2)        attack_skill = (keys(prepare))[query_temp("action_flag",me)];
        }

        attack_skill = me->query_skill_mapped(attack_skill);

        ap=query("combat_exp", me)/1000;
        ap+=query("jiali", me)*2;

        dp=query("combat_exp", victim)/1000;
        dp += victim->query_skill("luoying-shenfa", 1);
        dp += victim->query_skill("tanzhi-shentong", 1);
        dp = (dp + random(dp*3/2)) / 2;

        action=query("actions", me);

        if( ap > dp ) return;

        if(victim->query_skill_mapped("parry") !="tanzhi-shentong") return;

        if((int)victim->query_skill("tanzhi-shentong", 1) < 120) return;

        if(victim->query_skill_prepared("finger") != "tanzhi-shentong") return;

        if( query_temp("wuzhuan_hit", victim)<0)return ;
        if(attack_skill=="tanzhi-shentong")
                result = HIG"$n��ָһ�����͵�һ�����죬һ��ϸϸ�ľ��������ȥ�����ɡ���ָ��ͨ��ָ����������ʱ��������Ρ�\n" NOR;
        else if( objectp(w2) )
                result = HIG"$n��ָһ�����͵�һ�����죬һ��ϸϸ�ľ��������ȥ����ʱ��$N��"+w2->name()+HIG"�������ھ���������������������"+to_chinese(attack_skill)+"��\n" NOR;
        else result = HIG"$n��ָһ�����͵�һ�����죬һ��ϸϸ�ľ��������ȥ���⡸��ָ��ͨ����$N�ġ�"+to_chinese(attack_skill)+"�����˸�����൱��˭Ҳû����˭��\n" NOR;


        addn("neili", -(30+query("jiali", me)/2), victim);
        addn_temp("wuzhuan_hit", -1, victim);

        return ([ "msg" : result, "damage" : -damage ]);
}
