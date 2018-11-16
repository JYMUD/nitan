// This program is a part of NITAN MudLIB
// look.c

#pragma optimize
#pragma save_binary

#include <room.h>
#include <ansi.h>
#include <combat.h>
#include <armor.h>

// flag of func:look_all_inventroy_of_room/ret_str
#define SHOW_IMMEDIATELY        0
#define RETURN_RESULT           1

inherit F_CLEAN_UP;

#include <locate.h>
int look_room(object me, object env, int brief);
int look_item(object me, object obj);
int look_living(object me, object obj);
int look_room_item(object me, string arg);
string look_equiped(object me, object obj, string pro);
string look_all_inventory_of_room(object me, object env, int ret_str);
string gettof(object me, object obj);
string getdam(object me, object obj);

mapping df_bkpic=([
        "foshan":"xiaozheng",
        "village":"xiaozheng",
        "hangzhou":"hangzhou",
        "heimuya":"heimuya",
        "huashan":"huashan",
        "guanwai":"guanwai",
        "lingjiu":"lingjiu",
        "motianya":"motianya",
        "register":"yanluodian",
        "shenlong":"shenlong",
        "taohua":"taohua",
        "wudang":"wudang",
        "wanjiegu":"wanjiegu",
        "xiakedao":"xiakedao",
        "quanzhen":"quanzhen",
        "beijing":"beijing",
        "changan":"changan",
        "city":"city",
        "city3":"city3",
        "dali":"dali",
        "emei":"emei",
]);

mapping rf_bkpic=([
        "_d_beijing_dangpu":"dangpu",
        "_d_changan_dangpu":"dangpu",
        "_d_city_dangpu":"dangpu",
        "_d_foshan_dangpu":"dangpu",
        "_d_xiangyang_dangpu":"dangpu",
        "_d_suzhou_dangpu":"dangpu",
        "_d_city_shuyuan":"shuyuan",
        "_d_city_shuyuan2":"shuyuan",
        "_d_suzhou_shuyuan":"shuyuan",
        "_d_songshan_shuyuan":"shuyuan",
        "_d_hangzhou_shuyuan":"shuyuan",
        "_d_changan_zahuopu":"zahuopu",
        "_d_fuzhou_zahuopu":"zahuopu",
        "_d_beijing_huichuntang":"yaopu",
        "_d_changan_yaopu":"yaopu",
        "_d_xiangyang_yaopu":"yaopu",
        "_d_suzhou_yaopu":"yaopu",
        "_d_dali_yaoshop":"yaopu",
        "_d_city_zuixianlou":"jiulou",
        "_d_city_shuyuan":"shuyuan",
        "_d_city_shuyuan2":"shuyuan",
        "_d_suzhou_shuyuan":"shuyuan",
        "_d_songshan_shuyuan":"shuyuan",
        "_d_hangzhou_shuyuan":"shuyuan",
        "_d_changan_zahuopu":"zahuopu",
        "_d_fuzhou_zahuopu":"zahuopu",
        "_d_beijing_huichuntang":"yaopu",
        "_d_changan_yaopu":"yaopu",
        "_d_xiangyang_yaopu":"yaopu",
        "_d_suzhou_yaopu":"yaopu",
        "_d_dali_yaoshop":"yaopu",
        "_d_city_zuixianlou":"jiulou",
        "_d_dali_huanggs":"huanggs",
        "_d_emei_jinding":"jingding",
        "_d_death_gate":"guimenguan",
        "_d_changan_bank":"qiangzhuang",
        "_d_beijing_qianzhuang":"qianzhuang",
        "_d_city_qianzhuang":"qianzhuang",
        "_d_changan_bank":"qiangzhuang",
        "_d_beijing_qianzhuang":"qianzhuang",
        "_d_city_qianzhuang":"qianzhuang",
        "_d_emei_jinding":"jingding",
        "_d_dali_huanggs":"huanggs",
        "_d_beijing_dangpu":"dangpu",
        "_d_changan_dangpu":"dangpu",
        "_d_city_dangpu":"dangpu",
        "_d_foshan_dangpu":"dangpu",
        "_d_xiangyang_dangpu":"dangpu",
        "_d_suzhou_dangpu":"dangpu",
]);

string *power_level_desc = ({
        BLU "����һ��" NOR,
        BLU "��������" NOR,
        BLU "����ҳ�" NOR,
        BLU "��ѧէ��" NOR,
        BLU "����ǿǿ" NOR,
        HIB "�����ž�" NOR,
        HIB "����é®" NOR,
        HIB "��֪һ��" NOR,
        HIB "����ͨͨ" NOR,
        HIB "ƽƽ����" NOR,
        CYN "ƽ������" NOR,
        CYN "��ͨƤë" NOR,
        CYN "��������" NOR,
        CYN "������" NOR,
        CYN "����С��" NOR,
        HIC "����С��" NOR,
        HIC "������Ⱥ" NOR,
        HIC "�������" NOR,
        HIC "�������" NOR,
        HIC "�ڻ��ͨ" NOR,
        HIG "�������" NOR,
        HIG "¯����" NOR,
        HIG "��Ȼ����" NOR,
        HIG "���д��" NOR,
        HIG "���д��" NOR,
        YEL "��Ȼ��ͨ" NOR,
        YEL "�������" NOR,
        YEL "�޿�ƥ��" NOR,
        YEL "����Ⱥ��" NOR,
        YEL "����似" NOR,
        HIY "�����뻯" NOR,
        HIY "��ͬ����" NOR,
        HIY "����Ⱥ��" NOR,
        HIY "�Ƿ��켫" NOR,
        HIY "�����ױ�" NOR,
        RED "��������" NOR,
        RED "һ����ʦ" NOR,
        RED "�������" NOR,
        RED "�񹦸���" NOR,
        RED "������˫" NOR,
        WHT "��������" NOR,
        WHT "���춯��" NOR,
        WHT "������" NOR,
        WHT "������ʥ" NOR,
        WHT "�������" NOR,
        HIW "��ǰ����" NOR,
        HIW "���˺�һ" NOR,
        MAG "��ز�¶" NOR,
        HIM "��ɲ�" NOR,
        HIR "��豹���" NOR
});
string *heavy_level_desc= ({
        "����",
        "����",
        "����",
        "����",
        "����",
        "����"
});

