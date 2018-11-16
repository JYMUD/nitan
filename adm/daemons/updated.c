// updated.c
// write by Doing Lu for user management
// because a user may does much association with others,
// so I must assure all the data keep consistant
// Update by Lonely.

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <room.h>

inherit F_SAVE;

// data need save
mixed title_base;
int valid_level = 30;
string *total = ({});

nosave int max_exp = 50000;

nosave string *special_skill = ({
        "agile", "hatred", "power", "self", "mystery", "ironskin", "youth", "trick", "might", "cunning", "clever",
});

nosave string *special_ultimate = ({
        "emperor", "lonely", "queen",
});

string query_save_file() { return DATA_DIR "pinfo"; }

void remove_title(object ob);
void set_title(object ob);
object global_find_player(string user);
void global_destruct_player(object ob, int raw);
mixed query_max_exp() { return 100000000; }

int set_valid_level(int level)
{
        valid_level = level;
        return level;
}
// �ȼ���ӡ
int can_improve_level(int level)
{
        if (level >= valid_level)
                return 0;

        return 1;
}

#define LVL_BLK 10

int level_summary(object me, int level)
{
        mapping lvl_lst = ([]);
        string *lvl_term;    
        string str = sprintf("%s+%d","exp_level",level);
        int i, n, file_level;
             
        if( level%LVL_BLK  ) return 1;
        
        lvl_lst = DB_D->query_data("level_list");
        if( !mapp(lvl_lst) || sizeof(lvl_lst) < 1 )
        {
                lvl_lst = ([]);
                lvl_lst[str] = 1;
                CHANNEL_D->channel_broadcast(
                        "news", sprintf("%s(%s)������ȼ��Ѿ��ﵽ�� %d �����Ž����ֵ�һ�ˣ���",
                                        query("name", me),query("id", me),level));

                HISTORY_D->add_history("����ȼ�����", query("id", me), sprintf("����ȼ� %d �������� %d ����: 1.\n",
                                        level, query("age", me)));
        }
        else
        {
                lvl_term=keys(lvl_lst);
                for( i=0;i<sizeof(lvl_term);i++ )
                {
                        sscanf( lvl_term[i],"exp_level+%d",file_level );
                        if (level>file_level)
                        {
                                map_delete(lvl_lst,lvl_term[i]);
                                lvl_lst[str]=1;
                                CHANNEL_D->channel_broadcast(
                                        "news",sprintf("%s(%s)������ȼ��Ѿ��ﵽ�� %d �����������ֵ�һ�ˣ���",
                                                        query("name", me),query("id", me),level));
                                        
                                HISTORY_D->add_history("����ȼ�����", query("id", me), sprintf("����ȼ� %d �������� %d ����: 1.\n",
                                                        level, query("age", me)));
                        }

                        if (level==file_level)
                        {
                                lvl_lst[lvl_term[i]] +=1;
                                n = lvl_lst[lvl_term[i]];
                                if( n <= 10 )   
                                {
                                        CHANNEL_D->channel_broadcast(
                                                "news",sprintf("%s(%s)������ȼ��Ѿ��ﵽ�� %d �����������ֵ�%s�ˣ���",
                                                                query("name", me),query("id", me),level,chinese_number(lvl_lst[lvl_term[i]])));
                                
                                        HISTORY_D->add_history("����ȼ�����", query("id", me), sprintf("����ȼ� %d �������� %d ����: %d.\n",
                                                                level, query("age", me), n));
                                }
                        }

                        if (level<file_level)
                        {
                                CHANNEL_D->channel_broadcast(
                                        "news",sprintf("%s(%s)�������Ѿ��ﵽ�� %d ����",
                                                        query("name", me),query("id", me),level));
                        }
                }
        }
        DB_D->set_data("level_list", lvl_lst);
        return 1;
}

int improve_valid_level(object ob, int level)
{
        if( wizardp(ob) ) return 1;
        level_summary(ob, level);

        if( !total ) total = ({});

        if( level >= valid_level
        &&  member_array(query("id", ob),total) == -1 )
        {
                total+=({query("id", ob)});
                if (sizeof(total) >= 10)
                {
                        CHANNEL_D->channel_broadcast("news", HIM+query("id", ob)+HIM"��"+implode(total[0..sizeof(total) - 3], "��") +
                                "��" + total[sizeof(total) - 2] + "������֮����"+
                                "�Ƴ���" HIY + valid_level + NOR +HIM "����ӡ��\n" NOR);
                        valid_level += 10;
                        total = ({});
                }
                save();
        }

        return 1;
}

