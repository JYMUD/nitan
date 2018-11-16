//By rama@lxtx

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{ 
        set("short", HIG"����"NOR);
        set("long", @LONG
��Ȼ��ɫһת��ǰ������һƬ��������֡��㿴���˿����ܣ�
������Χ��Щ�ط���̫��ͷ������ȴ˵�ϲ����������������ƺ���Щ
�������������׸���ô���أ��㲻�ɳ��������
LONG );
        set("outdoors", "yangzhou");
        set("exits", ([
                "east" :  __FILE__,
                "west" :  __FILE__,
                "south" : __FILE__,
                "north" : __FILE__,
        ])); 
/*        set("objects", ([   
             "/d/city/npc/xdh-guard" : 2,   
            ]));
            */   
	set("coor/x", -10);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();            
}


int valid_leave(object me, string dir)
{
        int total_steps;

        if( query("bunch/bunch_name", me) == "С����" )
        {
                total_steps = 1; 
        } else
                       
                total_steps = 20;
        
        if (dir == "north")
                addn_temp("shulin/steps", 1, me);

        if (dir == "south")
                addn_temp("shulin/steps", -1, me);

        if( query_temp("shulin/steps", me) == total_steps )
        {
                me->move("/d/city/xdhzb");
                delete_temp("shulin/steps", me);
                write("�����ڵ���С���ᡣ\n");
                return -1;
        }  

        if( query_temp("shulin/steps", me) == -total_steps )
        {  
                me->move("/d/city/shulin1");
                delete_temp("shulin/steps", me);
                write("�����˰����ֻص���ԭ�ء�\n");
                return -1;
        }

        return ::valid_leave(me,dir);
}