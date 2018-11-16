// This program is a part of NT MudLIB
// Written by Lonely@nitan.org
// warcraft.c
// ħ��ϵͳ
        // �ǻ��ͣ�����.ľ��     ���������˻ر��ʼ�ڤ˼�ٶ�
        // �����ͣ��׻�.��     ���������������ʼ��������
        // �����ͣ�����.ˮ��     ���������˷���������������
        // �鶯�ͣ���ȸ.��     ���������˹�������Ǳ������
        // �����ͣ�����.����     ���������˹���������������

// ���������ľ�������ˮ�����䡢������ȡ����ĺ�ʵ��
/*
��  ϵ  �м�������������������Ͻ�����裬ʹ���ֹ����޴�����
        ����
ľ  ϵ  �м��������������ۼ���Ҫ����������ϣ�ȴ���������ľ
        ͷ�ϣ���ǿ��ĵ���������β��ȣ���ԭ�ش��˼���Ȧ����
ˮ  ϵ  �м����������������ֵĹ����������Ͼ���ʯţ�뺣����֪
        ���ա���
��  ϵ  �м����������������ܵĻ���ʹ���ֻ������ȣ�������δ��
        ����ǰ���Լ����˻�ȥ����
��  ϵ  �м����������������ֵĹ����������ϣ�ȴ�����ѻ�ʯ�㹥
        ������ʵ�Ĵ����������������
��  ��  �߼���������ս�����Զ���Ѫ�ָ����ܣ������޴ӹ�������
��  ��  ̫����̫ʼ��̫���ǹ���ϵ���ڷ�����ͬʱ���Զ��������ܣ�
        ̫ʼ�Ƿ���ϵ���ɷ����κ����ԵĹ�����
*/

#include <ansi.h>
#include <name.h>
#include <command.h>
#include <combat.h>

inherit NPC;
inherit F_NOCLONE;
inherit F_OBSAVE;
inherit F_SSERVER;

void remove(string euid)
{
        object env;
        
        if( is_fighting() ) remove_all_enemy(1);
        env = environment();
        if( objectp(env) && interactive(env) ) delete_temp("is_riding", env);
        save();
}

int is_warcraft() { return 1; }
int is_stay_in_room() { return 1; }

int is_owner(object me) { return query_temp("owner") == query("id", me); }
string chinese_s(mixed arg)
{
      if (arg == "�׻�")  return HIY "��" NOR;
      if (arg == "����")  return WHT "ľ" NOR;
      if (arg == "����")  return HIG "ˮ" NOR;
      if (arg == "��ȸ")  return HIR "��" NOR;
      if (arg == "����")  return YEL "��" NOR;
}

void create()
{
        seteuid(getuid());

        set_name("ħ����", ({ "warcraft" }));
        set("long", "��ҿ���������ȥָ���ĵط�(rideto)��\n");
        set("race", "Ұ��");
        set("race_type", WHT "����" NOR);
        set("unit", "ֻ");
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("no_sell", "����ҲҪ���������ǵ���������Ѫ֮��Լ��");
        set("owner", "lonely");
        set("owner_name", "�ߴ���ʤ��");
        set("limbs", ({ "ͷ��", "����", "ǰ��", "�ᱳ", "β��" }) );
        set("verbs", ({ "bite", "hoof" }) );

        set("qi", 300);
        set("max_qi", 300);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 100);
        set("max_neili", 100);
        set("jingli", 100);
        set("max_jingli", 100);
        set("shen_type", 0);
        set("combat_exp", 50000);
        set("attitude", "peaceful");
        set("obedience", 2);
        set("ridable", 1);

        set_skill("dodge", 100);
        set_skill("unarmed", 100);
        set_skill("parry", 100);
        set_skill("force", 100);

        set_temp("apply/attack", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/defence",100);
        set_temp("apply/armor", 200);
        set_temp("apply/dodge", 100);
        set_temp("apply/parry", 100);
        if (! check_clone()) return 0;
        restore();
        setup();

        keep_heart_beat();
}