void create()
{
        seteuid(getuid());
        restore();

        if (arrayp(title_base))
                title_base = filter_array(title_base, (: arrayp($1) && sizeof($1) == 2 :));
        else
                title_base = 0;
}

#define LUBAN           "/adm/npc/luban"
#define RING_DIR        "/data/item/ring/"

// check the user's data when login
void check_user(object ob)
{
        mapping my;
        mapping skill_status;
        string *sname;
        int combat_exp;
        int level;
        int i;
        mapping party;
        object budai;

        my = ob->query_entire_dbase();

        if( query("family/generation", ob) == 0 )
                delete("family", ob);

        if( query("gender", ob) == "����" )
                set("class", "eunach", ob);

        if( query("combat/today/which_day", ob) != time()/86400 )
                delete("combat/today", ob);

        if( query("couple", ob) && !query("static/marry", ob) )
                set("static/marry", 1, ob);
        /*
        if( query("family/family_name", ob) == "ؤ��" &&
            query("family/beggarlvl", ob) )
        {
                budai = new("/d/gaibang/obj/budai");
                budai->set_amount(query("family/beggarlvl", ob));
                budai->move(ob);
                budai->wear();
        }
        */
        if (mapp(party = my["party"]) && stringp(party["party_name"]))
                party["party_name"] = filter_color(party["party_name"]);

        // ��¼����
        NAME_D->map_name(query("name", ob),query("id", ob));

        // �����������м�ʱ��
        reset_eval_cost();

        // ����ƺ�
        set_title(ob);

        if (undefinedp(my["eff_jing"]))  my["eff_jing"] = my["max_jing"];
        if (undefinedp(my["eff_qi"])) my["eff_qi"] = my["max_qi"];
        if (my["eff_jing"] > my["max_jing"]) my["eff_jing"] = my["max_jing"];
        if (my["eff_qi"] > my["max_qi"]) my["eff_qi"] = my["max_qi"];
        if (my["jing"] > my["eff_jing"]) my["jing"] = my["eff_jing"];
        if (my["jing"] > my["eff_jing"]) my["jing"] = my["eff_jing"];
        if (my["neili"] > my["max_neili"] * 2) my["neili"] = my["max_neili"] * 2;

        combat_exp=query("combat_exp", ob);
        if (!wizardp(ob) && combat_exp > max_exp)
                max_exp = combat_exp;

        if (!mapp(skill_status = ob->query_skillc()))
                return;
        /*
        sname  = keys(skill_status);

        for (i = 0; i < sizeof(sname); i++)
        {
                if( query("reborn", ob) )
                        continue;

                level = skill_status[sname[i]];
                if( !find_object(SKILL_D(sname[i])) && !load_object(SKILL_D(sname[i])) )
                {
                        log_file("skills", sprintf("the skill %s of %s is no exists.\n", sname[i], query("id", ob)));
                        tell_object(ob, "No such skill:" + sname[i] + "\n");
                        continue;
                }

                if (SKILL_D(sname[i])->type() == "martial")
                {
                        while (level &&
                               (level - 1) * (level -1 ) * (level - 1) / 10 > combat_exp)
                                   level--;

                        ob->set_skill(sname[i], level);
                }
        }

        if ((level = ob->query_skill("zuoyou-hubo", 1)) > 0)
                addn_temp("apply/parry", -level/4, ob);
        */
        SKILLS_D->add_id_into_skills(ob);
        if( query("skill_mix", ob) )
                SKILLS_D->enable_skill_mix(ob,query("skill_mix", ob));
}

