// Written by Lonely@chinamud.cn
// npc.c

#pragma save_binary

#include <command.h>

inherit CHARACTER;
inherit F_CLEAN_UP;

nosave int keep_beat_flag = 0;
void scan();
void full_self();
int  heal_self();
int  chat();
int  exert_function(string func);

void keep_heart_beat()
{
        set_heart_beat(1);
        keep_beat_flag = 1;
}

void not_keep_heart_beat()
{
        keep_beat_flag = 0;
}

int open_heart_beat()
{
        mapping my;

        if( keep_beat_flag )
                return 1;

        if( is_fighting() )
                return 1;

        if( this_object()->query_condition() )
                return 1;

        if( !living(this_object()) )
                return 1;

        if( this_object()->is_busy() )
                return 1;

        if( this_object()->is_weak() ) 
                return 1; 

        if( query_temp("quest_ob") ||
            this_object()->is_quest_object() ||
            this_object()->is_time_ctl_ob() ) {
                keep_beat_flag = 1;
                return 1;
        }

        my = this_object()->query_entire_dbase();

        if( my["chat_chance"] ) {
                keep_beat_flag = 1;
                return 1;
        }

        if( (my["qi"] < my["max_qi"])
        ||      (my["eff_qi"] < my["max_qi"]) )
        {
                if( this_object()->is_master() ) full_self();
                return 1;
        }

        if( (my["jing"] < my["max_jing"])
        ||      (my["eff_jing"] < my["max_jing"]) )
        {
                if( this_object()->is_master() ) full_self();
                return 1;
        }

        return 0;
}

int init_master()
{
        int exp;
        int i, lvl, level;
        int degree;
        object ob;
        mapping sks;
        string *sk;

        ob = this_object();
        if( !query("master_ob") )
                return 0;

        exp = UPDATE_D->query_max_exp();
        level = to_int(pow(to_float(exp/100), 1.0 / 3)) * 10;

        lvl = 0;
        degree = query("master_ob");
        switch(degree)
        {
        case 1  :  lvl = level / 5;     exp = exp / 5;     break;
        case 2  :  lvl = level * 2 / 5; exp = exp * 2 / 5; break;
        case 3  :  lvl = level * 3 / 5; exp = exp * 3 / 5; break;
        case 4  :  lvl = level * 4 / 5; exp = exp * 4 / 5; break;
        case 5  :  lvl = level;         exp = exp;         break;
        default :  return 0;
        }

        set("combat_exp", exp, ob);
        sks = ob->query_skills();
        sk = keys(sks);

        if( !sizeof(sk) ) return 0;
        for( i = 0; i < sizeof(sk); i++ ) {
                /*
                if( SKILL_D(sk[i])->type() == "knowledge" )
                        continue;
                */
                if( sks[sk[i]] >= lvl )
                        continue;

                ob->set_skill(sk[i], lvl);
        }
        return 1;
}

void setup()
{
        ::setup();

        if( query("master_ob") > 4 )
                init_master();
}

object carry_object(string file)
{
        object ob, env, *clone;

        ob = new(file);
        if( !objectp(ob) ) {
                clone = filter_array(children( file ), (: clonep :));
                if( sizeof(clone) && objectp(clone[0]) &&
                    objectp(env = environment(clone[0])) && !clonep(env) )
                        ob = clone[0];
        }

        if( ob && ob->violate_unique() )
                ob = ob->create_replica();

        if( ob && ob->is_ctl_ob()     // control ob.
        && (!ob->valid_clone()
        || !clonep()) )
        {
                destruct(ob);
                return 0;
        }

        if( objectp(ob) )
                ob->move(this_object());
        return ob;
}

object add_money(string type, int amount)
{
        object ob;

        ob = carry_object("/clone/money/" + type);
        if( !ob ) return 0;
        ob->set_amount(amount);
}