varargs string short(int raw)
{
        string str;

        str = ::short();
        str += " ��" + query("race_type") + "��";
        return str;
}

string get_level()
{
        string level;

        if( query("level")/10 < 9 )
                level = CHINESE_D->chinese_number(query("level")/10+1) + "��" + CHINESE_D->chinese_number(query("level")%10) + "��";
        else
        if( query("level")/10 == 9 )
                level = HIM "�Ϲ�����" NOR;
        else
                level = HIY "Զ��ʥ��" NOR;

        // ̫ʼ��̫��
        return level;
}

string long()
{
        string result;
        string level;

        result = query("long");

        level = get_level();

        result += "\n";
        result += HIW "���޵ȼ���" + level + "\n" NOR;
        result += HIW "ħ�����ԣ�" + chinese_s(query("race_type")) + "\n" NOR;
        result += HIW "ħ����ֵ��" + query("magic/power")  + "\n" NOR;
        result += "\n";

        return result;
}

void init()
{
        if( query("id", this_player()) == query("owner") ) {
                add_action("do_modify", "modify");
                add_action("do_teach", "teach");
                add_action("do_shape", "shape");
        }

}

void del_hiding(object me, object target)
{

        if( !objectp(me) && !objectp(target) ) return;

        if( objectp(me) )
                delete_temp("hiding_kuihua", me);

        if( objectp(target) )
                target->clear_condition("no_perform");

        return;
}

void del_protect(object me)
{
        if( !objectp(me) ) return;

        delete_temp("protect_xuanwu", me);

        addn_temp("reduce_damage", -90, me);

        return;
}