// clear the user's data
// when catalog parameter equal to "all", I will remove all
// the informatino of this user. This may be used when the
// user was purged.
varargs string clear_user_data(string user, string cat, int raw)
{
        object login_ob;
        object ob;
        string couple_id;
        string path, file_name;
        string *dirs;
        object temp;
        string brothers;
        string bro_id;
        string *ks;
        mapping bro;
        int flag;
        int i;

        // only root uid can does it
        if (previous_object() &&
            getuid(previous_object()) != ROOT_UID &&
            geteuid(previous_object()) != "lonely" &&
            geteuid(previous_object()) != user)
                return "����Ȩ�������ҵ����ݡ�\n";

        // find the user's body
        seteuid(getuid());
        login_ob = 0;
        ob = find_player(user);
        if (!ob)
        {
                login_ob = new(LOGIN_OB);
                set("id", user, login_ob);
                ob = LOGIN_D->make_body(login_ob);
                if (!ob)
                {
                        catch(destruct(login_ob));
                        return "��ʱ�޷�������Ҷ���\n";
                }

                if (!ob->restore())
                {
                        catch(destruct(login_ob));
                        catch(destruct(ob));
                        return "û�������ҡ�\n";
                }

                ob->setup();
        }

        // no catalog? treat it as "all"
        if (!cat) cat = "all";
        flag = 0;

        // remove name information
        if (cat == "name" || cat == "all")
                NAME_D->remove_name(query("name", ob),query("id", ob));

        // remove room information
        if ((cat == "room" || cat == "all") &&
            mapp(query("private_room", ob)) )
        {
                // Demolish the room of the user
                LUBAN->demolish_room(ob);
                flag++;
        }

        // remove marriage information
        if ((cat == "couple" || cat == "all") &&
            mapp(query("couple", ob)) )
        {
                // clear the couple infomation

                // remove the ring
                file_name=RING_DIR+query("id", ob);
                if (file_size(file_name + ".c") > 0)
                {
                        if (temp = find_object(file_name))
                        {
                                if (environment(temp))
                                {
                                        message("vision", HIM + temp->name() +
                                                HIM "��Ȼ����һ�����̣������ˣ�\n" NOR,
                                                environment(temp));
                                }
                        }
                        DBASE_D->clear_object(file_name);
                }

                couple_id=query("couple/couple_id", ob);
                delete("couple", ob);
                delete("can_summon/wedding ring", ob);
                if( !sizeof(query("can_summon", ob)) )
                        delete("can_summon", ob);
                flag++;
                if (couple_id) clear_user_data(couple_id, "couple");
        }

        // remove item information
        if (cat == "item" || cat == "all")
        {
                object item;
                mapping sum;

                // clear the all item
                path=ITEM_DIR+query("id", ob)[0..0]+"/";
                dirs=get_dir(path+query("id", ob)+"-*");
                for (i = 0; i < sizeof(dirs); i++)
                {
                        file_name = path + dirs[i];
                        if ((item = find_object(file_name)) &&
                            environment(item))
                        {
                                message("vision", HIM + item->name() +
                                        "��Ȼ����һ�����̣������ˣ�\n" NOR,
                                        environment(item));
                        }

                        if (raw)
                        {
                                DBASE_D->clear_object(file_name);
                                rm(file_name);
                        }
                }

                if( mapp(sum=query("can_summon", ob)) )
                {
                        // clear summon information
                        ks = keys(sum);
                        for (i = 0; i < sizeof(ks); i++)
                                if( sscanf(sum[ks[i]],path+query("id", ob)+"-%*s") == 1 )
                                        map_delete(sum, ks[i]);

                        if (!sizeof(sum))
                                delete("can_summon", ob);
                }
        }

        // remove cruise information
        if (cat == "cruise" || cat == "all")
        {
                // clear the all item
                file_name=ITEM_DIR+"curise/"+query("id", ob);
                if (file_size(file_name + ".c") > 0)
                {
                        if (temp = find_object(file_name))
                        {
                                if (environment(temp))
                                {
                                        message("vision", HIM + temp->name() +
                                                HIM "��Ȼ����һ�����̣������ˣ�\n" NOR,
                                                environment(temp));
                                }
                        }

                        if (raw)
                        {
                                DBASE_D->clear_object(file_name);
                                rm(file_name + ".c");
                        }
                }
                delete("can_summon/qiankun", ob);
                if( !sizeof(query("can_summon", ob)) )
                        delete("can_summon", ob);
        }

        // remove warcraft information
        if (cat == "warcraft" || cat == "all")
        {
                mapping whi;

                file_name=DATA_DIR+"warcraft/"+query("id", ob);
                if (file_size(file_name + ".c") > 0)
                {
                        if (temp = find_object(file_name))
                        {
                                if (environment(temp))
                                {
                                        message("vision", HIM + temp->name() +
                                                HIM "��Ȼ����һ�����̣������ˣ�\n" NOR,
                                                environment(temp));
                                }
                        }

                        if (raw)
                        {
                                DBASE_D->clear_object(file_name);
                                rm(file_name + ".c");
                        }
                }
                if( mapp(whi=query("can_whistle", ob)) )
                {
                        // clear summon information
                        ks = keys(whi);
                        for (i = 0; i < sizeof(ks); i++)
                                if (whi[ks[i]] == file_name)
                                        delete("can_whistle/"+ks[i], ob);

                        if( !sizeof(query("can_whistle", ob)) )
                                delete("can_whistle", ob);
                }

        }

        /*
        // remove invent information
        if (cat == "invent" || cat == "all")
        {
                mapping invents;
                string  *meskill;

                if( mapp(invents=query("invent", ob)) )
                {
                        meskill = keys(invents);
                        for (i = 0; i < sizeof(meskill); i++)
                        {
                                CHINESE_D->remove_translate(invents[meskill[i]]);
                                SKILLS_D->remove_skill_from_skills(ob, invents[meskill[i]]);
                                ob->delete_skill(invents[meskill[i]]);
                                rm( SKILL_D(invents[meskill[i]]) + ".c" );
                                if (file_size(SKILL_D(invents[meskill[i]])) == -2)
                                rmtree( SKILL_D(invents[meskill[i]]) + "/" );
                        }

                        delete("invent", ob);
                }
        }

        // remove create information
        if (cat == "create" || cat == "all")
        {
                mapping creates;
                string  *skills, *perform;
                string  dir;
                object  pob;

                if( mapp(creates=query("create", ob)) )
                {
                        skills = keys(creates);
                        for (i = 0; i < sizeof(skills); i++)
                        {
                                dir = SKILL_D(skills[i]);
                                if (dir[strlen(dir) - 1] != '/')
                                        dir += "/";
                                if (SKILL_D(skills[i])->valid_enable("force"))
                                        dir += "perform/";
                                perform = keys(creates[skills[i]]);
                                foreach (string pfm in perform)
                                {
                                        if (pob = get_object(dir + pfm))
                                                destruct(pob);
                                        rm(dir + pfm + ".c");
                                        delete("can_perform/"+skills[i]+"/"+pfm, ob);
                                }
                                if (sizeof(get_dir(dir)) < 1)
                                        rmdir(dir);
                        }
                        delete("create", ob);
                }
        }
        */

        // remove board information
        if (cat == "board" || cat == "all")
        {
                object *rooms;
                rooms = filter_array(children(CHAT_ROOM),
                                     (:clonep($1) && query("owner_id", $1) == $(user):));
                for (i = 0; i < sizeof(rooms); i++)
                        destruct(rooms[i]);
                file_name = DATA_DIR + "board/chatroom_" + user + __SAVE_EXTENSION__;
                rm(file_name);
        }

        // remove haterd information
        if (cat == "hatred" || cat == "all")
        {
                // remove the hatred information about the
                // familys & leagues to this player
                FAMILY_D->remove_hatred(query("id", ob));
                LEAGUE_D->remove_hatred(query("id", ob));
                BUNCH_D->remove_hatred(query("id", ob));
        }

        // remove brothers information
        if( mapp(bro=query("brothers", ob)) &&
            (sscanf(cat, "brothers:%s", brothers) == 1 || cat == "all"))
        {
                // remove all the brothers information
                if (cat == "all") brothers = "all";

                // here, I remove the brothers information of
                // ob, when brothers equal to "all", then I
                // will remove all brothers for this ob, Does it
                // cause a BUG? I won't, because the ID "all"
                // can not be registered for this MUD.
                if (brothers == "all")
                {
                        foreach (bro_id in keys(bro))
                                // remove my brother's data for me
                                clear_user_data(bro_id,"brothers:"+query("id", ob));

                        delete("brothers", ob);
                } else
                if (!undefinedp(bro[brothers]) != -1)
                {
                        // remove this brother
                        map_delete(bro, brothers);
                        if (sizeof(bro) < 1)
                                delete("brothers", ob);
                        else
                                set("brothers", bro, ob);
                }
                flag++;
        }

        // remove league information
        if (cat == "league" || cat == "all")
        {
                // remove the user's league info
                LEAGUE_D->remove_member_from_league(ob);
                delete("league", ob);
        }

        // remove bunch information
        if (cat == "bunch" || cat == "all")
        {
                // remove the user's banghui info
                BUNCH_D->remove_member_from_bunch(ob);
                delete("bunch", ob);
                flag++;
        }

        if (cat == "skill" || cat == "all")
                SKILLS_D->remove_id_from_skills(ob);

        // remove title information
        if (cat == "title" || cat == "all")
                remove_title(ob);

        // remove granted information
        if (cat == "grant" || cat == "all")
                SECURITY_D->remove_grant(ob, "*");

        // save the data of the user
        if (flag) ob->save();

        // Destrut the object if create temporate
        if (login_ob)
        {
                catch(destruct(login_ob));
                catch(destruct(ob));
        }

        return "�ɹ���\n";
}

