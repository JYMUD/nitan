// This program is a part of NITAN MudLIB
// memberd.c ��Ա����

#pragma optimize
#pragma save_binary

#ifdef DB_SAVE

#include <ansi.h>
#include "/adm/etc/database.h"
#define GOODS_D         "/adm/daemons/goodsd"
#define VERSION         "V 2.0"

public int is_member(mixed ob);
public int is_valid_member(mixed ob);
public mixed db_query_member(mixed ob, string key);
public mixed db_find_member(string key, mixed data);
public varargs int db_create_member(mixed ob, int money, string from_id);
public int db_remove_member(mixed ob);
public int db_set_member(mixed ob, string key, mixed data);
public int db_add_member(mixed ob, string key, int num);
public varargs int db_pay_member(mixed ob, int money, string from_id);
public int db_transfer_member(mixed ob, mixed to, int value);

int clean_up() { return 1; }

protected int valid_caller()
{
#ifdef DEBUG
        return 1;
#else
        if (!previous_object() ||
            !is_root(previous_object()))
                return 0;
        else
                return 1;
#endif
}

void create()
{
        seteuid(ROOT_UID);
}

// ��ѯ ID �Ƿ��ǳ�ֵ�û�
public int is_member(mixed ob)
{
        mixed  ret;
        string id, sql;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        sql = sprintf("SELECT id FROM %s WHERE id = \"%s\"",
                      MEMBER_TABLE, id);

        ret = DATABASE_D->db_query(sql);

        if (!intp(ret))
                return 0;

        return ret;
}

// ��ѯ ID �Ƿ�����Ч��Ա
public int is_valid_member(mixed ob)
{
        mixed  ret;
        string id, sql;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        sql = sprintf("SELECT id FROM %s WHERE id = \"%s\" AND endtime > %d",
                      MEMBER_TABLE, id, time());

        ret = DATABASE_D->db_query(sql);

        if (!intp(ret))
                return 0;

        return ret;
}

// ��Ա˫������ʱ��
public int is_double_reward(object ob)
{
        int t;

        /*
        t = localtime(time())[2];

        if (is_valid_member(ob) &&
            t >= 20 && t < 24)
                return 1;
        t = localtime(time())[3];
        if (t >= 0 && t < 4)
                return 1;
        */

        if( query("time_reward/quest", ob) )
                return 1;

        return 0;
}

// ��ѯ ID �����Ϣ
public mixed db_query_member(mixed ob, string key)
{
        mixed  ret;
        string id, sql;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id)  || id  == "" ||
            !stringp(key) || key == "")
                return 0;

        sql = sprintf("SELECT %s FROM %s WHERE id = \"%s\"",
                      key, MEMBER_TABLE, id);

        ret = DATABASE_D->db_fetch_row(sql);

        if (arrayp(ret) && sizeof(ret))
                return ret[0];
        else
                return 0;
}

// ��������Ѱ�һ�Ա
public mixed db_find_member(string key, mixed data)
{
        mixed  ret;
        string sql;

        if (!stringp(key) || key == "" || !data)
                return 0;

        if (intp(data))
                sql = sprintf("SELECT id FROM %s WHERE %s = %d",
                              MEMBER_TABLE, key, data);
        else if (mapp(data) || arrayp(data))
                sql = sprintf("SELECT id FROM %s WHERE %s = \"%s\"",
                              MEMBER_TABLE, key, save_variable(data));
        else if (stringp(data))
                sql = sprintf("SELECT id FROM %s WHERE %s = \"%s\"",
                              MEMBER_TABLE, key, data);
        else
                sql = sprintf("SELECT id FROM %s WHERE %s = %O",
                              MEMBER_TABLE, key, data);

        ret = DATABASE_D->db_all_query(sql);

        return ret;
}

