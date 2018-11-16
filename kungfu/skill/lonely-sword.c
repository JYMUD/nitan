// lonely-sword.c ���¾Ž�

#include <ansi.h>
#include <combat.h>

inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
int action_po(object me, object victim, object weapon, int damage);//
int action_busy(object me, object victim, object weapon, int damage);
int action_damage(object me, object victim, object weapon, int damage);//
int action_parry(object me, object victim, object weapon, int damage);
int action_dodge(object me, object victim, object weapon, int damage);


string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *parry_msg = ({
        "ȴ��$n̤ǰһ������ʽбָ����ұۣ���Ҫʹ$P������ˡ�\n",
        "$n�Թ�Ϊ�أ��Խ�Ϊ�ˣ�����������$P�͹����ػӳ���λ�����̩ɽ"+(order[random(13)])+"���������"NOR"������\n",
        "$n����ͻ�䣬�����������������ڽ�ز����ʹ��ɽ������"+(order[random(13)])+"������������"NOR"��ͼ��ʹ$P���С�\n",
        "$nͻȻһ������$P��$l����һ��ȴ�����������ţ�$P�����޴룬���Ʋ�������ͣ��������\n",
        "$n�������ܣ��ٽ������ʹ��"+(order[random(13)])+"�����両�ࡹ"NOR"����$P��$l���뵲������С�\n",
        "$nͻȻʹ��������ɷ罣����"+(order[random(13)])+"�����ڤڤ��"NOR"�����Ƿ�λȴ����ƫ���������$Pһ�ʣ���\nͼͻ��$P�Ĺ��ƣ�\n",
        "$nͦ��һ������"+(order[random(13)])+"�����Ƴ�ᶡ�"NOR"�ش�$P��$l����ͼ��$P�Ĺ��ƻ��⡣\n",
        "ֻ��$n���˷���������Ʈ�磬�����һʽ"+(order[random(13)])+"������������"NOR"�������޶�����׽���ص�ס��$P��\n������\n",
        "$n���˷�����ʹ����ɽ����"+(order[random(13)])+"��������롹"NOR"��ɭɭ�����������ܣ��ܿ���$P������\n",
});
mapping *action = ({
([      "action" : "����$Nͦ����ϣ�$wһ����һ�з·�̩ɽ�����ġ�" HIC "������"
                   "Ȫ" NOR "��ֱ��$n��$l",
        "force" : 290,
        "attack": 145,
        "dodge" :-95,
        "parry" :-105,
        "damage": 160,
        "damage_type" : "����"
]),
([      "action" : "$N������$n�ӳ���" CYN "Ȫ��ܽ��" NOR "������" MAG "����"
                   "�ϸ�" NOR "������" HIG "ʯ������" NOR "������" HIW "����"
                   "����" NOR "������" HIY "���ף��" NOR "����\nɽ����",
        "force" : 410,
        "attack": 135,
        "dodge" :-135,
        "parry" :-175,
        "damage": 270,
        "damage_type" : "����"
]),
([
        "action" : "$N������ת�������̳�ʮ�Ž�����Ȼ�ǻ�ɽ��" HIW "��Ůʮ�Ž�"
                   NOR "�������������ʮ�Ž�����һ�У��ַ�֮�죬\nֱ�Ƿ�����"
                   "˼",
        "force" : 310,
        "attack": 115,
        "dodge" :-75,
        "parry" :-105,
        "damage": 205,
        "damage_type" : "����"
]),
([      "action" : "$N���ƺ��������裬�������������������ɽ����Ϊһ������$n��"
                   "����ȥ",
        "force" : 280,
        "attack": 125,
        "dodge" :-55,
        "parry" :-125,
        "damage": 160,
        "damage_type" : "����"
]),
([      "action" : "$N����ͻ������ɭ�ϣ�����ǧ�������۶�������ǹ��ꪣ���ɳǧ"
                   "�������ɽ���ƻ���$n",
        "force" : 340,
        "attack": 160,
        "dodge" :-65,
        "parry" :-95,
        "damage": 220,
        "damage_type" : "����"
]),
([      "action" : "ȴ��$N���潣�ߣ����һ�գ��ұ�һ�䣬����Ҳ��ԽתԽ�Ӻ�����"
                   "������" HIY "̩ɽʮ����" NOR "��Ϊһ����\n��$n",
        "force" : 250,
        "attack": 135,
        "dodge" :-85,
        "parry" :-105,
        "damage": 210,
        "damage_type" : "����"
]),
([      "action" : "$N����ͻ�䣬ʹ����ɽ�ġ�" HIB "һ�������" NOR "��������$n"
                   "��$l����֪������;��ͻȻת�򣬴��$n\n����֮��",
        "force" : 240,
        "attack": 105,
        "dodge" :-125,
        "parry" :-175,
        "damage": 180,
        "damage_type" : "����"
]),
([      "action" : "$N����������һ�����ǡ�" CYN "������ɽ" NOR "��������$w����"
                   "ն�䣬ֱ����$n��$l",
        "force" : 345,
        "attack": 125,
        "dodge" :-115,
        "parry" :-145,
        "damage": 210,
        "damage_type" : "����"
]),
([      "action" : "$N����$wԽתԽ�죬ʹ�ľ�Ȼ�Ǻ�ɽ�ġ�" HIW "�ٱ�ǧ������ʮ"
                   "��ʽ" NOR "������ʽ�����ƾ���ӿ���Թ�\n�߲��ɵ�ĿΪ֮ѣ",
        "force" : 350,
        "attack": 145,
        "dodge" :-165,
        "parry" :-185,
        "damage": 250,
        "damage_type" : "����"
]),
([      "action" : "$N��Ц����������ׯ�ϣ�$w��ӣ����ڡ�" HIR "��Ħ��" NOR "��"
                   "Ϊһʽ������ش���$n",
        "force" : 330,
        "attack": 135,
        "dodge" :-95,
        "parry" :-125,
        "damage": 260,
        "damage_type" : "����"
]),
([      "action" : "$N����$w��ʹ��" CYN "̫����" NOR "�����⣬�������СС��"
                   "����ԲȦ�������޾�ԴԴ�����ز���$n",
        "force" : 230,
        "attack": 105,
        "dodge" :-285,
        "parry" :-375,
        "damage": 140,
        "damage_type" : "����"
]),
([      "action" : "$N�������أ�$w�����������Һ�ɨ��Ю�������֮�Ʊ���$n����"
                   HIR "��Ħ��" NOR "���Ľ����¶����",
        "force" : 330,
        "attack": 185,
        "dodge" :-135,
        "parry" :-155,
        "damage": 280,
        "damage_type" : "����"
]),
([      "action" : "ȴ��$NͻȻ�鲽������ʹ�������䵱��" HIG "���ѵ�ˮ" NOR
                   "����һ��",
        "force" : 180,
        "attack": 95,
        "dodge" :-285,
        "parry" :-375,
        "damage": 130,
        "damage_type" : "����"
]),
([      "action" : "$N�˽���磬��������з���$n��$l�����Ա�$n���أ���������"
                   "��" HIR "��ħ��" NOR "���ġ�" HIR "����ʽ" NOR "��",
        "force" : 270,
        "attack": 155,
        "dodge" :-135,
        "parry" :-165,
        "damage": 260,
        "damage_type" : "����"
]),
([      "action" : "$NͻȻ�˽����һ�ֹ���ġ�" HIY "�����罣��" NOR "����"
                   "��Ȼ��$n�����Ҵ�����",
        "force" : 330,
        "attack": 145,
        "dodge" :-175,
        "parry" :-255,
        "damage": 220,
        "damage_type" : "����"
]),
([      "action" : "$N�������ߣ�����һ��������һ������$nĪ������ֲ���$N����"
                   "����ʵ",
        "force" : 310,
        "attack": 165,
        "dodge" :-115,
        "parry" :-135,
        "damage": 270,
        "damage_type" : "����"
]),
([      "action" : "$N��������ת��$n����������µ���$n�̳�һ������֪ʹ����"
                   "ʲô����",
        "force" : 330,
        "attack": 135,
        "dodge" :-175,
        "parry" :-215,
        "damage": 225,
        "damage_type" : "����"
]),
([      "action" : "$NͻȻһ������$n��$l����һ��ȴ�����������ţ�$n�����޴룬��"
                   "֪����Ǻ�",
        "force" : 360,
        "attack": 160,
        "dodge" :-150,
        "parry" :-285,
        "damage": 210,
        "damage_type" : "����"
]),
([      "action" : "$N��Ю���ƣ��󿪴��ص��ҿ�һͨ�������нԻ���$n���Ƶ�������"
                   "�ȵ�$n���ò���",
        "force" : 510,
        "attack": 225,
        "dodge" :-135,
        "parry" :-175,
        "damage": 190,
        "damage_type" : "����"
]),
([      "action" : "$N���ֺὣ����$n��$l���������������е�һ����������Ȼ���"
                   "$n���Կ��彣������",
        "force" : 334,
        "attack": 135,
        "dodge" :-155,
        "parry" :-185,
        "damage": 280,
        "damage_type" : "����"
]),
([      "action" : "$N�ٽ���ӣ�Ѹ���ޱȵص���$n��$l��ȴ���˿�������������ʲô"
                   "��ʽ",
        "force" : 380,
        "attack": 125,
        "dodge" :-145,
        "parry" :-215,
        "damage": 230,
        "damage_type" : "����"
]),
([      "action" : "$N����ͻ��Ц�ݣ��ƺ��ѿ���$n���书��ʽ�����г����һ������"
                   "$n��$l",
        "force" : 390,
        "attack": 155,
        "dodge" :-185,
        "parry" :-275,
        "damage": 230,
        "damage_type" : "����"
]),
});

