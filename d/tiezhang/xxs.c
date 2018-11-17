#include <room.h>
inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是一個黑不透光的大房間。所有的窗戶都用厚厚的帘子遮住，不露絲
毫光亮。屋內整齊的排列着十幾張木板搭成的床鋪，可以讓練功後的幫眾及
時得到休息。這裡靜悄悄的，黑暗中偶爾傳來清微的鼾聲。
LONG    );

        set("exits", ([
                "south" : __DIR__"zoulang-4",
        ]));

        create_door("south", "木門", "north", DOOR_CLOSED);

        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_clean_up", 0);

        setup();
}