string power_level(int power)
{
        int lvl;
        int rawlvl;
        int grade = 1;

        if (power < 0) power = 0;

        rawlvl = (int) pow( (float) 1.0 * power, 0.3);
        lvl = to_int(rawlvl/grade);
        if (lvl >= sizeof(power_level_desc))
                lvl = sizeof(power_level_desc)-1;
        else if (lvl >= sizeof(power_level_desc) - 1)
                lvl = sizeof(power_level_desc) - 2;
        return power_level_desc[((int)lvl)];
}

string gettof(object me, object ob)
{
        object weapon;
        string skill_type;
        mixed attack_points;
        mapping prepare;

        if( objectp(weapon=query_temp("weapon", ob)) )
        {
                skill_type=query("skill_type", weapon);
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
        } else
        {
                string *sk;

                prepare = me->query_skill_prepare();
                if (! prepare) prepare = ([]);
                sk = keys(prepare);

                if (sizeof(sk) == 0) skill_type = "unarmed";
                else skill_type = sk[0];
                attack_points = COMBAT_D->skill_power(ob, skill_type, SKILL_USAGE_ATTACK);
                if (sizeof(prepare) == 2)
                {
                        mixed temp;
                        temp = COMBAT_D->skill_power(ob, sk[1], SKILL_USAGE_ATTACK);

                        if (attack_points < temp)
                                attack_points = temp;
                 }
        }
        return power_level(attack_points/10000);
}

string getdam(object me, object obj)
{
        int level;

        if (objectp(query_temp("weapon", obj)))
                level=query_temp("apply/damage", obj);
        else
                level=query_temp("apply/unarmed_damage", obj);

        level+=query("jiali", obj);
        level = level / 200;
        if( level >= sizeof(heavy_level_desc) )
                level = sizeof(heavy_level_desc)-1;
        if( level < 0 ) level = 0;
        return heavy_level_desc[((int)level)];
}

//add by JackyBoy@XAJH 2001/5/6
string get_bkpic(object env)
{
        string rf, df;

        rf = replace_string(base_name(env),"/","_");
        df = domain_file(rf);
        if (! undefinedp(rf_bkpic[rf]))
                return rf_bkpic[rf];
        if (! undefinedp(df_bkpic[df]))
                return df_bkpic[df];
        return "";
}

int info(object me, object env)
{
        string *dirs;
        string df;
        mapping exits;

        if( mapp(exits=query("exits", env)) )
                dirs = keys(exits);

        if (sizeof(dirs) == 1 && sizeof(dirs) != 0)
                write(TMI("bnway "+dirs[0]+";"));
        else if (sizeof(dirs) != 0)
                write(TMI( sprintf("bnway "+"%s;",implode(dirs[0..sizeof(dirs)], ";")) ));
        df = get_bkpic(env);
        if (df == "") return 1;
        if( df != query_temp("bkpic", me) )
        {
                set_temp("bkpic", df, me);
                write(TMI("bkpic "+df));
        }
        return 1;
}

string locate(string file)
{
        string domain_file;
        string *all_place;
        string the_place;

        if (sscanf(file, "/f/%*s"))
                return "����";

        domain_file = domain_file(file);

        if (! undefinedp(place[domain_file]))
        {
                all_place = place[domain_file][1];
                the_place = place[domain_file][0];
                if (member_array(file, all_place) != -1)
                        return the_place;
        }

        if (! undefinedp(region_names[domain_file]))
                return region_names[domain_file];

        return "δ֪����";
}

mapping dict = ([
        "axe"           :"��",
        "bow"           :"��",
        "sword"         :"��",
        "blade"         :"��",
        "club"          :"��",
        "dagger"        :"ذ��",
        "fork"          :"��",
        "hammer"        :"��",
        "staff"         :"��",
        "throwing"      :"����",
        "whip"          :"��",
        "xsword"        :"��",
        "head"          :"ͷ��",
        "neck"          :"����",
        "cloth"         :"�·�",
        "charm"         :"�����",
        "rings"         :"��ָ",
        "armor"         :"����",
        "surcoat"       :"����",
        "waist"         :"����",
        "wrists"        :"����",
        "shield"        :"�ܼ�",
        "hands"         :"����",
        "boots"         :"ѥ��",
        "finger"        :"ָ��",
        //"0"             :"����",
        "0"             :HIC"��ͨ",
        "1"             :HIC"��ͨ",
        "2"             :HIC"����",
        "3"             :HIM"��ϡ",
        "4"             :HIM"ʷʫ",
        "5"             :HIY"��˵",
        "6"             :HIY"����",
]);

string status_chinese(int status)
{
        if( status == 0 ) return HIK "���ʵ�";
        else if( status == 1 ) return HIK "���ʵ�";
        else if( status == 2 ) return HIB "��ͨ��";
        else if( status == 3 ) return HIR "���µ�";
        else if( status == 4 ) return HIM "׿Խ��";
        else if( status == 5 ) return HIY "��Ͼ��";
        else if( status == 6 ) return HIY "������";
        else return HIY "�񻰵�";
}

string to_chinese(string str)
{
        if (! undefinedp(dict[str]))
                return dict[str];
        else
                return str;
}

void create() { seteuid(getuid()); }