// �����µĻ�Ա
public varargs int db_create_member(mixed ob, int money, string from_id)
{
        mixed  ret;
        string id, sql;
        string payinfo;
        object target;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id) || id == "")
                return 0;

        /*
        if (is_member(id))
                return 0;
        */

        if (!stringp(from_id) || from_id == "")
                payinfo = sprintf("���� %s ��ֵ %d $NT��\n", TIME_D->replace_ctime(time()), money);
        else
                payinfo = sprintf("���� %s �յ� %s ��ת�� %d $NT��\n",
                                  TIME_D->replace_ctime(time()), from_id, money);

        sql = sprintf("INSERT INTO %s SET id = \"%s\", uid = \"%s\", money = %d, paytimes = 1, payinfo = \"%s\",
                      payvalue = %d, last_payvalue = %d, last_paytime = %d",
                      MEMBER_TABLE, id, id, money, payinfo, money, money, time());

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        if (objectp(target = find_player(id)))
        {
                tell_object(target, "\a", 0);
                tell_object(target, HIR + payinfo + NOR);
        }
        return ret;
}

// ɾ����Ա
public int db_remove_member(mixed ob)
{
        mixed  ret;
        string id, sql;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id) || id == "")
                return 0;

        sql = sprintf("DELETE FROM %s WHERE id = \"%s\"",
                      MEMBER_TABLE, id);
        ret = DATABASE_D->db_query(sql);

        if (!intp(ret))
                return 0;

        return ret;
}

// �趨��Ա����
public int db_set_member(mixed ob, string key, mixed data)
{
        mixed  ret;
        string id, sql;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id)  || id  == "" ||
            !stringp(key) || key == "")
                return 0;

        /*
        if (intp(data))
                sql = sprintf("UPDATE %s SET %s = %d WHERE id = \"%s\"",
                              MEMBER_TABLE, key, data, id);
        else if (mapp(data) || arrayp(data))
                sql = sprintf("UPDATE %s SET %s = \"%s\" WHERE id = \"%s\"",
                              MEMBER_TABLE, key, save_variable(data), id);
        else if (stringp(data))
                sql = sprintf("UPDATE %s SET %s = \"%s\" WHERE id = \"%s\"",
                              MEMBER_TABLE, key, data, id);
        else
                sql = sprintf("UPDATE %s SET %s = %O WHERE id = \"%s\"",
                              MEMBER_TABLE, key, data, id);
        */
        if (intp(data))
                sql = "UPDATE members SET " + key + "=" + data + " WHERE id = '" + id + "'";
        else if (mapp(data) || arrayp(data))
                sql = "UPDATE members SET " + key + "=" + DB_STR(save_variable(data)) + " WHERE id = '" + id + "'";
        else if (stringp(data))
                sql = "UPDATE members SET " + key + "=" + DB_STR(data) + " WHERE id = '" + id + "'";
        else
                return 0;

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        return ret;
}

// ���ӻ�Ա���Ե�
public int db_add_member(mixed ob, string key, int num)
{
        mixed  ret;
        string id, sql;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id)  || id  == "" ||
            !stringp(key) || key == "" ||
            !intp(num)    || !num)
                return 0;

        sql = sprintf("UPDATE %s SET %s = %s + %d WHERE id = \"%s\"",
                      MEMBER_TABLE, key, key, num, id);

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        return ret;
}

// ��Ա��
public varargs mixed db_fee_member(mixed ob, int day, int flag)
{
        mixed  ret;
        string id, sql;
        int    jointime, endtime;
        object user, obj;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
        {
                id=query("id", ob);
                user = ob;
        }
        else
        if (stringp(ob))
        {
                id = ob;
                user = find_player(id);
        }
        else
                return 0;

        if (!user) return 0;
        BAN_D->add_welcome_user(id);

        jointime = db_query_member(id, "jointime");
        if (jointime < 1)
        {
                jointime = time();
                if (day > 90) addn("balance", 30000000, user);
                else addn("balance", 10000000, user);
        }

        if (flag)
        {
                day = 1999999999;
                obj = new("/d/room/obj/ultracard");
                obj->move(user, 1);
                obj = new("/clone/goods/noname");
                obj->move(user, 1);
        }
        else
        {
                endtime = (int)db_query_member(id, "endtime");
                if (endtime < 1 || endtime < time())
                        day = time() + day * 86400;
                else
                        day = endtime + day * 86400;
        }

        sql = sprintf("UPDATE %s SET jointime = %d, endtime = %d WHERE id = \"%s\"",
                      MEMBER_TABLE, jointime, day, id);

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        return ret;
}