mapping *action2 = ({
([      "action" : "$N����һ��ָ��$n���������$n���������ڣ��˵����������ף���"
                   "��˼��",
        "force" : 370,
        "attack": 135,
        "dodge" :-185,
        "parry" :-300,
        "damage": 238,
        "post_action" : (: action_busy :),
        "damage_type" : "����"
]),
([
        "action" : "$N��$w����һ�ڣ�����$n�Լ���$wײ����������֮������������"
                   "�Ѳ�",
        "force" : 410,
        "attack": 155,
        "dodge" :-300,
        "parry" :-300,
        "damage": 280,
        "post_action" : (: action_damage :),
        "damage_type" : "����"
]),
([      "action" : HIW "����$N����$w" HIW "�ƿճ�����ƽƽһ������$n��������ʽ����",
        "force" : 600,
        "attack": 300,
        "dodge" :-300,
        "parry" :-300,
        "damage": 460,
        "post_action" : (: action_parry :),
        "damage_type" : "����"
]),
([      "action" : HIW "$N�����۽������赭д������̳�һ������֮����������ʽ",
        "force" : 600,
        "attack": 300,
        "dodge" :-300,
        "parry" :-300,
        "damage": 460,
        "post_action" : (: action_dodge :),
        "damage_type" : "����"
]),
([      "action" : HIW "$N��Ʈ�ݣ���̬��Ȼ������������У�����$w" HIW "�����������������"
                   "�Ž��ѵ����շ�����ľ���",
        "force" : 600,
        "attack": 300,
        "dodge" :-300,
        "parry" :-300,
        "damage": 460,
        "post_action" : (: action_po :),
        "damage_type" : "����"
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int valid_learn(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me) )
        ||  query("skill_type", ob) != "sword" )
                return notify_fail("���������һ�ѽ�������������\n");

        if( query("int", me)<34 )
                return notify_fail("������ʲ��㣬�޷������¾Ž��Ľ��⡣\n");

        if( query("character", me) == "�ĺ�����" )
                return notify_fail("��һ����ɱ�����ˣ�û�������¾Ž��ĵ��������塣\n");

        if( query("character", me) == "���ռ�թ" )
                return notify_fail("��һ������ôѧ�ý���ȥ���ˣ����û�������¾Ž���\n");

        if( query("character", me) == "��������" )
                return notify_fail("�����а�����ʲô���¾Ž������߰���ģ�û�а�����ơ�\n");

        if( me->query_skill("sword", 1) < me->query_skill("lonely-sword", 1) )
                return notify_fail("��Ļ��������������ޣ��޷���������Ķ��¾Ž���\n");

        return 1;
}
int practice_skill(object me)
{
        return notify_fail("���¾Ž�ֻ��ͨ�����ܾ�ʽ����������\n");
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int lvl;
        lvl = (int) me->query_skill("lonely-sword", 1);
        if( objectp(weapon) && query("id", weapon) == "xuantie jian" )
        {
                if( me->query_str() >= 60 && me->query_int() >= 36
                &&  random(lvl) > 120
                &&  me->query_skill("force")>150 && query("neili", me) > 400 )
                {
                        addn("neili", -100, me);
                        return ([
                                "action": HIR "$N��ɫ�����ϣ��������������ؽ���ͻȻԾ������һ��"
                                          "Ԧ����Ϊһ��������$n��̶�ȥ" NOR,
                                "damage": 900,
                                "attack": 300,
                                "dodge" :-300,
                                "parry" :-300,
                                "damage_type" : "����"
                        ]);
                }
        }

        if( query("lonely-sword/nothing", me) )
               return action2[random(sizeof(action2))];

        else   return action[random(sizeof(action))];
}


int action_damage(object me, object victim, object weapon, int damage)
{
        string msg;
        string*limbs=query("limbs", victim);
        int dam;
        int skill= me->query_skill("lonely-sword", 1);
        if( !me->is_fighting(victim) ) return 0;
        if( damage == RESULT_DODGE && !victim->is_busy()
        &&  skill > 100
        &&  objectp(weapon=query_temp("weapon", me) )
        &&  query("neili", me)>100
        &&  random(skill) > victim->query_skill("force",1)/2 ) //���
        {
                addn("neili", -50, me);
                message_combatd("\n$Nһ����Х:"HIW"������������Х��ɽ�ӡ�"NOR", ˲�佣â����,��$n���������\n",me,victim);
                dam=skill*2+query_temp("apply/damage", me);
                dam-=query_temp("apply/armor", victim);
                if (dam < 0 ) dam = 0;
                victim->receive_damage("qi", dam);
                msg = COMBAT_D->damage_msg(dam, "����"); //�˴��˺�
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg, me, victim);
                COMBAT_D->report_status(victim);
                return 1;
        } else 
        if( damage > 0 && !victim->is_busy()
        &&  skill > 100
        &&  query("neili", me)>100
        &&  random(skill) > victim->query_skill("force",1)/4)   //���жԷ�
        {
                addn("neili", -50, me);
                message_combatd("\n$NͻȻ���"HIW"����������, ��������, �����项"NOR"֮����, ���г���ͻȻ��ʧ, ��$n������\n",me,victim);
                dam=skill+query_temp("apply/damage", me);
                dam-=query_temp("apply/armor", victim);
                if (dam < 0 ) dam = 0;
                victim->receive_damage("qi",dam);
                msg = COMBAT_D->damage_msg(skill*2, "����"); //�˴��˺�
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
                return 1;
        }
        return 1;
}