int main(object me, string arg)
{
        object obj;
        object env;
        int result;
        string objid, where;

        if (! arg) result = look_room(me, environment(me), 0);
        else
        {
                if (sscanf(arg, "%s of %s", objid, where) == 2)
                {
                        if (where == "here")
                                obj = present(objid, environment(me));
                        else
                        if (where == "me")
                                obj = present(objid, me);
                        else
                        {
                                env = present(where, environment(me));
                                if (! objectp(env))
                                        return notify_fail("��Ҫ������Ķ�����\n");
                                obj = present(objid, env);
                                if (env->is_character() && env != me)
                                {
                                        if (! objectp(obj) ||
                                            !query("equipped", obj) &&
                                            query_temp("handing", env) != obj )
                                                return notify_fail("���˺���û��©�������뿴�Ķ�������\n");
                                        if( query("env/invisible_item", env) )
                                                return notify_fail("���˾����Ժܸߣ����񲢲������㿴�κζ��������ԡ�\n");
                                        message("vision", me->name() + "�������" + obj->name() +
                                                "����һ�������֪���ڴ�ʲô���⡣\n", env);
                                        message("vision", me->name() + "����" + env->name() + "��" +
                                                obj->name() + "����һ�������֪���ڴ�ʲô���⡣\n",
                                                environment(me), ({ me, env }));
                                }
                        }

                        if (! obj)
                                return notify_fail("����û������������\n");
                }

                if( obj || (obj = present(arg, environment(me))) || (obj = present(arg, me)) )
                {
                        if( obj->is_character() && ! obj->is_corpse()) result = look_living(me, obj);
                        else result = look_item(me, obj);
                } else result = look_room_item(me, arg);
        }

        return result;
}

int look_room(object me, object env, int brief)
{
        int i;
        object room;
        mapping exits;
        string str, ext, *dirs;

        if( !env ) {
                tell_object(me, "������ܻ����ɵ�һƬ��ʲôҲû�С�\n");
                return 1;
        }

        if( !brief )
        {
                str = sprintf( HIC + "%s" + NOR + "%s\n    %s%s" + NOR,
                        env->short(),
                        wizardp(me)?"-"+file_name(env)+sprintf("-(%d,%d,%d)",query("coor/x", env),
                        query("coor/y", env),query("coor/z", env)):
                                     " - (��Ŀǰ��" + HIY + locate(base_name(env)) + NOR + ")",
                        env->long(),
                        query("outdoors", env)?NATURE_D->outdoor_room_description():"");
        } else
        {
                str = sprintf( HIC + "%s" + NOR + "%s\n" + NOR,
                        env->short(),
                        wizardp(me)?"-"+file_name(env)+sprintf("-(%d,%d,%d)",query("coor/x", env),
                        query("coor/y", env),query("coor/z", env)):"");
        }

        ext = "";
        if( mapp(exits=query("exits", env)) )
        {
                dirs = keys(exits);
                for(i=0; i<sizeof(dirs); i++)
                        if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED )
                                dirs[i] = 0;
                dirs -= ({ 0 });
                if (sizeof(dirs) == 0)
                        ext = "    ����û���κ����Եĳ�·��\n";
                else if (sizeof(dirs) == 1)
                        ext = "    ����Ψһ�ĳ����� " + HIY +
                              dirs[0] + NOR + "��\n";
                else
                        ext = sprintf("    �������Եĳ����� " + HIY "%s" + NOR + " �� " + HIY + "%s" + NOR + "��\n",
                              implode(dirs[0..sizeof(dirs)-2], NOR+"��"+HIY), dirs[sizeof(dirs)-1]);
        }

        if (! brief || (intp(brief) && brief > 2 && brief < 4))
                str += ext;

        if( !query_temp("tomud", me))//byLonely
                str += look_all_inventory_of_room(me, env, RETURN_RESULT);
        else
        {
                info(me, env); //By JackyBoy@XAJH 2001/5/6
                str +=CLEAN0+ look_all_inventory_of_room(me, env, RETURN_RESULT);
        }

        if (intp(brief) && brief >= 4)
                str += ext;

        tell_object(me, str);

        // ���²���Ϊ��ʾ��ͼ
        if( query("env/show_map", me) && !me->is_fighting() )
        {
                if( mapp(exits=query("exits", env)) )
                {
                        dirs = keys(exits);
                        for(i=0; i<sizeof(dirs); i++)
                                if ((int)env->query_door(dirs[i], "status") & DOOR_CLOSED)
                                        dirs[i] = 0;
                        dirs -= ({ 0 });
                        if (sizeof(dirs) != 0)
                        {
                        if( query("env/show_map", me) == 2 )
                        write(FRELINE(8, 40));
                        else write(ESC+"[r"+TOBOT(50));
                        write(SAVEC);

                        write(SETDISPLAY(7, 0) + DELLINE);
                        write(SETDISPLAY(1, 0) + DELLINE);
                        write(SETDISPLAY(2, 0) + DELLINE);
                        write(SETDISPLAY(3, 0) + DELLINE);
                        write(SETDISPLAY(4, 0) + DELLINE);
                        write(SETDISPLAY(5, 0) + DELLINE);
                        write(SETDISPLAY(6, 0) + DELLINE);

                        write(SETDISPLAY(4, 70) + HIR + filter_color(query("short", env)) + NOR);
                        for (i=0; i<sizeof(dirs); i++)
                        switch(dirs[i])
                        {
                        case "north":
                                write(SETDISPLAY(3, 72) + "��");
                                room = load_object(exits["north"]);
                                write(SETDISPLAY(2, 70) + filter_color(query("short", room)));
                                break;
                        case "up":
                                write(SETDISPLAY(3, 72) + "��");
                                room = load_object(exits["up"]);
                                write(SETDISPLAY(2, 70) + filter_color(query("short", room)));
                                break;
                        case "down":
                                write(SETDISPLAY(5, 72) + "��");
                                room = load_object(exits["down"]);
                                write(SETDISPLAY(6, 70) + filter_color(query("short", room)));
                                break;
                        case "south":
                                write(SETDISPLAY(5, 72) + "��");
                                room = load_object(exits["south"]);
                                write(SETDISPLAY(6, 70) + filter_color(query("short", room)));
                                break;
                        case "east":
                                room = load_object(exits["east"]);
                                write(SETDISPLAY(4, 80) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 78) + "��");
                                break;
                        case "west":
                                room = load_object(exits["west"]);
                                write(SETDISPLAY(4, 60) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 68) + "��");
                                break;
                        case "westup":
                                room = load_object(exits["westup"]);
                                write(SETDISPLAY(4, 60) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 68) + "��");
                                break;
                        case "eastup":
                                room = load_object(exits["eastup"]);
                                write(SETDISPLAY(4, 80) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 78) + "��");
                                break;
                        case "northup":
                                write(SETDISPLAY(3, 72) + "��");
                                room = load_object(exits["northup"]);
                                write(SETDISPLAY(2, 70) + filter_color(query("short", room)));
                                break;
                        case "southup":
                                write(SETDISPLAY(5, 72) + "��");
                                room = load_object(exits["southup"]);
                                write(SETDISPLAY(6, 70) + filter_color(query("short", room)));
                                break;
                         case "southdown":
                                write(SETDISPLAY(5, 72) + " �� ");
                                room = load_object(exits["southdown"]);
                                write(SETDISPLAY(6, 70) + filter_color(query("short", room)));
                                break;
                        case "northdown":
                                write(SETDISPLAY(3, 72) + " �� ");
                                room = load_object(exits["northdown"]);
                                write(SETDISPLAY(2, 70) + filter_color(query("short", room)));
                                break;
                        case "eastdown":
                                room = load_object(exits["eastdown"]);
                                write(SETDISPLAY(4, 80) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 78) + "��");
                                break;
                        case "westdown":
                                room = load_object(exits["westdown"]);
                                write(SETDISPLAY(4, 60) + filter_color(query("short", room)));
                                write(SETDISPLAY(4, 68) + "��");
                                break;
                        case "northwest":
                                write(SETDISPLAY(3, 68) + "��");
                                room = load_object(exits["northwest"]);
                                write(SETDISPLAY(2, 60) + filter_color(query("short", room)));
                                break;
                        case "southwest":
                                write(SETDISPLAY(5, 68) + "��");
                                room = load_object(exits["southwest"]);
                                write(SETDISPLAY(6, 60) + filter_color(query("short", room)));
                                break;
                        case "northeast":
                                write(SETDISPLAY(3, 76) + "��");
                                room = load_object(exits["northeast"]);
                                write(SETDISPLAY(2, 80) + filter_color(query("short", room)));
                                break;
                        case "southeast":
                                write(SETDISPLAY(5, 76) + "��");
                                room = load_object(exits["southeast"]);
                                write(SETDISPLAY(6, 80) + filter_color(query("short", room)));
                                break;
                        }

                        write(SETDISPLAY(1, 58) + "��������������������������������");
                        write(SETDISPLAY(2, 58) + "��");
                        write(SETDISPLAY(3, 58) + "��");
                        write(SETDISPLAY(4, 58) + "��");
                        write(SETDISPLAY(5, 58) + "��");
                        write(SETDISPLAY(6, 58) + "��");
                        write(SETDISPLAY(7, 58) + "��������������������������������");
                        write(SETDISPLAY(2, 88) + "��");
                        write(SETDISPLAY(3, 88) + "��");
                        write(SETDISPLAY(4, 88) + "��");
                        write(SETDISPLAY(5, 88) + "��");
                        write(SETDISPLAY(6, 88) + "��");

                        write(REST);
                        }
                write(TOBOT(50));
                }
        }

        //MYGIFT_D->check_mygift(me, "newbie_mygift/look");   
        return 1;
}

