// wuchang.c

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIR "無常丹" NOR, ({"wuchang dan", "dan"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這是一顆晶瑩火紅的無常丹，是桃花島精心練制的奇"
                            "葯。\n" NOR);
                set("base_unit", "顆");
                set("base_value", 8000);
                set("base_weight", 70);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "tianqi"   : 1,
                                    "honghua"  : 1,
                                    "moyao"    : 1,
                                    "xiongdan" : 1,
                                    "heshouwu" : 2,
                                    "renshen"  : 2,
                                    "zzfen"    : 1,
                                    "hugu"     : 1,
                                    "xuejie"   : 1,
                                    "xuelian"  : 1 ]),
                        "neili" : 400,
                        "jing"  : 60,
                        "time"  : 8,
                        "min_level" : 150,
                        "taohua-yaoli" : 250,
                ]));
        }
        setup();
}

int do_effect(object me)
{
        mapping my;

        if( time()-query_temp("last_eat/wuchang", me)<180 )
        {
                write("你剛服用過葯，需藥性發揮完效用以後才能繼續服用。\n");
                return 1;
        }

        set_temp("last_eat/wuchang", time(), me);

        message_vision(HIR "$N" HIR "吞下無常丹，臉色泛一陣紅暈。\n" NOR, me);
        tell_object(me, HIY "你只覺得真氣充沛，幾乎就要澎湃而出。\n" NOR);

        log_file("static/using", sprintf("%s(%s) eat 無常丹 at %s.\n",
                 me->name(1),query("id", me),ctime(time())));

        my = me->query_entire_dbase();
        my["neili"] = my["max_neili"] * 2;

        me->start_busy(3);

        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}