int action_po(object me, object victim, object weapon, int damage)
{
        // �ƶԷ��书���ڹ�  Ϊ�ռ�Ч��
        int skill= me->query_skill("lonely-sword", 1);
        string v_force = victim->query_skill_mapped("force");
        int jiali;
        if( !me->is_fighting(victim) ) return 0;
        if( damage > 0 )// ���жԷ� ���ڹ� ����������
        {
                if( v_force && skill > 250
                &&  random(skill/2) > random(victim->query_skill("force"))
                &&  random(skill) > 200
                &&  victim->query_map_skill("force")
                &&  objectp(weapon=query_temp("weapon", me) )
                &&  random(3)==1 )
                {
                        addn("neili", -100, me);
                        victim->map_skill("force");
                        message_combatd(HIC "$Nһ�����֣�����ԴԴ����������ֱ��$n���\n",me,victim);
                        message_combatd(RED "$nֻ���������������������������ѿأ���Ȼ����ʩչ"+to_chinese(v_force)+"��\n" NOR,me,victim);
                        return 1;
                } else 
                if( random(me->query_skill("lonely-sword",1)) > 100 &&
                    random(me->query_skill("sword",1))>100 &&
                    me->query_skill("force",1) > 120 &&  
                    !victim->is_busy() ) {
                        addn("neili", -50, me);
                        if( query("neili", victim)>600 )
                                addn("neili", -500, victim);
                        else
                                set("neili", 0, victim);
                        message_combatd(HIC "\n$Nһ�����֣�����ԴԴ����������$n������ס��\n",me,victim);
                        message_combatd(HIM "$n����������ʹ����������������ѳ���Ȧ��\n"NOR , me, victim);
                        return 1;
                }
        }
        else if( damage == RESULT_DODGE && !victim->is_busy()) //���  ����Է�
        {
                addn("neili", -50, me);
                message_combatd(HIY "$nֻ��$N���а���������������һ���ӣ����ҹ���ǰȥ��\n"NOR,me,victim);
                victim->start_busy(1+random(skill/50));
                return 1;
        }
        else if ( damage == RESULT_PARRY ) //�����м�ס ��˳���ٴ�����
        {
                jiali=query("jiali", me);
                if (!jiali) jiali=10;
                if( random(skill)>140 )
                {
                        addn("neili", -50, me);
                        message_combatd(HIC "$N�ཻһ�У���Ȼ����$n�书��·�����г���ش̳�һ��!\n",me,victim);
                        victim->receive_wound("qi", (random(jiali)*2+100));
                        message_combatd(HIM"$N�����ݺ�! һ������������$n���ؿڡ������Ѫ����!\n"NOR,me,victim);
                        COMBAT_D->report_status(victim,1);
                }
                return 1;
        }
        return 1;

}