string desc_of_objects(object *obs)
{
        int i;

        string  str;
        mapping count;
        mapping unit;
        string  short_name;
        string  *dk;

        if (obs && sizeof(obs) > 0)
        {
                str = "";
                count   = ([]);
                unit    = ([]);

                for (i = 0; i < sizeof(obs); i++)
                {
                        short_name = obs[i]->short();
                        if (undefinedp(count[short_name]))
                        {
                                count += ([ short_name : 1 ]);
                                unit += ([ short_name : query("unit", obs[i]) ]);
                        }
                        else
                                count[short_name] += 1;
                }

                dk = sort_array(keys(count), 1);
                for (i = 0; i < sizeof(dk); i++)
                {
                        str += "  ";
                        if (count[dk[i]] > 1)
                                str += chinese_number(count[dk[i]]) + unit[dk[i]];
                        str += dk[i] + "\n";
                }
                return str;
        }

        return "";
}

string look_all_inventory_of_room(object me, object env, int ret_str)
{
        object *inv;
        object *obs;
        object ob;
        string  str;

        if (! env || ! me) return "";

        str = "";

        inv = all_inventory(env);
        if (! sizeof(inv)) return str;

        if( query_temp("tomud", me) )
        {
                foreach(ob in inv)
                if (ob != me && me->visible(ob))
                        str += ADD0(ob); //By JackyBoy@XAJH 2001/5/6
        }

        if( !query("env/brief", me) || (intp(query("env/brief", me)) &&
            query("env/brief", me)>1) )
        {
                obs = filter_array(inv, (: $(me) != $1 && userp($1) && $(me)->visible($1) :));
                str += desc_of_objects(obs);

                obs = filter_array(inv, (: $(me) != $1 && ! userp($1) && $1->is_character() &&
                                           $(me)->visible($1) :));
                str += desc_of_objects(obs);

                obs = filter_array(inv, (: ! $1->is_character() :), me);
                str += desc_of_objects(obs);
        }
        if (! ret_str)
                tell_object(me, str);

        return str;
}