void heart_beat()
{
        object owner, ob, target;
        object env, env1, env2;

        ob = this_object();

        // �Զ��ظ�״̬
        if( !is_fighting() && (query("qi") < query("max_qi") ||
            query("jing") < query("max_jing") ||
            query("eff_qi") < query("max_qi") ||
            query("eff_jing") < query("max_jing")) )
                    full_self();

        // ��������������Զ�������뿪
        if( !(env1=environment()) || !objectp(owner = find_player(query("owner", ob))) ) {
                save();
                message_vision("$Nһ���Ͳ����ˡ�\n", ob);
                destruct(ob);
                return;
        }

        if( !(env2=environment(owner)) ) return;
        // ������˲���ͬһ��ͼ���ƶ�������ǰ
        // ����״̬����������(follow)������(guard)
        if( living(ob) && (query_temp("comedby", owner) == ob || query("actions", ob)) &&
            env1 != env2 && env1 != owner && !query("no_magic", env2) ) {
                if( is_fighting() ) remove_all_enemy(1);
                ob->move(env2);
                message_vision("��Ȼһ������Ϯ����$n" NOR "�ѳ��������\n", owner, ob);

                // �Զ�����
                ob->set_leader(owner);

                // �Զ�����������ǽ�����״̬�򲻱���
                if( query("actions", ob) == "guard" ) {
                        GUARD_CMD->main(ob, owner);
                }
        }

        env = environment();
        if( env != owner && env != env2 )
                ;
        else {

        // ��ѪС�ڱ�������������
        if( query("env/wimpy") > 0 ) {
                if (query("qi") * 100 / query("max_qi") <= query("env/wimpy") ) {
                        if( env == owner ) {
                                delete_temp("is_riding", owner);
                                delete_temp("is_rided_by");
                        }
                        // ����
                        save();
                        message_vision(HIR "\n$N" HIR "Ѹ���ƶ���" + owner->name() + HIR "��󣬶���������\n" NOR, ob);
                        destruct(ob);

                        return;
                }
        }

        // ͬ�鼼��=========
        // ���ˣ����ң����ѣ����壬����
        // ����������ɱ��������������
        // A������ս��B�������˺�C�������˺�D���˺�����E������״̬

        // ����--����
        if( (query("max_qi", owner) > query("qi", owner) || query("max_qi", owner) > query("eff_qi", owner))
            && query("race_type") == "����" ) {
                if( random(15) < query("level")/10 ) {
                        tell_object(owner, HIY + ob->name() + HIY "ȫ����������Ĺ�â�����㣬��о���Ѫ�����ָ���\n" NOR);
                        addn("qi", 500 + random(query("magic/power"))*200, owner);
                        addn("eff_qi", 200 + random(query("magic/power"))*80, owner);
                        if( query("eff_qi", owner) > query("max_qi", owner) ) set("eff_qi", query("max_qi", owner), owner);
                        if( query("qi", owner) > query("max_qi", owner) ) set("qi", query("max_qi", owner), owner);
                }
        }

        // �׻�--�����æ��
        if( query("race_type") == "�׻�" && owner->is_fighting() ) {
                int time_busy;
                target = offensive_target(owner);
                if( objectp(target) && random(15) < query("level")/10 && !target->is_busy() ) {
                        message_vision(HIG "$N" HIG "��˻һ��������������������ֱ����$n" HIG "$n" HIG
                                       "����ͻ�������ı��Ū����æ���ҡ�\n" NOR, ob, target);
                        time_busy = 1 + random(1 + query("level")/10);
                        if( time_busy > 5 ) time_busy = 5;
                        target->start_busy(time_busy);
                }
        }

        // ��ȸ--��������æ��ʱ��
        if( query("race_type") == "��ȸ" && owner->is_fighting() ) {
                int int_busy;
                if( owner->is_busy() && random(15) < query("level")/10 ) {
                        tell_object(owner, HIM + ob->name() + HIM "�ȶ��ž޴�ĳ�򣬿��������о�ͻȻ����������ࡣ\n" NOR);

                        int_busy = 1 + random(1 + query("level")/10);
                        owner->interrupt_me(owner, int_busy);
                }
        }

        // ����--������֣�������ʱ�޷���������Ч��ʱ�����Ϊ3-7��
        if( query("race_type") == "����" && owner->is_fighting() ) {
                target = offensive_target(owner);
                if( objectp(target) && random(15) < query("level")/10 && !query_temp("hiding_kuihua", owner) ) {
                        message_vision(HIR "$N" HIR "����$n" HIR"һ����Х��$n" HIR "ͻ��������ѣ������ޱȡ�\n" NOR,
                                       ob, target);

                        set_temp("hiding_kuihua", 1, owner);
                        target->apply_condition("no_perform", 7);
                        remove_call_out("del_hiding");
                        call_out("del_hiding", 3 + random(5), owner, target);
                }
        }

        // ����--����
        // ����--���������˺�
        if( query("race_type") == "����" && owner->is_fighting() ) {
                if( random(15) < query("level")/10 && !query_temp("protect_xuanwu", owner) ) {
                        tell_object(owner, HIM + ob->name() + HIM "����һ��ҫ�۵Ĺ�â������ȫ���������ڣ���о���ȫ������в��ǰ㱣����\n" NOR);
                        addn_temp("reduce_damage", 90, owner);
                        set_temp("protect_xuanwu", 1, owner);
                        remove_call_out("del_protect");
                        call_out("del_protect", 3 + random(5), owner);
                }
        }
        }

        ::heart_beat();
}

