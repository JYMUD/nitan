#include <ansi.h>
inherit ROOM;

void message_competition(string msg);
void create()
{
        set("short", "猴子望月");
        set("long", @LONG
此处原是一仞高耸入云的峭壁，不知何年由人从峭壁的半腰硬是
开出一条栈道来，栈道旁有一粗十余丈的擎天石柱，石柱顶生一松，
松旁有一天生奇石，宛如翘首望月的猴子。 
LONG );
        set("exits", ([ /* sizeof() == 3 */
                "southdown" : __DIR__"liyubei",
/*
                "northup" : "/adm/npc/huashanjueding",
                "up" : "/adm/npc/kantai",
                "1" : "/adm/npc/biwu1",
                "2" : "/adm/npc/biwu2",
                "3" : "/adm/npc/biwu3",
                "4" : "/adm/npc/biwu4",
*/
        ]));

        set("outdoors", "huashan" );

        set("no_fight", 1);
        setup();
}

void init()
{
        if (wiz_level(this_player()) >= 3)
        {
                add_action("do_open", "open");
                add_action("do_close", "close");
        }
}

int do_open()
{
        object me = this_player();

        if (query("exits/up"))
                return notify_fail("门已经是开着的了。\n");

        set("exits", ([ /* sizeof() == 3 */
                "southdown" : __DIR__"liyubei",
                "northup" : "/adm/npc/huashanjueding",
                "up" : "/adm/npc/kantai",
                "1" : "/adm/npc/biwu1",
                "2" : "/adm/npc/biwu2",
                "3" : "/adm/npc/biwu3",
                "4" : "/adm/npc/biwu4",
        ]));

        message_vision(HIY "$N" HIY "轻轻一推，将通向武林大会会场的"
                       "大门开启了。\n" NOR, me);

        shout(HIY "【华山论剑】" NOR + WHT + me->name() + WHT "[" +
              query("id", me)+WHT"]开启了华山绝顶的武林大会会场。\n"NOR);

        return 1;
}

int do_close()
{
        object me = this_player();

        if (! query("exits/up"))
                return notify_fail("门已经是关着的了。\n");

        set("exits", ([ /* sizeof() == 3 */
                "southdown" : __DIR__"liyubei",
        ]));
        message_vision(WHT "$N" WHT "顺手一带，将通向武林大会会场的"
                       "大门关上了。\n" NOR, me);
        return 1;
}

void message_competition(string msg)
{
        CHANNEL_D->channel_broadcast("rumor", msg);
}

int valid_leave(object me, string dir)
{
        int i;
        object *inv;
        int age=query("age", me);

        if (dir == "southdown" || dir == "up")
                return 1;
                
        inv = deep_inventory(me);

        if( dir != "northup" )
        for(i=sizeof(inv)-1; i>=0; i--)
        {
                if (me->query_condition("killer"))
                        return notify_fail("杀人者不可以进入比武场！！！\n");

                if (! wizardp(me) &&
                    inv[i]->is_cruise_ob())
                        return notify_fail("不可以携带"+inv[i]->name(1)+"进入比武场！！！\n");

                if (! wizardp(me) &&
                    inv[i]->is_item_make())
                        return notify_fail("不可以携带"+inv[i]->name(1)+"进入比武场！！！\n");

                if (! wizardp(me) &&
                    query("weapon_prop", inv[i]) )
                        return notify_fail("不可以携带"+inv[i]->name(1)+"进入比武场！！！\n");

                if (! wizardp(me) &&
                    query("armor_prop", inv[i]) )
                        return notify_fail("不可以携带"+inv[i]->name(1)+"进入比武场！！！\n");
                /*
                if (! wizardp(me) &&
                    query("id", inv[i]) == "tang hua" )
                        return notify_fail("不可以携带暗器唐花进入比武场！！！\n");
                */
        }

        if (wizardp(me)
/*
        ||  (dir == "1" && age < 21) 
        ||  (dir == "2" && (age >= 21 && age < 31)) 
        ||  (dir == "3" && ( age >= 31 && age < 41)) 
        ||  (dir == "4" && age >= 41)) 
*/
        ||  (dir == "1" && query("level", me) >= 10 && query("level", me) <= 30) 
        ||  (dir == "2" && query("level", me) >= 31 && query("level", me) <= 50) 
        ||  (dir == "3" && query("level", me) >= 51 && query("level", me) <= 70) 
        //||  (dir == "4" && query("level", me) >= 71 && query("level", me) <= 90))
        ||  (dir == "4" && query("level", me) >= 10 && query("level", me) <= 200))
        {
                /*
                message_competition((ultrap(me) ? "大宗师" : "") +
                            me->name(1) + "进入华山绝顶的武林大会会场。");
                */
                return 1;
        }
        if (dir == "northup")
        {
                /*
                message_competition((ultrap(me) ? "大宗师" : "") +
                            me->name(1) + "进入华山绝顶的武林大会会场。");
                */
                if (me->query_condition("killer"))
                        return notify_fail("杀人者不可以进入比武场！！！\n");
                return 1;
        }
        return notify_fail("你不可以到那边比武！！\n");
}

