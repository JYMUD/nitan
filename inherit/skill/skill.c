// skill.c
// This is the standard skill daemon object. All objects defining a skill
// should inherit this as its skeleton.

#pragma save_binary

#include <ansi.h>
inherit F_CLEAN_UP;
inherit F_SSERVER;

void create()
{
        seteuid(getuid());
}

// Check if the user(me) has been ready for combininh some sub
// skills to this skill
int get_ready(object me)
{
        return 1;
}

// Check if the user(me) has finished to combine some sub skills
// to this skill
int get_finish(object me)
{
        return 1;
}

// All the sub skills for combine. Default is null indicating
// that the skill needn't combine from other skills.
mapping query_sub_skills()
{
        return 0;
}

//
// valid_learn()
//
// This function is to check if a character should be able to
// learn/study/practice the skill. The default function just
// returns 1 to allow any characters improve the skill. However,
// a good skill should has its own feature and restriction. Redefine
// this function in your skill object and make it reasonable
// according to the power of the skill.

int valid_learn(object me) { return 1; }

//
// valid_research()
//
// This function is to check if a character should be able to
// research the skill.
int valid_research(object me) { return 1; }

// do effect when parry
int valid_effect(object me, object weapon, string action_name, int skill)
{
        return 1;
}

//
// type()
//
// This function should return the type of the skill. The skill type now
// affects if the skill requires combat exp in order to be learned (see
// /cmds/std/learn.c ) and the ranking of a skill level (see
// /cmds/usr/skills.c )。
// Currently we have only 2 types of skill: "martial" and "knowledge".

string type() { return "martial"; }

// When I learn from others, The max level I can learn.
int valid_learn_level(object me)
{
        return (type() == "martial") ? 200 : 10000;
}

//
// skill_improved()
//
// This function is called when a character's skill has gained a new level.
// You can make some modify to a character according to the skill.

void skill_improved(object me) {}

int practice_level() { return 100; }
// 自己練隱含級別

//
// exert_function()
//
//     This function is used by the "exert" command as specific skill's
// command parser. This function parses the arguments in the standard form
// (that is, exert <function> [<target>]). When <target> is not present,
// use the character himself as default.
//     In order to use this default exert command parser, you must define
// a function called exert_function_file(string func) in the skill object
// that takes the function name as argument and return the file name that
// defines the specified function.

int exert_function(object me, string arg)
{
        string func, target, file;
        object target_ob;

        if( sscanf(arg, "%s %s", func, target)==2 ) {
                target_ob = present(target, environment(me));
                if( !target_ob )
                        return notify_fail("這裡沒有 " + target + "。\n");
        } else {
                func = arg;
                target_ob = me;
        }

        if( !stringp(file = (string)this_object()->exert_function_file(func))
        ||      file_size(file + ".c") <= 0 )
                return 0;

        return (int)call_other( file, "exert", me, target_ob);
}

