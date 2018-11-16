// This program is a part of NT MudLIB
// ��ҵϵͳ�ܿس���
// edit by smallfish 2002.3.17
// Updated by Vin for heros.cn
// Updated by Jjgod.
// Updated by Lonely@nitan.org

#include <ansi.h>
#include <config.h>
#include <getconfig.h>

/*
���ļ�Ϊ��ҵϵͳ�е��̵����ɳ���
���ļ��ṩ�����ļ����ã�
/cmds/usr/shop.c                        ���̲�ѯ����ָ��
/inherit/char/waiter.c                  ��Ƴ���ӿ��ļ�
/inherit/room/shop.c                    ���̳���ӿ��ļ�

�����Լ���Ƶĳ�����·����/clone/shop
���̻�Ƽ̳��ļ���/inherit/char/waiter.c

���̼̳��ļ���/inherit/room/shop.c
���̻�Ʋ��� *.o ��ʽ���ļ��洢���洢�ļ�����ڣ�/data/shop
������Ҫ������
string owner:           ����ID
int shop_type��         ����״̬(0 ��ʾ�ر�)
mapping vendor_goods:           ����۸�keys Ϊ����� base_name
mapping vendor_goods_num:       ��������������keys Ϊ����� base_name
int all_vendor_goods:           ���л��������ܺ�
mapping invite:                 ������ۿۣ�keys Ϊ����� id
string *ban:                    �ڻ��б�keys Ϊ�ڻ� id
*/

public mapping *query_shop();                                  // ���ص����б�
public int is_inited();                                        // ���ص����Ƿ�ȫ����ʼ��
private int check_owner(string arg);                           // ���������˺͵��̻�������Ƿ���ͬ
public int change_owner(object me,string arg,string owner);    // �޸ĵ��̵������������˺͵��̻�����ˣ�
public int is_owner(string owner);                             // �鿴��� owner �Ƿ���̵���
public int close_all(object me);                               // �ر����е���
public int close_shop(object me,string arg);                   // �ر�ָ������
public int open_all(object me);                                // �������е���
public int open_shop(object me,string arg);                    // ����ָ������
public int reset_all(object me);                               // ��ʼ�����е���
public int reset_shop(object me,string arg);                   // ��ʼ��ָ������
public int list_shop(object me);                               // ��ѯ����
public string do_modify(object obj, object me, string arg);    // �޸ĵ��̻�Ƶ�����
public string do_stock(object ob, object me, string arg);      // ��۲����ۻ���
public string do_unstock(object ob, object me, string arg);    // ȡ�»���
public string do_list(object ob, object me, string arg);       // ��ѯ����
public int do_listall(object me);                              // �������̵����
public int do_buy(object obj, object me, string arg);          // �������
private int player_pay(object who, object target, int amount); // ���������ҵ�����Լ�˰��
public string do_jiezhang(object ob, object me);               // ���ʣ��������˲�����ʱ��ĵ������룩
public string list_invite(object ob, object me);               // ��ѯ����б�
public string do_invite(object ob, object me, string arg);     // ����|ȡ�� ���
public string list_ban(object ob, object me);                  // ��ѯ�ڻ��б�
public string do_ban(object ob, object me, string arg);        // ����|ȡ�� �ڻ�
public string list_order(object ob,object me);                 // ������ʾԤԼ
public string do_order(object ob,object me,string arg);        // ԤԼ��Ʒ
private void destruct_it(object ob);
public void reset_goods(object obj);                              // �����Ұ�̯��Ʒ
string makeup_space(string s,int max);
string *special_props = ({ "short", "long" });
string top;                                                     //������۶������(��������԰)

nosave mapping *all_shop = ({
        ([
                "id":             "����",
                "name":           "ͨ���",
                "start_room":     "yangzhou_shop",
                "type":           "shop",
                "price":          800,
        ]),
        ([
                "id":             "����",
                "name":           "�����",
                "start_room":     "beijing_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "����",
                "name":           "ͬʢ��",
                "start_room":     "changan_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "����",
                "name":           "��徸�",
                "start_room":     "luoyang_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "�ɶ�",
                "name":           "����԰",
                "start_room":     "chengdu_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "����",
                "name":           "������",
                "start_room":     "xiangyang_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "����",
                "name":           "��֥ի",
                "start_room":     "suzhou_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "����",
                "name":           "����ի",
                "start_room":     "hangzhou_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "����",
                "name":           "�۴�԰",
                "start_room":     "fuzhou_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "����",
                "name":           "�۷�԰",
                "start_room":     "wuxi_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "����",
                "name":           "����ի",
                "start_room":     "kaifeng_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "��ƽ",
                "name":           "˫Ϫ¥",
                "start_room":     "yanping_shop",
                "type":           "shop",
                "price":          50000,
        ]),
        ([
                "id":             "Ȫ��",
                "name":           "������",
                "start_room":     "quanzhou_shop",
                "type":           "shop",
                "price":          50000,
        ]),
        ([
                "id":             "��ɽ",
                "name":           "�캣¥",
                "start_room":     "foshan_shop",
                "type":           "shop",
                "price":          50000,
        ]),
        ([
                "id":             "����",
                "name":           "ף�ھ�",
                "start_room":     "hengyang_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "����",
                "name":           "�ٺ�ի",
                "start_room":     "zhongzhou_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "����",
                "name":           "������",
                "start_room":     "dali_shop",
                "type":           "shop",
                "price":          500,
        ]),
        ([
                "id":             "���",
                "name":           "���²�",
                "start_room":     "wuchang_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "����",
                "name":           "ͬ����",
                "start_room":     "lingzhou_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "����",
                "name":           "ţ����",
                "start_room":     "yili_shop",
                "type":           "shop",
                "price":          300,
        ]),
        ([
                "id":             "����",
                "name":           "�廪¥",
                "start_room":     "jingzhou_shop",
                "type":           "shop",
                "price":          300,
        ]),
});

public mapping *query_shop()
{
        return all_shop;
}

public string query_top()
{
        return top;
}

public int is_inited()
{
        int i, is_ok;
        object shop;

        is_ok = 1;

        for (i = 0; i < sizeof(all_shop); i++)
        {
                shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

                if( query("short", shop) == query_top())continue;
                if( !shop || query("shop_type", shop) )
                {
                        is_ok = 0;
                        break;
                }
                else
                {
                        if( (query("vendor_goods", shop) && 
                             sizeof(query("vendor_goods", shop))>0) || 
                             query("all_vendor_goods", shop) || 
                             query("owner", shop) != "VOID_SHOP" )
                        {
                                is_ok = 0;
                                break;
                        }
                }
        }
        return is_ok;
}

