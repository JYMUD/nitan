// /d/gaoli/xingguan
// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "內堂");
        set("long", @LONG
這裡是武士行館的內堂，梁間有一塊匾，上寫着一個大大的「武」
字，堂上布置肅穆，兩壁懸着長劍，腰刀。地下沒有桌椅，地上放着幾
個蒲團。
LONG);
set("exits", ([
                "out":__DIR__"xingguan"
        ]));
   set("objects",([
      __DIR__"obj/changjian":3,
      ]));
       setup();
        replace_program(ROOM);
}        