int look_item(object me, object obj)
{
        object hob;
        mixed *inv;
        mapping count;
        mapping equiped;
        mapping unit;
        mapping insert;
        string ins;
        string short_name;

        string str, desc;
        string *dk;
        mapping enchase_prop, applied_prop = ([]);
        mapping in_data;
        string in_desc = "";
        string *ikey;
        string *apply, *apply1, *apply2, *apply3;
        int i, f;
        int n, t;

        count   = ([]);
        unit    = ([]);
        equiped = ([]);
        enchase_prop = ([]);
        applied_prop = ([]);
        apply = ({});
        apply1 = ({});
        apply2 = ({});
        apply3 = ({});

        str = obj->long();
        str += "\n";
        if( query("no_identify", obj) )
        {
                str += HIW "----------------------------------------\n" NOR;
                str += HIK "����Ʒδ����\n" NOR;
                str += HIW "----------------------------------------\n" NOR;
        } else
        if (mapp(query("weapon_prop", obj)) ||
            mapp(query("armor_prop", obj)) )
        {
                if( query("skill_type", obj) ) {
                        applied_prop = copy(query("weapon_prop", obj));
                        str += HIW "װ������ : ���� - " + to_chinese(query("skill_type", obj)) +"\n" NOR;
                }
                else if( query("armor_type", obj) ) {
                        applied_prop = copy(query("armor_prop", obj));
                        if( query("armor_type", obj) == "rings" || query("armor_type", obj) == "neck" ||
                            query("armor_type", obj) == "charm" )
                                str += HIW "װ������ : ��Ʒ - " + to_chinese(query("armor_type", obj)) +"\n" NOR;
                        else if( query("armor_type", obj) == "hands" || query("armor_type", obj) == "finger" )
                                str += HIW "װ������ : �������� - " + to_chinese(query("armor_type", obj)) +"\n" NOR;
                        else
                                str += HIW "װ������ : ���� - " + to_chinese(query("armor_type", obj)) +"\n" NOR;
                }
                
                str += HIW "װ��Ʒ�� : " + status_chinese(query("status", obj)) +"\n" NOR;
                //str += HIW "ϡ �� �� : " + to_chinese(to_string(query("quality_level", obj))) +"\n" NOR;
                str += HIW "������ : ";
                if( intp(t=query("bindable", obj))){
                        if( t == 1 )      str += "װ�����";
                        else if( t == 2 ) str += "ʰȡ��ﶨ";
                        else if( t == 3 ) str += "ֱ�ӵ����";
                        else              str += "�ް�����";
                }
                if( query("bind_owner", obj) )
                        str += HIM "���Ѱ󶨣�\n" NOR;
                else
                        str += HIK "���ް󶨣�\n" NOR;

                if( query("require/level", obj) ) str += HIW "װ��Ҫ�� : �ȼ� Lv." + query("require/level", obj) + "\n" NOR;
                if( query("require/int", obj) ) str += HIW "װ��Ҫ�� : ���� " + query("require/int", obj) + "\n" NOR;
                if( query("require/str", obj) ) str += HIW "װ��Ҫ�� : ���� " + query("require/str", obj) + "\n" NOR;
                if( query("require/con", obj) ) str += HIW "װ��Ҫ�� : ���� " + query("require/con", obj) + "\n" NOR;
                if( query("require/dex", obj) ) str += HIW "װ��Ҫ�� : ���� " + query("require/dex", obj) + "\n" NOR;

                t = query("max_consistence", obj);
                if( !t ) t = 100;
                str += HIW "�� �� ֵ : " + query("consistence", obj)+"/"+ t + "\n" NOR;
                str += "\n";
                insert=query("insert", obj);
                if( mapp(insert) && sizeof(insert) )
                {
                        ikey = keys(insert);
                        n = sizeof(ikey);
                        str += sprintf(HIW "��Ƕ��ʯ : %d/%d\n" NOR, (int)query("enchase/used", obj), (int)query("enchase/flute", obj));
                        for( i = 0; i < n; i++ )
                        {
                                ins = ikey[i];
                                if( !obj->is_item_make() )
                                {
                                        in_data = copy(insert[ins]["apply_prop"]);
                                        in_desc = "";
                                        foreach( string key in keys(in_data) )
                                                in_desc += HIK + filter_color(EQUIPMENT_D->chinese(key, in_data[key]),1) + NOR+",";

                                        in_desc = in_desc[0..<2];
                                }
                                str += sprintf(HIK "��" NOR "%s(%s)<%s>\n" NOR,
                                        insert[ins]["name"], insert[ins]["id"], obj->is_item_make() ? "":in_desc);
                        }
                        str += "\n";
                }
                /*
                if (mapp(query("enchase/apply_prop", obj))) {
                        enchase_prop = copy(query("enchase/apply_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                if (! sizeof(applied_prop) || undefinedp(applied_prop[apply3[i]]))
                                        applied_prop[apply3[i]] = enchase_prop[apply3[i]];
                                else
                                        applied_prop[apply3[i]] += enchase_prop[apply3[i]];
                        }
                }
                if (mapp(query("reform/apply_prop", obj))) {
                        enchase_prop = copy(query("reform/apply_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                if (! sizeof(applied_prop) || undefinedp(applied_prop[apply3[i]]))
                                        applied_prop[apply3[i]] = enchase_prop[apply3[i]];
                                else
                                        applied_prop[apply3[i]] += enchase_prop[apply3[i]];
                        }
                }
                */
                if (mapp(applied_prop) && sizeof(applied_prop) > 0) {
                        apply = keys(applied_prop);
                        for (i = 0; i<sizeof(apply); i++)
                        {
                                f = applied_prop[apply[i]];
                                if( !f ) continue;
                                str += HBCYN "װ��Ч��" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply[i], f);
                                desc = HIC + desc + NOR;
                                str += desc + "\n";
                        }
                }
                if (mapp(query("enchase/apply_prop", obj))) {
                        enchase_prop = copy(query("enchase/apply_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                f = enchase_prop[apply3[i]];
                                if( !f ) continue;
                                str += HBBLU "װ��Ч��" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply3[i], f);
                                desc = HIB + desc + NOR;
                                str += desc + "\n";

                        }
                }
                if (mapp(query("reform/apply_prop", obj))) {
                        enchase_prop = copy(query("reform/apply_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                f = enchase_prop[apply3[i]];
                                if( !f ) continue;
                                str += HBMAG "װ��Ч��" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply3[i], f);
                                desc = HIM + desc + NOR;
                                str += desc + "\n";

                        }
                }
                if (mapp(query("enchase/rune_prop", obj))) { // ��������
                        enchase_prop = copy(query("enchase/rune_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                f = enchase_prop[apply3[i]];
                                if( !f ) continue;
                                str += HBRED "װ��Ч��" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply3[i], f);
                                desc = HIR + desc + NOR;
                                str += desc + "\n";

                        }
                }
                if (mapp(query("qianghua/apply_prop", obj))) {
                        enchase_prop = copy(query("qianghua/apply_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                f = enchase_prop[apply3[i]];
                                if( !f ) continue;
                                str += HBYEL "װ��Ч��" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply3[i], f);
                                desc = HIY + desc + NOR;
                                str += desc + "\n";

                        }
                }
                if (mapp(query("enchase/mod_prop", obj))) {
                        enchase_prop = copy(query("enchase/mod_prop", obj));
                        apply3 = keys(enchase_prop);
                        for (i = 0; i<sizeof(apply3); i++)
                        {
                                f = enchase_prop[apply3[i]];
                                if( !f ) continue;
                                str += HBGRN "��װЧ��" NOR " : ";
                                desc = EQUIPMENT_D->chinese(apply3[i], f);
                                desc = (query_temp("mod_active", obj) ? HIG : HIK) + desc + NOR;
                                str += desc + "\n";

                        }
                }
                str += "\n";
                if (stringp(query("mod_level", obj)))
                        // str = column_string(filter_color(str, 1), MODULE_D->module_stats(obj, me), 64);
                        str = column_string(sort_string(str, 56, 0), MODULE_D->module_stats(obj, me), 60);
        }

        while (mapp(query_temp("daub", obj)))
        {
                if( !query_temp("daub/poison/remain", obj) )
                        // no poison remain now
                        break;

                if( query_temp("daub/poison/id", obj) == query("id", me) )
                {
                        str += HIG "�㷢�������滹�������Ƶ�" +
                               query_temp("daub/poison/name", obj)+
                               HIG "�ء�\n" NOR;
                        break;
                }

                if( query_temp("daub/who_id", obj) == query("id", me) )
                {
                        str += HIG "�����滹�������ֲ��µ�" +
                               query_temp("daub/poison/name", obj)+
                               HIG "�ء�\n" NOR;
                        break;
                }

                if (random(4) && random((int)me->query_skill("poison", 1)) < 30)
                        // nothing was worked out
                        break;

                str += HIG "��Ȼ���㷢�������ƺ�����һЩ����ӫ��";
                if (me->query_skill("poison", 1) >= 120)
                {
                        str+="��������"+query_temp("daub/poison/name", obj);
                }

                str += "��\n" NOR;
                break;
        }

        /*if (query("consistence", obj))
                str += sprintf("�;�ֵ��" WHT "%d\n" NOR, query("consistence", obj));*/

        inv = all_inventory(obj);
        if (! sizeof(inv))
        {
                message("vision", str, me);
                return 1;
        }

        if (obj->is_corpse())
        {
                if( objectp(hob=query_temp("handing", obj)) )
                {
                        if (hob->query_amount())
                                str += "���л���������һ" + query("base_unit", hob) +
                                       hob->name() + "��";
                        else
                                str += "���л���������һ" + query("unit", hob) +
                                       hob->name() + "��";
                        inv -= ({ hob });
                        if (! sizeof(inv))
                                str += "û��ʲô���������ˡ�\n";
                        else
                                str += "����������У�\n";
                } else
                        str += "����������У�\n";
        } else
                str += "�����У�\n";

        for (i = 0; i < sizeof(inv); i++)
        {
                short_name = inv[i]->short();
                if (undefinedp(count[short_name]))
                {
                        count += ([ short_name : 1 ]);
                        unit += ([ short_name : query("unit", inv[i]) ]);
                }
                else
                        count[short_name] += 1;

                if( query("equipped", inv[i]) )
                        equiped[short_name] = 1;
        }

        dk = keys(count);
        dk = sort_array(dk, 1);
        for (i = 0; i < sizeof(dk); i++)
        {
                if (equiped[dk[i]])
                {
                        if( dk[i] == query_temp("secondary_weapon", obj) )
                                str += HIM "  ��" NOR;
                        else
                                str += HIC "  ��" NOR;
                }
                else
                        str += "    ";

                if (count[dk[i]] > 1)
                        str += chinese_number(count[dk[i]]) + unit[dk[i]];
                str += dk[i] + "\n";
        }

        if (strlen(str) > 4096)
                me->start_more(str);
        else
                message("vision", str, me);
        return 1;
}