// remove an user
varargs string remove_user(string user, int raw)
{
        object ob;
        string result;
        string flogin, fuser, fpackage;

        if (user == "lonely") return "���󲻿���Ү��";

        // destruct the user object
        if (ob = find_player(user))
        {
                if( query_temp("link_ob", ob) )
                        catch(destruct(query_temp("link_ob", ob)));
                catch(destruct(ob));
        }

        // Remove the user from wizlist if the user was wizard
        SECURITY_D->set_status(user, "(player)");

        flogin = "login/" + user[0..0] + "/" + user + __SAVE_EXTENSION__;
        fuser  = "user/"  + user[0..0] + "/" + user + __SAVE_EXTENSION__;
#ifdef QUIT_SAVE_ALL
        fpackage = "user/"  + user[0..0] + "/" + user + ".package" + __SAVE_EXTENSION__;
        assure_file(TEMP_DIR + fpackage);
#endif
        assure_file(TEMP_DIR + flogin);
        assure_file(TEMP_DIR + fuser);

        // clear the data of user first
        result = clear_user_data(user, "all", raw);

#ifdef DB_SAVE
        if (!DATABASE_D->query_db_status())
                DATABASE_D->connect_to_database();
        DATABASE_D->db_remove_player(user);

        if (raw)
                MEMBER_D->db_remove_member(user);

        if (TX_SAVE)
        {
                cp(DATA_DIR + flogin, TEMP_DIR + flogin);
                cp(DATA_DIR + fuser,  TEMP_DIR + fuser);
#ifdef QUIT_SAVE_ALL
                cp(DATA_DIR + fpackage, TEMP_DIR + fpackage);
                rm(DATA_DIR + fpackage);
#endif
                rm(DATA_DIR + flogin);
                rm(DATA_DIR + fuser);
        }
        // ��̳ɾ��ID
        BOARD_D->db_remove_player(user);
#else
        cp(DATA_DIR + flogin, TEMP_DIR + flogin);
        cp(DATA_DIR + fuser,  TEMP_DIR + fuser);
#ifdef QUIT_SAVE_ALL
        cp(DATA_DIR + fpackage, TEMP_DIR + fpackage);
        rm(DATA_DIR + fpackage);
#endif
        rm(DATA_DIR + flogin);
        rm(DATA_DIR + fuser);
#endif
}

