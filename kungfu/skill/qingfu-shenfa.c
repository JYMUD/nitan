// This program is a part of NT MudLIB
// qingfu-shenfa.c ������

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "ֻ��$nһ��"HIC"������Ǭ����"NOR"�����ζ�Ȼ���𣬶����$N��һ�С�\n",
        "$nһʽ"HIC"���������١�"NOR"�����λζ�����һ��Ʈ�����ܿ���$N��һ�С���\n",
        "$nʹ��"HIC"�����츣�ء�"NOR"��һ�����Ľ��󷭳����ܿ���$N���������ơ�\n",
        "$nһ��"HIC"����������"NOR"��������ת��$Nֻ����ǰһ����$n������$N�����\n",
});

int valid_enable(string usage) { return usage == "dodge" || usage == "move"; }
int valid_learn(object me)
{
        /*
        if( query("dex", me)<26 )
                return notify_fail("��������̫��޷�ѧϰ��������\n");
        */

        if (me->query_skill("dodge", 1) < 100)
                return notify_fail("���Ṧ�������㣬�޷�ѧϰ��������\n");
        return 1;
}

int practice_skill(object me)
{
        if( (int)query("qi", me) < 60 )
                return notify_fail("�������̫���ˣ���������������\n");

        if( (int)query("neili", me) < 60 )
                return notify_fail("���������������������\n");

        me->receive_damage("qi", 50);
        addn("neili", -55, me);
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("qingfu-shenfa", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 10;
        if (lvl < 150) return 20;
        if (lvl < 200) return 30;
        if (lvl < 250) return 40;
        if (lvl < 300) return 50;
        if (lvl < 350) return 60;
        return 80;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("qingfu-shenfa", 1) < 100 ||
            ! living(me) || random(3) != 1)
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) / 2 +
             me->query_skill("qingfu-shenfa", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIG "ֻ��$n" HIG "��Хһ������һֻ��"
                                            "��һ����������ڰ�յ�����$N" HIG
                                            "����ȴ���˸��ա�\n" NOR]);
                        break;

                default:
                        result += (["msg" : HIG "����$n" HIG "����ӯ�ޱȣ���ȻԾ"
                                    "�ߺ������£���$N" HIG "��ȫ�޴ӹ�����\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "ֻ��$n" HIY "��Хһ������һֻ��"
                                 "��һ����������ڰ�յ���������$N"
                                 HIY "��ͨ������������ʵ������������\n" NOR;

                default:
                        result = HIY "����$n" HIY "����ӯ�ޱȣ���ȻԾ"
                                     "�ߺ������£�$N" HIY "����˼������"
                                     "����У����������޷���\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.4; }

int help(object me)
{
        write(HIC"\n��������"NOR"\n");
        write(@HELP

    ���̵ı����Ṧ������Ҫ�Ǵ�ΤһЦ���Ṧ��������

        ѧϰҪ��
                ��
HELP
        );
        return 1;
}