string look_equiped(object me, object obj, string pro)
{
        mixed *inv;
        string str;
        string subs;
        object hob;
        int i;
        int n;

        inv = all_inventory(obj);
        n = 0;

        str = "";
        subs = "";
        for (i = 0; i < sizeof(inv); i++)
        {
                switch(query("equipped", inv[i]) )
                {
                case "wielded":
                        n++;
                        if( inv[i] == query_temp("secondary_weapon", obj) )
                                subs = HIM "  ��" NOR + inv[i]->short() + "\n" + subs;
                        else
                                subs = HIC "  ��" NOR + inv[i]->short() + "\n" + subs;
                        break;

                case "worn":
                        n++;
                        subs += HIC "  ��" NOR + inv[i]->short() + "\n";
                        break;

                default:
                        break;
                }
        }

        if (n)
                str += pro + "װ���ţ�\n" + subs;

        if( objectp(hob=query_temp("handing", obj)) &&
            (me == obj || obj->query_weight() > 200))
        {
                int mad;

                // dress nothing but handing a cloth !
                mad = (! objectp(query_temp("armor/cloth", obj)) &&
                       query("armor_type", hob) == "cloth");

                str = pro + "����" + (mad ? "ȴ" : "" ) + "����һ" +
                      (hob->query_amount() ? query("base_unit", hob)
                                           : query("unit", hob)) +
                      hob->name() +
                      (mad ? "�����ˣ�һ���Ƿ��ˣ�\n" : "��\n") + str;
        }

        if (playerp(obj) &&
            ! objectp(query_temp("armor/cloth", obj)))
        {
                str = pro + "����û�д��·�����\n" + str;
        }

        return str;
}