int do_modify(string arg)
{
        string item, msg;
        object me = this_player();

        if( !arg || sscanf(arg,"%s %s", item, msg) != 2 )
                return notify_fail("SYNTAX: modify ���� ����\n");

        if( item == "flee" ) {
                set("env/wimpy", atoi(msg));
                write("�ϣ�\n");
                save();
                return 1;
        }

        if( item == "actions" ) {
                if( msg != "follow" && msg != "guard" )
                        return notify_fail("��ֻ��������Ϊfollow����guard״̬��\n");

                set("actions", msg);
                set_temp("comedby", this_object(), me);
                write("�ϣ�\n");
                save();
                return 1;
        }

        if( CHINESE_D->check_control(msg) )
                return notify_fail("���������п��Ʒ���\n");

        if( CHINESE_D->check_space(msg) )
                return notify_fail("�������費���ո�\n");

        if( CHINESE_D->check_return(msg) )
                return notify_fail("�������費���س�����\n");

        msg = trans_color(msg, 3);
        switch(item)
        {
        case "desc":
                if( CHINESE_D->check_length(msg) > 100 )
                        return notify_fail("����̫����\n");
                set("long", msg+NOR"\n");
                write("�ϣ�\n");
                save();
                return 1;
        case "nickname" :
                if( CHINESE_D->check_length(msg) > 20 )
                        return notify_fail("����̫����\n");
                set("nickname",msg+NOR);
                write("�ϣ�\n");
                save();
                return 1;
        case "title" :
                if( CHINESE_D->check_length(msg) > 20 )
                        return notify_fail("����̫����\n");
                set("title",msg+NOR);
                write("�ϣ�\n");
                save();
                return 1;
        case "arrive_msg" :
                if( CHINESE_D->check_length(msg) > 60 )
                        return notify_fail("����̫����\n");
                set("arrive_msg",msg+NOR);
                write("�ϣ�\n");
                save();
                return 1;
        case "leave_msg" :
                if( CHINESE_D->check_length(msg) > 60 )
                        return notify_fail("����̫����\n");
                set("leave_msg",msg+NOR);
                write("�ϣ�\n");
                save();
                return 1;

        }
        return notify_fail("��Ҫ�޸�ʲô��\n");

}

int do_teach(string arg)
{
        object me;
        int gin_cost,amount;
        int myskill, itskill;

        me = this_player();

        if( !myskill = me->query_skill(arg, 1) )
                return notify_fail("���������󻹲����أ�\n");

        if( arg != "unarmed" && arg != "parry" && arg != "dodge" && arg != "force" )
                return notify_fail("��ѧ��������ܵģ�\n");

        itskill = query_skill(arg,1);
        if( myskill <= itskill )
                return notify_fail(name()+"�Գ�Ц��Ŀ�������㡣\n");

        if( query("potential", me) - query("learned_points", me) < 1 )
                return notify_fail("���Ǳ�ܲ�����\n");

        gin_cost = 100/ (int) query_int();
        if( (int)query("jing", me) < gin_cost )
                return notify_fail("����Ȼ̫����û�а취�̣�\n");

        me->receive_damage("jing", gin_cost);
        addn("potential", -1, me);
        amount = (int)me->query_int() * (int) query_int();
        message_vision(sprintf("$N�����䷳�ؽ�$n��%s����\n", to_chinese(arg)), me, this_object());

        if( random(100) < query("obedience") )
                command("emote �ܲ���Ը�غ���һ����");
        else
        {
                improve_skill(arg, amount);
                message_vision(sprintf("$N�ƺ����ѧ����һЩ��%s����\n", to_chinese(arg)), this_object());
        }
        return 1;

}

string status_color(int current, int max)
{
        int percent;

        if( max>0 ) percent = current * 100 / max;
                else percent = 100;
        if( percent > 100 ) return HIC;
        if( percent >= 90 ) return HIG;
        if( percent >= 60 ) return HIY;
        if( percent >= 30 ) return YEL;
        if( percent >= 10 ) return HIR;
        return RED;
}
/*
int do_shape(string arg)
{
        mapping my;
        string shape;
        mixed at_pt, pa_pt, do_pt;

        my = query_entire_dbase();

        printf("������ %s%3d/ %3d %s(%3d%%)"NOR"  ��Ѫ�� %s%3d/ %3d %s(%3d%%)\n"+NOR,
                status_color(my["jing"], my["eff_jing"]), my["jing"],my["eff_jing"],
                status_color(my["eff_jing"], my["max_jing"]),     my["eff_jing"] * 100 / my["max_jing"],
                status_color(my["qi"], my["eff_qi"]), my["qi"], my["eff_qi"],
                status_color(my["eff_qi"], my["max_qi"]),     my["eff_qi"] * 100 / my["max_qi"]
        );

        printf("ʳ� %d\t\t��ˮ�� %d\n",
        my["food"], my["water"]);
        printf("���ˣ� %s\t\t�ȼ��� %s\n",
        my["owner"],get_level());
        printf("���飺 %d\t\tɱ���� %d\n",
        my["combat_exp"],my["bellicosity"]
        );
        printf("�ǻۣ� %d\t\t���ʣ� %d\n",
        query_int(), query_con()
        );
        printf("�ٶȣ� %d\t\t������ %d\n",
        query_dex(), query_str()
        );

        at_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_ATTACK);
        pa_pt= COMBAT_D->skill_power(this_object(), "parry", SKILL_USAGE_DEFENSE);
        do_pt= COMBAT_D->skill_power(this_object(), "dodge", SKILL_USAGE_DEFENSE);
        printf("������ %d\t\t������ %d\n\n",
        at_pt+1, pa_pt/2+do_pt/2+1
        );
        return 1;
}
*/

