#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIR "牛气冲天新年红包" NOR, ({ "hongbao2009"}) );
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "这一是个新年红包，上面用金色的字体写着" HIY "「牛年快乐，牛气冲天」" HIR " ！\n"
                                "拆开(chai)红包可以获得新年压岁钱及小小的经验潜能奖励。并有机会获得随机物品一件。\n"
                                "*请于2009年3月1日前使用红包，过期则使用无效！！！\n\n" NOR);
                set("value", 0);
                set("no_give", 1);
                set("no_sell", 1);
                set("no_store", 1);
                set("no_drop", 1);
                set("unit", "个"); 
        }
}

void init()
{
        add_action("do_chai", "chai");
}

int do_chai(string arg)
{
        object me = this_player();
        string msg;
        int i, exp, pot;
        object obgift;
        
        string *oblist = 
        ({
                "/clone/fam/gift/dex3",
                "/clone/fam/gift/con3",
                "/clone/fam/gift/int3",
                "/clone/fam/gift/str3",
                "/clone/fam/gift/dex2",
                "/clone/fam/gift/con2",
                "/clone/fam/gift/int2",
                "/clone/fam/gift/str2",                
                "/clone/fam/max/naobaijin",
                "/clone/fam/item/jintiao",
                "/clone/fam/item/moye-shengfu",
                "/clone/armor/fusang/shenxing-xue",
                "/clone/armor/qilin/jixing",
                "/clone/armor/fudai",
                "/clone/armor/shuixian-erhuan",
        });

        // 新手村的拿不到
        if (! objectp(me))return 0;

        if (! arg || arg != "hongbao2009")
                return notify_fail("你要拆开什么？\n");

        if (environment(this_object()) != me)
                return notify_fail("你身上没有这样东西呀。\n");

        i = 12009;
        exp = 102009;
        pot = 102009;

        message_vision(HIR "$N一阵兴奋，赶紧将红包拆开，用无比期待地眼神朝红包内一望，刹那间，一阵光环"
                       "将$N笼罩 ……\n" NOR, me);

        tell_object(me, HIG "恭喜你，获得了" HIY + chinese_number(exp) + HIG "点实战经验、" HIY + chinese_number(pot) + 
                        HIG "点潜能及" HIY + chinese_number(i) + HIG "两黄金（YSG）。\n炎黄祝您「牛年快乐，牛气冲天」！\n" NOR);

        me->add("stocks/balance", i);
        me->add("combat_exp", exp);
        me->add("potential", pot);

        // 10%机率获取随机物品一件
        if (random(10) == 1)
        {
                obgift = new(oblist[random(sizeof(oblist))]);
                if (obgift)
                {
                        tell_object(HIY "恭喜你，从红包中获得" + obgift->name() + HIY "，恭喜恭喜！。\n" NOR);
                        CHANNEL_D->do_channel(this_object(), "rumor", "听说" + me->name() + "开启新年红包获得随"
                                                                    "机物品" + obgift->name() + HIM "奖励！\n");  
                        obgift->move(me, 1);
                        log_file("hongbao2009", HIY + me->query("id") + "从红包中获得 " + obgift->name() + "。\n" NOR);
                }
        }

        me->save();

        log_file("hongbao2009", me->query("id") + " 于 " + ctime(time()) + " 打开红包。(/clone/misc/hongbao2009) \n");

        destruct(this_object());
        return 1;
}

int query_autoload()
{
        return 1;
}
