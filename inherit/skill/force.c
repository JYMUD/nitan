// force.c

#include <ansi.h>

inherit SKILL;

int valid_learn(object me)
{
        if( (int)me->query_skill("force", 1) < 10 )
                return notify_fail("��Ļ����ڹ���򲻹�������ѧϰ�����ڹ���\n");

        return 1;
}

// hit effect called by combatd
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int damage;
        int me_fac;
        int victim_fac;
        int f;
        int m_lvl;
        int v_lvl;
        string skill;
        mixed result;

        skill = victim->query_skill_mapped("force");
        if( stringp(skill) ) {
                if( result = SKILL_D(skill)->valid_damage(me, victim, damage_bonus) )
                        return result;
        }

        me_fac=query("neili", me);
        if( me_fac>query("max_neili", me) )
                me_fac=query("max_neili", me);

        victim_fac=query("neili", victim);
        if( victim_fac>query("max_neili", victim) )
                victim_fac=query("max_neili", victim);

        if( query("combat_exp", me) < query("combat_exp", victim) * 10 )
                addn("neili", -factor, me);

        damage = me_fac / 20 + factor - victim_fac / 24;

        if( damage < 0 ) {
                v_lvl = victim->query_skill("force");
                m_lvl = me->query_skill("force");
                if( !query_temp("weapon", me) && m_lvl+random(m_lvl/3)<v_lvl){
                        result = ([ "damage" : damage * 2 ]);
                        damage = -damage;
                        me->receive_damage("qi", damage * 4, victim);
                        me->receive_wound("qi", damage * 4, victim);
                        if( damage < 10 )
                                result += ([ "msg" : HIY "$N" HIY "�ܵ�$n"
                                                     HIY "�����������ƺ�һ����\n" NOR ]);
                        else if( damage < 20 )
                                result += ([ "msg" : YEL "$N" YEL "��$n"
                                                     YEL "���������𣬡��١���һ������������\n" NOR ]);
                        else if( damage < 40 )
                                result += ([ "msg" : HIC "$N" HIC "��$n"
                                                     HIC "������һ���ؿ������ܵ�һ���ش�����������������\n" NOR ]);
                        else if( damage < 80 )
                                result += ([ "msg" : HIR "$N" HIR "��$n"
                                                     HIR "������һ����ǰһ�ڣ��������ɳ�������\n" NOR ]);
                        else
                                result += ([ "msg" : RED "$N" RED "��$n"
                                                     RED "������һ��ֻ�����������ϣ���Ѫ�������������˹�ȥ��\n" NOR ]);
                        return result;
                }

                return 0;
        }

        damage-=query_temp("apply/armor_vs_force", victim);
        if( damage_bonus + damage < 0 )
                return - damage_bonus;
        if( (f = random(me->query_skill("force"))) < damage )
                return f;

        return damage;
}

int shaolin_check(object me)
{
        int lvl;
        int n;
        mapping skmap;
        string sk;

        if( !userp(me) )
                // only user does effect
                return 0;

        if( query("special_skill/nopoison", me) )
                return 0;

        n = 0;
        skmap = me->query_skills();
        if( !skmap || !sizeof(skmap) )
                return 0;

        foreach( sk in keys(skmap) ) {
                if( !SKILL_D(sk)->is_shaolin_skill() )
                        continue;
                n += skmap[sk] * skmap[sk] / 1000;
        }

        if( n < 10000 ) return 0;
        lvl = me->query_skill("buddhism", 1);
        //�����ֵ��ӣ�������taoism��mahayana��lamaism���������
        if( query("family/family_name", me) != "������"){
                if( me->query_skill("taoism", 1) >= 100 )
                        lvl += me->query_skill("taoism", 1) * 3 / 5;
                if( me->query_skill("mahayana", 1) >= 100 )
                        lvl += me->query_skill("mahayana", 1) * 3 / 5;
                if( me->query_skill("lamaism", 1) >= 100 )
                        lvl += me->query_skill("lamaism", 1) * 3 / 5;
        }
        if( query("family/family_name", me) == "������" )
                lvl += lvl * 5 / 2;
        lvl *= lvl / 25;
        if( lvl < n * 9 / 10 ) {
                write(RED "��ֻ��������һ���ʹ����ȫ�޷�������Ϣ����"
                      "��ס���һ�����ƶ���ĺ����乶��¡�\n" NOR);
                message("vision", RED + me->name() + RED "��Ȼ���һ����"
                        "�ƶ���ĺ����乶��£�������ʹ��֮����\n" NOR,
                        environment(me), ({ me }));
                me->receive_damage("jing", 200 + random(200));
                me->receive_damage("qi", 400 + random(400));
                return 1;
        } else if( lvl < n ) {
                write(HIR "��ֻ������Ϣһ�����ң���֫�ٺ���ʱ���䣬��"
                      "��ü�������������Ĳ�����\n" NOR);
                message("vision", HIR + me->name() + RED "������ס��"
                        "��������ü������΢΢������\n" NOR,
                        environment(me), ({ me }));
                me->receive_damage("jing", 100 + random(100));
                me->receive_damage("qi", 200 + random(200));
                return 1;
        } else if( lvl < n * 11 / 10 ) {
                write(HIY "������е��ķ����ң�������������"
                      "�٣�����������Щ���ѡ�\n" NOR);
        } else if( lvl < n * 13 / 10 ) {
                write(HIC "�������е������ĸо���\n" NOR);
        }

        return 0;
}

int hatred_check(object me)
{
        int hatred;
        int force;
        int i;

        hatred=query("total_hatred", me);
        force = me->query_skill("force");
        if( hatred < 3 * force )
                return 0;
        else if( hatred < 4 * force )
                write(HIY "��ֻ������Ѫ����������֮�������嵴��\n" NOR);
        else if( hatred < 5 * force )
                write(HIR "��ֻ����Ѫ�����ţ�����ɱ������������һʱ�̲�סֻ����������\n" NOR);
        else if( hatred < 6 * force ) {
                write(HIR "����ͷһʹ����Ϣ�������Ʋ�ס��ֻ������ǰ������ð��\n" NOR);
                return 1;
        } else {
                write(RED "һʱ����ֻ����ɱ���󳤣��������գ��������³嵴���������������\n"
                          "��ҡҡ�λ�ǿ֧Ƭ�̣�ɤ��һ����ǰ��ʱ����һ�ڣ������ˡ�һ�µ��ڵ��ϡ�\n" NOR);
                me->unconcious();
                call_out("do_owner_die", 0, me);
                return 1;
        }

        return 0;
}

void do_owner_die(object me)
{
        mapping sk;
        string skill;

        if( !objectp(me) )
                return;

        me->receive_damage("qi", 1);
        sk = me->query_skills();
        foreach( skill in keys(sk) ) {
                if( !SKILL_D(skill)->valid_enable("force") ||
                    skill == "force" )
                        continue;
                if( sk[skill] > 50 )
                        sk[skill] /= 2;
        }

        if( query("max_neili", me)>500 )
                set("max_neili",query("max_neili",  me)/2, me);

        set_temp("die_reason", "ɱ¾̫�أ��������Ķ���", me);
        me->die();
        set("total_hatred",query("total_hatred",  me)/2, me);
}

// can I exercise force?
int do_effect(object me)
{
        return shaolin_check(me) || hatred_check(me);
}
