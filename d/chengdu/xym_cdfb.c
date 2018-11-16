#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "������ǰ");
        set("long", @LONG
�����������˳ɶ��ֲ��Ĵ���ǰ�棬�����˵ĳɶ��ֲ�����λ��
���ã���ӳ����ɽ��ˮ֮�䡣����һ����߷��Ľ��������˾���һ
�������ƴ������֮�䡣          
LONG );
        set("outdoors", "chengdu");
        set("exits", ([
                "west" :  __DIR__"eastroad3",
                "east" : __DIR__"xym_cddt",
        ])); 
        set("objects", ([   
             __DIR__"npc/xym-guard" : 2,   
            ]));
               
        set("coor/x", -15190);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "east") 
        {
           if( !query_temp("good_xym2", me) && query("bunch/bunch_name", me) != "������" )
               return notify_fail("����һ����ס�㣬�����ȵ��������������������˵���������\n"); 
           else
           {
              delete_temp("good_xym2", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 