private int check_owner(string arg)
{
        int i, have_it;
        object the_shop;
        string shop_owner;

        have_it = 0;
        for (i = 0; i < sizeof(all_shop); i++)
        {
                if (all_shop[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }

        // û���ҵ�ָ���ĵ���
        if (! have_it)
                return 0;

        the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

        if (! the_shop)
                return 0;

        shop_owner = query("owner", the_shop);
        return 1;
}

public int change_owner(object me, string arg, string owner)
{
        int i, have_it;
        object the_shop;

        have_it = 0;
        for (i = 0; i < sizeof(all_shop); i++)
        {
                if (all_shop[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }

        if (! have_it)
        {
                tell_object(me, "�Բ���" + arg + "���̲������ڡ�\n");
                return 1;
        }

        if (! check_owner(arg))
        {
                tell_object(me, "���棺" + arg + "�������˺͵��̻�����������쳣������ϸ��顣\n");

                log_file("static/shop", sprintf("%s���������쳣��ʱ�䣺%s��\n", arg, ctime(time())));
                return 1;
        }

        the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

        if (the_shop)
        {
                set("owner", owner, the_shop);
                the_shop->save();
                tell_object(me, arg + "���̵����޸���ϡ�\n");
        } else
        {
                tell_object(me, arg + "�����ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }

        return 1;
}

public int is_owner(string owner)
{
        int i;
        object shop;

        for (i = 0; i < sizeof(all_shop); i ++)
        {
                shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

                if (! objectp(shop))
                        return 0;

                if( query("owner", shop) == owner )
                        return 1;
        }
        return 0;
}

public int close_all(object me)
{
        int i;

        for (i = 0; i < sizeof(all_shop); i++)
        {
                close_shop(me, all_shop[i]["id"]);
        }

        return 1;
}

// �رյ������޸ĵ��̵� shop_type Ϊ 0
public int close_shop(object me, string arg)
{
        int i, have_it;
        object the_shop;

        have_it = 0;

        for (i = 0; i < sizeof(all_shop); i++)
        {
                if (all_shop[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }

        if (! have_it)
        {
                tell_object(me, "�Բ���" + arg + "���̲������ڡ�\n");
                return 1;
        }

        if (! check_owner(arg))
        {
                tell_object(me, "���棺" + arg + "�������˺͵��̻�����������쳣������ϸ��顣\n");
                log_file("static/shop",sprintf("%s���������쳣��ʱ�䣺%s��\n", arg, ctime(time())));
                return 1;
        }

        the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

        if (the_shop)
        {
                set("shop_type", 0, the_shop);
                the_shop->save();
                tell_object(me, arg + "���̳ɹ��رա�\n");
        } else
        {
                tell_object(me, arg + "�����ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }
        return 1;
}

public int open_all(object me)
{
        int i;
        for (i = 0; i < sizeof(all_shop); i++)
                open_shop(me, all_shop[i]["id"]);
        return 1;
}

// ���ŵ������޸ĵ��̵� shop_type Ϊ 1
public int open_shop(object me, string arg)
{
        int i, have_it;
        object the_shop;

        have_it = 0;
        for (i = 0; i < sizeof(all_shop); i++)
        {
                if (all_shop[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }
        if (! have_it)
        {
                tell_object(me, "�Բ���" + arg + "���̲������ڡ�\n");
                return 1;
        }

        if (! check_owner(arg))
        {
                tell_object(me, "���棺" + arg + "�������˺͵��̻�����������쳣������ϸ��飡\n");
                log_file("static/shop", sprintf("%s���������쳣��ʱ�䣺%s��\n", arg, ctime(time())));
                return 1;
        }

        the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

        if (the_shop)
        {
                set("shop_type", 1, the_shop);
                the_shop->save();
                tell_object(me, arg + "���̳ɹ����ţ�\n");
        }
        else
        {
                tell_object(me, arg + "�����ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }
        return 1;
}

public int reset_all(object me)
{
        int i;
        int topscore;
        object the_shop;

        topscore = 0;
        for (i=0; i<sizeof(all_shop);i++)
        {
                the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);
                if( query("score", the_shop)>topscore )
                {
                        topscore=query("score", the_shop);
                        top=query("short", the_shop);
                }
                reset_shop(me, all_shop[i]["id"]);
        }
        return 1;
}

// ��ʼ�����̰�����
// �رյ���
// ���õ��̺ͻ�Ƶ�����Ϊ��ֵ
// �����ƵĻ����Լ���ƵĴ��
// �����ƵĹ���ͺڻ�
public int reset_shop(object me, string arg)
{
        int i, have_it;
        string *props, prop;
        object the_shop, the_waiter;
        mapping m;

        have_it = 0;
        for (i = 0; i < sizeof(all_shop); i++)
        {
                if (all_shop[i]["id"] == arg)
                {
                        have_it = 1;
                        break;
                }
        }
        if (! have_it)
        {
                tell_object(me,"�Բ���" + arg + "���̲������ڡ�\n");
                return 1;
        }

        the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

        if (the_shop)
        {
                set("shop_type", 0, the_shop);
                set("owner", "VOID_SHOP", the_shop);
                set("balance", 0, the_shop);
                delete("vendor_goods", the_shop);
                delete("vendor_goods_num", the_shop);
                delete("all_vendor_goods", the_shop);
                delete("invite", the_shop);
                delete("ban", the_shop);
                delete("waiter", the_shop);
                delete("score", the_shop);

                the_shop->save();

                tell_object(me, arg + "���̳ɹ���ʼ����\n");
        } else
        {
                tell_object(me, arg + "�����ļ������ڣ�����ϸ�鿴��\n");
                return 1;
        }

        the_waiter = present("huo ji", the_shop);
        if (the_waiter)
        {
                if( arrayp(m=query("waiter", the_shop)) && 
                        sizeof(props = keys(m)))
                {
                        foreach (prop in props)
                        {
                                if (prop == "name")
                                        the_waiter->set_name("���̻��", ({ "huo ji", "huo", "ji" }));
                                if (prop == "long")
                                        set("long", "��������ҵ��̵Ļ�ơ�\n", the_waiter);
                                delete(prop, the_waiter);
                        }
                        delete("waiter", the_shop);
                }
                tell_object(me, arg + "��Ƴɹ���ʼ����\n");
        } else
        {
                tell_object(me, arg + "���̻�Ʋ����ڣ�����ϸ�鿴��\n");
                return 1;
        }
        return 1;
}

public int list_shop(object me)
{
        int i;
        string arg, na, msg;
        object ob, the_shop;
        string str;

        msg = WHT "��ǰ" + LOCAL_MUD_NAME() + "�ĵ����б����£�\n" NOR;
        msg += HIC"��" HIY "������������������������������������������������������������������������" HIC "��\n" NOR;
        for (i = 0; i < sizeof(all_shop); i++)
        {
                arg = all_shop[i]["id"];

                if (! check_owner(arg))
                        continue;

                the_shop = load_object(SHOP_DIR + all_shop[i]["start_room"]);

                if (! the_shop)
                        continue;

                if( objectp(ob=find_player(query("owner", the_shop))) && 
                        this_player()->visible(ob))
                        na=HIR+query("name", ob);
                else
                {
                        na = GRN "�������";
                }

                msg += sprintf(WHT " ���̣�" HIG "%s[" HIW "%s" HIG "] " NOR ,
                                all_shop[i]["name"], arg);

               str=(query("shop_type", the_shop) && 
                               query("owner", the_shop) != "VOID_SHOP")?
                               HIG " Ӫҵ�� " NOR : HIY "�ݲ�Ӫҵ" NOR,
               msg += sprintf(HIG"%8s%s"NOR,str,makeup_space(str,8));

               msg += WHT " ���ۻ��֣�" HIC ;
               if( query("score", the_shop) <= 0 )
               str = HIY"����"NOR;
               else
               str=sprintf("%d",query("score", the_shop));
               msg += sprintf("%-6s%s",str,makeup_space(str,6));

               str=query("owner", the_shop) == "VOID_SHOP"?
                               HIC "���(ϵͳ)" NOR : na +
                               "("+query("owner", the_shop)+")"NOR,
               msg += sprintf(WHT "  �������ˣ�" HIG "%-20s%s" NOR ,str,makeup_space(str,20));

               msg += "\n";
        }
        msg += HIC"��"HIY"������������������������������������������������������������������������" HIC "��\n" NOR;
        msg += WHT"�ܹ���" + chinese_number(sizeof(all_shop)) + "�ҵ��̡�\n"NOR;
        tell_object(me, msg);
        return 1;
}

public string do_modify(object obj, object me, string arg)
{
        string item, msg;
        mapping dbase;
        object room;

        room = environment(obj);

        if( !query("shop_type", room) )
                return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        if (! arg || sscanf(arg,"%s %s", item, msg) != 2)
                return "�趨��ʽΪ��modify <��Ŀ> <����>\n";

        if (CHINESE_D->check_control(msg))
                return "���������п��Ʒ���\n";

        if (CHINESE_D->check_space(msg))
                return "�������費���ո�\n";

        if (CHINESE_D->check_return(msg))
                return "�������費���س�����\n";

        msg = trans_color(msg, 1);
        msg = replace_string(msg, "$S$", BLINK);

        switch(item)
        {
        case "short":
                if (CHINESE_D->check_length(msg) > 10)
                        return "�����趨������̫���ˡ�\n";

                if (! is_chinese(filter_color(msg, 1)))
                        return "���̵�����ֻ�������ġ�\n";

                set("apply/short", msg, room);

                room->save();
                return WHT "��Ϊ���������趨�������ơ�\n" NOR;

        case "long":
                if (CHINESE_D->check_length(msg) > 200)
                        return "�����趨������̫���ˡ�\n";

                set("apply/long", msg+NOR"\n", room);

                room->save();
                return WHT "��Ϊ���������趨����������\n" NOR;

        case "desc":
                if (CHINESE_D->check_length(msg) > 200)
                        return "�����趨������̫���ˡ�\n";

                set("long", sort_msg(msg+NOR"\n"), obj);
                set("waiter/long", sort_msg(msg+NOR"\n"), room);

                room->save();
                return WHT "��Ϊ���̻���趨����������\n" NOR;

        case "nickname" :
                if (CHINESE_D->check_length(msg) > 20)
                        return "�����趨������̫���ˡ�\n";

                set("nickname", msg+NOR, obj);
                set("waiter/nickname", msg+NOR, room);

                room->save();
                return WHT "��Ϊ���̻���趨���˴ºš�\n" NOR;

        case "title" :
                if (CHINESE_D->check_length(msg) > 20)
                        return "�����趨������̫���ˡ�\n";

                set("title", msg+NOR, obj);
                set("waiter/title", msg+NOR, room);

                room->save();
                return WHT "��Ϊ���̻���趨����ͷ�Ρ�\n" NOR;

        case "name" :
                if (CHINESE_D->check_length(msg) > 10)
                        return "�����趨������̫���ˡ�\n";

                if (! is_chinese(filter_color(msg, 1)))
                        return "���̻�Ƶ�����ֻ�������ġ�\n";

                dbase = obj->query_entire_dbase();
                dbase["name"] = msg;

                set("waiter/name", msg, room);

                room->save();
                return WHT "��Ϊ���̻���趨�������֡�\n" NOR;

        case "gender" :
                if (msg != "����" && msg != "Ů��" && msg != "����")
                        return "�Ա�ֻ�������ԡ�Ů�Ի����ԣ�û�������Ա��˵��\n";

                set("gender", msg, obj);
                set("waiter/gender", msg, room);

                room->save();
                return WHT "��Ϊ���̻���趨�����Ա�\n" NOR;
        }
        return "��Ҫ�޸�ʲô��\n";
}

/*
public string do_stock(object ob, object me, string arg)
{
        object obj, goods, obj2;
        mixed value;
        mapping all_goods, all_goods_num;
        object room;
        mapping data;

        room = environment(ob);

        // intp(value) Ϊgold, stringp(value) Ϊ$NT
        if( !query("shop_type", room) )
                return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        if (! arg || (sscanf(arg, "%s value %d", arg, value) != 2 &&
            sscanf(arg, "%s nt %s", arg, value) != 2) )
                return "ָ���ʽ��stock <����> value * ( ���� * ����ͭ������λ�ļ۸� )��\n"
                       "          stock <����> nt * ( ���� * ���� $NT ����λ�ļ۸� )\n";

        if (! value)
                return "ָ���ʽ��stock <����> value * ( ���� * ����ͭ������λ�ļ۸� )��\n"
                       "          stock <����> nt * ( ���� * ���� $NT ����λ�ļ۸� )\n";

        if (intp(value) && value > 100000000 && !wizardp(me))
                return "���������һ�����ƽ���ͱ���ô�ĺ��˰ɡ�\n";

        if (stringp(value) && to_int(value) < 0 || to_int(value) > 1000000)
                return "���������һ����$NT����ͱ���ô�ĺ��˰ɡ�\n";

        if (! (goods = present(arg, me)) || ! objectp(goods))
                return "�����ϲ�û��������ﰡ��\n";

        if( query("no_sell", goods) )
                return "�������̫��ҡ�ˣ����Ǳ��ó���������\n";

        if( query("no_get", goods) || query("no_drop", goods) || 
            query("no_put", goods) || query("no_beg", goods) || 
            query("no_steal", goods) || query("no_drop", goods) || 
            query("item_make", goods) || query("owner", goods) )
                return "��������ڲ��ϻ��ܣ�����ʱ���ó���������\n";

        if (goods->is_item_make())
                return "�������̫��ҡ�ˣ����Ǳ��ó���������\n";

        if( query("wiz_only", goods) && !wizardp(me) )
                return "�������ֻ������ʦ�̵�������\n";

        if (goods->is_character())
                return "�㲻�ܷ������\n";

        if( query("money_id", goods) )
                return "���ǮҲ�������ۣ�\n";

        if( query("all_vendor_goods", room) >= 80 )
                return "������ϵĶ���̫���ˣ����ռ��ֻ����ٰڰɡ�\n";

        if (goods->is_dynamic_equip()) //��̬��Ʒ����data
                data = goods->query_entire_dbase();

        all_goods=query("vendor_goods", room);

        if (! all_goods)
                all_goods = ([ ]);

        all_goods_num=query("vendor_goods_num", room);
        if (! all_goods_num) all_goods_num = ([ ]);

        // ��̬��Ʒ��������base_nameΪ����

        all_goods[base_name(goods)] = value;
        all_goods_num[base_name(goods)] += 1;

        set("vendor_goods", all_goods, room);
        set("vendor_goods_num", all_goods_num, room);
        addn("all_vendor_goods", 1, room);

        message_vision(HIW "$N" HIW "����" HIG + goods->name(1) + HIW "������" HIY +
                (intp(value) ? MONEY_D->price_str(value) : value+"$NT") + HIW "�ļ۸�ʼ���ۡ�\n" NOR, me);
        room->save();
        if (goods->query_amount() && goods->query_amount() > 1)
        {
                goods->set_amount((int)goods->query_amount() - 1);
                obj2 = new(base_name(goods));
                obj2->set_amount(1);
                destruct(obj2);
        }
        else destruct(goods);
        return "����ú��˻��\n";
}

public string do_unstock(object ob, object me, string arg)
{
        object obj, goods, room;
        int i, amount, value, have_it = 0;
        mapping all_goods, all_goods_num;
        string *goods_key, ob_file;

        seteuid(getuid());
        room = environment(ob);
        if( !query("shop_type", room) )
                return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        if (! arg)
                return "ָ���ʽ��unstock <����>\n";

        if( !query("all_vendor_goods", room) )
                return "�����ڻ�û�а����κλ��\n";

        all_goods=query("vendor_goods", room);
        all_goods_num=query("vendor_goods_num", room);

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED && !wizardp(me))
                return "�����ϵĶ���̫���ˣ�û���ӻ�����ȡ������\n";

        all_goods=query("vendor_goods", room);

        if (! all_goods)
                all_goods = ([ ]);

        all_goods_num=query("vendor_goods_num", room);

        if (! all_goods_num)
                all_goods_num = ([ ]);

        goods_key = keys(all_goods);

        if (arrayp(goods_key))
        {
                for (i = 0; i < sizeof(goods_key); i++)
                {
                        if (goods_key[i]->id(arg))
                                ob_file = goods_key[i];
                        else

                        if (filter_color(goods_key[i]->name(1)) == arg)
                                ob_file = goods_key[i];
                }
        }

        if (! ob_file)
                return "����"+query("short", environment(ob))+"�Ļ����ϲ�û���������\n";

        goods = new(ob_file);
        goods->set_amount(1);

        addn("all_vendor_goods", -1, room);
        all_goods_num[base_name(goods)] -= 1;

        if (all_goods_num[base_name(goods)] == 0)
        {
                map_delete(all_goods, base_name(goods));
                map_delete(all_goods_num, base_name(goods));
        }

        message_vision(HIW "$N" HIW "����" HIG + goods->name(1) + HIW"���ӻ�����ȡ���������ˡ�\n" NOR, me);

        set("vendor_goods", all_goods, room);
        set("vendor_goods_num", all_goods_num, room);
        room->save();

        if (! goods->move(me))
        {
                goods->move(environment(me));
                tell_object(me, "�������Ѿ��ò����ˣ�ֻ�ð�" + goods->name(1) + NOR "���ڵ��ϡ�\n");
        }
        return "��ȡ���˻��\n";
}

public string do_list(object ob, object me, string arg)
{
        mapping goods, goods_num;
        string *gks;
        object *obs, *inv, room;
        string msg;
        int i, have_vendor = 0;

        mapping price;
        mapping unit;
        mapping count;
        string  short_name;
        string  prefix;
        string  *dk;

        room = environment(ob);
        if( !query("shop_type", room) )
                return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        if( query("ban", room) && 
                member_array(query("id", me),query("ban", room)) != -1 )
                return "������ҵ��̲��ܻ�ӭ������޷���������\n";

        if( !query("all_vendor_goods", room) )
                return "����"+query("short", room)+"Ŀǰ��û�г����κλ��\n";

        goods=query("vendor_goods", room);

        if (! goods)
                goods = ([]);

        goods_num=query("vendor_goods_num", room);

        if (! goods_num)
                goods_num = ([]);

        count   = ([]);
        unit    = ([]);
        price   = ([]);

        gks = keys(goods);
        for (i = 0; i < sizeof(gks); i++)
        {
                object gob;
                call_other(gks[i], "???");

                if (! objectp(find_object(gks[i])))
                {
                        log_file("user_vendor", sprintf("No found vendor good:%s\n", gks[i]));
                        continue;
                }

                gob = find_object(gks[i]);
                short_name=gob->name(1)+"("+query("id", gob)+")";

                if( query("base_unit", gob) )
                        prefix = "base_";
                else
                        prefix = "";

                unit+=([short_name:query(prefix+"unit", gob)]);
                price += ([ short_name : goods[gks[i]] ]);
                count += ([ short_name : goods_num[gks[i]] ]);
        }

        msg = "�õ���Ŀǰ����������Ʒ��\n";
        msg += "-------------------------------------------------------\n";
        dk = sort_array(keys(unit), 1);

        for (i = 0; i < sizeof(dk); i++)
        {
                mixed p;
                p = price[dk[i]];
                msg += sprintf("%" + sprintf("%d", (30 + color_len(dk[i])) ) + "-s��ÿ%s%s" CYN "(�ֻ�%s)\n" NOR,
                               dk[i], unit[dk[i]],
                               intp(p) ? MONEY_D->price_str(p) : (p + "$NT"),
                               chinese_number(count[dk[i]]) + unit[dk[i]]);
        }

        msg += "-------------------------------------------------------\n";

        if( query("id", me) == query("owner", room) )
                msg+="�ܹ�"+chinese_number(query("all_vendor_goods", room))+"�����\n";

        if( query("invite/"+query("id", me, room)) )
                msg+=WHT"���Ǳ��������������л��������"HIW+chinese_number(query("id", room, query("invite/"+me)))+HIW"��"NOR+WHT"���Żݡ�\n"NOR;
        return msg;
}

public int do_buy(object obj, object me, string arg)
{
        mapping goods,goods_num;
        int amount;
        int val_factor;
        mixed value;
        string ob_file, *goods_key;
        object *obs,ob, env;
        string my_id;
        int i;
        object room;

        room = environment(obj);
        if( !query("shop_type", room) )
        {
               tell_object(me, "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n");
               return 1;
        }

        if( query("ban", room) && 
                member_array(query("id", me),query("ban", room)) != -1 )
        {

               tell_object(me, "������ҵ��̲��ܻ�ӭ������޷���������\n");
               return 1;
        }

        if(me->is_busy())
        {
                tell_object(me, "ʲô�¶��õ���æ����˵�ɣ�\n");
                return 1;
        }

        if (! arg)
        {
                tell_object(me, "��Ҫ��ʲô������\n");
                return 1;
        }

        if (sizeof(all_inventory(me)) >= MAX_ITEM_CARRIED)
        {
                tell_object(me, "�����ϵĶ���̫���ˣ��ȴ���һ���������ɡ�\n");
                return 1;
        }

        goods=query("vendor_goods", room);

        if (! goods) goods = ([ ]);

        goods_num=query("vendor_goods_num", room);

        if (!goods_num) goods_num = ([]);

        goods_key = keys(goods);

        if (arrayp(goods_key))
        {
                for (i = 0; i < sizeof(goods_key); i++)
                {
                        if (goods_key[i]->id(arg)) ob_file = goods_key[i];
                        else
                                if (filter_color(goods_key[i]->name(1)) == arg)
                                        ob_file = goods_key[i];
                }
        }

        if (! ob_file)
        {
                tell_object(me, "�õ��̲�û�г����������\n");
                return 1;
        }

        value = goods[ob_file];

        // ����ǹ���������Ż�
        if( query("invite/"+query("id", me, room)) )
        {
                if (intp(value))
                        value=value*query("invite/"+query("id", me, room))/10;
                else
                        value=to_string(to_int(value)*query("invite/"+query("id", me, room))/10);
        }

        ob = new(ob_file);
        call_out("destruct_it", 0, ob);

        if (intp(value))
        {
                switch (player_pay(me, obj, value))
                {
                case 0:
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "��Ц������⵰��һ�ߴ���ȥ��\n" NOR);
                        return 1;

                case 2:
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "��ü����������û����Ǯ������Ʊ�ҿ��Ҳ�����\n" NOR);
                        return 1;

                default:
                        if (ob->query_amount())
                        {
                                message_vision("$N��$n����������" + ob->short() + "��\n", me, obj);
                        }
                        else
                        {
                                message_vision("$N��$n����������һ"+query("unit", ob)+query("name", ob)+"��\n",me,obj);
                        }

                        ob->move(me, 1);
                        goods_num[ob_file] -= 1;

                        if (goods_num[ob_file] == 0)
                        {
                                map_delete(goods, ob_file);
                                map_delete(goods_num, ob_file);
                        }

                        set("vendor_goods", goods, room);
                        set("vendor_goods_num", goods_num, room);
                        addn("all_vendor_goods", -1, room);
                }
        } else
        {
                if (!MEMBER_D->player_pay(me, to_int(value), obj))
                {
                        tell_object(me, CYN + obj->name(1) + NOR + CYN "��Ц������û���㹻��$NT��������ȥ��ֵ�ɡ�\n" NOR);
                        return 1;
                }
                if (ob->query_amount())
                {
                        message_vision("$N��$n����������" + ob->short() + "��\n", me, obj);
                }
                else
                {
                        message_vision("$N��$n����������һ"+query("unit", ob)+query("name", ob)+"��\n",me,obj);
                }

                ob->move(me, 1);
                goods_num[ob_file] -= 1;

                if (goods_num[ob_file] == 0)
                {
                        map_delete(goods, ob_file);
                        map_delete(goods_num, ob_file);
                }

                set("vendor_goods", goods, room);
                set("vendor_goods_num", goods_num, room);
                addn("all_vendor_goods", -1, room);
        }
        me->start_busy(1);
        room->save();
        return 1;
}
*/
public int player_pay(object who, object target, int amount)
{
        object t_ob, g_ob, s_ob, c_ob, owner;
        int tc, gc, sc, cc, left;
        int v;
        int pay_amount;

        seteuid(getuid());

        if (amount >= 100000 && t_ob = present("cash_money", who))
                tc = t_ob->query_amount();
        else
        {
                tc = 0;
                t_ob = 0;
        }

        if (g_ob = present("gold_money", who))
                gc = g_ob->query_amount();
        else
                gc = 0;

        if (s_ob = present("silver_money", who))
                sc = s_ob->query_amount();
        else
                sc = 0;

        if (c_ob = present("coin_money", who))
                cc = c_ob->query_amount();
        else
                cc = 0;

        v = cc + sc * 100 + gc * 10000;

        if (amount < 100000 && v < amount)
        {
                if (present("cash_money", who))
                        return 2;
                else
                        return 0;
        }

        v += tc * 100000;

        if (v < amount)
                return 0;
        else {
                left = v - amount;
                if (tc)
                {
                        tc = left / 100000;
                        left %= 100000;
                }
                gc = left / 10000;
                left = left % 10000;
                sc = left / 100;
                cc = left % 100;

                if (t_ob && ! g_ob && gc)
                {
                        g_ob = new(GOLD_OB);
                        g_ob->move(who, 1);
                }

                if (t_ob)
                        t_ob->set_amount(tc);

                if (g_ob)
                        g_ob->set_amount(gc);
                else
                        sc += (gc * 100);

                if (s_ob)
                {
                        s_ob->set_amount(sc);
                } else
                if (sc)
                {
                        s_ob = new(SILVER_OB);
                        s_ob->set_amount(sc);
                        s_ob->move(who, 1);
                }

                if (c_ob)
                {
                        c_ob->set_amount(cc);
                } else
                if (cc)
                {
                        c_ob = new(COIN_OB);
                        c_ob->set_amount(cc);
                        c_ob->move(who, 1);
                }
                /*
                // ����˰�ʣ�ÿ 10 ���ƽ���� 10% ��˰
                if (amount >= 500000)
                        pay_amount = amount * 5 / 10;
                else if (amount >= 400000)
                        pay_amount = amount * 6 / 10;
                else if (amount >= 300000)
                        pay_amount = amount * 7 / 10;
                else if (amount >= 200000)
                        pay_amount = amount * 8 / 10;
                else if (amount >= 100000)
                        pay_amount = amount * 9 / 10;
                else
                        pay_amount = amount;
                */
                pay_amount = amount * 99 / 100;

                if( owner=query("owner", find_player(environment(target))) )
                {
                        addn("balance", pay_amount, owner);
                        addn("trade_balance", pay_amount, owner);

                        if (query_ip_number(owner) != query_ip_number(who))
                                addn("vendor_score", pay_amount/10000, owner);
                        addn("score", pay_amount/10000, environment(target));
                } else
                {
                        addn("balance", pay_amount, environment(target));
                        addn("score", pay_amount/10000, environment(target));
                }
                log_file("shop_log",sprintf("%-20s��%6s��%9i����",query("name", who)+"("+query("id", who)+")",query("short", environment(who)),amount));
                return 1;
        }
}

public string do_jiezhang(object ob, object me)
{
       int amount;
       object room;

       room = environment(ob);
       if( !query("shop_type", room) )
               return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

       amount=query("balance", room);

       if (amount < 1) return "�����ڵ�ʱ��û���κε����롣\n";

       addn("balance", amount, me);
       addn("trade_balance", amount, me);
       addn("vendor_score", amount/10000, me);

       tell_object(me, HIY"��������ʱ����"+MONEY_D->price_str(amount)+HIY"�����룬����ȫ��ת���������š�\n"NOR);
       set("balance", 0, room);
       room->save();
       return "������ϣ��뼴ʱ�˶���Ŀ��\n";
}

public string list_invite(object ob, object me)
{
        int i;
        string msg, *invite_key;
        mapping invite;
        object room;

        room = environment(ob);
        if( !query("shop_type", room) )
                return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        invite=query("invite", room);

        if (! invite || sizeof(invite) < 1)
                return "����û���趨�κεĹ����\n";

        msg = HIC "��������Ĺ�������¼�λ��\n" NOR;
        msg += HIC "��" HIY "������������������������" HIC "��\n" NOR;
        invite_key = sort_array(keys(invite), 1);

        for (i = 0; i < sizeof(invite_key); i++)
        {
                msg += sprintf(CYN "%-20s  " WHT "%s��\n" NOR,
                               invite_key[i], chinese_number(invite[invite_key[i]]));
        }

        msg += HIC "��" HIY "������������������������" HIC "��\n" NOR;
        msg += HIC "�ܹ��� " HIY + sizeof(invite) + HIC " �������\n" NOR;
        return msg;
}

public string do_invite(object ob, object me, string arg)
{
        int num;
        object body, room;

        room = environment(ob);

        if( !query("shop_type", room) )
                return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        if (! sscanf(arg, "%s %d", arg, num) == 2)
                return "ָ���ʽ��invite <id> <����>\n";

        if (num < 1 || num > 10)
                return "ָ���ʽ��invite <id> <����>\n";

        if (num == 10)
        {
                if( !query("invite/"+arg, room) )
                        return CYN + ob->name(1) + NOR + CYN "����˵�����ϰ壬�� " + arg + " �����Ͳ������ǵ�Ĺ������\n" NOR;

                delete("invite/"+arg, room);
                room->save();
                return CYN + ob->name(1) + NOR + CYN "�����ʲ��û��˻�����Ц�����ϰ壬�Ѿ�������ķԸ�ȡ���� " + arg + " �Ĺ���ʸ��ˡ�\n" NOR;
        }

        if( sizeof(query("invite", room)) >= 30 )
                return "���Ѿ��趨����ʮ��������Ѳ��������Ȼ����ɡ�\n";

        set("invite/"+arg, num, room);
        room->save();

        return CYN + ob->name(1) + NOR + CYN "�����ʲ���д��˵�����ϰ壬�Ѿ�������ķԸ��� " WHT + arg + CYN " ʵ��" + HIY + chinese_number(num) + "��" + NOR + CYN "�Żݡ�\n" NOR;
}

public string list_ban(object ob, object me)
{
        int i;
        string msg, *ban;
        object room;

        room = environment(ob);

        if( !query("shop_type", room) )
               return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        ban=query("ban", room);

        if (! ban || sizeof(ban) < 1)
        {
                msg = "����û���趨�κεĺڻ���\n";
                return msg;
        }
        msg = HIC "��������ĺڻ���������ң�\n" NOR;
        msg += HIC "��" HIY "������������������������" HIC "��\n" NOR;
        for (i = 0;i < sizeof(ban);i++)
        {
                msg += sprintf(CYN "  %s\n" NOR, ban[i]);
        }
        msg += HIC "��" HIY "������������������������" HIC "��\n" NOR;
        msg += HIC "�ܹ��� " HIY + sizeof(ban) + HIC " ���ڻ���\n" NOR;
        return msg;
}

public string do_ban(object ob, object me, string arg)
{
        string the_id, type, *ban;
        object room;

        room = environment(ob);

        if( !query("shop_type", room) )
               return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        ban=query("ban", room);

        if (! ban)
                ban = ({ });

        if (sscanf(arg, "%s %s", type, the_id) == 2 && type == "-")
        {
                if (member_array(the_id, ban) == -1)
                        return CYN + ob->name(1) + NOR + CYN "����˵�����ϰ壬�� " + arg + " �����Ͳ������ǵ�ĺڻ�����\n" NOR;

                ban -= ({ the_id });
                set("ban", ban, room);
                room->save();
                return CYN + ob->name(1) + NOR + CYN "�����ʲ����˻���������Ц�����ϰ壬�Ѿ�ȡ���� " + the_id + " �ڻ���ݡ�\n" NOR;
        }

        if (member_array(arg, ban) != -1)
                return CYN + ob->name(1) + NOR + CYN "��Ц�ŵ����ϰ壬�������ˣ���" + arg + "���ѱ���Ϊ�ڻ�����\n" NOR;

        if( sizeof(query("ban", ob)) >= 30 )
                return "���Ѿ��趨����ʮ���ڻ��������Ȼ���һЩ�ɡ�\n";

        ban += ({ arg });
        set("ban", ban, room);
        room->save();
        return CYN + ob->name(1) + NOR + CYN "�����ʲ���д��˵�����ϰ壬�Ѿ�������ķԸ��� " WHT + arg + CYN " ��Ϊ�˺ڻ���\n"NOR;
}

public string do_order(object ob,object me,string arg)
{
        object room;
        string str;
        string ab;
        string buyer,obname;
        string *clist;

        room = environment(ob);

        if( !query("shop_type", room) )
               return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        if( query("id", me) == query("owner", room) )
        {
                //��������
                if (sscanf(arg,"%s %s",ab,buyer)!=2)
                        return "ɾ������������� order - �˿�id [ĳһ��Ʒ]\n";

                if (ab!="-")
                        return "ɾ������������� order - �˿�id [ĳһ��Ʒ]\n";


                if (sscanf(buyer,"%s %s",buyer,obname)==2)
                {
                        if( !arrayp(query("order/"+buyer, room)) )
                        return "�˿�"+buyer+"��û�ж�������Ʒ��\n";
                        clist=query("order/"+buyer, room);
                        if (member_array(obname,clist)==-1)
                                return "�˿�"+buyer+"��û�ж�����"+HIC+obname+NOR+"������Ʒ��\n";
                        clist -= ({ obname });
                        if (sizeof(clist)>0)
                        set("order/"+buyer, clist, room);
                        else delete("order/"+buyer, room);
                        room->save();
                        return "����˿�"+buyer+"����"+HIC+obname+NOR+"����Ϣ��\n";
                }
                else
                {
                        if( !arrayp(query("order/"+buyer, room)) )
                        return "�˿�"+buyer+"��û�ж�������Ʒ��\n";
                        delete("order/"+buyer, room);
                        room->save();
                        return "����˿�"+buyer+"�����ж�����Ϣ��\n";
                }
        }
        else
        {
                buyer=query("id", me);
                clist=query("order/"+buyer, room);
                if (sscanf(arg,"- %s",arg)==1)
                {
                        if (!arrayp(clist) || member_array(arg,clist)==-1)
                        return "�㲢û�ж���������Ʒ��\n";
                        clist -= ({arg});
                        if (sizeof(clist)>0)
                        set("order/"+buyer, clist, room);
                        else delete("order/"+buyer, room);
                        room->save();
                        return "�������"+HIC+arg+NOR+"����Ϣ��\n";
                }
                if (arrayp(clist))
                {
                        if (member_array(arg,clist)>=0)
                        return "���Ѿ���������"+arg+"��\n";
                        if (sizeof(clist)>20)
                        return "����������̶����Ķ����Ѿ��ܶ��ˣ��ȵ����ȴ�����ɡ�\n";
                }
                else clist = ({});
                clist += ({ arg });
                set("order/"+buyer, clist, room);
                room->save();
                tell_object(find_player(query("owner", room)),"�������µĶ�����Ϣ�ˣ���ȥ����ɡ�\n");
                return "����"+query("short", room)+"������Ʒ"+arg+"�ɹ�����ȴ���������\n";
        }
}
public string list_order(object ob,object me)
{
        mapping orders;
        int i;
        string str;
        string *korder;
        object room;
        string *clist;

        room = environment(ob);
        if( !query("shop_type", room) )
               return "�Բ��𣬸õ���Ŀǰ�Ѿ�����ʦ�رա�\n";

        if( query("id", me) != query("owner", room) && !wizardp(me) )
        {
                clist = query("order/"+query("id", me), room);
                if (!arrayp(clist) || sizeof(clist)<1)
                return "���붨��ʲô��order ��Ʒ����\n";
                str=HIW"���Ѿ���"+query("short", room)+"������������Ʒ��\n"NOR;
                str += implode(clist,"\n");
                str += "\n";
                return str;
        }

        if( !mapp(orders=query("order", room)) || sizeof(orders)<1 )
                return "Ŀǰû���κζ�����Ϣ��\n";

        str = HIG"��ǰ���̶�����Ϣ���£�\n"NOR;
        korder = keys(orders);
        for (i=0;i<sizeof(orders);i++)
        {
                if (arrayp(orders[korder[i]]))
                {
                        str += HIW"���"+korder[i]+"Ҫ����\n"NOR;
                        str += implode(orders[korder[i]],"\n");
                        str += "\n";
                }
        }
        str += HIC"����˿Ͷ�����Ϣ���� order - �˿�id [��Ʒ����]\n"NOR;
        return str;
}

private void destruct_it(object ob)
{
        if (! ob || environment(ob))
                return;

        destruct(ob);
}
public string do_list_all(object me,string arg)
{
        mapping goods, goods_num;
        string *gks;
        string name;
        object *obs, *inv, ob, obj, *all_user;
        string msg, err;
        int i, j, have_vendor = 0;
        int is_ok = 0;
        int have_it = 0;

        mapping price;
        mapping unit;
        mapping count;
        string  short_name;
        string  prefix;
        string  *dk;

        msg = WHT "��̶���е��̣���ѯ���� " + arg + " �Ľ�����£�\n" NOR;
        msg += HIC "��" HIY "��������������������������������������������������������������������" HIC "��\n" NOR;

        for (j = 0; j < sizeof(all_shop); j++)
        {
                have_it = 0;
                name = all_shop[j]["name"] + "(" + all_shop[j]["id"] + ") ��";
                ob = get_object(SHOP_DIR + all_shop[j]["start_room"]);
                if (! ob) continue;
                if( !query("shop_type", ob) )
                {
                        // destruct(ob);
                        continue;
                }
                if( query("ban", ob) && 
                    member_array(query("id", me),query("ban", ob)) != -1 )
                {
                        // destruct(ob);
                        continue;
                }

                if( !query("all_vendor_goods", ob) )
                {
                        // destruct(ob);
                        continue;
                }

                goods=query("vendor_goods", ob);
                if (! goods) goods = ([]);
                goods_num=query("vendor_goods_num", ob);
                if (! goods_num) goods_num = ([]);

                count   = ([]);
                unit    = ([]);
                price   = ([]);

                gks = keys(goods);
                for (i = 0; i < sizeof(gks); i++)
                {
                        object gob;
                        is_ok = 0;
                        err = call_other(gks[i], "???");
                        if (err)
                        {
                                log_file("user_vendor", sprintf("%s ERROR ** \n%s\n", gks[i], err));
                                continue;
                        }
                        if (! objectp(find_object(gks[i])))
                        {
                                log_file("user_vendor", sprintf("No found vendor good:%s\n", gks[i]));
                                continue;
                        }
                        gob = find_object(gks[i]);

                        if (gob->id(arg))
                        {
                                is_ok = 1;
                                have_it = 1;
                        }
                        else if (filter_color(gob->name(1)) == arg)
                        {
                                is_ok = 1;
                                have_it = 1;
                        }

                        if (! is_ok)
                                continue;

                        short_name=gob->name(1)+"("+query("id", gob)+")";
                        if( query("base_unit", gob) )
                                prefix = "base_";
                        else
                                prefix = "";
                        unit+=([short_name:query(prefix+"unit", gob)]);
                        price += ([ short_name : goods[gks[i]] ]);
                        count += ([ short_name : goods_num[gks[i]] ]);
                }
                // destruct(ob);
                if (! have_it) continue;
                dk = sort_array(keys(unit), 1);
                for (i = 0; i < sizeof(dk); i++)
                {
                        int p;
                        p = price[dk[i]];
                        msg += sprintf(" %-6s%" + sprintf("%d", (30 + color_len(dk[i]))) +
                               "-s��ÿ%s" HIY "%s\n" NOR,
                               name, dk[i], unit[dk[i]], MONEY_D->price_str(p));
                }
                msg += "------------------------------------------------------------------------\n";
        }
        msg += HIC "��" HIY "��������������������������������������������������������������������" HIC "��\n" NOR;

        msg += WHT "��̶����С���Ӳ�ѯ���� " + arg + " ������£�\n" NOR;

        msg += HIC "��" HIY "��������������������������������������������������������������������" HIC "��\n" NOR;
        all_user=filter_array(users(),(:query_temp("on_bantan", $1):));
        if (sizeof(all_user))
        {
                for (j = 0;j < sizeof(all_user);j ++)
                {
                        obj = all_user[j];
                        goods=query("vendor_goods", obj);

                        if (! goods) continue;

                        gks = keys(goods);
                        for (i = 0;i < sizeof(gks);i++)
                        {
                                if (! present(query("id", get_object(gks[i])), obj))
                                        map_delete(goods,gks[i]);
                        }

                        set("vendor_goods", goods, obj);
                        goods=query("vendor_goods", obj);

                        if (! goods) continue;

                        gks = keys(goods);
                        for (i = 0; i < sizeof(gks); i++)
                        {
                                object gob;
                                is_ok = 0;
                                call_other(gks[i], "???");
                                if (! objectp(find_object(gks[i])))
                                {
                                        log_file("user_vendor", sprintf("No found vendor good:%s\n", gks[i]));
                                        continue;
                                }
                                gob = find_object(gks[i]);


                                if (gob->id(arg))
                                {
                                        is_ok = 1;
                                        have_it = 1;
                                }
                                else if (filter_color(gob->name(1)) == arg)
                                {
                                        is_ok = 1;
                                        have_it = 1;
                                }

                                if (! is_ok)
                                        continue;

                                short_name=gob->name(1)+"("+query("id", gob)+")";
                                if( query("base_unit", gob) )
                                        prefix = "base_";
                                else
                                        prefix = "";
                                unit+=([short_name:query(prefix+"unit", gob)]);
                                price += ([ short_name : goods[gks[i]] ]);
                        }

                        if (! is_ok) continue;

                        name = obj->name();
                        name += "(" + (environment(obj)?environment(obj)->short():"����") + ")��";
                        dk = sort_array(keys(unit), 1);
                        for (i = 0; i < sizeof(dk); i++)
                        {
                                int p;
                                p = price[dk[i]];
                                msg += sprintf(" %-20s%" + sprintf("%d", (30 + color_len(dk[i]))) +
                                                "-s��ÿ%s%s" CYN "\n" NOR,
                                                name, dk[i], unit[dk[i]], MONEY_D->price_str(p));
                        }
                        msg += "------------------------------------------------------------------------\n";
                }
        }

        msg += HIC "��" HIY "��������������������������������������������������������������������" HIC "��\n" NOR;

        return msg;
}

public string check_shop_status()
{
        int i, profit, tax, all_profit, all_tax;
        object the_shop;
        string msg;

        all_profit = 0;
        all_tax = 0;

        msg = "\n������������" + HIC + LOCAL_MUD_NAME() + "�����̵꣬����Ӫҵ״���б����£�\n" NOR;
        msg += HIC "��" HIY "��������������������������������������������������������������������" HIC "��\n" NOR;
        msg += sprintf(HIC " %-14s%-30s%s\n" NOR,"������","������������","��������˰");
        msg += HIC "��" HIY "��������������������������������������������������������������������" HIC "��\n" NOR;
        for (i = 0;i < sizeof(all_shop);i++)
        {
                the_shop = get_object(SHOP_DIR + all_shop[i]["start_room"]);

                if (! the_shop) continue;

                profit=query("check_shop_profit", the_shop)/10000*10000;
                all_profit += profit / 10000;
                tax=query("check_shop_tax", the_shop)/10000*10000;
                all_tax += tax / 10000;

                msg += sprintf(HIW " %-14s" HIY "%-30s%s\n" NOR,
                               all_shop[i]["name"] + "����",
                               profit ? MONEY_D->money_str(profit) : "��",
                               tax ? MONEY_D->money_str(tax) : "��");

                // destruct(the_shop);
        }
        msg += HIC "��" HIY "��������������������������������������������������������������������" HIC "��\n" NOR;
        msg += sprintf(HIC "%-14s%-30s%s\n\n" NOR,
                       chinese_number(sizeof(all_shop)) + "�ҵ���",
                       chinese_number(all_profit) + "���ƽ�",
                       chinese_number(all_tax) + "���ƽ�");
        return msg;
}


public void reset_goods(object obj)
{
        mapping goods;
        string *gks;
        object ob;
        int i;

        if (! obj ) return;
        goods=query("vendor_goods", obj);
        if (! goods ) return;
        gks = keys(goods);
        for (i = 0; i < sizeof(gks); i++)
        {
                if (!objectp(ob = find_object(gks[i]))  ||
                    !objectp(environment(ob)) ||
                     environment(ob) != obj )
                map_delete(goods, gks[i]);
        }
        set("vendor_goods", goods, obj);
}
string makeup_space(string s,int max)
{
        string *ansi_char = ({
                BLK,   RED,   GRN,   YEL,   BLU,   MAG,   CYN,   WHT,
                BBLK,  BRED,  BGRN,  BYEL,  BBLU,  BMAG,  BCYN,
                       HIR,   HIG,   HIY,   HIB,   HIM,   HIC,   HIW,
                       HBRED, HBGRN, HBYEL, HBBLU, HBMAG, HBCYN, HBWHT,
                NOR
        });

        string space = s;
        int i, space_count;

        for (i = 0; i < sizeof(ansi_char); i ++)
                space = replace_string(space, ansi_char[i], "", 0);

        space_count = sizeof(s) - sizeof(space);
        if (sizeof(s) >= max)
                space_count = max - sizeof(space);

        space = "";

        for (i = 0; i < space_count; i ++) space += " ";
        return space;
}
