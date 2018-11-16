// Written by Lonely@chinamud.cn
// cruise_ob.c

#include <ansi.h>

inherit ITEM;
inherit F_NOCLONE;
inherit F_OBSAVE;

int is_cruise_ob() { return 1; }
int clean_up() { return 1; }
int store_item(object me, object ob, int amount);

class store {
        string name;
        string id;
        string *ids;
        string file;
        mapping data;
        mapping temp_data;
        int amount;
}
nosave class store *all = ({});
mixed query_store() { return all; }

void create()
{
        set_name(HIC"����"HIM"Ǭ����" NOR, ({ "qiankun bag", "qiankun", "bag" }));
        set_weight(100);
        set("long", "һ�����ܱ�Ե���������ع⻷������Ǭ��������ǧ���羡�ɲ������С���˵"
                    "���Խ����������ƵĴ棨store����ȥ,���ᶪʧ��������ʲôʱ�򶼿���ȡ"
                    "��take����������ؼ��ǻ�����ʹ��������Ʒ���ε�����վ��");

        set("unit", "��");
        set("no_sell", 1);
        set("no_get", 1);
        set("no_put", 1);
        set("no_give", 1);
        set("no_store", 1);
        setup();

        ::restore();
}

string extra_long()
{
        mixed ob_name_real_len;
        string msg;

        if( !all || sizeof(all) < 1 )
                return "Ŀǰû�д���κ���Ʒ������Ǭ�����\n";

        msg = HIW "\nĿǰ���ŵ���Ʒ�У�\n���  ��Ʒ                                      ����\n"
                  "����������������������������������������������������������������\n" NOR;
        for( int i=0; i<sizeof(all); i++ ) {
#ifdef LONELY_IMPROVED
                ob_name_real_len = 0;
#else
                ob_name_real_len = color_len(all[i]->name + "(" + all[i]->id + ")");
#endif
                msg += sprintf("[%2d]  %-" + (36 + ob_name_real_len) + "s      %-11d\n",
                               i+1, all[i]->name + "(" + all[i]->id + ")",
                               all[i]->amount);
                if (all[i]->amount == 0)
                        all[i] = 0;
        }
        msg += HIW "����������������������������������������������������������������\n" NOR;
        all -= ({ 0 });
        return msg;
}

void init()
{
        add_action("do_store", ({ "store", "cun" }));
        add_action("do_take",  ({ "take",  "qu"  }));
}

int do_take(string arg)
{
        object me, ob;
        int n, amount, num;
        mapping fun_data;
        string *ks;
        string k;

        me = this_player();

        if( me->is_busy() ) return notify_fail("����æ���ء�\n");

        if( !arg || sscanf(arg, "%d %d", n, amount) != 2 )
                return notify_fail("��ʽ�������� take ��� ���� ��ȡ����Ʒ��\n");

        if( amount < 1 || amount > 10000 )
                return notify_fail("ÿ��ȡ��Ʒ����������С��һͬʱҲ���ܴ���һ��\n");

        if( n < 1 ) return notify_fail("��Ҫȡ�ڼ�����Ʒ��\n");

        if( !all || sizeof(all) < 1 || n > sizeof(all) )
                return notify_fail("�������Ǭ������û�д��������Ʒ��\n");
        n--;
        if( amount > all[n]->amount )
                // return notify_fail("������Ʒ��û����ô�����\n");
                amount = all[n]->amount;

        if( !(ob = new(all[n]->file)) ) {
                all[n] = 0;
                all -= ({ 0 });
                tell_object(me, "�޷�ȡ������Ʒ��ϵͳ�Զ����֮��\n");
                return 1;
        }

        if( me->query_encumbrance() + ob->query_weight() * amount > me->query_max_encumbrance() ) {
                tell_object(me, "��ĸ��ز������޷�һ��ȡ����ô����Ʒ��\n");
                destruct(ob);
                return 1;
        }

        if( ob->query_amount() ) {
                all[n]->amount -= amount;
                if( all[n]->amount == 0 ) {
                        all[n] = 0;
                        all -= ({ 0 });
                }
                ob->set_amount(amount);
                ob->move(me, 1);
                save();

                message_vision("$N������Ǭ������ȡ��һ" +
                                query("unit", ob)+query("name", ob)+"��\n",me);
                return 1;
        }
        destruct(ob);

        if( amount > 100 ) amount = 100;
        all[n]->amount -= amount;
        num = amount;
        while( num-- ) {
                if( !all[n]->data && !all[n]->temp_data ) {
                        ob = new(all[n]->file);
                        ob->move(me, 1);
                        continue;
                }

                if( all[n]->data ) {
                           ob = TEMPLATE_D->create_object(all[n]->file, all[n]->id, all[n]->data);
                           ob->set_name(query("name", ob),all[n]->ids);
                }
                else
                           ob = new(all[n]->file);

                if( all[n]->temp_data )
                        ob->set_temp_dbase(all[n]->temp_data);

                if( mapp(fun_data=query("function", ob)) && sizeof(fun_data)){
                        ks = keys(fun_data);
                        foreach (k in ks)
                                call_other(ob, k, fun_data[k]);
                }

                if( query("bind_owner", ob) && 
                    query("bind_owner", ob) != query("id", me)){
                        all[n]->amount += amount;
                        tell_object(me, ob->name() + "�Ѿ��󶨣��޷��ƶ���\n");
                        destruct(ob);
                        return 1;
                }

                if( query("equipped", ob))delete("equipped", ob);
                ob->move(me, 1);
        }

        message_vision("$N������Ǭ������ȡ��" + chinese_number(amount) +
                        query("unit", ob)+query("name", ob)+"��\n",me);

        if( random(2) )
                me->start_busy(1);

        if( all[n]->amount == 0 ) {
                all[n] = 0;
                all -= ({ 0 });
        }
        save();
        return 1;
}