// ��Ա��ֵ
public varargs int db_pay_member(mixed ob, int money, string from_id)
{
        string id, sql;
        string payinfo;
        string info;
        int paytimes, payvalue, last_payvalue;
        mixed ret;
        object target;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (!stringp(id) || id == "")
                return 0;

        /*
        if (!is_member(id))
        {
                db_create_member(id, money, from_id);
                return 1;
        }
        */

        paytimes = db_query_member(id, "paytimes") + 1;
        payinfo  = db_query_member(id, "payinfo");
        if (!payinfo) payinfo = "";

        if (!stringp(from_id) || from_id == "")
                info = sprintf("���� %s ��ֵ %d $NT��\n", TIME_D->replace_ctime(time()), money);
        else
                info = sprintf("���� %s �յ� %s ��ת�� %d $NT��\n",
                                TIME_D->replace_ctime(time()), from_id, money);

        payinfo += info;
        payvalue = db_query_member(id, "payvalue") + money;
        last_payvalue = money;
        money   += db_query_member(id, "money");
        /*
        sql = sprintf("UPDATE %s SET money = %d, paytimes = %d, payinfo = \"%s\",
                      payvalue = %d, last_payvalue = %d, last_paytime = %d WHERE id = \"%s\"",
                      MEMBER_TABLE, money, paytimes, payinfo, payvalue, last_payvalue, time(), id);
        */
        sql = "UPDATE members SET money=" + money + ", paytimes=" + paytimes + ", payinfo=" + DB_STR(payinfo) +
              ", payvalue=" + payvalue + ", last_payvalue=" + last_payvalue + ", last_paytime=" +time()+ " WHERE id= '" + id + "'";

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        if (objectp(target = find_player(id)))
        {
                tell_object(target, "\a", 0);
                tell_object(target, HIR + info + NOR);
        }

        return ret;
}

public varargs int player_pay(mixed from, int money, mixed to)
{
        mixed  ret;
        string fid, sql;

        if (!from)
                return 0;

        if (objectp(from))
                fid=query("id", from);
        else
        if (stringp(from))
                fid = from;
        else
                return 0;

        if (!stringp(fid)  || fid  == "" || !money)
                return 0;

        sql = sprintf("UPDATE %s SET money = money - %d WHERE id = \"%s\"",
                      MEMBER_TABLE, money, fid);

        ret = DATABASE_D->db_query(sql);
        if (!intp(ret))
                return 0;

        if (to)
        {
                money = money*99/100;
                if (money < 1) money = 1;
                if (MEMBER_D->is_member(to))
                        MEMBER_D->db_pay_member(to, money, fid);
                else
                        MEMBER_D->db_create_member(to, money, fid);
        }
        return ret;
}

// ��Աת��
public int db_transfer_member(mixed ob, mixed to, int value)
{
        string id, to_id, sql;
        string zhuaninfo;
        int money;
        mixed ret;
        object target;

        if (!valid_caller())
                return 0;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        if (objectp(to))
                to_id=query("id", to);
        else
        if (stringp(to))
                to_id = to;
        else
                return 0;

        if (!stringp(id) || id == "" ||
            !stringp(to_id) || to_id == "" ||
            !intp(value) || value < 1)
                return 0;

        target = UPDATE_D->global_find_player(to_id);
        if (!objectp(target))
        {
                write("û�������ң�����ȷ�Ϻ����ԣ�\n");
                return 0;
        }

        UPDATE_D->global_destruct_player(target, 1);

        if (!is_member(id))
        {
                write("��Ŀǰû�г�ֵ��¼��Ҳû�����߽�ң�\n");
                return 0;
        }


        money = db_query_member(id, "money");
        if (money < value)
        {
                write("�Բ����������߽������������\n");
                return 0;
        }

        if (!db_set_member(ob, "money", (money - value)))
        {
                write("ת��ʧ�ܣ����뱾վADMIN��ϵ��\n");
                return 0;
        }

        if (!is_member(to_id))
                db_create_member(to_id, value, id);
        else
                db_pay_member(to_id, value, id);

        zhuaninfo  = db_query_member(id, "transferinfo");
        zhuaninfo += sprintf("���� %s ת�� %d $NT����� %s��\n",
                           TIME_D->replace_ctime(time()),
                           value,
                           to_id);

        db_set_member(ob, "transferinfo", zhuaninfo);
        db_add_member(ob, "transfervalue", value);
        db_add_member(ob, "transfertimes", 1);
        write(HIG "ת�ʳɹ��� ����ת�ʼ�¼��д���ļ�����ʹ�� " HIR "member show zhuaninfo " HIG " ��ѯ�� \n" NOR);
        write(HIC "���ܹ�ת���� " + HIY + value + HIC + " $NT , ף�����ˣ�\n" NOR);

        return 1;
}