int accept_fight(object who)
{
        string att;
        int perqi;
        int perjing;

        if( !query("can_speak") ) {
                kill_ob(who);
                return 1;
        }

        if( this_object()->is_guarder() )
                return this_object()->check_enemy(who, "fight");

        att = query("attitude");
        perqi = (int)query("qi") * 100 / query("max_qi");
        perjing = (int)query("jing") * 100 / query("max_jing");

        if( is_fighting() ) {
                switch(att)
                {
                case "heroism":
                        if( perqi >= 50 ) {
                                command("say �ߣ����аɣ�");
                                return 1;
                        } else {
                                command("say �ߣ���СЪƬ������ʰ�㲻�١�");
                                return 0;
                        }
                        break;
                default:
                        command("say ���ж�Ϊʤ���ⲻ������̫����");
                        return 0;
                }
        }

        if( perqi >= 75 && perjing >= 75 ) {
                switch (att)
                {
                case "friendly":
                        command("say " + RANK_D->query_self(this_object())
                                + "��ô������" + RANK_D->query_respect(who)
                                + "�Ķ��֣�");
                        return 0;
                case "aggressive":
                case "killer":
                        command("say �ߣ����аɣ�");
                        break;
                default:
                        command("say ��Ȼ" + RANK_D->query_respect(who)
                                + "�ͽ̣�" + RANK_D->query_self(this_object())
                                + "ֻ�÷��㡣");
                        break;
                }
                return 1;
        }

        command("say ������Щƣ����������սҲ���ٰ���");
        return 0;
}

int accept_hit(object who)
{
        int t;
        string att;
        int perqi;
        int perjing;

        if( !query("can_speak") ) {
                kill_ob(who);
                return 1;
        }

        if( this_object()->is_guarder() )
                return this_object()->check_enemy(who, "hit");

/*
        if( this_object()->is_master() ) {
                command("say ��λ" + RANK_D->query_respect(who)
                        + "�����Ǹ������д�ɣ�");
                return -1;
        }
*/

        att = query("attitude");
        perqi = (int)query("qi") * 100 / query("max_qi");
        perjing = (int)query("jing") * 100 / query("max_jing");

        addn_temp("attempt_hit", 1);
        t = query_temp("attempt_hit");

        if( perqi >= 50 && perjing >= 50 ) {
                switch(att)
                {
                case "friendly":
                case "peaceful":
                        command("say ��λ" + RANK_D->query_respect(who)
                                + "��������");
                        break;
                case "aggressive":
                        if( random(t) > 8 ) {
                                command("say �����̵ģ���ô��ô��������" +
                                        RANK_D->query_self_rude(this_object()) +
                                        "����ɱ�䣡");
                                kill_ob(who);
                                return 1;
                        }
                        command("say �ø�" + RANK_D->query_rude(who) +
                                "�����У�");
                        break;
                case "killer":
                        if( random(t) > 3 ) {
                                command("say �ߣ������ҵ��������ˣ�" +
                                        RANK_D->query_self_rude(this_object()) +
                                        "�������أ�");
                                kill_ob(who);
                                return 1;
                        }
                        command("say ���аɣ�");
                        break;
                default:
                        if( random(t) > 7 ) {
                                command("say ��Ҫ��������");
                                kill_ob(who);
                                return 1;
                        }
                        command("say ��λ" + RANK_D->query_respect(who)
                                + "��������");
                        break;
                        switch (random(3))
                        {
                        case 0:
                                command("say ��������");
                                break;
                        case 1:
                                command("say �Ǿͽ���������");
                                break;
                        case 2:
                                command("say ���ɣ��һ��������㲻�ɣ�");
                                break;
                        }
                        break;
                }
        } else {
                switch(att) {
                case "friendly":
                case "peaceful":
                        command("say ��Ȼ" + RANK_D->query_respect(who)
                                + "���������ֻ�в������ˣ�");
                        break;
                case "aggressive":
                case "killer":
                        command("say " + RANK_D->query_rude(who) +
                                "����������");
                        break;
                default:
                        command("say �㲻�ʣ��Ҳ��壡" + RANK_D->query_rude(who) +
                                "���ɲ�Ҫ���ҡ�");
                        break;
                }
                this_object()->kill_ob(who);
        }
        return 1;
}

int accept_kill(object who)
{
        if( !living(this_object()) )
                return 1;

        if( !query("can_speak") ) {
                kill_ob(who);
                return 1;
        }

        if( this_object()->is_guarder())
                return this_object()->check_enemy(who, "kill");

        switch(query("attitude"))
        {
        case "friendly":
        case "peaceful":
                command("say ��Ȼ" + RANK_D->query_respect(who)
                        + "��˱��ȣ�Ī�����²����飡");
                break;
        case "aggressive":
        case "killer":
                command("say " + RANK_D->query_rude(who) +
                        "������Ľ��죬������ļ��գ���");
                break;
        default:
                command("say �ã�" + RANK_D->query_rude(who)
                        + "�����Ǿ�һ��������");
                break;
        }
        return 1;
}

int accept_ansuan(object who)
{
        if( !query("can_speak") ) {
                kill_ob(who);
                return 1;
        }

        if( this_object()->is_guarder())
                return this_object()->check_enemy(who, "ansuan");

        command(random(2) ? "say �ţ���ô��" : "say ��ѽ�����ã�");
        return 1;
}

