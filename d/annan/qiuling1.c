#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","丘陵");
  set ("long", @LONG
這裡是安南城南的一片丘陵地，丘陵起伏不平，紅褐色的岩石奇型
怪狀，沙石路到這裡逐漸隱沒於丘陵之中，因為這附近有強人出沒，行
人幾乎都不到這裡來。
LONG);

  set("exits", ([ 

  "southwest":__DIR__"tulu3",
  "northeast":__DIR__"qiuling2",  
       ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