// ��ʾͬ��״̬
int do_shape(string arg)
{
        object ob;
        string line = HIC "=-------------------------------------=\n" NOR;
        string str;
        mixed at_pt, pa_pt, do_pt;
        string actions;

        ob = this_object();


        actions = query("actions", ob);
        if( !stringp(actions) )

                actions = "����";
        else
                actions == "follow" ? "������" : "����";

	str = HIY + ob->name() + HIY "״̬��������(" + HIR + actions + HIY + ")��\n" NOR;
        str += line;

        str += HIR "�ȼ���" + sprintf("%s",get_level()) + "\n" NOR;
        str += HIR "���ԣ�" + sprintf("%s",chinese_s(query("race_type"))) + "\n" NOR;
        str += HIR "ħֵ��" + sprintf("%d",query("magic/power")) + "\n" NOR;

        str += HIW "���飺" + sprintf("%d", query("combat_exp")) + "\n" + NOR;
        str += HIW "���ԣ�" + sprintf("%-22d�ٶȣ�%d", query("int"), query("dex")) + "\n" + NOR;
        str += HIW "������" + sprintf("%-22d���ǣ�%d", query("str"), query("con")) + "\n" + NOR;

        str += HIC "������" + sprintf("%d", query("qi")) + "/" + sprintf("%d", query("eff_qi")) + "\n" NOR;
        str += HIC "������" + sprintf("%d", query("neili")) + "/" + sprintf("%d", query("max_neili")) + "\n" NOR;
        str += HIC "������" + sprintf("%d", query("jing")) + "/" + sprintf("%d", query("eff_jing")) + "\n" NOR;
        str += HIC "������" + sprintf("%d", query("jingli")) + "/" + sprintf("%d", query("max_jingli")) + "\n" NOR;

        at_pt= COMBAT_D->skill_power(this_object(), "unarmed", SKILL_USAGE_ATTACK);
        pa_pt= COMBAT_D->skill_power(this_object(), "parry", SKILL_USAGE_DEFENSE);
        do_pt= COMBAT_D->skill_power(this_object(), "dodge", SKILL_USAGE_DEFENSE);

        str += HIM "������" + sprintf("%d", at_pt+1) + "\n" NOR;
        str += HIM "������" + sprintf("%d", pa_pt/2+do_pt/2+1) + "\n" NOR;

        str+= line;

        write(str);
        return 1;
}

varargs mixed set(string idx, mixed para, object ob)
{
        int i, j, lvl, level;

        if( !ob )
                ob = this_object();

        if( idx == "combat_exp" && para ) {
                if( para > query("combat_exp") ) {
                        level = query("level");
                        if( !level || level < 1 ) level = 1;

                        for (i = level; ;i++) {
                                if( (i + 1) * (i + 1) * (i + 1) > (para / 10000) ) {
                                        lvl = i;
                                        break;
                                }
                        }

                        if( lvl > level ) {
                                j = lvl - level;
                                set("level", lvl);

                                addn("max_jingli", 1000*j);
                                addn("max_neili", 2000*j);
                                addn("max_jing", 500*j);
                                addn("max_qi", 300*j);
                                addn("int", j);
                                addn("str", j);
                                addn("con", j);
                                addn("dex", j);
                                set("magic/power", 100*lvl);

                                add_skill("dodge", 50*j);
                                add_skill("parry", 50*j);
                                add_skill("unarmed", 50*j);
                                add_skill("force", 50*j);

                                message_vision(HIY "$N" HIY "����ķ����⣬�������Ϲ�����$N" HIY "�����壬�����ˣ�\n" NOR, ob);
                                if( lvl%10 == 0 )
                                        message_vision(HIY "ͻȻ��ճ���һ��������$N" HIY "����ĺ����ӣ�$N" HIY "ȫ��ͨ�죡\n" NOR, ob);
                        }
                }
                return efun::set(idx, para);
        } else
                return efun::set(idx, para);
}

