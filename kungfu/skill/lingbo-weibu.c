#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "dodge"; }

string *dodge_msg = ({
        "$n�������ɵ���ǰһ��������Ʈ����һʽ"HIW"�����Ʊ��¡�"NOR"��Ӱ����縡�ƣ�\n$Nֻ���ۻ����ҡ�\n",
        "$n����������εض����ڿ���ת��һȦ��һʽ"HIW"�������ѩ��"NOR"��������\n�����裬$NĿѣ���ԣ��治�巽��\n",
        "$ņ�����棬��ȻһЦ����һ�����Ҷ�����б������������һʽ"MAG"������������"NOR"\n�����ȣ�ֻ�������˳����$N�������Σ���������γ��С�\n",
        "$n��$N�������ţ�ͻȻ���κ��������˼�����һʽ"MAG"������ҷ��"NOR"ʩʩȻ\n�����$N��һ�С�\n",
        "$nһʽ"HIM"�����������"NOR"��һ������ƮȻ����ת������$N���\n",
        "$n��չ���壬���Ӿ���һʽ"HIY"��������ɡ�"NOR"Ѹ����磬�����ù���$N���С�\n",
        "$n������Ȼ��һʽ"HIG"������Ū�ġ�"NOR"������ˮ��ʪ���ģ�ɲ�Ǽ们��������\n$N��һ�����˸��ա�\n",
        "$n̩Ȼ�����������������������ţ�һʽ"HIG"�������㡹"NOR"��Ծ�ڼ��ɿ��⡣\n",
        "$n�������У����䲻��������ȴ�Ƿ���ˮ��һʽ"HIB"�������շ硹"NOR"ƮȻ�ܹ�\n$N���С�\n",
        "$n���ν���δ�㣬����������һʽ"HIC"�����󾲲���"NOR"��΢������ˮ�棬ٿ����\n������Ӱ��\n",
});

int valid_enable(string usage)
{
        return usage == "dodge";
}

int valid_learn(object me)
{
        int lvl;

        lvl = me->query_skill("lingbo-weibu", 1);
        if (lvl > 300) lvl = 300;

       if( query("dex", me)<21 )
                return notify_fail("��������̫��޷�ѧϰ�貨΢����\n");

        if( query("max_neili", me)<3000+lvl*20 )
                return notify_fail("�����������������پ���"
                                   "�ڷ���֮�����������������á�\n");
        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("lingbo-weibu", 1) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("dodge") + mp;
        dp = me->query_skill("dodge", 1) * 3/5 +
             me->query_skill("lingbo-weibu", 1);

        if( query_temp("immortal", me) )
        {
                me->stop_busy(); 
                me->clear_weak(); 
        }

        if( ap/3+random(ap)<dp || query_temp("immortal", me) )
        {
                result = ([ "damage": -damage ]);

                switch (random(4))
                {
                case 0:
                        result += (["msg" : HIW "$n" HIW "��������ζ���$N" HIW
                                            "��ǰ��ʱ������������$n" HIW "�Ļ�Ӱ����$N"
                                            HIW "��ȫ�޷������ʵ��\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIW "$n" HIW "���Ա�����бб������һ����ȴǡ"
                                            "����$N" HIW "�Ĺ���ʧ֮���塣\n" NOR]);
                        break;
                case 2:
                        result += (["msg" : HIW "$N" HIW "��һ�����ĺÿ죬Ȼ��$n"
                                            HIW "һ�����ƺ����Ѱ��������ȴ��$N"
                                            HIW "��һ�иպñܿ���\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIW "$n" HIW "����һԾ���Ѳ�������Ӱ��$N"
                                            HIW "���д󺧣�ȴ�ּ�$n" HIW "���籼����"
                                            "��������˼�����ǡ�\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(4))
                {
                case 0:
                        result = HIY "ֻ��$n" HIY "΢΢һЦ����������ζ���"
                                 "��ʱ������������$n" HIY "�Ļ�Ӱ������$N"
                                 HIY "��ͨ������������ʵ������������\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "���Ա�����бб������һ����Ȼ��$N"
                                 HIY "�����棬��λ���岻�\n" NOR;
                        break;
                case 2:
                        result = HIY "$n" HIY "һ�����ƺ����Ѱ��������ȴ��$N"
                                 HIY "��һ�иպñܿ�������$N"
                                 HIY "�������У�����ȴ�ǲ�ֹ��\n" NOR;
                        break;
                default:
                        result = HIY "����$n" HIY "����һԾ���Ѳ�������Ӱ��$N"
                                 HIY "����˼����������У����������޷���\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lingbo-weibu", 1);
        if (lvl < 50)  return 0;
        if (lvl < 100) return 30;
        if (lvl < 150) return 50;
        if (lvl < 200) return 80;
        if (lvl < 250) return 100;
        if (lvl < 300) return 120;
        if (lvl < 350) return 140;
        return 150;
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("�������̫���ˣ�������ϰ�貨΢����\n");

        if( query("neili", me)<70 )
                return notify_fail("������������ˣ��޷���ϰ�貨΢����\n");

        me->receive_damage("qi", 65);
        addn("neili", -65, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"lingbo-weibu/" + action;
}
void skill_improved(object me)
{
        if( me->query_skill("lingboweibu",1) == 80 && !query("lbwb", me )
        &&  me->query_skill("literate", 1) > 80)
        {
                tell_object(me, HIY "$Nһ������������ֻ���������泩����֪���������������ۡ�\n" NOR);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
        if( me->query_skill("lingboweibu",1) == 120 && query("lbwb", me) == 1
        &&  me->query_skill("literate", 1) > 100)
        {
                tell_object(me, HIM "$N��ʮ�������꣬�պ�����һ����Ȧ���ص�ԭ�أ��������\n" NOR);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
        if( me->query_skill("lingboweibu",1) == 160 && query("lbwb", me) == 2
        &&  me->query_skill("literate", 1) > 120)
        {
                tell_object(me, CYN "$NԽ��Խ�죬��Ϣ���Ų�����ס��ת������Ȼ�Լ��������Ѿ�������ߣ�\n" NOR);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
        if( me->query_skill("lingboweibu",1) == 200 && query("lbwb", me) == 3
        &&  me->query_skill("literate", 1) > 140)
        {
                message_vision(RED "$N������죬����̤�����Ų���Բ��ֻ��������ˬ��ȫ����������\n" NOR, me);
                addn("max_neili", random(30)+20, me);
                addn("lbwb", 1, me);
        }
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) {
        if (me->query_family() =="xiaoyao")        return 1.5;
        return 1.0;
}

int help(object me)
{
        write(HIC"\n�貨΢����"NOR"\n");
        write(@HELP

    ���񸳣����貨΢����������������ת���������������ա���
��δ�£�����������������ȣ��������͡��ۺ�ũ���˵��ԣ��޶�
�϶ȣ��������ɣ�������أ��Ӿ������ʳ�¶�������޼ӣ�Ǧ
�����������ٶ�룬��ü���ꡣ�������ʣ������ʡ�����������
��޵��Ȩ���������ݣ��Ǿ����С������̬���������ԡ������̫
������ϼ������ܽ�س��̲�����
    �貨΢��ԭ���ڱ�ڤ�񹦲����ĩ����������ʮ���Զ��ţ���
���б�һ���죬�Ų���̤����ʮ����һ���졣��������Ѹ�ݣ�����
�貨���У����������������Ѽ���
    �貨΢��������֮����Ǻ���֮����Ҳ����֮�а�������һ
����

        ѧϰҪ��
          ��ڤ��10��
HELP
        );
        return 1;
}