public void show_member_info(mixed ob, string arg)
{
        mixed  ret, res;
        int    i;
        string id;

        if (objectp(ob))
                id=query("id", ob);
        else
        if (stringp(ob))
                id = ob;
        else
                return 0;

        switch(arg)
        {
        // ��ֵ��¼
        case "payinfo":
                if (!is_member(ob))
                {
                        write("��Ŀǰû�г�ֵ��¼��\n");
                        return;
                }
                ret = db_query_member(ob, arg);
                write(BBLU + HIW "���ĳ�ֵ��¼���£�\n\n" NOR);
                res = explode(ret, "\n");
                for (i = 0; i < sizeof(res); i++)
                        write(BBLU + HIY + res[i] + "\n" NOR);
                break;
        // �����¼
        case "buyinfo":
                if (!is_member(ob))
                {
                        write("��Ŀǰû�й����¼��\n");
                        return;
                }
                ret = db_query_member(ob, arg);
                if (!stringp(ret) || ret == "")
                {
                     write("��Ŀǰû�й����¼��\n");
                     return;
                }
                write(BBLU + HIW "���Ĺ����¼���£�\n\n" NOR);
                /*
                res = explode(ret, "\n");
                for (i = 0; i < sizeof(res); i++)
                        write(BBLU + HIY + res[i] + "\n" NOR);
                */
                ob->start_more(BBLU + HIY + ret + "\n" NOR);
                break;

        // ת�ʼ�¼
        case "zhuaninfo":
        case "transferinfo":
                if (!is_member(ob))
                {
                        write("��Ŀǰû��ת�ʼ�¼��\n");
                        return;
                }
                //ret = db_query_member(ob, arg);
                ret = db_query_member(ob, "transferinfo");
                if (!stringp(ret) || ret == "")
                {
                     write("��Ŀǰû��ת�ʼ�¼��\n");
                     return;
                }
                write(BBLU + HIW "����ת�ʼ�¼���£�\n\n" NOR);
                res = explode(ret, "\n");
                for (i = 0; i < sizeof(res); i++)
                        write(BBLU + HIY + res[i] + "\n" NOR);
                break;

        // ���
        case "info":
                write(BBLU + HIW "\t\t       ����֮ս��Աϵͳ���\t\t     " + VERSION + "\n" NOR);
                write(HIW "��---------------------------------------------------------------��\n" NOR);
                write(HIY "WELCOME TO JOIN IN THE MEMBERS OF NT5 AND HOPE YOU ALL GOES WELL.\n\n" NOR);

                write(sprintf(HIC "  ��Ա���ţ�%-25s�����%s\n" NOR,
                              id, db_query_member(ob, "money") + " $NT"));
                write(sprintf(HIC "  ���ʱ�䣺%-25s��Чʱ�䣺%s\n" NOR,
                              db_query_member(ob, "jointime") ?
                              TIME_D->replace_ctime(db_query_member(ob, "jointime")) : "û�����",
                              db_query_member(ob, "endtime") > 1888888888 ?
                              "�����Ա" : (db_query_member(ob, "endtime") ?
                              TIME_D->replace_ctime(db_query_member(ob, "endtime")) : "0")));
                write(sprintf(HIC "  ��ֵ�ۼƣ�%-25s��ֵ������%d\n" NOR,
                              db_query_member(ob, "payvalue") + " $NT",
                              db_query_member(ob, "paytimes")));
                write(sprintf(HIC "  �����ۼƣ�%-25s���������%d\n" NOR,
                              db_query_member(ob, "buyvalue") + " $NT",
                              db_query_member(ob, "buytimes")));
                write(sprintf(HIC "  ת���ۼƣ�%-25sת�ʴ�����%d\n" NOR,
                              db_query_member(ob, "transfervalue") + " $NT",
                              db_query_member(ob, "transfertimes")));
                write(sprintf(HIM "\n  �����һ�γ�ֵʱ����               %s\n" NOR,
                              TIME_D->replace_ctime(db_query_member(ob, "last_paytime"))));
                write(sprintf(HIM "  �����һ�ι���ʱ����               %s\n" NOR,
                              db_query_member(ob, "last_buytime") ?
                              TIME_D->replace_ctime(db_query_member(ob, "last_buytime")) : "��������"));
                write(sprintf(HIM "  �����һ�ι�����Ʒ��               %s(%s)\n" NOR,
                              sizeof(db_query_member(ob, "last_buyob")) ?
                              db_query_member(ob, "last_buyob") : "��������",
                              db_query_member(ob, "last_buyvalue") ?
                              db_query_member(ob, "last_buyvalue") + " $NT" : "0"));

                write(HIG "\n  *��ʹ��" HIR " member show info " HIG "          ����̶��Աϵͳ��塣\n" NOR);
                write(HIG "  *��ʹ��" HIR " member show payinfo " HIG "       �鿴��ʷ��ֵ��¼��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member show buyinfo " HIG "       �鿴������Ʒ��¼��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member show zhuaninfo " HIG "     �鿴��ʷת�ʼ�¼��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member show goods " HIG "         �鿴�����̵���۵���Ʒ��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member zhuan <$NT> to <id>" HIG " ת�ʽ��($NT)����Ľ�ɫ(ID)��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member buy <��Ʒ����> " HIG "     ������Ʒ��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member look <��Ʒ����> " HIG "    �鿴��Ʒ��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member check <id> " HIG "         ����Ա��Ϣ��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member stats " HIG "              �г����еĻ�Ա��\n" NOR);
                write(HIG "  *��ʹ��" HIR " member ?? " HIG "                 member ָ�������\n\n\n" NOR);


                write(HIR "  Ϊ�����������Ҫ����ʧ�������Ķ�����֮ս��Ա�ƶ��ļ�" HIY "(help member)\n\n" NOR);
                write(HIY "                                                 NT5 WIZARD GROUP\n" NOR);
                write(HIW "��---------------------------------------------------------------��\n" NOR);

                break;
           // ��Ʒ�嵥
           case "goods":
                GOODS_D->show_goods(ob);
                break;

           default:
                break;
      }

      return;
}