mixed add(string prop, mixed data)
{
        string para;
        mixed old;
        int level;

        if( prop == "combat_exp" ) {
                if( !(old = query(prop)) )
                        return set(prop, data);

                if( data < 1 )
                        return efun::set(prop, old + data);

                level = query("level");
                if( !level || level < 1 ) level = 1;

                return set(prop, old + data);
        } else
                return efun::addn(prop, data);
}

// �ٻ��ӿ�
int receive_whistle(object me)
{
        object env, follower;
        int    period;

        if( (env = environment()) && env == me )
        {
                write(name() + "�㲻�������������ٻ���ʲô����\n");
                return 1;
        }

        if( env == environment(me) )
        {
                if( is_fighting() )
                        remove_all_enemy(1);
                message_vision(name() + "һ���Ͳ����ˡ�\n", me);
                period = time() - ((int) query("last_save"));
                if( period < 0 || period > 900 )
                {
                        set("last_save", time());
                        save();
                }
                destruct(this_object());
                return 1;
        }
        else
        {
                if( env )
                {
                        if( env->is_character() && environment(env) )
                                env = environment(env);

                        message("vision", HIG "ͻȻ" + name() + HIG "����һ����â��"
                                HIG "˲����ʧ�ˣ�\n\n" NOR, env);

                        if( interactive(env = environment()) )
                        {
                                delete_temp("is_riding", env);
                                delete_temp("is_rided_by");
                                tell_object(env, HIM + name() +
                                        HIM "��Ȼ�����ȥ�ˣ�\n" NOR);
                                // �����е���Ҳ����
                                if (objectp(follower = query_temp("is_rided_follow", this_object())))
                                {
                                        delete_temp("is_riding_follow", follower);
                                        delete_temp("is_rided_follow");
                                        tell_object(follower, HIM + name() + HIM "��Ȼ�����ȥ�ˣ�\n" NOR);
                                }
                        }
                }
                message_vision(HIG "$n" HIG "��֪������ܵ�$N" HIG "��ǰ��\n\n" NOR,
                        me, this_object());
        }

        move(environment(me));

        if( environment() != environment(me) )
                return 0;

        return 1;
}

varargs void die(object killer)
{
        object owner;
        int exp;


        owner = UPDATE_D->global_find_player(query("owner"));

        if( !objectp(owner) )
                return ::die(killer);

        message_vision(HIR "$N" HIR "���˵�˵�����Բ������ˣ��Ҳ����ٱ������ˣ����أ�\n" NOR, this_object());
        tell_object(owner, HIG "���ħ�������ˣ��뵽����ʦ����ask zhang about ħ�޸�������������ħ�ޣ�\n" NOR);
        set("warcraft/status", "died", owner);

        UPDATE_D->global_destruct_player(owner, 1);

        // ����������2%
        exp = query("combat_exp");
        add("combat_exp", -exp*2/100);

        // ״̬��ԭ
        full_self();

        save();
        destruct(this_object());

        return;
}