int perform_action(object me, string arg)
{
        int    lock, avoid;
        string action, target, file;
        object target_ob;
        object ob;

        ob = this_object();
        if( sscanf(arg, "%s %s", action, target) == 2 ) {
                target_ob = present(target, environment(me));
                if( !target_ob )
                        return notify_fail("這裡沒有" + target + "。\n");
        } else {
                action = arg;
        }

        if( !stringp(file = (string)ob->perform_action_file(action)) ||
            file_size(file + ".c") <= 0 )
                return 0;

        if( !SKILLS_D->valid_perform(me, file) )
                return 0;

        if( !target_ob ) target_ob = offensive_target(me);

        if( target_ob ) {
                avoid=query_temp("apply/avoid_forget", me);
                lock=query_temp("apply/add_forget", target_ob);
                lock = lock * (100 - query("reborn/times", me)*10)/100;
                if( lock > 90) lock = 90;
                if( me != target_ob && random(100) >= avoid && random(100) < lock )
                        return notify_fail(HIC BWHT + target_ob->name() +
                                "全身突然發出一道耀眼的光芒，你突然心中一亂，頓時遺忘了絕招如何使用。\n" NOR);
        }
        /*
        if( base_name(ob) != SKILL_D("six-finger") &&
            base_name(ob) != SKILL_D("dragon-strike") &&
            base_name(ob) != SKILL_D("lonely-sword") ) {
                if( target_ob && living(target_ob) &&
                    query("neili", target_ob)>500 && 
                   (target_ob->query_skill("qiankun-danuoyi", 1) > 200 ||
                    target_ob->query_skill("douzhuan-xingyi", 1) > 200) &&
                   (target_ob->query_skill_mapped("parry") == "qiankun-danuoyi" ||
                    target_ob->query_skill_mapped("parry") == "douzhuan-xingyi") &&
                    random(target_ob->query_skill("parry")) > me->query_skill("force") / 4 ) {
                        if( (int)call_other(file, "perform", me, me) ) {
                                if( target_ob->query_skill_mapped("parry") == "qiankun-danuoyi" )
                                        tell_object(all_inventory(environment(me)),
                                                sprintf(HIG+query("name", target_ob)+
                                                        "施展出絕技―― 「" NOR + BLINK + HIR +
                                                        "乾坤大挪移" NOR + HIG "」\n" +
                                                        "竟將" + me->name(1) + "的成名絕技盡數挪移於" +
                                                        me->name(1) + "自身！！！\n" NOR));
                                else
                                        tell_object(all_inventory(environment(me)),
                                                sprintf(HIG+query("name", target_ob)+
                                                        "施展出姑蘇慕容家傳絕技―― 「" NOR + BLINK + HIR +
                                                        "以彼之道 * * * 還施彼身" NOR + HIG "」\n" +
                                                        "竟將" + me->name(1) + "的成名絕技盡數返施於" +
                                                        me->name(1) + "自身！！！\n" NOR));

                                addn("neili", -300, target_ob);
                                return 1;
                        }
                }
        }
        */

        return (int)call_other(file, "perform", me, target_ob);
}

int NewRandom(int n, int base, int d)
{
        int sum;
        int i;
        int k;

        k = 6;
        if( k > n ) k = n;
        if( !k ) return n;

        sum = 0;
        for( i = 0; i < k; i++ ) sum += i;
        sum = random(sum);
        for( i = 0; i < k; i++ ) {
                sum -= i;
                if( sum <= 0 ) {
                        n = n - k + i;
                        if( n <= 0 ) n = 0;
                        break;
                }
        }
        return n;
}

// 特殊招式(由combatd.c調用)
void do_interlink(object me, object victim) { return; }

// 以下是魔法系技能調用
int is_reinpose(object me, object target) { return 0; }

int reinpose(object me, object target, int damage) { return damage; }

int cast_spell(object me, string spell, object target)
{
        string file;

        notify_fail("你所選用的咒文系中沒有這種咒文。\n");
        if( !stringp(file = (string)this_object()->cast_spell_file(spell))
        ||      file_size(file + ".c") <= 0 ) {
                file = "/kungfu/magicpool/" + spell;
                // 魔法池的魔法
                if( file_size(file + ".c") <= 0 )
                        return 0;
        }

        return (int)call_other( file, "cast", me, target);

}

int conjure_magic(object me, string spell, object target)
{
        string file;

        notify_fail("你所選用的法術系中沒有這種法術。\n");

        if( !stringp(file = (string)this_object()->conjure_magic_file(spell))
        ||      file_size(file + ".c") <= 0 )
                return 0;

        return (int)call_other( file, "conjure", me, target);
}

int scribe_spell(object me, object ob, string spell)
{
        string file;

        if( !stringp(file = (string)this_object()->scribe_spell_file(spell))
        ||      file_size(file + ".c") <= 0 )
                return 0;

        return (int)call_other( file, "scribe", me, ob );
}