int action_busy(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        if( !me->is_fighting(victim) ) return 0;
        if( damage <= 0 && !victim->is_busy()
        &&  skill > 100
        &&  objectp(weapon=query_temp("weapon", me) )
        &&  query("neili", me)>100
        &&  random(query("combat_exp", me))>query("combat_exp", victim)/3)//������С,���û�������������������м�
        {
                addn("neili", -50, me);
                message_combatd("$N��Ȼ������"HIW"����������, ���಻����"NOR"֮����, ����˲�䱬���������СС,\n����бֱ���ָ�����ԲȦ, ��$n������ס��\n",me,victim);
                victim->start_busy(2+random(skill/50));
                return 1;
        } else 
        if( damage > 0  && !victim->is_busy()
        &&  skill > 100
        &&  random(skill) > victim->query_skill("force",1)/3)
        {
                addn("neili", -30, me);
                message_combatd(CYN"$N����Ԧ������������"RED"ԲȦ"CYN"�����Ҽ�ˣ���$n�������У�\n" NOR,me,victim);
                victim->start_busy(1+random(skill/50));
        }
        return 1;
}

int action_dodge(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        string msg;
        string*limbs=query("limbs", victim);
        if( !me->is_fighting(victim)) return 0;
        if( random(me->query_skill("lonely-sword",1)) >= 200 &&
            random(me->query_skill("sword",1))>180 &&
            me->query_skill("force",1) >= 200 &&
            objectp(weapon=query_temp("weapon", me)) &&
            victim->query_map_skill("dodge") ) {
                addn("neili", -50, me);
                victim->map_skill("dodge");
                if( !victim->is_busy() )
                        victim->start_busy(random(3)+1);

                msg = HIC "\n$NͻȻ�ٽ�һ�̣�����������£�ȴĪ�������ͻ����$n�Ĺ��ƣ����$n���ϣ�\n" ;
                msg += HIR"$n���һ������Ȼ�������ܣ�\n"NOR;
                message_combatd(msg,me,victim);
                return 1;
        }
        else if( damage <= 0 && random(skill) > random(victim->query_skill("dodge",1)/3))
        {
                addn("neili", -50, me);
                message_combatd("\nȴ��$NƮ����ϣ�����оٽ������������ѷ�ס��$n��������֮�أ����þ����ޱȣ�\n",me,victim);
                victim->receive_damage("qi",skill/2);
                msg = COMBAT_D->damage_msg(skill/2, "����");
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg=replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
                return 1;
       }
       return 1;
}

