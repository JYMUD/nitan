//zsh_dldamen.c

#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "ǰ��");
        set("long", @LONG
���������������ֻ����ڵء����������������֮�ٵõ�����
���ڶ�������ʿ�ĳ��ޣ���а��֮�������ջ̡̻���཭���ú���Ľ
���������������������֮�����Բ��Ϸ�չ׳��
LONG );
        set("outdoors", "dali");
        set("exits", ([    
                "south"  :  "/d/dali/zsh_dlfh",
                "east"   :  "/d/dali/dahejiewest",
        ])); 
        set("objects", ([   
             "/d/suzhou/npc/zsh_guard" : 2,   
            ]));
               
	set("coor/x", -19150);
	set("coor/y", -6900);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "south") 
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