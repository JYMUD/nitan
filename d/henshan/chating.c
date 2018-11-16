inherit ROOM;

void create()
{        
       set("short", "茶亭");        
        set("long", @LONG
这是一家路边的小茶亭，赶山路的人常在此处歇歇脚。亭子里有
几张桌子和几支条凳。周围是一片树林。
LONG );
    
       set("outdoors", "henshan");        

       set("exits", ([                
              "west"  : __DIR__"hsroad6",        
       ]));        

       set("objects", ([                
               __DIR__"npc/yuanziyi" :1,        
       ])); 
      
       set("no_clean_up", 0);        

	set("coor/x", -6920);
	set("coor/y", -5690);
	set("coor/z", 0);
	setup();        
       replace_program(ROOM);
}