int action_parry(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        string msg;
        string*limbs=query("limbs", victim);
        if( !me->is_fighting(victim)) return 0;
        if( damage == RESULT_DODGE &&
            random(me->query_skill("lonely-sword",1)) > 140 &&
            random(me->query_skill("sword",1))>140 &&
            me->query_skill("force",1) >= 200 &&
            objectp(weapon=query_temp("weapon", me)) &&
            victim->query_map_skill("parry") ) {
                addn("neili", -50, me);
                victim->map_skill("parry");
                if( !victim->is_busy() )
                        victim->start_busy(random(2)+1);

                msg = HIC "\n$N�ٽ��������������ش���$n��������$n��������������һ������������\n" NOR;
                msg += HIY"$n���Կ��彣������,��Ȼ�����мܣ�\n"NOR;
                message_combatd(msg,me,victim);
        }
        else if (damage <= 0 && random(skill) > random(victim->query_skill("parry",1)/3))
        {
                addn("neili", -50, me);
                msg = "\n$Nһ�������ݵ�$n��ǰ������΢�����ӽ�б�ã�����$n$l�����������鶯���\n";
                victim->receive_damage("qi",skill/2);
                msg += COMBAT_D->damage_msg(skill/2, "����"); //�˴��˺�
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
       }
}