// user born
void born_player(object me)
{
        mixed files;
        int i;
        string special;
        string msg;

        set("max_neili", 2000, me);
        set("neili", 2000, me);
        set("max_jingli", 1000, me);
        set("jingli", 1000, me);
        set("max_qi", 600, me);
        set("eff_qi", 600, me);
        set("qi", 600, me);
        set("max_jing", 450, me);
        set("eff_jing", 450, me);
        set("jing", 450, me);

        msg = HIG "�����������ļ����У�" NOR;

        // �鿴���е����⼼���ļ�
        // files = get_dir("/kungfu/special/");
        files = special_skill;
        delete("special_skill", me);

        if (sizeof(files))
        {
                // �������еļ����ļ�
                // for (i = 0; i < sizeof(files); i++)
                        // sscanf(files[i], "%s.c", files[i]);

                // ������ò < 20 ����פ��
                if( query("per", me)<20 )
                        files -= ({ "youth" });

                // ��õ�һ���
                special = files[random(sizeof(files))];
                set("special_skill/"+special, 1, me);
                msg += SPECIAL_D(special)->name();

                files -= ({ special });
                //if (sizeof(files) && random(100) == 1)
                if (sizeof(files))
                {
                        // ��õڶ����
                        special = files[random(sizeof(files))];
                        set("special_skill/"+special, 1, me);
                        msg += HIG "��" NOR + SPECIAL_D(special)->name();
                }

                if (random(1000000) == 1)
                {
                        // ����ռ�����
                        special = special_ultimate[random(sizeof(special_ultimate))];
                        set("special_skill/"+special, 1, me);
                        msg += HIG "��" NOR + SPECIAL_D(special)->name();
                }

                msg += HIG "��\n" NOR;
                me->start_call_out((: call_other, __FILE__,
                                      "notice_player", me, msg :), 0);
        }
#ifdef DB_BOARD
        // ��̳����ID
        BOARD_D->db_create_user(me);
#endif
}