public mixed show_all_members(int flag)
{
        int nCount, m = 0;
        string status;
        object ob;
        string name, jointime;
        mixed members;

        members = DATABASE_D->db_all_query(sprintf("SELECT id from %s where endtime >= %d", MEMBER_TABLE, time()));


        if (!sizeof(members))
        {
                if (flag) return ({});
                write(HIG "���޻�Ա��\n" NOR);
                return;
        }

        if (flag) return members;

        write(HIM "���������߹��������л�Ա�б�\n" NOR);
        write(HIW "��-------------------------------------------------------------------��\n" NOR);

        write(sprintf(HIR "%-18s%-18s%-26s%-20s\n\n" NOR,
                    "��  ��", "��  ��", "���ʱ��", "״  ��"));

        for (nCount = 0; nCount < sizeof(members); nCount ++)
        {
                if (ob = find_player(members[nCount][0]))
                {
                        if( query("doing", ob))status=HIY"�ƻ���"NOR;
                        else if (interactive(ob) && query_idle(ob) > 120)status = HIM "����" NOR;
                        else if (is_valid_member(members[nCount][0]))status = HIW "����" NOR;
                        else status = HIR "����" NOR;
                        name = ob->name(1);
                        jointime = TIME_D->replace_ctime(db_query_member(members[nCount][0], "jointime"));
                }
                else
                {
                        if (is_valid_member(members[nCount][0])) status = NOR + WHT "����" NOR;
                        else status = HIR "����" NOR;
                        name = "������";
                        jointime = "������";
                }

                write(sprintf(HIG "%-18s%-18s%-26s%-20s\n" NOR,
                           name,
                           members[nCount][0],
                           jointime,
                           status));

                m ++; // ���˵�ת�ʼ�¼�ļ���ʵ�ʻ�Ա��

        }
        write(HIY "\n�ܹ��� " + m + " ��ע���Ա��\n" NOR);
        write(HIW "��-------------------------------------------------------------------��\n\n" NOR);
        return 1;
}

#endif

