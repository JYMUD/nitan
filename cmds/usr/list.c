#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
        mapping goods;
        string *gks;
        object *obs, obj, env, *inv;
        string msg;
        int i, have_vendor = 0;

        mapping price;
        mapping unit;
        string short_name;
        string prefix;
        string *dk;

        env = environment(me);

        if (! arg)
        {
                inv = all_inventory(env);

                if (! inv)
                        return notify_fail("這裡並沒有任何在擺攤的商人。\n");

                msg = HIC "現在這裡的小攤子有："
                      HIY "\n──────────────\n" NOR;
                for (i = 0; i < sizeof(inv); i++)
                {
                        if( userp(inv[i]) && query_temp("on_baitan", inv[i]) )
                        {
                                have_vendor = 1;
                                msg += WHT + inv[i]->name(1) + "的雜貨攤(" +
                                       query("id", inv[i])+")\n";
                        }
                }
                if (! have_vendor) 
                        msg = WHT "目前這裡並沒有任何擺攤的商人。\n" NOR;
                else
                        msg += HIY "──────────────\n" NOR;
                write(msg);
                return 1;
        }

        if (! (obj = present(arg, env)) || ! userp(obj))
                return notify_fail("這裡並沒有這個商人。\n");

        if( !query("is_vendor", obj) )
                return notify_fail(obj->name(1) + "並不是商人。\n");

        if( !query_temp("on_baitan", obj) )
                return notify_fail(obj->name(1) + "目前並沒有在擺攤。\n");

        goods=query("vendor_goods", obj);

        if (! goods)
                return notify_fail(obj->name(1) + "目前並沒有兜售任何貨物。\n");

        gks = keys(goods);

        for (i = 0; i < sizeof(gks); i++)
        {
                if (! present(query("id", get_object(gks[i])), obj))
                        map_delete(goods, gks[i]);
        }

        set("vendor_goods", goods, obj);
        goods=query("vendor_goods", obj);

        unit = ([]);
        price = ([]);

        gks = keys(goods);

        for (i = 0; i < sizeof(gks); i++)
        {
                object gob;
                call_other(gks[i], "???");

                if (! objectp(find_object(gks[i])))
                {
                        log_file("user_vendor", sprintf("No found vend"
                                 "or good:%s\n", gks[i]));
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
        }

        msg = HIC + obj->name(1) + "目前出售以下物品："
              HIY "\n─────────────────────────\n" NOR;
        dk = sort_array(keys(unit), 1);

        for (i = 0; i < sizeof(dk); i++)
        {
                int p;
                p = price[dk[i]];

                msg += sprintf("%" + sprintf("%d", (30 + color_len(dk[i]))) +
                               "-s：每%s%s" CYN "\n" NOR, 
                               dk[i], unit[dk[i]], MONEY_D->price_str(p));
        }
        msg += HIY "─────────────────────────\n" NOR;
        write(msg);
        return 1;
}       

int help (object me)
{
        write(@HELP
指令格式: list <ID>
 
列出一個玩家商人正在出售的商品。
 
HELP);
        return 1;
}
