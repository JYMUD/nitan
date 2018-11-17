// /d/gaoli/xuanwumen
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "北烽火台");
        set("long", @LONG
這裡是高麗的東烽火台。這裡用來檢查邊境的情況，以及時傳遞戰
況。再往南邊走，就是高麗的玉龍門了。這裡戒備森嚴，有幾個官兵在
這裡檢查來往的行人。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "southdown" : __DIR__"shanlu13",
                //"northup":__DIR__"beifenghuotai",
        ]));
        set("objects",([
         __DIR__"npc/bing":2,
         ]));
       setup();
        
}

int valid_leave(object ob,string dir)
{
  if(ob->query_temp("gaoli_xunluo"))
    ob->add_temp_array("xunluo_dir","beifenghuotai");
  return ::valid_leave(ob,dir);
}