int accept_touxi(object who)
{
        if( !query("can_speak") )
                return 1;

        if( this_object()->is_guarder() )
                return this_object()->check_enemy(who, "touxi");

        command(random(2) ? "say �ţ���ô����˭��" : "say ��ѽ���㡭");
        return 1;
}

// Ϊ�����ṩ����
mixed accept_ask(object who, string topic)
{
        if( this_object()->is_quester() )
                return QUEST_D->accept_ask(this_object(), who, topic);

        // ����ĳ���Ϊ��ʦ�������
        if( !this_object()->is_knower() ) {
                if( query("ultraquest/id", who) == query("id") )
                        return ULTRA_QUEST_D->ask_information(this_object(), who, topic);
        }
}

// ������Ʒ
int accept_object(object who, object ob)
{
        string id;

        if( this_object()->is_quester() )
                return QUEST_D->accept_object(this_object(), who, ob);

        // �������Ϊ��ʦ�������
        id = query("ultraquest/id", who);

        if( !id ) return 0;

        if( !this_object()->is_knower() &&
            (id == query("id") ||
            query("ultraquest/quest/id", who) == query("id")) )
                return ULTRA_QUEST_D->accept_object(this_object(), who, ob);
}

// �ظ����������Ӧ��
int need_accede(object who)
{
        string id;

        id = query("ultraquest/id", who);

        if( !id ) return 0;

        if( !this_object()->is_knower() &&
            (id == query("id") ||
            query("ultraquest/quest/id", who) == query("id")) )
                return ULTRA_QUEST_D->need_accede(this_object(), who);
}

// This function is called by the reset() of the room that creates this
// npc. When this function is called, it means the room demand the npc
// to return its startroom.
int return_home(object home)
{
        // Are we at home already?
        if( !environment() || environment() == home )
                return 1;

        // Are we able to leave?
        if( !living(this_object()) || is_fighting() ||
            !mapp(query("exits", environment())) )
                return 0;

        // Leave for home now.
        message("vision", this_object()->name() + "����ææ���뿪�ˡ�\n",
                environment(), this_object());

        return move(home);
}

void scan()
{
        object me;

        me = this_object();
        if( !environment() || !living(me) ) return;

        if( me->is_coagent() && me->is_helping() && !me->is_fighting() ) {
                // finish helping
                me->finish_help();
        }

        if( !me->is_fighting() ) {
                // �������
                me->remove_hatred();
        }

        if( heal_self() ) return;

        chat();
}

// Here, the NPC will process the heal/recover.
int heal_self()
{
        mapping my;
        int cost;

        if( is_busy() || is_fighting() )
                // ��æ��
                return 0;

        if( query("not_living") )
                // ������
                return 0;

        if( !query_skill_mapped("force") )
                // û�м����ڹ�
                return 0;

        if( query_temp("no_exert") )
                // ���������ֹʹ���ڹ�
                return 0;

        my = this_object()->query_entire_dbase();
        if( my["neili"] < 50 )
                return 0;

        if( my["jing"] < my["eff_jing"] * 8 / 10 ) {
                // ����̫��
                exert_function("regenerate");
                return 1;
        }

        if( my["qi"] < my["eff_qi"] * 8 / 10 &&
            query_skill("force") >= 150 &&
            my["eff_qi"] > my["max_qi"]/2 ) {
                // ��Ѫ�������沢���ڹ��ȼ���
                exert_function("recover");
                return 1;
        }

        if( my["eff_qi"] < my["max_qi"] ) {
                // ������
                exert_function("heal");
                return 1;
        }

        if( my["eff_jing"] < my["max_jing"] &&
            my["eff_qi"] > my["max_qi"]/2 ) {
                // ���ܵ�����ʧ
                exert_function("jingheal");
                return 1;
        }

        if( my["neili"] < my["max_neili"] - 10 ) {
                // �����������棬�����ָ�
                cost = my["max_neili"] - my["neili"];
                if( cost > my["qi"] / 2 ) cost = my["qi"] / 2;
                command(sprintf("dazuo %d", cost));
                return 1;
        }

        return 0;
}

// This is the chat function dispatcher. If you use function type chat
// message, you can either define your own functions or use the default
// ones.
int chat()
{
        mixed msg, str;
        int chance, rnd;

        if( is_busy() )
                return 0;
        if( !chance = (int)query(is_fighting() ? "chat_chance_combat" : "chat_chance") )
                return 0;

        if( arrayp(msg = query(is_fighting() ? "chat_msg_combat" : "chat_msg")) && sizeof(msg) ) {
                if( random(120) < chance ) {
                        rnd = random(sizeof(msg));
                        str = msg[rnd];
                        if( stringp(str) )
                                say(str);
                        else if( functionp(str) )
                                return evaluate(str);
                }
                return 1;
        }
}