// notice user a piece of message, delay call by born user
void notice_player(object me, string msg)
{
        tell_object(me, msg);
        me->start_call_out((: call_other, __FILE__, "give_new_mygift_quest",
                                      me:), 3);
}

// �����µ�MYGIFT��������
void give_new_mygift_quest(object me)
{
        MYGIFT_D->give_mygift(me, "1");
}

// query title dbase
mixed query_title_base()
{
        if (!is_root(previous_object()))
                return 0;

        return title_base;
}

// set title dbase
mixed set_title_base(mixed ts)
{
        if (!is_root(previous_object()))
                return 0;

        title_base = ts;
}

// ���ĳ����ҵ� title
void remove_title(object ob)
{
        int i;

        if( !arrayp(title_base) || !query("granted_title", ob) )
                return;

        delete_temp("title", ob);
        delete("granted_title", ob);

        for (i = 0; i < sizeof(title_base); i++)
        {
                // �������е� title
                if( title_base[i][1] == query("id", ob) )
                        // ȥ��title
                        title_base[i][1] = 0;
        }
        save();
        return;
}

// ����ĳ����ҵ� title
void set_title(object ob)
{
        string id;
        int i;

        if( !arrayp(title_base) || !query("granted_title", ob) )
                return;

        id=query("id", ob);
        for (i = 0; i < sizeof(title_base); i++)
                if (title_base[i][1] == id)
                {
                        // ����title
                        set_temp("title", title_base[i][0], ob);
                        return;
                }

        // ����û���û�з���ĳƺ�
        delete("granted_title", ob);
}

// Ѱ�һ����ĳһ�����
// �������������Ҫ������Щ�����ߵ���ң������ʹ�øú���
// �������ҵ��벢�ҽ����޸ģ���ע�⣺�޸�����Ժ�������
// ������ң�����ʹ�� global_destruct_player �������������
// ��û�е������������������ҵĶ�ʱ�����Զ�������ҡ�
object global_find_player(string user)
{
        object ob;
        object login_ob;

        ob = find_player(user);
        if (!ob)
        {
                login_ob = new(LOGIN_OB);
                set("id", user, login_ob);
                ob = LOGIN_D->make_body(login_ob);
                if (!ob)
                {
                        catch(destruct(login_ob));
                        return 0;
                }

                evaluate(bind((: seteuid(getuid()) :), ob));

                if (!ob->restore())
                {
                        catch(destruct(login_ob));
                        catch(destruct(ob));
                        return 0;
                }

                set_temp("temp_loaded", 1, ob);
                ob->start_call_out(bind((: call_other, __FILE__, "global_destruct_player", ob, 0 :), ob), 0);
                catch(destruct(login_ob));
        }

        return ob;
}

// ����һ���� UPDATE_D ��������
void global_destruct_player(object ob, int raw)
{
        if( objectp(ob) && query_temp("temp_loaded", ob) )
        {
                if (raw) ob->save();
                destruct(ob);
        }
}