varargs void unconcious(object defeater)
{
        die(defeater);
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;

        result = ([ "damage": -query("magic/power") ]);

        result += (["msg" :   HIC "$N" HIC "�Ĺ�������$n"
                              HIC "��ʵ�Ļ����ϡ�\n" NOR ]);

        return result;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{

        ob->receive_wound("qi", 200 + query("magic/power"), me);

        return sort_msg(HIR "$N" HIR "���쳯��$n��" HIR "�����΢"
               "΢������â��һ��Լʮ���ִ�С�Ļ�����$N"
               HIR "����������ɿ�Ļ���$n" HIR "���ؿڣ�"
               "$n" HIR "�ŵŵŵĵ����˼���������������\n" NOR);
}

/*
int do_look(string target)
{
        object ob, me;

        string msg;

        ob = this_object();


        if (! id(target))
                return notify_fail("��Ҫ��ʲô��");

        if (! stringp(msg = query("look_msg", ob)) ) return 1;

        message_sort(HIC + "\n" + msg + "\n" NOR, this_object());

        return 1;
}

int accept_ask(object who, string topic)
{
        // ���õĻش��б�
        object ob;

        mapping ans;
        string *key_ans;
        string msg;

        if (! sizeof(topic))return 0;

        ob = this_object();
        ans = query("answer", ob);

        if (! sizeof(ans))return 0;

        key_ans = keys(ans);

        if (! sizeof(key_ans))return 0;

        if (member_array(topic, key_ans) == -1)return 0;

        return ans[topic];

}

// whichask ָ��ص��б�
mixed whichask()
{
        object ob;

        mapping ans;
        string *key_ans;
        string msg;
        int i;

        ob = this_object();
        ans = query("answer", ob);

        if (! sizeof(ans))return 0;

        key_ans = keys(ans);

        if (! sizeof(key_ans))return 0;

        msg = "";
        for (i = 0; i < sizeof(key_ans); i ++)
        {
                if (i < 10)
                        msg = msg + sprintf(" %d", i + 1) + ". " + key_ans[i] + "\n";
                else
                        msg = msg + sprintf("%d", i + 1) + ". " + key_ans[i] + "\n";
        }


        return msg;
}

// ��ѯ���õĶԻ��б�
mixed answer_list()
{
        object ob;

        mapping ans;
        string *key_ans;
        string msg;
        int i;

        ob = this_object();
        ans = query("answer", ob);

        if (! sizeof(ans))return 0;

        key_ans = keys(ans);

        if (! sizeof(key_ans))return 0;

        msg = "";
        for (i = 0; i < sizeof(key_ans); i ++)
        {
                if (i < 10)
                {
                        msg += HIG + sprintf(" %d", i + 1) + ". " + "ask    : " + key_ans[i] + "��\n" NOR;
                        msg += HIR "    answer : " + ans[key_ans[i]] + "\n\n" NOR;
                }
                else
                {
                        msg += HIG + sprintf("%d", i + 1) + ". " + "ask    : " + key_ans[i] + "��\n" NOR;
                        msg += HIR "   answer : " + ans[key_ans[i]] + "\n\n" NOR;
                }
        }


        return msg;
}

int delete_answer(int n)
{
        object ob;

        mapping ans;
        string *key_ans;
        int i;

        ob = this_object();

        ans = query("answer", ob);

        if (! sizeof(ans)) return notify_fail("��A���޷�ɾ������Ϣ��\n");

        key_ans = keys(ans);

        if (! sizeof(key_ans)) return notify_fail("��B���޷�ɾ������Ϣ��\n");

        if (n > sizeof(key_ans) + 1)
                return notify_fail("��C���޷�ɾ������Ϣ��\n");

        if (n < 1)
                return notify_fail("��D���޷�ɾ������Ϣ��\n");

        // ��ʼɾ��
        map_delete(ans, key_ans[n - 1]);
        set("answer", ans, ob);
        write("ɾ����ϣ�\n");
        return 1;
}
*/

// ���ܴ������ݵĽӿں���
int receive_dbase_data(mixed data)
{
        if( !mapp(data) )
                return 0;

        this_object()->set_dbase(data);

        return 1;
}

// ���б������ݵĽӿں���
mixed save_dbase_data()
{
        mapping data;

        data = this_object()->query_entire_dbase();

        return data;
}
