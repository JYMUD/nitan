// Room: /d/huangshan/huangshan.c
// Last Modified by winder on Sep. 27 2001

inherit ROOM;
void create()
{
        object con,item;
        set("short", "黃山劍廬");
        set("long", @LONG
好不容易過鐵索，眼前一亮，居然有間茅屋，屋上居然也有牌匾上
書“黃山劍廬”，屋內陳設簡單，一張紅木桌上放着幾冊經卷，筆筒中
稀疏地插着幾隻狼毫，西牆一柄長劍，上書“蒼穹”二字。
LONG
        );
        set("exits", ([ 
                "west" : __DIR__"tiesuo",
        ]));
        set("no_clean_up", 0);
        setup();
}
init()
{
        add_action("do_climb","climb");
}
int do_climb(string arg)
{
        object         me;
        int mlvl;

        if(!arg || arg != "down")
        {
                write("你要往哪裡爬？\n");
                return 1;
        }
        me = this_player();
        message_vision( "\n$N慢慢地向下爬去。\n" , me);
        me->start_busy(4);
        call_out("fliping",4,me);
        me->stop_busy();
        return 1;
}

int fliping(object me)
{
        if( !me->is_ghost())
        {
                me->move(__DIR__"kuzhu");
                message_vision("$N順着崖壁爬了下來。\n", me);
        }
        return 1;
}