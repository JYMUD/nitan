// This program is a part of NITAN MudLIB
// Written by Lonely@nitan.org
// saled.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <config.h>

inherit F_SAVE;
inherit F_DBASE;

#define MAX_OBS    20
#define TAX        5

void create()
{
        mapping data;

        seteuid(ROOT_UID); 
        restore();
        data = query_entire_dbase();
        if( !mapp(data) || undefinedp(data["data"]) )
        {
                set("data", ([]));
                save();
        }
}

void remove()
{
        save();
}

public void mud_shutdown()
{
        save();
}

public string query_save_file() { return DATA_DIR "saled"; }

protected void log_buyinfo(object ob, string which, int value)
{
        string buyinfo;

        buyinfo = MEMBER_D->db_query_member(ob, "buyinfo");
        buyinfo += sprintf("%s(%s)��%s���� %d $NT������Ʒ %s 1��\n",
                           ob->name(1),
                           query("id", ob),
                           TIME_D->replace_ctime(time()),
                           value,
                           which);

        MEMBER_D->db_set_member(ob, "buyinfo", buyinfo);
        MEMBER_D->db_add_member(ob, "buytimes", 1);
        MEMBER_D->db_add_member(ob, "buyvalue", value);
        MEMBER_D->db_set_member(ob, "last_buytime", time());
        MEMBER_D->db_set_member(ob, "last_buyob", which);
        MEMBER_D->db_set_member(ob, "last_buyvalue", value);
        return;
}

public string do_stock(object me, string arg)
{
        object ob, obj;
        int n, value;
        string file, id, key, str, db;
        mapping data;

        id=query("id", me);
        if( !arg || sscanf(arg, "%s value %d", arg, value) != 2 )
                return "ָ���ʽ��stock <����> value * (���� * ������̶��($NT)����λ�ļ۸�)\n";

        if( !value || value < 0 )
                return "ָ���ʽ��stock <����> value * (���� * ������̶��($NT)����λ�ļ۸�)\n";

        if( value > 100000000 )
                return "�����һ����̶��($NT)����ͱ���ô�ĺ��˰ɡ�\n";

        if( !objectp(ob = present(arg, me)) )
                return "�����ϲ�û��������ﰡ��\n";

        if( query("no_sell", ob) || query("id", ob) == "key" )
                return "�������̫��ҡ�ˣ����Ǳ��ó���������\n";

        if( query("task_ob", ob) )
                return "�������̫��ҡ�ˣ����Ǳ��ó���������\n";

        if( ob->is_item_make() || query("unique", ob) )
                return "�������̫��ҡ�ˣ����Ǳ��ó���������\n";

        if( sscanf(base_name(ob), "/data/%*s") )
                return "�������̫��ҡ�ˣ����Ǳ��ó���������\n";

        file = file_name(ob);
        if( strsrch(file, "#") == -1 )
                return "�Բ��𣬸���Ʒ�����Լ��ۣ�\n";

        if( ob->is_character() )
                return "�㲻�ܷ������\n";

        if( query("money_id", ob) )
                return "���ǮҲ�������ۣ�\n";

        if( query("bindable", ob) )
                delete("bind_owner", ob);

        key = "data/" + id + "/";
        if( sizeof(query(key+"objects")) >= MAX_OBS )
                return "�Բ������Ѿ�������" + query(key + "cnt") +
                       "����Ʒ�ˡ������ټ��۸���Ķ����ˡ�\n";

        str=query("unit", ob);
        if( !str ) str = "��";
        if( n = ob->query_amount() )
                db = "";
        else {
                obj = new(base_name(ob));
                if( !mapping_eqv(ob->query_entire_dbase(), obj->query_entire_dbase()) )
                        db = save_variable(ob->query_entire_dbase());
                else
                        db = "";
                destruct(obj);
        }
        if( n < 1 ) n = 1;
        data = ([
                "file" : file,
                "name":query("name", ob),
                "id":query("id", ob),
                "ids" : ob->my_id(),
                "unit" : str,
                "num" : n,
                "value" : value,
                "dbase" : db,
        ]);

        n = query(key + "cnt");
        n++;
        set(key + "cnt", n);
        set(key + "objects/" + n, data);

        message_vision(HIW "$N" HIW "����" HIG + ob->name(1) +
                       HIW "������" HIY + value +
                       HIW "NT�۸�ʼ���ۡ�\n" NOR, me);
        destruct(ob);

        if( objectp(ob) ) {
                set(key + "cnt", n - 1);
                delete(key + "objects/" + n);
                save();
                return "���󣡼���ʧ�ܣ�����ϵ����Ա��\n";
        } else {
                save();
                return data["name"] + "�Ѿ����ۺ��ˣ���ţ�" + n + " ��\n";
        }
}