int do_store(string arg)
{
        int i, amount;
        string item;
        object me, ob1, ob2, *inv;

        me = this_player();

        if( !arg ) return notify_fail("��Ҫ���ʲô������\n");

        if( me->is_busy() ) return notify_fail("������æ���أ�\n");

        if( all && sizeof(all) >= 100 )
                return notify_fail("����Ǭ�������ֻ�ܴ���һ�ٸ����ӣ��������������Ǭ������\n");

        if( arg == "all" ) {
                inv = all_inventory(me);
                inv -= ({ this_object() });
                if( sizeof(inv) > 100 )
                {
                        tell_object(me, "�����ϵ���Ʒ̫���ˣ������׸�죬�㻹��һ��һ����ɡ�\n");
                        return 1;
                }

                if( sizeof(inv) < 1 )
                {
                        tell_object(me, "������û���κ���Ʒ��\n");
                        return 1;
                }

                for( i=0; i<sizeof(inv); i++ )
                        do_store(query("id", inv[i]));
                return 1;
        } else if (sscanf(arg, "%d %s", amount, item) == 2) {
                if( !objectp(ob1 = present(item, me)) )
                        return notify_fail("������û������������\n");

                if( !ob1->query_amount() )
                        return notify_fail(ob1->name() + "���ܱ��ֿ���š�\n");

                if( amount < 1 )
                        return notify_fail("�涫��������������һ����\n");

                if( amount > ob1->query_amount() )
                        return notify_fail("��û����ô���" + ob1->name() + "��\n");

                if( amount == (int)ob1->query_amount() ) {
                        return store_item(me, ob1, amount);
                } else {
                        ob1->set_amount((int)ob1->query_amount() - amount);
                        ob2 = new(base_name(ob1));
                        ob2->set_amount(amount);
                        if( !store_item(me, ob2, amount) ) {
                                ob2->move(me, 1);
                                return 0;
                        }
                        return 1;
                }
        }

        if( !objectp(ob1 = present(arg, me)) )
                return notify_fail("������û������������\n");

        if( ob1->query_amount() )
                return do_store(ob1->query_amount() + " " + arg);

        store_item(me, ob1, 1);
        return 1;
}

