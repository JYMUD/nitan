#include <room.h>

inherit ROOM;

void create()
{ 
        set("short", "��  ��");
        set("long", @LONG
�����������������ܲ��Ĵ��ţ�һ�����ӭ����չ�����顺����
�񾡡��ĸ����֡�
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "west" :  __DIR__"jiekou2",
                "north" : __DIR__"xym_dating",
        ])); 
        set("objects", ([   
             __DIR__"npc/xym_guard" : 2,   
            ]));
               
        setup();            
}

int valid_leave(object me, string dir) 
{ 
        if (objectp(present("shou wei", environment(me))) && dir == "north") 
        {
           if( !query_temp("good_xym1", me) && query("bunch/bunch_name", me) != "������" )
               return notify_fail("����һ����ס�㣬�����ȵ��������������������˵���������\n"); 
           else
           {
              delete_temp("good_xym1", me);
              return ::valid_leave(me, dir);
           }
        }
        return ::valid_leave(me, dir); 
} 