string description(object obj)
{
        if (playerp(obj))
        {
            int per;
            int age;
            per = obj->query_per();
            age=query("age", obj);
            if( query("special_skill/youth", obj) ) age = 14;
            if ((string)query("gender", obj) == "����" || (string)query("gender", obj) == "����")
            {
                    if (per >= 30) return "�������������ٷ磬�������Σ�����֮�䣬��ɷ���������������\n";
                    if (per >= 26) return "Ӣ������������������������棬��Ŀ���ʣ�ò���˰���\n";
                    if (per >= 22) return "��òӢ�����Ǳ����á��Ǹ����棬���˷��ס�\n";
                    if (per >= 18) return "��ٶ�����\n";
                    if (per >= 15) return "��òƽƽ��ûʲô�ÿ��ġ�\n";
                                   return "����... �е�Բ�ס���ˡ�\n";
            } else
            {
                    if (per >= 30) return "��������֮ò����ɫ���������޾��ף������˼����ӣ�\n�������ƣ�����ʤѩ���绪��������֪�㵹�˶���Ӣ�ۺ��ܡ�\n";
                    if (per >= 28) return "�������ף����˶��ˡ��г�������֮�ݣ������߻�֮ò��\n������������Ŀ���飬������ɣ�����һЦ������������Ȼ�Ķ���\n";
                    if (per >= 26) return "������֬��üĿ�续���������֣��������ˡ��������Ҽ�������\n";
                    if (per >= 24) return "��ɫ����������κ죬�ۺ��ﲨ������Ͷ��֮�䣬ȷ��һ�����ϡ�\n";
                    if (per >= 21) return "���ʸ��ţ���Ŀ毺ã����㲻�Ͼ������ˣ�Ҳ���м�����ɫ��\n";
                    if (per >= 18) return "��òƽƽ�������ù�ȥ��\n";
                    if (per >= 15) return "����ò��... �������ɡ�\n";
                                   return "���ú������е�����Ү��\n";
            }
        } else
        if( !query("can_speak", obj) && living(obj) )
        {
                if( !query_temp("owner", obj) )
                        return "��һֻδ��ѱ�����������۹������ǽ��ĺ͵��⡣\n";
                else
                        return "��һֻ��"+query_temp("owner_name", obj)+
                               "ѱ����������һ������ѱ�����ӡ�\n";
        }

        return "";
}

