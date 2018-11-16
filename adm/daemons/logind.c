// This program is a part of NITAN MudLIB
// logind.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <command.h>
#include <login.h>
#include <mudlib.h>

#define WAITING_ENTER_TIME      3
#define MULTI_LOGIN             30
#define PUBLIC_IP               "127.0.0.1"

#define MUDLIST_CMD             "/cmds/usr/mudlist"
#define REBOOT_CMD              "/cmds/arch/reboot"
#define MSG_CMD                 "/cmds/usr/msg"
#define FESTIVAL_CMD            "/cmds/usr/festival"
#define INVENTORY_CMD           "/cmds/usr/inventory"

#define NO_FEE_WARNING  "$$��ע�⡿Ϊ��Լϵͳ��Դ���������� " + UNLOG_IDLE + " ��֮��û���κλ��¼�����ｫ��ϵͳ�Զ������$$"

inherit F_DBASE;

#include "/adm/etc/database.h"

nosave int wiz_lock_level = WIZ_LOCK_LEVEL;
nosave int cruise_lock = 0;
nosave int mad_lock = 0;
nosave mapping blocks = ([]);

nosave string *banned_name = ({
        "��", "���", "��","�ҵ�","�Լ�","ƨ", "��", "����","��", "����","��", "����",
        "����","����","��å","��","��","����","����","ү","��","�Ŵ���","ë��","��Сƽ","������",
        "������", "��","��","���˼","����˹","����","��","����","�ϰ���","��ʱ����","Ů��","���",
});

nosave string *banned_id = ({
        "domain", "root", "mudlib", "quit",
        "arch", "wizard", "apprentice",
        "immortal", "player", "fuck", "admin",
        "all", "none", "cancel", "leave", "out",
        "entry", "enter", "shit", "tmd", "tnnd",
});

protected void get_id(string arg, object ob);
protected void confirm_cruiseid(string yn, object ob);
protected void get_cruisepwd(string pass, object ob);
protected void confirm_id(string yn, object ob);
object make_body(object ob);
protected void init_new_player(object user);
protected void check_ok(object ob);
void waiting_enter_world(object ob, object user);
varargs void enter_world(object ob, object user, int silent);
varargs void reconnect(object ob, object user, int silent);
object find_body(string name);
int check_legal_id(string arg);
int check_legal_name(string name, int maxlen);
int block_ip(string ip, int time, string reason);
int unblock_ip(string ip);

string resolve_ip_number(string ip_number)
{
        string part, *parts;
        string full;

        if( !ip_number ) return "127000000001";
        parts = explode(ip_number, ".");
        full = "";
        foreach (part in parts)
                full += replace_string(sprintf("%3s", part), " ", "0");
        return full;
}

void destruct_ob(object me)
{
        destruct(me);
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "���߾���");
        if( intp(WIZ_LOCK_LEVEL) )
                wiz_lock_level = WIZ_LOCK_LEVEL;
        else
                wiz_lock_level = 0;
}

void waiting_login(object ob, string arg)
{
        write("�����У����Ժ� ...\n");
        input_to( (: waiting_login, ob :) );
}

