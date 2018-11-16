//zsh_szdamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "������ǰ��");
        set("long", @LONG
�������������ܲ����ڵء��������ڽ������ж����أ���������
֮�٣���཭���ú���Ľ��������
LONG );
        set("outdoors", "suzhou");
        set("exits", ([
                "south"  :  __DIR__"hehuating",
                "north"  :  __DIR__"zsh_szzb",
        ])); 
        set("objects", ([   
                __DIR__"npc/zsh_guard" : 2,   
        ]));
               
	set("coor/x", 1090);
	set("coor/y", -1070);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
        {
           if( !query_temp("good_zsh", me) && query("bunch/bunch_name", me) != "������" )
               return notify_fail("����һ����ס�㣺���������᲻��ӭ���ˣ���ذɣ���\n"); 
           else
           {
              delete_temp("good_zsh", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 