//room: /d/btshan/restroom.c
inherit ROOM;

void create()
{
        set("short","藥房");
        set("long", @LONG
這裡是間藥房，靠牆放着一隻大葯櫃。屋子裡有張桌子，上邊擺
滿了煉藥用的瓶瓶罐罐。其中一個藥瓶(bottle)里只裝了清水。煉藥
師是位小姑娘，正在那裡發獃，不知在想什麼。北面是氣派的長廊。
LONG );

        set("exits",([
                "north" : __DIR__"changlang",
        ]));

        set("item_desc",([
                "bottle" : "藥罐上貼着標籤：『蛇膽膏』，乃珍"
                           "貴補品，生精補氣，效果奇佳。\n",
        ]));

        set("objects",([
                __DIR__"npc/xiaoqing" : 1,
        ]));

        set("coor/x", -49980);
        set("coor/y", 20020);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}