int store_item(object me, object ob, int amount)
{
        class store item;
        mapping data, temp_data;
        object obj;
        int i, n;
        string file, name, id;

        if( !objectp(ob) ) {
                error("no this object!\n");
                return 0;
        }

        if( file_size(base_name(ob) + ".c") < 0 )
                return 0;

        if( inherits(F_SILENTDEST, ob) ) {
                tell_object(me,"����Ǭ����������"+query("name", ob)+"�������Լ����ƴ���\n");
                return 0;
        }

        if( member_array(ITEM + ".c", deep_inherit_list(ob)) == -1 &&
            member_array(COMBINED_ITEM + ".c", deep_inherit_list(ob)) == -1 ) {
                tell_object(me,"����Ǭ����������"+query("name", ob)+"�������Լ����ƴ���\n");
                return 0;
        }

        if( query("task_ob", ob) || query("unique", ob) || 
            query("no_store", ob) || ob->is_no_clone() || query("hj_game", ob) || 
            query("maze_item", ob) || ob->is_money() || query("no_put", ob)){
                tell_object(me,"����Ǭ����������"+query("name", ob)+"�������Լ����ƴ���\n");
                return 0;
        }

        if( ob->is_character() || ob->is_item_make() || !clonep(ob) ) {
                tell_object(me,"����Ǭ����������"+query("name", ob)+"�������Լ����ƴ���\n");
                return 0;
        }

        if( sscanf(base_name(ob), "/data/%*s") && !ob->is_inlaid() ) {
                tell_object(me,"����Ǭ����������"+query("name", ob)+"�������Լ����ƴ���\n");
                return 0;
        }

        switch(query("equipped", ob)){
        case "worn":
                tell_object(me, ob->name() + "���������������ܴ�š�\n");
                return 0;
        case "wielded":
                tell_object(me, ob->name() + "�����Ƚ��װ�����ܴ�š�\n");
                return 0;
        }

        if( sizeof(all_inventory(ob)) ) {
                tell_object(me,"�����Ȱ�"+query("name", ob)+"����Ķ������ó�����\n");
                return 0;
        }

        name=query("name", ob);
        file = base_name(ob);
        id=query("id", ob);
        data = ob->query_entire_dbase();
        temp_data = ob->query_entire_temp_dbase();

        map_delete(data, "equipped");
        n = sizeof(all);
        obj = new(file);
        if( !ob->query_amount() && (query("set_data", ob) || !mapping_eqv(temp_data, obj->query_entire_temp_dbase())
        ||  !mapping_eqv(data, obj->query_entire_dbase())) ) {
                destruct(obj);
                for( i=0;i<n;i++ ) {
                        if( all[i]->file == file &&
                            all[i]->id == id &&
                            all[i]->name == name ) {
/*
                                if( mapping_eqv(data, all[i]->data) &&
                                    mapping_eqv(temp_data, all[i]->temp_data) ) {
*/
                                        all[i]->amount += amount;
                                        save();
                                        message_vision("$N����"+chinese_number(amount)+query("unit", ob)+
                                                        query("name", ob)+"������Ǭ�����\n",me);
                                        destruct(ob);
                                        return 1;
/*
                                }
*/
                        }
                }

                item = new(class store);
                item->file = file;
                item->name = name;
                item->id = id;
                item->ids = ob->my_id();
                item->data = data;
                item->temp_data = temp_data;
                item->amount = amount;
                all += ({ item });
                save();
                message_vision("$N����"+chinese_number(amount)+query("unit", ob)+
                                query("name", ob)+"������Ǭ�����\n",me);
                destruct(ob);
                return 1;
        }
        destruct(obj);

        for( i=0;i<n;i++ ) {
                if( all[i]->file == file &&
                    all[i]->id == id &&
                    all[i]->name == name /*&&
                    !all[i]->data && !all[i]->temp_data*/ ) {
                        all[i]->amount += amount;
                        save();
                        message_vision("$N����"+chinese_number(amount)+query("unit", ob)+
                                        query("name", ob)+"������Ǭ�����\n",me);
                        destruct(ob);
                        return 1;
                }
        }

        item = new(class store);
        item->file = file;
        item->name = name;
        item->id = id;
        item->ids = ob->my_id();
        item->amount = amount;
        all += ({ item });
        save();
        message_vision("$N����"+chinese_number(amount)+query("unit", ob)+
                        query("name", ob)+"������Ǭ�����\n",me);
        destruct(ob);
        return 1;
}

int receive_summon(object me)
{
        object env;

        if( (env = environment()) && env == me ) {
                write(name() + "����������������ٻ���ʲô����\n");
                return 1;
        }

        if( env == environment(me) ) {
                message_vision(HIG "ֻ�����ϵ�" + name() +
                               HIG "����һ����â����Ծ��$N" HIW
                               "�����У�\n\n" NOR, me);
        } else {
                if( env ) {
                        if( env->is_character() && environment(env) )
                                env = environment(env);

                        message("vision", HIG "ͻȻ" + name() + HIG "����һ��"
                                HIG "��â��ʧ�ˣ�\n\n" NOR, env);

                        if( interactive(env = environment()) ) {
                                tell_object(env, HIM + name() +
                                                 HIM "��Ȼ�����ȥ�ˣ�\n" NOR);
                        }
                }

                message_vision(HIG "һ����â������ֻ��$N"
                               HIG "���ж���һ��$n" HIG "��\n\n" NOR,
                               me, this_object());
        }

        //move(me, 1);
        if( !this_object()->move(me) )
                tell_object(me, HIR "������ĸ���̫�ߣ�"+this_object()->name()+HIR "����һ����â����Ȼ�����ټ���\n" NOR);
        return 1;
}

int hide_anywhere(object me)
{
        if( query("jingli", me)<100){
                tell_object(me, "����ͼ��" + name() +
                            "��ȥ�����Ǿ������ã����Է�������������\n");
                return 0;
        }
        addn("jingli", -100, me);

        message_vision(HIM "$N" HIM "����һ��" + name() +
                       HIM "����Ȼ�����ټ���\n", me);
        save();
        destruct(this_object());
        return 1;
}

int receive_dbase_data(mixed data)
{
        if( !mapp(data) || sizeof(data) < 1 )
                return 0;

        if( data["all"] )
                all = data["all"];

        return 1;
}

mixed save_dbase_data()
{
        mapping data;

        data = ([]);

        if( sizeof(all) > 0 )
                data += ([ "all" : all ]);

        return data;
}