public string do_unstock(object me, string arg)
{
        string kid,*ks,id;
        string file="";
        object ob;
        mapping data;
        int i,flag=0;
        id=query("id", me);

        if( !arg || arg == "" )
                return "ָ���ʽ��unstock <��Ʒ> | <��Ʒ���>\n";

        arg = lower_case(arg);
        kid = "data/" + id + "/objects";
        data = query(kid);
        if( sizeof(data) < 1 )
                return "��ʲô��Ʒ��û�м����ţ���������ʲô��\n";

        if( sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED )
                return "�����ϵĶ���̫���ˣ�û���ӻ�����ȡ������\n";

        ks = keys(data);
        for( i = 0; i < sizeof(ks); i++ ) {
                if( ks[i] == arg || data[ks[i]]["id"] == arg ) {
                        data = data[ks[i]];
                        flag = 1;
                        break;
                }
        }

        if( flag ) {
                file = data["file"];
                sscanf(file, "%s#%*s", file);
                ob = new(file);
                if( data["dbase"] ) {
                        ob->set_dbase(restore_variable(data["dbase"]));
                        ob->set_name(query("name", ob),data["ids"]);
                }

                if( objectp(ob) ) {
                        ob->set_amount(data["num"]);
                        ob->move(me, 1);
                        delete(kid+"/"+ks[i]);
                        save();
                        message_vision( HIW "$N" HIW "����" HIG + ob->name(1) +
                                        HIW "���ӻ�����ȡ���������ˡ�\n" NOR, me );
                        return "��Ӽ��۹�ȡ����"+data["name"]+"("+data["id"]+") ��\n";
                }
        }
        return "����" + environment(me)->short() + "�Ļ����ϲ�û���������\n";
}

public string do_list(object me, string arg)
{
        string k, msg, *ks;
        mapping data, m, om;
        int i, j, w;
        string id;

        data = query("data");
        if( !mapp(data) || sizeof(data) < 1 )
                return "Ŀǰ��û�г����κλ��\n";

        msg = "�ü��۵�Ŀǰ����������Ʒ��\n";
        msg += "-------------------------------------------------------\n";
        ks = keys(data);
        j=0;
        w=wizardp(me);
        for( i = 0; i < sizeof(ks); i++ ) {
                if( mapp(m = data[ks[i]]["objects"]) && sizeof(m) > 0 ) {
                        foreach(k in keys(m)) {
                                om = m[k];
                                j++;
                                msg+=sprintf("��%d����Ʒ ���%5s �� %20s(%10s) ������%5d �ۼۣ�%8d$NT (%s) %s\n",
                                             j,k,om["name"],om["id"],om["num"],om["value"],ks[i],(w?om["file"]:""));
                        }
                }
        }

        msg += "-------------------------------------------------------\n";

        msg += "�ܹ�" + chinese_number(j) + "�����\n";

        // me->start_more(msg);
        return msg;
}

public string do_buy(object me, string arg)
{
        string kid, *ks, id;
        string file;
        object ob;
        mapping data;
        int value, money, fees;
        int i, flag = 0;
        int m;

        if( me->is_busy() )
                return "ʲô�¶��õ���æ����˵�ɣ�\n";

        if( !arg || sscanf(arg, "%s from %s", arg, id) != 2 )
                return "buy <ĳ��> from <id>\n";

        if( sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED )
                return "�����ϵĶ���̫���ˣ��ȴ���һ���������ɡ�\n";

        arg = lower_case(arg);
        kid = "data/" + id + "/objects";
        data = query(kid);
        if( sizeof(data) < 1 )
                return "��ʲô��Ʒ��û�м����š�\n";

        ks = keys(data);
        for( i = 0; i < sizeof(ks); i++ ) {
                if( ks[i] == arg || data[ks[i]]["id"] == arg ) {
                        data = data[ks[i]];
                        flag = 1;
                        break;
                }
        }

        if( flag ) {
                value = data["value"];
                money = MEMBER_D->db_query_member(me, "money");
                if( money < value )
                        return "�Բ���������̶����������������ֵ��������\n";

                fees = (int)value * TAX / 100;
                if( fees > 0 ) {
                        if( !MEMBER_D->player_pay(me, fees) ||
                            !MEMBER_D->player_pay(me, (value - fees), id) )
                                return "������Ʒʧ�ܣ����뱾վ��ʦ��ϵ��\n";
                }
                else
                {
                        if( !MEMBER_D->player_pay(me, value, id) )
                                return "������Ʒʧ�ܣ����뱾վ��ʦ��ϵ��\n";
                }

                file = data["file"];
                sscanf(file, "%s#%*s", file);
                ob = new(file);
                if( data["dbase"] ) {
                        ob->set_dbase(restore_variable(data["dbase"]));
                        ob->set_name(query("name", ob),({query("id", ob)}));
                }

                if( objectp(ob) ) {
                        ob->set_amount(data["num"]);
                        if( ob->query_amount() )
                                message_vision("$N������" + ob->short() + "��\n", me);
                        else
                                message_vision("$N����������һ"+query("unit", ob)+
                                                query("name", ob)+"��\n",me);

                        ob->move(me, 1);
                        delete(kid+"/"+ks[i]);
                        save();
                        me->start_busy(1);
                        log_buyinfo(me, data["name"], value);
                        return "��Ӽ��۹�ȡ����"+data["name"]+"("+data["id"]+") ��\n";
                }
        }
        return "����" + environment(me)->short() + "�Ļ����ϲ�û���������\n";
}