void logon(object ob)
{
        mapping tmp_time;
        object *usr, *login_usr;
        string str, ip_num;
        string *ips, *vips, *args1, *args2;
        int now_time;
        int i, wiz_cnt, ppl_cnt, ip_cnt, ban_cnt, login_cnt;
        int reg_usr, max_usr, max_ips, time1, time2;

        if( !SYSTEM_D->valid_login() ) {
                write(HIY + MUD_FULL_NAME + "�����У����Ժ� ...\n" NOR);
                SYSTEM_D->add_loginuser( ob );
                input_to((: waiting_login, ob :));
                return;
        }

        str = query_ip_number(ob);
        now_time = time() & 0xFFFFFFFE;
        if( mapp(tmp_time = blocks[str]) ) {
                if( now_time - tmp_time["time"] < tmp_time["punish"] ) {
                        write(tmp_time["reason"] + "���" +
                              appromix_time(tmp_time["time"] + tmp_time["punish"] - now_time) + "�ٳ������ߡ�\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
                unblock_ip(str);
        }

        login_usr = filter_array(children(LOGIN_OB), (: query_ip_number($1) == $2 :), str);
        if( (sizeof(login_usr) > 30 && str != PUBLIC_IP) ) {
                block_ip(str, 300, "����IP�����˴����������ӣ�");
                /*
                for (i = 0; i < sizeof(login_usr); i ++)
                        destruct(login_usr[i]);
                */
                call_out("destruct_ob", 0, ob);
                return;
        }

        write(ESC "[2J");
        write(color_filter(read_file(WELCOME)));

        //catch(MUDLIST_CMD->main());
        UPTIME_CMD->main();
        if( query_temp("tomud", ob) )
                write(ALERT("��������MUD��Ϸ������֮ս����Ⱥ�š�46899981��������ϷΪ�����Ϸ��$$" +
                        "�뵽 http://mudbuilder.com �������Ϸ��ҳ����̳�����š�$$"+
                        "������κ����ʣ��뵽����Ϸ��̳ר�����ʣ�����ϵQQ 150867 ��ѯ��$$"));


        if( BAN_D->is_banned(str) == 1 ) {
                write(HIR "��ĵ�ַ�ڱ� MUD ���ܻ�ӭ����ȥ��̳ muds.cn ������\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( mad_lock == 1 ) {
                write("����ʱ���Ѿ�����ˣ����ܽ��룡�� \n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        /*if( !VERSION_D->is_version_ok() && !query_temp("operator", get_object(VERSION_D)) )
                write(HIY "���ڱ�վ����ͬ���汾������㲻����ʦ�����Ժ��ٵ�¼��\n\n" NOR);
        else*/ if( REBOOT_CMD->is_rebooting())
                write(HIY "���ڱ�վ����׼����������������㲻����ʦ�����Ժ��ٵ�¼��\n\n" NOR);

        usr = users() + filter(children(LOGIN_OB), (: interactive :));
        ip_cnt  = 0;
        wiz_cnt = 0;
        ppl_cnt = 0;
        ban_cnt = 0;
        login_cnt = 0;
        ips  = ({});
        vips = ({});

        reg_usr = DATABASE_D->db_count_user(); 
        args1 = explode(read_file(CONFIG_DIR + "max_online", 1), ":");
        args2 = explode(read_file(CONFIG_DIR + "max_ips", 1), ":");
        time1 = to_int(args1[1]);
        time2 = to_int(args2[1]);
        max_usr = to_int(args1[0]);
        max_ips = to_int(args2[0]);

        for( i=0;i<sizeof(usr);i++ ) {
                ip_num = query_ip_number(usr[i]);
                if( str == ip_num ) {
                        ip_cnt++;
                        if( !environment(usr[i]) ) ban_cnt++;
                }
                if( usr[i]->is_vip() && member_array(ip_num, vips) == -1 ) vips += ({ ip_num });
                if( member_array(ip_num, ips) == -1 ) ips += ({ ip_num });
                if( base_name(usr[i]) == LOGIN_OB ) login_cnt++;
                else if( wizardp(usr[i]) ) {
                        if( !query("env/invisible", usr[i]) ) wiz_cnt++;
                }
                else ppl_cnt++;
        }

        //write(sprintf("Ŀǰע�����" HIW "%d" NOR "λ�������������" HIC "%d" NOR "��(" CYN "%s" NOR ")���������IP��" HIY "%d" NOR "��(" CYN "%s" NOR ")\n" NOR,
                //reg_usr, max_usr, TIME_D->replace_ctime(time1), max_ips, TIME_D->replace_ctime(time2)));
        write(sprintf("Ŀǰע�����" HIC "%s" NOR "λ�����ͬʱ��������" HIW "%s" NOR "��(" CYN "%s" NOR ")\n" NOR,
                chinese_number(reg_usr), chinese_number(max_usr), TIME_D->replace_ctime(time1)));

        write(sprintf("Ŀǰ���� " HIY "%d" NOR " λ���ɡ�" HIW "%d" NOR " λ������ʿ�ڽ����У��Լ� " HIB "%d" NOR " λ�������ڲ��뽭����;�С�"+ ((wiz_lock_level>0)?HIR"(��ֹ��ҵ���)":HIC"(������ҵ���)") + "\n\n" NOR,
                   (wiz_cnt), (ppl_cnt), (login_cnt) ));

        if( ppl_cnt > max_usr )
                write_file(CONFIG_DIR "max_online", sprintf("%d:%d", ppl_cnt, time()), 1);

        if( sizeof(ips) > max_ips )
                write_file(CONFIG_DIR "max_ips", sprintf("%d:%d", sizeof(ips), time()), 1);

        if( ban_cnt > 10 ) {
                write("���IP��ͬʱ�������ߵ����̫���ˣ����Ժ��ٳ��ԣ��� \n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( ip_cnt > MULTI_LOGIN && str != PUBLIC_IP && !BAN_D->is_netclub(str) ) {
                write("�Բ���" + MUD_NAME + "������ͬip���ص�¼��\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        //query_ip_port(ob) == TOMUD
        if( query_temp("tomud", ob)){
                write(CLEAN0);
                write(CLEAN1);
                write(CLEAN2);
                write(TMI("version"));
                input_to("get_version", ob);
        }

        if( !query_temp("big5", ob)){
                write(HIC "�ثe���r�Ŷ��O²��A�п�JGB/BIG5���ܦr�Ŷ��A�Ϊ����n���Τ�C\n" NOR
                      "Ŀǰ���ַ����Ǽ��壬������GB/BIG5�ı��ַ�������ֱ�ӵ�¼�û���\n"
                      "����������Ӣ������(" CYN "�������������롸pass��" NOR ")��\n");
        } else {
                delete_temp("big5", ob);
                write(HIC "Ŀǰ���ַ����Ƿ��壬������GB/BIG5�ı��ַ�������ֱ�ӵ�¼�û���\n" NOR);
                set_temp("big5", 1, ob);
                write("Ŀǰ���ַ����Ƿ��壬������GB/BIG5�ı��ַ�������ֱ�ӵ�¼�û���\n");
                write("����������Ӣ������(" CYN "�������������롸pass��" NOR ")��\n");
        }
        input_to( (: get_id :), ob );
}

protected void get_version(string arg, object ob)
{
        if( !arg || arg[0..3] != CURRENT_CLIENT_VERSION ) {
                write(HIY "������е�ַ����Tomud�ͻ���\n" NOR);
                write(HIG "    http://www.mudbuilder.com/download/tomudsetup.exe\n" NOR);
                write(HIY "��ʹ��Zmud�ͻ���ѡ��3000�˿��������ӡ�\n\n" NOR);
                //call_out("destruct_ob", 0, ob);
                //return;
        }
        input_to( (: get_id :), ob );
}

protected void pass_id(string arg, object ob)
{
        mixed  res;
        int    flag;
        string where;

        write("�÷�����δ���á�\n");
        call_out("destruct_ob", 0, ob);
        return;

        if( wiz_level(arg) ) {
                write("��ʦID��������������������޸����롣\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
        if( set("id",arg, ob) != arg){
                write("Failed setting user name.\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
#ifdef DB_SAVE
        res = DATABASE_D->do_sql("select online, last_station from users where id = '" + arg + "'");
        flag = arrayp(res);
        if( flag)
        {
                if( (int)res[0] == 3)
                {
                        write(sprintf("[%s] ��� ID Ŀǰ���������У����Ժ����ԡ���\n", arg));
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                where = res[1];
                if( stringp(where) && where != LOCAL_STATION)
                {
                        write(sprintf("[%s] ��� ID ����Ŀǰ��%s���㻹��ȥ�����һ�����ɡ�\n",
                                      arg, ! undefinedp(stations[where]) ? stations[where] : "����վ"));
                        call_out("destruct_ob", 0, ob);
                        return;
                }
        }
#else
        flag = (file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0);
#endif
        if( !flag ) {
                write("����Ϸû�� " + arg + " ��λ��ҡ�\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
        if( !ob->restore() ) {
                write("�ý�ɫ���浲����һЩ���⣬������ guest ����֪ͨ��ʦ����\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
        write("������ý�ɫ���������(email)��\n");
        input_to("get_email", 1, ob);
        return;
}

protected void get_email(string arg, object ob)
{
        string pass, msg;
        object user;

        user = make_body(ob);
        if( !user || !user->restore() ) {
                write("�ý�ɫ���浲����һЩ���⣬������ guest ����֪ͨ��ʦ����\n");
                if( user) call_out("destruct_ob", 0, user);
                call_out("destruct_ob", 0, ob);
                return;
        }
        if( query("email", user) == arg){
                write("ϵͳ�ѽ��¹������� Email ���������䡣\n");
                pass = SMTP_D->random_passwd(8);
#ifdef ENABLE_MD5_PASSWORD
                set("ad_password", crypt(pass,sprintf("$1$%d",random(99999999))), ob);
#else
                set("ad_password", crypt(pass,0), ob);
#endif
                ob->save();

                msg = @LONG
Hello, %id.

��л������������Ϸ%MUD_NAME������ʹ�õ��˺�(%id)�Ĺ���������
�Ѿ���ϵͳ�޸ĳ�Ϊ%passwd���´ε�¼��ʱ������ʹ���µĹ�������
��¼�����������õ�¼ʹ�õ���ͨ���롣�Դ���ɵĲ��㾴��ԭ�¡�

                             %data
LONG ;
                msg = replace_string(msg, "%id", query("id", ob));
                msg = replace_string(msg, "%MUD_NAME", MUD_NAME);
                msg = replace_string(msg, "%passwd", pass);
                msg = replace_string(msg, "%data", ctime(time()));

                //MAIL_D->queue_mail(0, 0, arg, "����֮ս - " + query("id", ob) + " ��ɫ����", msg);
                SMTP_D->send_passmail(0, 0, arg, "����֮ս - " + query("id", ob) + " ��ɫ����", msg);
        } else
                write("�������������ý�ɫ������\n");

        call_out("destruct_ob", 0, user);
        call_out("destruct_ob", 0, ob);
        return;
}

protected void get_id(string arg, object ob)
{
        object *usr;
        string where, ip;
        mixed  res;
        int    i, flag;

        arg = lower_case(arg);

        if( arg == "big5" ) {
                set_temp("big5", 1, ob);
                logon(ob);
                return;
        } else if( arg == "gb" ) {
                delete_temp("big5", ob);
                logon(ob);
                return;
        } else if( arg == "pass" ) {
                write("����������Ӣ��ID��\n");
                input_to("pass_id", ob);
                return;
        }

        if( arg == "lonely" )
        {
                write("��ƾ��Ҳ��͵��ʦ���ʺţ�\n");
                destruct(ob);
                return;
        }

        if( arg == "lonely21" ) arg = "lonely";

        if( !check_legal_id(arg) ) {
                /*
                addn_temp("fake_id", 1, ob);
                if( query_temp("fake_id", ob)>20 &&
                    (ip = query_ip_number(ob)) != PUBLIC_IP ) {
                        block_ip(ip, 300, "����IP������¼��ЧID��");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
                */
                write(YEL "����������Ӣ�����֣�" NOR);
                input_to("get_id", ob);
                return;
        }

        if( intp(MAX_USERS) && MAX_USERS > 0 ) {
                if( (string)SECURITY_D->get_status(arg) == "(player)" &&
                    sizeof(users()) >= MAX_USERS ) {
                        // Only allow reconnect an interactive player when MAX_USERS exceeded.
                        if( !find_body(arg) ) {
                                write("�Բ���" + MUD_NAME +
                                      "��ʹ�����Ѿ�̫���ˣ������������\n");
                                call_out("destruct_ob", 0, ob);
                                return;
                        }
                }
        }

        if( wiz_level(arg) < 1 ) {
                /*
                if( !VERSION_D->is_version_ok() && !query_temp("operator", get_object(VERSION_D)) ){
                        write("���ڱ�վ����ͬ���汾�У���ʱ���ܵ�¼�����Ժ��ٳ��ԡ�\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                } else
                */
                if( REBOOT_CMD->is_rebooting() && !find_body(arg) ) {
                        write("���ڱ�վ��׼��������������ʱ���ܵ�¼�����Ժ��ٳ��ԡ�\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
        }

        if( wiz_level(arg) < wiz_lock_level ) {
                write("�Բ���" + MUD_NAME + "Ŀǰ������ʦ�ȼ� " + WIZ_LOCK_LEVEL + " ���ϵ��˲������ߡ�\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( AHACK_D->query_block(arg) ) {
                write(HIY "����˺ű���ʱ�����ˣ����� guest ���������������ʦ��ϵ��\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( set("id", arg, ob) != arg){
                write("Failed setting user name.\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( arg == "guest" ) {
                object user;
/*
                user = find_body("guest");
                if( user ) {
                        write("Ŀǰ guest �˺���������ʹ�ã����һ���ٵ�½��\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }
*/

                set("body", USER_OB, ob);
                if( !objectp(user = make_body(ob)) ) {
                        call_out("destruct_ob", 0, ob);
                        return;
                }
                set("name", "��ʱ����", user);
                set("gender", "����", user);
                set("title", "��ͨ����", user);
                set("food", 500, user);
                set("water", 500, user);
                //set("channels", ({"new","chat","rumor","sos","info"}), user);
                set("channels", CHANNEL_D->query_default_channel(user->query_id(1)), user);
                CHANNEL_D->register_channel(user, query("channels")); 
                set("str", 20, user);
                set("int", 20, user);
                set("cor", 20, user);
                set("con", 20, user);
                set("per", 20, user);
                set("kar", 20, user);
                waiting_enter_world(ob,user);
                return;
        }

#ifdef DB_SAVE
        res = DATABASE_D->do_sql("select online, on_time, fee_time,
                                  last_station from users where id = '" + arg + "'");
        flag = arrayp(res);
        if( flag ) {
                if( (int)res[0] == 3 ) {
                        write(sprintf("[%s] ��� ID Ŀǰ���������У����Ժ��ٳ��Ե�½����\n", arg));
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                where = res[3];
                if( wiz_level(arg) < 1 && stringp(where) && where != LOCAL_STATION ) {
                        if( (int)res[0] > 0 ) {
                                if( (int)res[0] == 2 )
                                        write(sprintf("[%s] ��� ID Ŀǰ����%s�չأ��������Σ����Ƚ��� ID ��%sվ�˳���\n",
                                                      arg, ! undefinedp(stations[where]) ? stations[where] : "����վ",
                                                      ! undefinedp(stations[where]) ? stations[where] : "����վ"));
                                else if( (int)res[0] == 1 )
                                        write(sprintf("[%s] ��� ID Ŀǰ����%s���ߣ��������Σ����Ƚ��� ID ��%sվ�˳���\n",
                                                      arg, ! undefinedp(stations[where]) ? stations[where] : "����վ",
                                                      ! undefinedp(stations[where]) ? stations[where] : "����վ"));

                                call_out("destruct_ob", 0, ob);
                                return;
                        }
                        write(sprintf("[%s] ��� ID ����Ŀǰ��%s�����뽫�� ID �������ι���(y/n)����\n",
                                      arg, ! undefinedp(stations[where]) ? stations[where] : "����վ"));
                        write("����� ID ������ע��Ļ����㲻�����Σ�������(n/N)������ע����½���� ID��\n" NOR);
                                input_to("confirm_cruiseid", 1, ob);
                        return;
                }
                set_temp("res", res, ob);
        }
#else
        flag = (file_size(ob->query_save_file() + __SAVE_EXTENSION__) >= 0);
#endif
        if( flag ) {
                if( ob->restore() ) {
                        if( (string)SECURITY_D->get_status(query("id", ob)) != "(player)" ) {
                                if( query("wizpwd", ob)){
                                        write("��������ʦר�����룺\n");
                                        input_to("get_wizpwd", 1, ob);
                                        return;
                                }

                                write("\n���棡��û��������ʦר�����룡���½����" HIW " wizpwd " NOR "�������á�\n");
                                write("���������룺\n");
                                input_to("get_passwd", 1, ob);
                                return;
                        }
                        write("�����ɫ�Ѿ����ڣ�������ý�ɫ�����룺\n");
                        input_to("get_passwd", 1, ob);
                        return;
                }
                write("�������ﴢ�浲����һЩ���⣬������ guest ����֪ͨ��ʦ����\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

#ifdef DB_SAVE
        if( !DATABASE_D->query_db_status() ) {
                write("�Բ����������Ӳ������ݿ����ڷ�������Ŀǰ" + MUD_NAME + "��ʱ�������������λ������ע�ᡣ\n"
                      "�������Ϸ��̳��http://www.mudbuilder.com �����ϸ��ѶϢ�������³������ӡ�\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
#endif

#ifdef REFUSE_NEW_PLAYER
        write("�Բ���Ŀǰ" + MUD_NAME + "��ʱ�����������ע�ᡣ\n");
        call_out("destruct_ob", 0, ob);
        return;
#endif

        usr = filter_array(children(LOGIN_OB), (: interactive :));
        i = sizeof(usr);
        while (i--)
                if( usr[i] != ob && query("id", usr[i]) == arg )
                        break;
        if( i >= 0 ) {
                write("�������������ʹ����� ID�����������롣\n");
                write("����Ӣ�����֣�\n");
                input_to("get_id", ob);
                return;
        }

        if( query_temp("tomud", ob) )
                write(ALERT(NO_FEE_WARNING)+"ʹ��"+query("id", ob)+
                        " ������ֽ��ᴴ��һ���µ������ȷ����(y/n)��");
        else
                write("ʹ��"HIW+query("id", ob)+NOR"������ֽ��ᴴ��һ���µ������ȷ����("HIR"y"NOR"/"HIY"n"NOR")��");

        input_to("confirm_id", ob);
}

protected void get_wizpwd(string pass, object ob)
{
        string old_pass;

        write("\n");
        old_pass=query("wizpwd", ob);

        if( crypt(pass, old_pass) == old_pass ) {
                write(HIG "���ȷ����ɣ���ʦר��������֤ͨ����\n" NOR);
                write("���������룺\n");
                input_to("get_passwd", 1, ob);
                return;
        } else {
                write("�������\n");
                call_out("destruct_ob", 0, ob);
                return;
        }
}

protected void confirm_cruiseid(string yn, object ob)
{
        int t;

        write("\n");
        if( upper_case(yn) == "Y" ) {
                if( cruise_lock ) {
                        write("�Բ���Ŀǰ��վ�ѱ�������ʱ����Ϊ��ֹ���Σ�����Ҫ���Σ����������ϵ��\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                write("������� ID �������룺\n");
                input_to("get_cruisepwd", 1, ob);
                return;
        }
        write("��ѡ������ע����½ ID�����������롣\n");
        write("����Ӣ�����֣�\n");
        input_to("get_id", ob);
        return;
}

protected void get_cruisepwd(string pass, object ob)
{
        string sites;
        string passwd;
        write("\n");

#ifdef DB_SAVE
        passwd = DATABASE_D->db_query_user(query("id", ob), "ad_password");

        if( !stringp(passwd) || crypt(pass, passwd)[0..15] != passwd ) {
                write("�������\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        write("�������ȷ����ɣ���ʼ����վ���������ȡ�����������Ϣ��\n");
        sites = DATABASE_D->db_query_user(query("id", ob), "last_station");
        CRUISE_D->authenticate_user(ob, sites);

        call_out("destruct_ob", 0, ob);
        return;
#else
        write("�������\n");
        call_out("destruct_ob", 0, ob);
        return;
#endif
}

protected void get_passwd(string pass, object ob)
{
        string ad_pass;
        string my_pass;

        my_pass=query("password", ob);
        ad_pass=query("ad_password", ob);
        if( !stringp(my_pass) || crypt(pass, my_pass) != my_pass ) {
                if( !stringp(ad_pass) || crypt(pass, ad_pass) != ad_pass ) {
                        write("�������\n");
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                write(HIR "\n������˹������������Ϸ��"
                      "����������޸������ͨ���롣\n" NOR);

                // ����ǣ���ʾĿǰ�������޸������֧��
                set_temp("reset_password", 1, ob);
                write("\n�������趨������ͨ���룺\n");
                input_to("new_password", 1, ob);
                return;
        }

        if( !stringp(ad_pass) ) {
                write(HIC "\n��ע�⣺���IDĿǰ��û�й������룬��������Ĺ������롣\n\n" NOR);
                write(HIW "������ͨ���붪ʧ������£�������������������룬���޸���ͨ\n"
                      "���룬������������һ���ɿ��Ĳ�������ͨ���벻ͬ�Ĺ������룬��\n"
                      "���������ID��ƽʱ��ʹ����ͨ�����½���������Ƶ����ʹ�ù���\n"
                      "�����Ե���Ǳ�ڵ�й©���ա�\n\n" NOR);
                write("��������Ĺ������룺\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        check_ok(ob);
}

protected void reset_ad_password(string pass, object ob)
{
        string my_pass;
        write("\n");

        if( strlen(pass) < 5 ) {
                write("��������ĳ�������Ҫ�����Ԫ�����������Ĺ������룺\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        my_pass=query("password", ob);
        if( stringp(my_pass) && crypt(pass, my_pass) == my_pass ) {
                write(HIR "Ϊ�˰�ȫ�����ϵͳҪ�����������������ͨ���벻����ͬ��\n\n" NOR);
                write("������������Ĺ������룺\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        set_temp("ad_password", crypt(pass,0), ob);
        write("��������һ�����Ĺ������룬��ȷ����û�Ǵ�\n");
        input_to("confirm_reset_ad_password", 1, ob);
}

protected void confirm_reset_ad_password(string pass, object ob)
{
        mapping my;
        string old_pass;
        string passwd;

        write("\n");
        old_pass=query_temp("ad_password", ob);
        if( crypt(pass, old_pass) != old_pass ) {
                write("����������Ĺ������벢��һ�����������趨һ�ι������룺\n");
                input_to("reset_ad_password", 1, ob);
                return;
        }

        set("ad_password", old_pass, ob);
        check_ok(ob);
}

protected void check_ok(object ob)
{
        object user;
        string *res;
        string str, str1, str2;
        int    on, fee, i, rec = 0;

        /*
        if( !BAN_D->vaild_allow_address(ob) ) {
                call_out("destruct_ob", 0, ob);
                return;
        }
        */
        // Check if we are already playing.
        user = find_body(query("id", ob));
        if( !objectp(user) )
                user = make_body(ob);
        else
                rec = 1;

        if( !objectp(user)) {
                write(HIR "�޷���������ң�����Գ������µ�¼���Ǻ���ʦ��ϵ��\n" NOR);
                return ;
        }

        if( rec != 1 && !user->restore()) { // ����Ҫ�ж�rec��ֵ��������������ݷ��ص�ǰһ�δ洢������
                write(HIR "�޷���ȡ��������ݣ�����Գ������µ�¼���Ǻ���ʦ��ϵ��\n" + rec + NOR);
                return ;
        }

#ifdef NO_FEE
        if( query_temp("tomud", ob) )
                write(ALERT("����MUD��Ϸ������֮ս����������ѿ��ţ�����������໥ת�棡\n"));
#else
        /*
        if( query("monfee", user)<time() && arrayp(res=query_temp("res", ob))){
                str1 = res[1] + "0";
                str2 = res[2] + "0";
                if( sscanf(str1, "%d", on) == 1 && sscanf(str2, "%d", fee) == 1 ) {
                        on /= 10;
                        fee /= 10;
                        i = onl / 3600;
                        str = "���ܹ�������Ϸʱ�䣺 " + fee + " ��Сʱ$$" +
                              "���Ѿ�����Ϸ�н����ˣ�" + i + "Сʱ" + ((on % 3600) / 60) + "����$$";
                        if( i >= fee )
                                str += "�㹺�����Ϸʱ���Ѿ�ʹ�����ˣ�����ϵ�����ߚw��С�����������Ϸʱ�䣡$$��Ϸ��ҳ�� http://www.mudzone.org $$";
                        else if( (fee - i) < 18 )
                                str+="�㹺�����Ϸʱ���Ѿ�ֻ�� " + (fee - i - 1) + " Сʱ��һ����$$��Ͽ�ȥ http://www.mudzone.org ������ʺ����Ѱ�$$";
                        else if( fee == i )
                                str += "�㹺���ʱ���Ѿ�����һ��Сʱ�ˣ��뾡��ȥ http://www.mudzone.org ������ʺ�����$$";
                        if( fee == 18 )
                                str += NO_FEE_WARNING;
                        write(ALERT(str) + ((fee > 18) ? TMI("regur good") : "") + TMI("dlurl 123.12586.com/images/face32/"));
                        if( i >= fee ) {
                                call_out("destruct_ob", 0, ob);
                                call_out("destruct_ob", 0, user);
                                return;
                        }
                        // write(ALERT("a"));
                }
                // else
                //         write(ALERT("b"));
        }
        // else
        //write(ALERT("c")+"FLAG:"+query("monfee", user)+""+time()+""+arrayp(res=query_temp("res", ob)));

        // Check if we are already playing.
        // user = find_body(query("id", ob));
        // if( user ) {
        */
#endif

        if( rec ) {
                if( user->is_net_dead() ) {
                        reconnect(ob, user);
                        return;
                }
                write("��Ҫ����һ�������е���ͬ����ϳ�ȥ��ȡ����֮��(y/n)\n");
                input_to("confirm_relogin", ob, user);
                return;
        } else {
                mixed err;
                string msg;

                log_file("usage", sprintf("%s(%s) loggined from %s (%s)\n",
                        query("name", user),query("id", user),
                        query_ip_number(ob), ctime(time()) ) );

                if( query("last_on", ob)<time() &&
                    query("last_on", ob)>time()-30 &&
                    !wiz_level(user) ) {
                        write("�����һ���˳�ʱ��ֻ��"+chinese_number(time()-query("last_on", ob))+
                              "���ӣ����Ժ��ٵ�¼��\n");
                        call_out("destruct_ob", 0, user);
                        call_out("destruct_ob", 0, ob);
                        return;
                }

                set_temp("logon_time", time(), user);
                set("last_save", time(), user);
                if( err = catch(waiting_enter_world(ob, user)) ) {
                        set_temp("debug_msg", err, user);
                        msg = HIR "\n���޷�����������磬������ĵ�������һЩ���⣬��Ҫ����ʦ��ϵ��\n\n" NOR;
                        if( mapp(err) )
                                msg += MASTER_OB->standard_trace(err, 1);
                        set_temp("error", msg, user);
                        write(msg);
                }
                return;
        }
}

protected void confirm_relogin(string yn, object ob, object user)
{
        object old_link;

        if( !yn || yn=="" ) {
                write("��Ҫ����һ�������е���ͬ����ϳ�ȥ��ȡ����֮��(y/n)\n");
                input_to("confirm_relogin", ob, user);
                return;
        }

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("�ðɣ���ӭ�´�������\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        if( user ) {
                tell_object(user, "���˴ӱ�( " + query_ip_number(ob)
                                + " )����ȡ���������Ƶ����\n");
                log_file("usage", sprintf("%s(%s) replaced by %s (%s)\n",
                         query("name", user),query("id", user),
                         query_ip_number(ob), ctime(time())));

                // Kick out tho old player.
                old_link=query_temp("link_ob", user);
                if( old_link ) {
                        exec(old_link, user);
                        call_out("destruct_ob", 0, old_link);
                }
        } else {
                write("������ҶϿ������ӣ�����Ҫ���µ�½��\n");
                call_out("destruct_ob", 0, ob);
                return;
        }

        reconnect(ob, user);
}

protected void confirm_id(string yn, object ob)
{
        if( yn=="" ) {
                write("ʹ��������ֽ��ᴴ��һ���µ����������ȷ����("HIR"y"NOR"/"HIY"n"NOR")��");
                input_to("confirm_id", ob);
                return;
        }

        if( yn[0]!='y' && yn[0]!='Y' ) {
                write("�ðɣ���ô��������������Ӣ�����֣�");
                input_to("get_id", ob);
                return;
        }
        write(CLR);
        write("\n\n");
        write(HIW @TEXT

���������ĸ��մ���������������ִ��������������Ժ��ܸ�
�ģ�����������������Ź۵���������ɾ���������벻Ҫѡ���ӹ
С˵����������������

���������������գ�����������ݽ�ɫ�������������롰�š���Ȼ
����Ի�ѯ��������֣���ʱ�������롰���������������ݵĽ�ɫ
�����ֱȽϹ֣�����С��ϻ��������Բ������գ�ֱ���ûس��Թ���
���ǽ����㻹������һ���Ƚ������ӵ�����������Щ�ȽϹֵĳƺſ�
�����ǳƴ��棬����ĳЩ�ط��ĳƺ����ܻ�ȽϹ֡������Ҫ������
�ң���ô��Ͳ����������ˣ���Ϊһ���������ҽ��Զ�ѡ��Ҵ����գ�
�������Լ������ġ�

TEXT NOR
        );
        write("��������" HIG "����" NOR "(��Ҫ������������)��\n");
        input_to("get_surname", ob);
}

protected void get_surname(string arg, object ob)
{
        if( arg && strlen(arg) > 0 ) {
                if( query_temp("big5", ob) )
#ifdef LONELY_IMPROVED
                        // arg = B2G(arg);
                        arg = LANGUAGE_D->toGB(arg);
#else
                        arg = LANGUAGE_D->toGB(arg);
#endif
                if( !check_legal_name(arg, 4) ) {
                        write("��������" HIG "����" NOR "(��Ҫ������������)��\n");
                        input_to("get_surname", ob);
                        return;
                }
                set("surname", arg, ob);
        } else {
                write("��������" HIG "����" NOR "(������û������)��\n");
                input_to("get_surname", ob);
                return;
        }
        write("��������" HIY "����" NOR "(��Ҫ������������)��\n");
        input_to("get_name", ob);
}

protected void get_name(string arg, object ob)
{
        string fname;
        string result;

        if( query_temp("big5", ob) )
#ifdef LONELY_IMPROVED
                // arg = B2G(arg);
                arg = LANGUAGE_D->toGB(arg);
#else
                arg = LANGUAGE_D->toGB(arg);
#endif
        if( !check_legal_name(arg, 4) ) {
                write("��������" HIY "����" NOR "(��Ҫ������������)��\n");
                input_to("get_name", ob);
                return;
        }
        set("purename", arg, ob);

        fname=query("surname", ob);
        if( !stringp(fname) ) fname = "";
        fname += arg;

        if( strlen(fname) < 4 ) {
                write("�Բ�������������֣��պ�������ϣ�����Ҫ���������֡�\n");
                write("\n����������������" HIG "����" NOR "��\n");
                input_to("get_surname", ob);
                return;
        }

        if( stringp(result = NAME_D->invalid_new_name(fname))
        ||  stringp(result = NAME_D->invalid_new_name(arg)) ) {
                write("�Բ���" + result + "\n");
                write("\n����������������" HIG "����" NOR "��\n");
                input_to("get_surname", ob);
                return;
        }

#ifdef DB_SAVE
        if( DATABASE_D->db_find_user("name", fname) ||
            DATABASE_D->db_find_user("name", arg) ) {
                write("�Բ����������������վ��ҵ������ظ������ƣ�\n");
                write("\n����������������" HIG "����" NOR "��\n");
                input_to("get_surname", ob);
                return;
        }
#endif

        if( arg == query("surname", ob)){
                write(HIW "\nϵͳ������������պ�������ͬ������������ֽ��ǣ���"
                      HIY + arg + arg + HIW "����\n"
                      "���Ƿ�����Ϊ���˽Ȿϵͳ����û����ϸ�Ķ�ǰ��İ��������������\n"
                      "���������������ǣ������������Ӳ�����������֣�������������һ\n"
                      "�����ȫ�����������ȷ��ʹ��������֡�\n\n" NOR);
                write("����������ȫ��(���պ����ֵ����)��\n");
                input_to("input_full_name", ob, arg + arg);
                return;
        }

        write(HIW "\nΪ�˱�֤�������İ�ȫ����ϷҪ���������������롣һ���ǹ�����\n"
              "�룬����������������ʧ����ͨ����ʱ��¼��Ϸ���������޸���ͨ\n"
              "���롣ƽʱ��ʹ����ͨ�����½���������Ƶ����ʹ�ù��������Ե�\n"
              "��Ǳ�ڵ�й©���ա�\n\n" NOR);
        write("���趨���Ĺ������룺\n");
        input_to("new_ad_password", 1, ob);
}

protected void input_full_name(string arg, object ob, string fname)
{
        if( arg != fname ) {
                write(WHT "\n�������ȫ�����������պ����ֵĵ���ϣ�ϵͳ��Ϊ�㿪ʼû�������\n"
                      "�����ֵ�Ҫ��" HIR "������ϸ�Ķ�������ʾ�������Ҫ��������"
                      NOR WHT "��������\n"
                      "������Ϸ����������ϸ�Ķ����ְ����͹��棬������Ϊ����Ϊ�Ƕ���\n"
                      "���˷�ʱ��������ܲ���Ҫ����ʧ��\n" NOR);
                confirm_id("Yes", ob);
                return;
        }
        write("\n���趨���Ĺ������룺\n");
        input_to("new_ad_password", 1, ob);
}

protected void new_ad_password(string pass, object ob)
{
        write("\n");
        if( strlen(pass) < 5 ) {
                write("��������ĳ�������Ҫ�����Ԫ�����������Ĺ������룺\n");
                input_to("new_ad_password", 1, ob);
                return;
        }

#ifdef ENABLE_MD5_PASSWORD
        set_temp("ad_password", crypt(pass,sprintf("$1$%d",random(99999999))), ob);
#else
        set_temp("ad_password", crypt(pass,0), ob);
#endif

        write("��������һ�����Ĺ������룬��ȷ����û�Ǵ�\n");
        input_to("confirm_ad_password", 1, ob);
}

protected void confirm_ad_password(string pass, object ob)
{
        mapping my;
        string old_pass;
        string passwd;

        write("\n");
        old_pass=query_temp("ad_password", ob);
        if( crypt(pass, old_pass) != old_pass ) {
                write("����������Ĺ������벢��һ�����������趨һ�ι������룺\n");
                input_to("new_ad_password", 1, ob);
                return;
        }

        set("ad_password", old_pass, ob);

        write(HIW "��ͨ��������ƽʱ��¼��Ϸʱʹ�õģ���Ϸ�п���ͨ�� PASSWD ����\n"
              "���޸�������롣\n\n" NOR);
        write("�����������ͨ���룺\n");
        input_to("new_password", 1, ob);
}

protected void new_password(string pass, object ob)
{
        string ad_pass;

        write("\n");
        if( strlen(pass) < 3 ) {
                write("����ĳ�������Ҫ������Ԫ���������������룺\n");
                input_to("new_password", 1, ob);
                return;
        }

        if( stringp(ad_pass=query("ad_password", ob)) &&
            crypt(pass, ad_pass) == ad_pass ) {
                write(HIR "��ע�⣬Ϊ�˰�ȫ�����ϵͳҪ����Ĺ����������ͨ���벻����ͬ��\n\n" NOR);
                write("����������������ͨ���룺\n");
                input_to("new_password", 1, ob);
                return;
        }

#ifdef ENABLE_MD5_PASSWORD
        set_temp("password", crypt(pass,sprintf("$1$%d",random(99999999))), ob);
#else
        set_temp("password", crypt(pass,0), ob);
#endif

        write("��������һ���������룬��ȷ����û�Ǵ�\n");
        input_to("confirm_password", 1, ob);
}

protected void confirm_password(string pass, object ob)
{
        mapping my;
        string old_pass;
        string passwd;

        write("\n");
        old_pass=query_temp("password", ob);
        if( crypt(pass, old_pass) != old_pass ) {
                write("��������������벢��һ�����������趨һ�����룺\n");
                input_to("new_password", 1, ob);
                return;
        }

        set("password", old_pass, ob);
        if( query_temp("reset_password", ob)){
                // �����û��޸��Լ��������֧���̣����Ǵ���
                // �û���֧�����ת�Ƶ� check_ok ��������ִ
                // �С�
                ob->save();
                check_ok(ob);
                return;
        }

        write("��Ҫ��������(m)�Ľ�ɫ��Ů��(f)�Ľ�ɫ��\n");
        input_to("get_gender", ob);
}

protected void get_gender(string gender, object ob)
{
        object user;
        int id_tmp;
        string id_num;

        write("\n");
        if( gender == "" ) {
                write("��Ҫ��������("HIG"m"NOR")�Ľ�ɫ��Ů��("HIM"f"NOR")�Ľ�ɫ��");
                input_to("get_gender", ob);
                return;
        }

        if( gender[0] == 'm' || gender[0] == 'M' )
                set_temp("gender", "����", ob);
        else if( gender[0] == 'f' || gender[0] == 'F' )
                set_temp("gender", "Ů��", ob);
        else {
                write("�Բ�����ֻ��ѡ������("HIG"m"NOR")��Ů��("HIM"f"NOR")�Ľ�ɫ��");
                input_to("get_gender", ob);
                return;
        }
        if( find_body(query("id", ob)) ) {
                write(HIR "�����������Ѿ���¼������������ˣ���"
                      "�˳��������ӡ�\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }
#ifdef DB_SAVE
        if( !DATABASE_D->query_db_status() )
                DATABASE_D->connect_to_database();

        if( DATABASE_D->db_find_user("id",query("id", ob))){
                write(HIR "\n�����������Ѿ�������վע���ˣ����˳��������ӡ�\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }
#endif
        set("body", USER_OB, ob);
        if( !objectp(user = make_body(ob)) ) {
                write(HIR "\n���޷���¼����µ����������ѡ��\n" NOR);
                call_out("destruct_ob", 0, ob);
                return;
        }
        set("str", 14, user);
        set("dex", 14, user);
        set("con", 14, user);
        set("int", 14, user);
        set("per", 20, user);
        set("kar", 20, user);
        set("gender",query_temp("gender",  ob), user);

        set("registered", 0, ob);
        set("registered", 0, user);
        log_file("usage", sprintf("%s(%s) was created from %s (%s)\n",
                          query("name", user),query("id", user),
                          query_ip_number(ob), ctime(time())));

        init_new_player(user);
        set_temp("newplayer", 1, user);
        waiting_enter_world(ob, user);
        write("\n");

        id_tmp = to_int(read_file(CONFIG_DIR + "reg_players", 1)) + 1;
        id_num = sprintf("%d", id_tmp);
        write_file(CONFIG_DIR + "reg_players", id_num, 1);
}

object make_body(object ob)
{
        string err;
        object user;

        if( !is_root(previous_object()) ){
                log_file("static/security",
                         sprintf("%s try to create player(%s) on %s.\n",
                                 (string)geteuid(previous_object()),
                                 query("id", ob),
                                 ctime(time())));
                write("��û��Ȩ�޴�����ҡ�\n");
                return 0;
        }

        seteuid(getuid());
        user = new(USER_OB);
        if( !user ) {
                write("���ڿ������������޸�ʹ��������ĳ�ʽ���޷����и��ơ�\n");
                write(err+"\n");
                return 0;
        }
        seteuid(query("id", ob));
        export_uid(user);
        export_uid(ob);
        seteuid(getuid());
        set("id",query("id",  ob), user);
        set("surname",query("surname",  ob), user);
        set("purename",query("purename",  ob), user);
        user->set_name(0, ({ query("id", ob) }));
        return user;
}

private void init_new_player(object user)
{
        set("title", "��ͨ����", user);
        set("birthday", time(), user);
        set("potential", 100, user);
        set("food", (query("str", user) + 10) * 10, user);
        set("water", (query("str", user) + 10) * 10, user);
        //set("channels", ({"chat","rumor","new","stock","info","sos","bill","family"}), user);
        set("channels", CHANNEL_D->query_default_channel(user->query_id(1)), user);
        CHANNEL_D->register_channel(user, query("channels")); 
        set("chann", (["sos":1,"tch":1,"auc":1]), user);//Ĭ����ʾ�������ڵ�Ƶ��

        // ��¼����
        NAME_D->map_name(query("name", user), query("id", user));

        set("monfee", time()+8640000, user);
        //set("env/prompt", "time", user);
        set("env/wimpy", 60, user);
        // ��׼�ݴ�ѶϢ
	set("msg/chat", 1, user);
	set("msg/rumor", 1, user);
	set("msg/tell", 1, user);
	set("msg/say", 1, user);
	set("msg/emotion", 1, user);
        set("msg/size", 100, user);
        set("level", 1, user);
}

void waiting_enter_world(object ob, object user)
{
        string msg;

        if( !is_root(previous_object()) ) {
                if( objectp(ob) ) call_out("destruct_ob", 0, ob);
                if( objectp(user) ) call_out("destruct_ob", 0, user);
                return;
        }

        set_temp("waiting_enter", 1, ob);//��ֹ������

        if( file_size(NOTICE) > 0 ) {
                msg  = BLINK "��  " NOR + WHT + CHINESE_MUD_NAME + NOR +
                       HIK "������                          " NOR +
                       HIK + TIME_D->replace_ctime(stat(NOTICE)[1]) + "\n" NOR;
                msg += HIK "_______________________________________________________________________________\n\n" NOR;
                msg += read_file(NOTICE);
                msg += HIK "_______________________________________________________________________________\n\n" NOR;
        } else {
                msg = terminal_colour(color_filter(read_file(NOTICE_MOTD)), ([
                        "MUD_NAME"      : CHINESE_MUD_NAME,
                        "ENGLISH_NAME"  : INTERMUD_MUD_NAME,
                        "MUDLIB_VERSION": MUDLIB_VERSION_NUMBER,
                        "MUDOS_VERSION" : __VERSION__ ,
                        "ARCH"          : __ARCH__,
                        "UPDATE"        : TIME_D->replace_ctime(stat(NOTICE_MOTD)[1]),
                ]));
        }

        write(msg);

        write(WHT "����������������� " HIR + WAITING_ENTER_TIME + NOR + WHT " ����Զ�������Ϸ\n" NOR);
        set_temp("call_out_handle", call_out((:enter_world,ob,user,0,WAITING_ENTER_TIME:),1), ob);

        input_to( (: enter_world, ob, user, 0, 1 :) );
}

varargs void enter_world(object ob, object user, int silent, int timer, string arg)
{
        object cloth, shoe;
        string startroom;
        string place, address;
        string sql, ip_number;
        string msg;
        string *ret;
        object login_ob, *users;
        mapping marry;
        mixed err;

        if( !is_root(previous_object()) ) {
                if( objectp(ob) ) call_out("destruct_ob", 0, ob);
                if( objectp(user) ) call_out("destruct_ob", 0, user);
                return;
        }

        if( !ob || !user ) {
                if( objectp(ob) ) call_out("destruct_ob", 0, ob);
                if( objectp(user) ) call_out("destruct_ob", 0, user);
                return;
        }

        if( timer && --timer ) {
#ifdef LONELY_IMPROVED
                remove_input_to(ob);
#endif
                write(TOTOP(1) + WHT "����������������� " HIR + timer + NOR + WHT " ����Զ�������Ϸ\n" NOR);
                set_temp("call_out_handle", call_out((:enter_world,ob,user,silent,timer:),1), ob);
                input_to( (: enter_world, ob, user, silent, 1 :) );
                return;
        }

        set_temp("link_ob", ob, user);
        set_temp("body_ob", user, ob);
        set("registered",query("registered",  user), ob);
        delete_temp("waiting_enter", ob);

        if( intp(query_temp("call_out_handle", ob)) )
                remove_call_out(copy(query_temp("call_out_handle", ob)));

        delete_temp("call_out_handle", ob);
#ifdef LONELY_IMPROVED
        remove_input_to(ob);
#endif
        ob->clear_msg_buffer();

        //user->set_encoding(ob->query_encoding());
        if( query_temp("big5", ob) ) set_temp("big5", 1, user);
        if( query_temp("tomud", ob) ) set_temp("tomud", 1, user);

        if( interactive(ob) ) exec(user, ob);
        user->setup();

        if( query("age", ob) == 14){
                set("food", user->max_food_capacity(), user);
                set("water", user->max_water_capacity(), user);
        }

#ifdef DB_SAVE
        if( query_temp("newplayer", user) && query("id", user) != "guest"){
                if( !DATABASE_D->query_db_status() )
                        DATABASE_D->connect_to_database();
                DATABASE_D->db_new_player(ob, user);
        }
#endif

#ifdef QUIT_SAVE_ALL
        if( query_temp("newplayer", user)){
                if( query("gender", user) == "Ů��"){
                        shoe = new("/clone/cloth/female-shoe.c");
                        cloth = new(sprintf("/clone/cloth/female%d-cloth.c", 1 + random(8)));
                } else {
                        shoe = new("/clone/cloth/male-shoe.c");
                        cloth = new(sprintf("/clone/cloth/male%d-cloth.c", 1 + random(8)));
                }
                cloth->move(user);
                //catch(cloth->wear());
                cloth->wear();
                shoe->move(user);
                //catch(shoe->wear());
                shoe->wear();
        } else {
                if( err = catch(user->restore_package()) ) {
                        set_temp("debug_msg", err, user);
                        write(HIR "\n���������Ʒ��������һЩ���⣬��Ҫ����ʦ��ϵ��\n\n" NOR);
                }
        }
#else
        if( !query_temp("newplayer", user)){
                if( err = catch(user->restore_package()) ) {
                        set_temp("debug_msg", err, user);
                        write(HIR "\n���������Ʒ��������һЩ���⣬��Ҫ����ʦ��ϵ��\n\n" NOR);
                }
        }
        if( wizhood(user) == "(player)" ) {
                if( query("class", user) == "bonze"){
                        if( query("gender", user) == "Ů��"){
                                cloth = new("/clone/cloth/ni-cloth.c");
                                shoe = new("/clone/cloth/ni-xie.c");
                        } else {
                                cloth = new("/clone/cloth/seng-cloth.c");
                                shoe = new("/clone/cloth/seng-xie.c");
                        }
                } else {
                        if( query("class", user) == "taoist"){
                                if( query("gender", user) == "Ů��"){
                                        cloth = new("/clone/cloth/daogu-cloth.c");
                                        shoe = new("/clone/cloth/dao-xie.c");
                                } else {
                                        cloth = new("/clone/cloth/dao-cloth.c");
                                        shoe = new("/clone/cloth/dao-xie.c");
                                }
                        } else {
                                if( query("gender", user) == "Ů��"){
                                        shoe = new("/clone/cloth/female-shoe.c");
                                        cloth = new(sprintf("/clone/cloth/female%d-cloth.c", 1 + random(8)));
                                } else {
                                        shoe = new("/clone/cloth/male-shoe.c");
                                        cloth = new(sprintf("/clone/cloth/male%d-cloth.c", 1 + random(8)));
                                }
                        }
                }
        } else {
                if( query("gender", user) == "Ů��"){
                        cloth = new("/clone/cloth/yunshang");
                } else {
                        cloth = new("/clone/cloth/jinduan");
                }
                shoe  = new("/clone/cloth/xianlv");
        }
        user->force_me("wear all"); // �������߲����ķ����ȴ���
        cloth->move(user);
        //catch(cloth->wear());
        cloth->wear();
        shoe->move(user);
        //catch(shoe->wear());
        shoe->wear();
        if( cloth && (!environment(cloth) || !query("equipped", cloth)) )
                destruct(cloth);
        if( shoe && (!environment(shoe) || !query("equipped", shoe)) )
                destruct(shoe);
#endif
        if( user->over_encumbranced() )
                write(HIY ">>>>>>>> ���ѳ���. <<<<<<<<\n" NOR );

        user->save();
        ob->save();

        UPDATE_D->check_user(user);

        if( !silent ) {
                write("\n\n");

                if( !query("registered", user)){
                        if( user->is_ghost() )
                                user->reincarnate();
                        set("startroom", REGISTER_ROOM, user);
                } else
                if( !stringp(query("born", user)) ) {
                        if( user->is_ghost() )
                                user->reincarnate();
                        set("startroom", BORN_ROOM, user);
                } else
                if( query("reborn_lunhui", user) || query("hell_quest", user) || query("over_quest/hell_quest", user) ) {
                        set("startroom", "/d/death/youmingdian", user);
                }

                if( (string)SECURITY_D->get_status(query("id", ob)) != "(player)" )
                        startroom = WIZARD_ROOM;
                else if( user->is_in_prison() )
                        startroom = user->query_prison();
                else if( user->is_ghost() )
                        startroom = DEATH_ROOM;
                else {
                        startroom=query("startroom", user);
                        if( !stringp(startroom)
                        ||  file_size(startroom + ".c") < 0
                        ||  startroom == CHAT_ROOM
                        ||  startroom == DEATH_ROOM )
                                startroom = START_ROOM;
                }

                if( !catch(load_object(startroom)) )
                        user->move(startroom);
                else {
                        startroom = START_ROOM;
                        user->move(startroom);
                        set("startroom", startroom, user);
                }

                if( !query("registered", user) )
                        write(color_filter(read_file(UNREG_MOTD)));
                else
                        write(color_filter(read_file(MOTD)));

                write("�����߽���" + MUD_NAME + "��\n");
                tell_room(startroom,query("name", user)+
                          "���߽���������硣\n", ({ user }));

#ifdef MCCP_SUPPORT
                if( !compressedp(user) )
                        write(YEL "����ʹ�õ���������δ������·����ѹ��("
                              HIY "MCCP" NOR YEL ")���ܣ������������ù�������·����˳����\n" NOR);
#endif
        }

        if( query("id", user) == "guest"){
                write(HIG "\n>>>>> ��ӭ����������ιۡ�\n" NOR);
                user->guest_count();
        }

        login_ob = new(LOGIN_OB);
        set("id",query("id",  user), login_ob);
        login_ob->restore();
        if( !query("login_times", login_ob)){
                //write(NOR "���ǵ�һ�ι���" + MUD_NAME + "��\n");
                write(HIG "\n>>>>> ��ӭ���һ������������磡:)\n" NOR);
                set("login_times", 1, ob);
        // show rules
        } else {
                addn("login_times", 1, ob);
                write("���ϴι���" + MUD_NAME + "�� " + HIG +
                        ctime(query("last_on", login_ob))+NOR+"��"+HIR+
                        query("last_from", login_ob)+NOR+"���ӵġ�\n");
        }
        destruct(login_ob);

        /*
        if( query_temp("no_allow_ip", ob) )
                write(HIR "���棺��δ�趨�Լ��ĵ�¼��ַ��Χ������" HIY " allowip " HIR "ָ�����á�\n" NOR);
        */
#ifdef DB_SAVE
        ip_number = resolve_ip_number(query_ip_number(user));
        sql = sprintf("SELECT place,address FROM %s WHERE ipstart <= \"%s\" AND"
                      " ipend >= \"%s\" ORDER BY ipend LIMIT 1", IP_TABLE,
                      ip_number, ip_number);
        if( sizeof(ret = DATABASE_D->db_fetch_row(sql)) )
        {
                place = ret[0];
                address = ret[1];
                msg = sprintf("%s(%s)��%s(%s��%s)���߽��롣", user->name(), query("id", user), query_ip_number(user), place, address);
        }
        else
#endif
                msg = sprintf("%s(%s)��%s���߽��롣", user->name(), query("id", user), query_ip_number(user));

        if( !(wizardp(user) && query("env/no_loginmsg", user)) )
                CHANNEL_D->do_channel(this_object(), "sys", msg);

#ifdef DB_SAVE
        DATABASE_D->db_set_player(query("id", user),"online",1);
        DATABASE_D->db_set_player(query("id", user),"last_station",LOCAL_STATION);
#endif

#if INSTALL_EXAMINE
        EXAMINE_D->examine_player(user);
#endif

       if( /*wizhood(user) != "(admin)" &&*/
           query("log_by/" + query("id", user), get_object(EXAMINE_D)) )
                user->start_log();

#ifdef DB_SAVE
        if( user->is_vip() && !BAN_D->is_netclub(query_ip_number(user)) )
#else
        if( BAN_D->is_welcome(query("id", user)) && !BAN_D->is_netclub(query_ip_number(user)) )
#endif
                BAN_D->open_club_line(user);    // �Զ�������������

        // notice user the user of this mud
        NEWS_D->prompt_user(user);
        MSG_CMD->main(user, "system");
        ANALECTA_D->prompt_user(user);
        TOPTEN_D->topten_checkplayer(user);
        FESTIVAL_CMD->main(user);

        if( mapp(marry=query("couple", user)) && !undefinedp(marry["couple_id"])){
                string tmpstr, tmpstr1;
                object couple_ob = find_player(marry["couple_id"]);
                if( couple_ob ) {
                        if( query("gender", user) != "����"){
                                tmpstr1 = "���";
                                tmpstr  = "����";
                        } else {
                                tmpstr1 = "����";
                                tmpstr  = "���";
                        }
                        write(sprintf(WHT HIM "\n���%s%s�Ѿ����������þ��ˣ���ȥ��%s�ɡ�����\n" NOR,
                                      tmpstr1, couple_ob->name(), gender_pronoun(query("gender", couple_ob))));
                        tell_object(couple_ob, sprintf(WHT HIM "\n���%s%s���Ʋ�ס�����˼����������������ȥ��%s����к��ɡ�����\n" NOR,
                                                       tmpstr,user->name(),gender_pronoun(query("gender", user))));
                }
        }

        if( (query("qi", user)<0 || query("jing", user)<0) && living(user) )
                user->unconcious();

        if( !wizardp(user) || !query("env/invisible", user)){
                users = filter_array(users(), (: query_temp("tomud", $1) :));
                message("system", ADD2(user), users);
        }
        if( query_temp("tomud", user)){
                foreach( object player in users() )
                        tell_object(user, ADD2(player));
                user->force_me("inventory");
                user->force_me("wear all");
                user->force_me("cmdbar");
        }
}

varargs void reconnect(object ob, object user, int silent)
{
        string sql, ip_number;
        string place, address;
        string msg;
        string *ret;

        set_temp("link_ob", ob, user);
        set_temp("body_ob", user, ob);
        if( query_temp("big5", ob) )
                set_temp("big5", 1, user);
        else
                delete_temp("big5", user);
        if( query_temp("tomud", ob) )
                set_temp("tomud", 1, user);
        else
                delete_temp("tomud", user);

        exec(user, ob);
        user->reconnect();

        if( !silent && (!wizardp(user) || !query("env/invisible", user))){
                tell_room(environment(user),query("name", user)+YEL"�������߻ص�������硣\n"NOR,
                ({user}));
        }

        if( query_temp("tomud", user)){
                user->force_me("look");
                user->force_me("inventory");
                user->force_me("cmdbar");
        }
#ifdef DB_SAVE
        DATABASE_D->db_set_player(query("id", user), "online", 1);

        ip_number = resolve_ip_number(query_ip_number(user));
        sql = sprintf("SELECT place,address FROM %s WHERE ipstart <= \"%s\" AND"
                      " ipend >= \"%s\" ORDER BY ipend LIMIT 1", IP_TABLE,
                      ip_number, ip_number);
        if( sizeof(ret = DATABASE_D->db_fetch_row(sql)) )
        {
                place = ret[0];
                address = ret[1];
                msg = sprintf("%s(%s)��%s(%s��%s)�������߽��롣",query("name", user),query("id", user),query_ip_number(user),place,address);
        }
        else
#endif
        msg = sprintf("%s(%s)��(%s)�������߽��롣",query("name", user),query("id", user),query_ip_number(user));
        CHANNEL_D->do_channel( this_object(), "sys", msg );

}

int check_legal_id(string id)
{
        int i;
        i = strlen(id);

        if( (strlen(id) < 3) || (strlen(id) > 10 ) ) {
                write("�Բ������"+HIW"Ӣ��"NOR+"���ֱ����� 3 �� 10 ��Ӣ����ĸ��\n");
                return 0;
        }

        if( member_array(id, banned_id) != -1 ) {
                write("�Բ���" HIC"��" + id + "��" NOR"�����������"
                      "��ĺ��⣬��������Ӣ�����֡�\n");
                return 0;
        }

        while(i--) {
                if( id[i]<'a' || id[i]>'z' ) {
                        write("�Բ������"+HIW"Ӣ��"NOR+"����ֻ����Ӣ����ĸ��\n");
                        return 0;
                }
        }
        return 1;
}

int check_legal_name(string name, int maxlen)
{
        int i;

        i = strlen(name);
        if( (strlen(name) < 2) || (strlen(name) > maxlen) ) {
                write("�Բ������������������̫����̫�̡�\n");
                return 0;
        }

        if( !is_chinese(name) ) {
                write("�Բ��������á����ġ�ȡ���֡�\n");
                return 0;
        }

        if( member_array(name, banned_name) != -1 ) {
                write("�Բ����������ֻ���������˵����š�\n");
                return 0;
        }

        //if( member_array(name, banned_name) % 2 == 0 )
        for( i=0; i<sizeof(banned_name); i++ ) {
                if( strsrch(name, banned_name[i]) != -1 ){
                        write("�Բ����������ֻ���������˵����š�\n");
                        return 0;
                }
        }
        return 1;
}

object find_body(string name)
{
        object ob, *body;

        if( objectp(ob = find_player(name)) )
                return ob;
        body = children(USER_OB);
        for( int i=0; i<sizeof(body); i++ ) {
                if( clonep(body[i]) &&
                    getuid(body[i]) == name ) {
                        if( !userp(body[i]) )
                                destruct(body[i]);
                        else    return body[i];
                }
        }
        return 0;
}

int set_wizlock(int level)
{
        if( wiz_level(this_player(1)) <= level )
                return 0;
        if( geteuid(previous_object()) != ROOT_UID )
                return 0;
        wiz_lock_level = level;
        return 1;
}

int set_cruiselock(int level)
{
        if( wiz_level(this_player(1)) <= 4 )
                return 0;

        cruise_lock = level;
        return 1;
}

int set_madlock(int setmark)
{
        if( wiz_level(this_player(1)) < wiz_level("(arch)") )
                return 0;
        if( setmark == 1 ) mad_lock = 1;
        else    mad_lock = 0;
        return 1;
}

int get_madlock()
{
        return mad_lock;
}

int can_login(int level)
{
        if( level < wiz_lock_level )
                return 0;

        return 1;
}

int block_ip(string ip, int time, string reason)
{
        mapping tmp_ban = ([]);

        tmp_ban["reason"] = reason;
        tmp_ban["time"] = time();
        tmp_ban["punish"] = time;
        map_delete(blocks, ip);
        blocks[ip] = tmp_ban;

        return 1;
}

int unblock_ip(string ip)
{
        if( ip == "all" )
                blocks = ([]);
        else
                map_delete(blocks, ip);

        return 1;
}

mapping query_block()
{
        return blocks;
}