// Default chat
// Default chat function: Let the npc random move to another room.
int random_move()
{
        mapping exits;
        string *dirs;

        if( !environment() || !living(this_object()) ) return 0;
        if( !mapp(exits = query("exits", environment())) || !sizeof(exits) ) return 0;

        dirs = keys(exits);
        command("go " + dirs[random(sizeof(dirs))]);
        return 1;
}

// Default chat function: Let the npc cast his/her enabled spells
void cast_spell(string spell)
{
        string spell_skill;

        if( !environment() || !living(this_object()) ) return;
        if( stringp(spell_skill = query_skill_mapped("spells")))
                SKILL_D(spell_skill)->cast_spell(this_object(), spell);
}

// Default chat function: Let the npc exert his/her enabled force
int exert_function(string func)
{
        string force_skill;

        if( !environment() || !living(this_object()) ) return 0;
        if( !stringp(force_skill = query_skill_mapped("force")) )
                return 0;
        if( this_object()->query_condition("no_exert") )
                return 0;

        if( SKILL_D(force_skill)->exert_function(this_object(), func) )
                return 1;

        return SKILL_D("force")->exert_function(this_object(), func);
}
// Default chat function: Let the npc perform special action with
// his/her enabled martial art
int perform_action(string action)
{
        string martial_skill, act;

        if( !environment() || !living(this_object()) ) return 0;
        if( this_object()->query_condition("no_perform") )
                return 0;
        if( !stringp(action))   return 0;
        if( sscanf(action, "%s.%s", martial_skill, act) != 2 )
                return 0;
        martial_skill = query_skill_mapped(martial_skill);
        if( stringp(martial_skill) )
                return SKILL_D(martial_skill)->perform_action(this_object(), act);
}

// Check the player wether is belong a family
int check_family(object ob, string fam)
{
        if( query("family/family_name", ob) == fam )
                return 1;

        if( !query("family/family_name", ob) &&
            query("born_name", ob) == fam )
                return 1;

        return 0;
}

// when remove
void remove()
{
        mixed fun;

        if( functionp(fun = query_temp("override/destruct")) )
                catch(evaluate(fun, this_object()));

        ::remove();
}

// environment destruct
void move_or_destruct()
{
        remove();
}
/*
void relay_emote(object me, string verb)
{
        string player_id, att, relay_msg;
        string *emote;
        string cmd_emote;
        object ob = this_object();
        int    i;

        if( !userp(me) )
                return;

        if( !query("can_speak", ob) )
                return;

        player_id = query("id", me);

        att = query( "attitude" );

        // ������npc��������emote���mapping
        // ��һЩemote������ķ�Ӧ��
        // �����Ӧ�����Ǹ�string��Ҳ�����Ǹ�function

        if( relay_msg = query("emote/" + verb) ) {
                if( stringp(relay_msg) )
                        message_vision(relay_msg + "\n", ob, me);
                else if( functionp(relay_msg) )
                        return evaluate(relay_msg);

                return;
        }

        if( random(2) != 1 )
                return ;

        emote = sort_array(EMOTE_D->query_all_emote(), 1);
        i = 0;
        i = sizeof(emote);

        if( !i ) return ;

        cmd_emote = emote[random(i)];
        command(cmd_emote + " " + player_id);
}
*/

void full_self()
{
        mapping my;

        clear_condition(0);
        clear_weak();
        this_object()->interrupt_me(this_object());

        my = this_object()->query_entire_dbase();

        my["eff_qi"] = my["max_qi"];
        my["qi" ] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["jing" ] = my["max_jing"];
        if( /*undefinedp*/(my["init_max_neili"]) )
                my["max_neili"] = my["init_max_neili"];
        if( /*!undefinedp*/(my["init_max_jingli"]) )
                my["max_jingli"] = my["init_max_jingli"];
        my["neili" ] = my["max_neili"];
        my["jingli" ] = my["max_jingli"];
        return;
}

void attempt_apprentice(object ob)
{
        command("sigh "+query("id", ob));
        command("say "+RANK_D->query_self(this_object())+"����ѧǳ�����������ӵܣ���λ"+
                       RANK_D->query_respect(ob)+"��ı�߾Ͱɣ�");
        return;
}