int double_attack() { return 1; }

int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return 0;

        lvl = me->query_skill("lonely-sword", 1);
        if (lvl < 90)  return 0;
        if (lvl < 100) return 50;
        if (lvl < 125) return 55;
        if (lvl < 150) return 60;
        if (lvl < 175) return 65;
        if (lvl < 200) return 70;
        if (lvl < 225) return 75;
        if (lvl < 250) return 80;
        if (lvl < 275) return 90;
        if (lvl < 325) return 100;
        if (lvl < 350) return 110;
        return 120;
}

void skill_improved(object me)
{
        int lvl, i;

        i=query("int", me)/3;
        lvl = me->query_skill("lonely-sword", 1);

        if (lvl >= 20
         && !query("can_perform/lonely-sword/jue", me))
        {
                tell_object(me, HIC "��ͨ���˶��¾Ž���" HIW "�ܾ�ʽ" HIC "���İ��ء�\n" NOR);
                set("can_perform/lonely-sword/jue", 1, me);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
        }

        if (lvl > 120
         && query("can_perform/lonely-sword/qi", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/qi",random(i))<100 )
                {
                        tell_object(me, HIC "��Զ��¾Ž���" HIW "����ʽ"
                                        HIC "�������µ�����\n" NOR);
                } else
                {
                        tell_object(me, HIC "��ͨ���˶��¾Ž���" HIW "��"
                                        "��ʽ" HIC "���İ��ء�\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }

        if (lvl > 150
         && query("can_perform/lonely-sword/po", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/po",random(i))<100 )
                {
                        tell_object(me, HIC "��Զ��¾Ž���" HIR "����ʽ"
                                        HIC "�������µ�����\n" NOR);
                } else
                {
                        tell_object(me, HIC "��ͨ���˶��¾Ž���" HIR "��"
                                        "��ʽ" HIC "���İ��ء�\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }

        if (lvl > 200
         && query("can_perform/lonely-sword/yi", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/yi",random(i))<100 )
                {
                        tell_object(me, HIC "��Զ��¾Ž���" HIR "����"
                                        HIC "�������µ�����\n" NOR);
                } else
                {
                        tell_object(me, HIC "��ͨ���˶��¾Ž���" HIR "��"
                                        "��" HIC "���İ��ء�\n" NOR);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                        me->improve_skill("martial-cognize", 1500000);
                }
        }
}

int difficult_level()
{
        object me = this_object();

        if( query("lonely-sword/nothing", me) )
                return 300;

        else   return 200;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int) me->query_skill("lonely-sword", 1) < 120
         || !(m_weapon=query_temp("weapon", me) )
        ||  ! living(me)
         || query("skill_type", m_weapon) != "sword" )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("parry") + mp;
        dp = me->query_skill("parry", 1) / 2 +
        me->query_skill("lonely-sword", 1);

        // ����
        if( query("lonely-sword/nothing", me) )
        {
                if (me->query_skill("sword") * 2 / 3 + random(me->query_skill("sword")) >
                    ob->query_skill("parry"))
                {
                        result = ([ "damage": -damage ]);

                        result += (["msg" : HIC "$n" HIC "ͻȻ�ٽ�һ�̣������������£�"
                                            "ȴĪ�������ͻ����$N�Ĺ��ƣ����$N���ϡ�\n"
                                            "$nһת���ƣ�����ԴԴ��������$N�������ƣ�\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));

                        if (! ob->is_busy())
                        ob->start_busy(2 + random(2));
                        return result;
                }

        }

        if (ap / 3 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(6))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "ͻȻ�ٽ�һ�̣������������£�"
                                            "ȴĪ�������ͻ����$N�Ĺ��ƣ����$N���ϡ�\n"
                                            "$nһת���ƣ�����ԴԴ��������$N�������ƣ�\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        break;
                case 1:
                        result += (["msg" : HIC "$n" HIC "�ٽ��������������ش���$N��������"
                                            "$N��������������һ������������\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        break;
                case 2:
                        result += (["msg" : HIC "$n" HIC "�ὣ�ش̣��������$N��������"
                                            "$N���ò��������أ�����һ�μ����˳�����\n" NOR]);
                        break;
                case 3:
                        result += (["msg" : HIC "ȴ��$n" HIC "̤ǰһ������ʽбָ$P" HIC
                                            "�ұۣ���ʽѸ���ޱȣ�ʹ��$N" HIC "�������"
                                            "��\n" NOR]);
                        break;
                case 4:
                        result += (["msg" : HIC "$n" HIC "ͻȻһ������$N" HIC "����һ��"
                                            "ȴ�����������ţ�$N" HIC "��ʱ�����޴룬��"
                                            "�Ʋ�������ͣ��������\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIC "$n" HIC "�ۼ����޿ɱܣ�ֻ���ὣ�Ҵ�һͨ��"
                                            "��Ȼ�������ϵؽ�$N�Ĺ�����ȥ��\n" NOR]);
                        break;
                }

                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "һ�����е�" + m_weapon->name() +
                                 HIY "���й�ֱ��һ��ͦ��������$N" HIY "���и���"
                                 "����Ϯ$n" HIY "��\n" NOR;
                        break;

                case 1:
                        result = HIY "$n" HIY "����" + m_weapon->name() + "����"
                                 "��" HIY "��ָ��$N" HIY "�����е�����������$N"
                                 HIY "����һ�䣬�������̲���Ϊ������\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "����" + m_weapon->name() + HIY
                                 "���任���ֽ��У�Ȼ��$N" HIY "��Ҳ�����ٴι�"
                                 "����˿������$n" HIY "���Ի�\n"  NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;
        int lvl;
        object weapon, weapon2;
        int i, ap, dpp, dpd, dpf;
        string type, msg, msg1;

        lvl = me->query_skill("lonely-sword", 1);

        if( query("neili", me)<300
        ||  me->query_skill_mapped("sword") != "lonely-sword"
         || !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"
         || !query("lonely-sword/nothing", me) )
                return 0;

        ap = me->query_skill("sword");
        dpp = victim->query_skill("parry");
        dpd = victim->query_skill("dodge");
        dpf = victim->query_skill("force");

        switch(random(3))
        {
        case 1:
                if (ap * 3 / 4 + random(ap) > dpp)
                {
                        addn("neili", -100, me);
                        result = ([ "damage" : damage_bonus / 2 ]);

                        msg1 = random(2) ? HIR "$N" HIR "һ��������������ɣ�" + weapon->name() + HIR
                                           "ʱ���������գ�ʱ��������ƣ�ȴ��֪����ͨ��"
                                           "һ��֮�о��̲������������\n" NOR:
                                           HIR "$N" HIR "����" + weapon->name() + HIR "��"
                                           "�������۾�һ�㣬һ������ӳ�����ֱ����$n" HIR
                                           "С��������ƽ��������λ������ȴ�����ǡ���ô���\n" NOR;
                        result += ([ "msg" : msg1 ]);
                        return result;
                }
                break;

        case 2:
                message_combatd(HIC "\n$N" HIC "����������е�" + weapon->name() +
                               HIC "�����дӳ��䲻��ķ�λֱָ$n" HIC "��ʽ�е�"
                               "������\n" NOR, me, victim);

                if (! me->is_busy())
                {
                        weapon=query_temp("weapon", me);
                        weapon2=query_temp("weapon", victim);
                        if( weapon2)type=query("skill_type", weapon2);


                        if (ap * 3 / 4 + random(ap) >= dpf && weapon2
                        &&  type != "pin")
                        {
                                msg = HIW "$n" HIW "������ǰ�ۻ����ң�����"
                                      "��" + weapon2->name() + HIW "һʱ��"
                                      "Ȼ����ס�����ֶ�����\n" NOR;
                                weapon2->move(environment(me));
                                addn("neili", -100, me);
                        } else
                        {
                                msg = HIY "$n" HIY "�Եÿ�϶��Ϣ��һʱ��ȴ"
                                      "Ҳ����������\n" NOR;
                                addn("neili", -40, me);
                        }
                }else
                if (ap * 4 / 5 + random(ap) > dpd)
                {
                        msg = HIY "$n" HIY "��æ�ֵ���һʱ�䲻����æ���ң�"
                              "��Ͼ������\n" NOR;

                        if (! victim->is_busy())
                        victim->start_busy(1 + random(lvl / 30));
                }
                else
                {
                        msg = HIC "$N" HIC "������������е�" + weapon->name() +
                              HIC "����$n" HIC "������$n" HIC "���ص��쳣���ܣ�$N"
                              HIC "һʱ��Ȼ�޷��ҵ�������\n" NOR;
                        if (! victim->is_busy())
                        victim->start_busy(1);
                }
                message_combatd(msg, me, victim);
                break;

        default :
                if (ap * 2 / 3 + random(ap) > dpd &&
                    ! me->is_busy() &&
                    ! random(2) &&
                    !query_temp("lonely-sword/lian", me) )
                {
                        weapon=query_temp("weapon", me);
                        message_combatd(HIY "\n$N" HIY "�زؽ��⣬����" + weapon->name() + HIY
                                     "��������������ٶ�֮�죬��λ֮׼��\n���Ƕ��¾Ž��Ѵﵽ"
                                     "�շ�����ľ��硣\n" NOR,
                                     me, victim);

                        addn("neili", -270, me);

                        set_temp("lonely-sword/lian", 1, me);
                        for (i = 0; i < 5; i++)
                        {
                                if (! me->is_fighting(victim))
                                        break;

                                if (! victim->is_busy() && random(2) == 1)
                                        victim->start_busy(1);

                                COMBAT_D->do_attack(me, victim, weapon, 0);
                        }
                        delete_temp("lonely-sword/lian", me);

                }
                break;
        }
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int valid_effect(object me, object weapon, string name, int skill)
{
}
string perform_action_file(string action)
{
        return __DIR__"lonely-sword/" + action;
}

int help(object me)
{
        write(HIC"\n���¾Ž���"NOR"\n");
        write(@HELP

    �����¾Ž����н����ˣ���
    �������׽����Ķ������ǰ�������ֽ�������ܡ�����������
��һ�ܶ����ɵã��⽣��ʩչ�����������޵У��������̽�������
�޵������£�����һ���������Ƶ�������һ�ж����ɵã�ίʵ����
�ɾ����塣
    ����ʤ���У���ǿ�Ҹ�ǿ�����¾Ž�������ʽ�����м����У�
���������С����¾Ž�Ҫּ���ڡ��򡹣����ɾ��಻���������ϵ�
���ȣ�������ʤ��ͨ���˾Ž����⣬������ʩ�����ɡ�
    ���¾Ž����ԡ��ܾ�ʽ�������ƽ�ʽ�������Ƶ�ʽ����������
ǹʽ�������Ʊ�ʽ����������ʽ����������ʽ�������Ƽ�ʽ������
�ھŽ�������ʽ�����Ž��ĵ�һ�С��ܾ�ʽ���������ֱ仯������
�����ܾ���������ϰ���ڶ��С��ƽ�ʽ���������ƽ������¸��Ÿ�
�ɵĽ����������С��Ƶ�ʽ���������ƽⵥ����˫������Ҷ������
ͷ�����󿳵���ն�����ֵ����������С���ǹʽ���������ƽⳤ
ǹ����ꪡ���ì����ü�����������������ˡ����ȡ���������ֳ�
����֮���������С��Ʊ�ʽ���������ƽ�ֱޡ���ﵡ���Ѩ�ӡ���
�ӡ���ü�̡�ذ�ס��師�����ơ��˽�鳡���׵�ȵȶ̱��У�����
�С�����ʽ�����ƽ���ǳ�������ޡ����ڹ�������ǹ����������
�����ɴ����ǵȵ�����С������С�����ʽ�����Ƶ���ȭ��ָ����
�Ĺ��򣬽���ȭ�̴����õ�Ѩ��ħצ��צ����ɳ���ƣ����ȭ��
�������������ڡ��ڰ��С��Ƽ�ʽ������������֣����������
����������һ��ʱ�������ѧ�������֮��������Ҫ����һ������
�������˷����������ְ�����������������Ե��������İ�����
���˵С��ھŽ�������ʽ������Ϊ�Ը�����ϳ��ڹ��ĵ��˶��ã�
�����֮�����һ�ġ�

        ѧϰҪ��
                ֻ���������ѧϰ
                ��ϼ��100��
                ����600
HELP
        );
        return 1;
}