int look_living(object me, object obj)
{
        int per;
        int age;
        string str="", pro, desc,icon;
        mapping my_fam, fam;
        int me_shen, obj_shen;
        mixed tmp;

        if( (tmp=query("icon", obj)) )
        {
                if( intp(tmp) )
                {
                        icon = sprintf("%d",tmp);
                        str=L_ICON(icon);
                }
                else if( stringp(tmp) )
                {
                        icon = tmp;
                        str=L_ICON(icon);
                }
        }
        obj_shen=query("shen", obj);
        per = obj->query_per();
        age=query("age", obj);
        pro = (obj==me) ? gender_self(query("gender", obj)) : gender_pronoun(query("gender", obj));

        me_shen=query("shen", me);
        if (me != obj)
        {
                message("vision", me->name() + "�������㿴����֪���ڴ�ʲô���⡣\n", obj);
                message("vision", me->name() + "����" + obj->name() +
                        "����һ�������֪���ڴ�ʲô���⡣\n",
                        environment(me), ({ me, obj }));
        }

        str += obj->long();
        if (me != obj && objectp(query_temp("is_riding", obj)))
                str += sprintf("%s������%s�ϣ���ͷ�����㡣\n", pro, query_temp("is_riding", obj)->name());

        // if (me != obj && objectp(query_temp("is_changing", obj)))
        if (objectp(query_temp("is_changing", obj)))
        {
                if( query_temp("armor/beast", obj) )
                        str += sprintf("%sȫ��������ħ����(%s)ϸ����֯�����ţ���ȫ����Ž�ɫ�����Ƶġ�\n", pro,
                                query_temp("is_changing", obj)->name());
                else
                        str += sprintf("%s�����ֱ�������ħ����(%s)�����ĺۼ���\n", pro,
                                query_temp("is_changing", obj)->name());
        }

        if (obj->is_character() &&
            query("can_speak", obj) )
        {
                int charlevel;
                charlevel=query("level", obj)?query("level", obj):1;
                str += pro + "��һλ" + chinese_number(charlevel) + "����" + query("gender", obj) + "��ʿ��\n";
                // �������ɫ
                if (age >= 25 && query("special_skill/youth", obj))
                        str += pro + "��������͵Ĵ�С������ֻ�ж�ʮ���ꡣ\n";
                else
                {
                        if (age >= 200)
                                str += pro + "��������ͺܴ��ˣ����Թ��ơ�\n";
                        else
                        if (age < 10)
                                str += pro + "������������ס�\n";
                        else
                                str += pro + "��������" + chinese_number(age / 10 * 10) +
                                       "���ꡣ\n";
                }
                str += sprintf("%s���书����", pro);
                str += gettof(me, obj);
                str += sprintf("��");
                str += sprintf("�����ƺ�");
                str += getdam(me, obj);
                str += sprintf("��\n");
        }

        desc = description(obj);
        if (desc && desc != "")
                str += pro + desc;

        //check about wife and husband
        if( query("id", obj) == query("couple/id", me) )
        {
                // ���޹�ϵ
                if( query("gender", me) == "Ů��" )
                        str += sprintf("%s������ķ����\n", pro);
                else
                        str += sprintf("%s����������ӡ�\n", pro);
        } else
        if (obj->is_brother(me))
        {
                // �ֵ�
                if( query("gender", obj) == "Ů��" )
                {
                        if( query("mud_age", obj) > query("mud_age", me) )
                                str += sprintf("%s�������㡣\n", pro);
                        else
                                str += sprintf("%s����Ľ������ӡ�\n", pro);
                } else
                {
                        if (query("mud_age", obj) > query("mud_age", me))
                                str += sprintf("%s����Ľ����ֳ���\n", pro);
                        else
                                str += sprintf("%s�������ܡ�\n", pro);
                }
        } else
        if (obj != me && query("league", obj) &&
            query("league/league_name", obj) == query("league/league_name", me) )
        {
                str += sprintf("%s�������%s��ͬ����ʿ��\n", pro,
                               query("league/league_name", obj));
        }

        if (obj != me && query("bunch", obj) && stringp(query("bunch/bunch_name", obj)) &&
            query("bunch/bunch_name", obj) == query("bunch/bunch_name", me) )
        {
                str += sprintf("%s�������%s�İ��ѣ�%s�ڰ��е�ְλΪ%s��", pro,
                               query("bunch/bunch_name", obj),pro,
                               stringp(query("bunch/title", obj)) ? query("bunch/title", obj) : "����");
                if( query("bunch/level", obj)>query("bunch/level", me) )
                        str += "��λ����ߡ�\n";
                else
                if( query("bunch/level", obj) == query("bunch/level", me) )
                        str += "��λ�����൱��\n";
                else
                        str += "��λ����͡�\n";
        } else
        if (obj != me && query("bunch", obj) && stringp(query("bunch/bunch_name", obj)) &&
            query("bunch/bunch_name", obj) != query("bunch/bunch_name", me) )
        {
                str += sprintf("%s�ǽ�����%s��%s��\n", pro,
                               query("bunch/bunch_name", obj),
                               stringp(query("bunch/title", obj)) ? query("bunch/title", obj) : "����");
        }

        // If we both has family, check if we have any relations.
        if (obj != me &&
            mapp(fam=query("family", obj)) &&
            mapp(my_fam=query("family", me)) &&
            fam["family_name"] == my_fam["family_name"])
        {

                if (fam["generation"] == my_fam["generation"])
                {

                        if( query("gender", obj) == "����" ||
                                query("gender", obj) == "����" )
                                str += sprintf( pro + "�����%s%s��\n",
                                        my_fam["master_id"] == fam["master_id"]? "": "ͬ��",
                                        my_fam["enter_time"] > fam["enter_time"] ? "ʦ��": "ʦ��");
                        else
                                str += sprintf( pro + "�����%s%s��\n",
                                        my_fam["master_id"] == fam["master_id"]? "": "ͬ��",
                                        my_fam["enter_time"] > fam["enter_time"] ? "ʦ��": "ʦ��");
                } else
                if (fam["generation"] < my_fam["generation"])
                {
                        if( my_fam["master_id"] == query("id", obj) )
                                str += pro + "�����ʦ����\n";
                        else
                        if (my_fam["generation"] - fam["generation"] > 1)
                                str += pro + "�����ͬ�ų�����\n";
                        else
                        if (fam["enter_time"] < my_fam["enter_time"])
                                str += pro + "�����ʦ����\n";
                        else
                                str += pro + "�����ʦ�塣\n";
                } else
                {
                        if (fam["generation"] - my_fam["generation"] > 1)
                                str += pro + "�����ͬ������\n";
                        else
                        if( fam["master_id"] == query("id", me) )
                                str += pro + "����ĵ��ӡ�\n";
                        else
                                str += pro + "�����ʦֶ��\n";
                }
        }

        if (obj->is_chatter())
        {
                message("vision", str, me);
                return 1;
        }

        if (stringp(query_temp("eff_status_msg", obj)))
        {
                str+=query_temp("eff_status_msg", obj)+"\n";
        } else
        if( query("max_qi", obj) )
                str += pro + COMBAT_D->eff_status_msg((int)query("eff_qi", obj)* 100 / (int)query("max_qi", obj)) + "\n";

        if( query_temp("daub/poison/remain", obj) &&
            (me == obj || random((int)me->query_skill("poison", 1)) > 80))
        {
                str += pro + HIG "��������" + (me == obj ? "" : "�ƺ�") +
                       "����" + (me == obj ? query_temp("daub/poison/name", obj) : "��") +
                       NOR "��\n";
        }

        str += look_equiped(me, obj, pro);
        message("vision", str, me);

        if (obj != me && living(obj) &&
            ! me->is_brother(obj) &&
            query("couple/id", me) != query("id", obj) &&
            (((me_shen < 0) && (obj_shen > 0)) ||
             ((me_shen > 0) && (obj_shen < 0))) &&
            (((me_shen-obj_shen)>(query("max_neili", obj)*20)) ||
             ((obj_shen-me_shen)>(query("max_neili", obj)*20))) )
        {
                tell_object(me, obj->name() + "ͻȻת��ͷ������һ�ۡ�\n");
                /*
                if( query("age", obj)>15 && query("age", me)>15 )
                   if (! wizardp(obj) && ! wizardp(me))
                        COMBAT_D->auto_fight(obj, me, "berserk");
                */
        }

        return 1;
}

int look_room_item(object me, string arg)
{
        object env;
        mapping item, exits;

        if (! objectp(env = environment(me)))
                return notify_fail("����ֻ�л����ɵ�һƬ��ʲôҲû�С�\n");
        if( mapp(item=query("item_desc", env)) && !undefinedp(item[arg]) )
        {
                if (stringp(item[arg]))
                        tell_object(me, item[arg]);
                else
                if(functionp(item[arg]))
                        tell_object(me, (string)(*item[arg])(me));

                return 1;
        }
        if( mapp(exits=query("exits", env)) && !undefinedp(exits[arg]) )
        {
                if (objectp(env = find_object(exits[arg])))
                        look_room(me, env, 0);
                else
                {
                        call_other(exits[arg], "???");
                        if( !find_object(exits[arg]) ) return notify_fail("�Ǳ��ǿռ��ѷ죬�޷������۲졣\n");
                        look_room(me, find_object(exits[arg]), 0);
                }
                return 1;
        }
        return notify_fail("��Ҫ��ʲô��\n");
}

int help(object me)
{
        write(@HELP
ָ���ʽ: look [<��Ʒ>|<����>|<����>]

���ָ������鿴�����ڵĻ�����ĳ����Ʒ��������Ƿ������
��lookָ������в��������Ȳ쿴�����Ƿ��и���Ʒ�����û�����
�������ڵĻ������Ƿ��и���Ʒ�������������ϵ���Ʒ��������
�Ļ�����ID��ͬ����Ʒ�������ָ��look ??? of me/here ��ָ����
��Ҫ�쿴�Լ����ϵ���Ʒ���Ǹ��������е���Ʒ��ͬʱ�����ʹ����
�� look ??? of <id> ���Կ����˵�װ����������������Ʒ��

HELP
);
        return 1;
}
