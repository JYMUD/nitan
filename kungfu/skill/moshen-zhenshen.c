// This program is a part of NITAN MudLIB

#include <ansi.h>

inherit SKILL;

int valid_enable(string usage) { return usage == "parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 300)
                return notify_fail("����ڹ���򲻹���������ϰ����񹦡�\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("�����������������ϰ����񹦡�\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("moshen-zhenshen", 1))
                return notify_fail("��Ļ����ڹ�ˮƽ���ޣ��޷����������ħ��������\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("moshen-zhenshen", 1) < 100 ||
            query("family/family_name", ob) == "������" || 
            query("neili", me)<300 )
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1) * 12;
        ap=ob->query_skill("force")*12+query("max_neili", ob)+mp;
        dp=me->query_skill("force")*12+query("neili", me);

        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);
 
                result += (["msg" : HIY "$n" HIY "����һ��ĵ����γ�һ����Ӱ��ǽ�ڣ�������$N"
                                    HIY "�Ĺ�����\n" NOR]);
 
                return result;
        }
        else if (mp >= 100)
        {
                result = HIY "$n��ǰ�·���һ��������ǽ����$N���ѿ���$n������ֱ����$nҪ����\n";

                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("moshen-zhenshen", 1);
        if (lvl < 100) return 0;
        if (lvl < 150) return 50;
        if (lvl < 200) return 60;
        if (lvl < 250) return 70;
        if (lvl < 300) return 80;
        if (lvl < 350) return 90;
        if (lvl < 400) return 100;
        return 120;
}

int practice_skill(object me)
{
        return notify_fail("ħ������ֻ����ѧϰ���о�����ߡ�\n"); 
        if (me->query_skill("moshen-zhenshen", 1) < 100)
                return notify_fail("���ħ���������˽���ǳ�������������ж�����\n");

        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˡ�\n");

        if( query("neili", me)<100 )
                return notify_fail("������������������񹦡�\n");

        me->receive_damage("qi", 50);
        addn("neili", -85, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"moshen-zhenshen/" + action;
}