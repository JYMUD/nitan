//1997-3-10 by qyz
#include <room.h>

inherit DOOR_ROOM;



void create()
{
        set("short","����̨");
        set("long",@LONG
���������ɽ�ľ������·����ţ�����ϼ���ഫΪ�Ƶ��ڵ�̳���ұ߾���
������Ԩ���ڴ˵Ǹ�һ������ɽ��Ӧ��������������������������ǰ���繰
��Ҿ���Ʊ���������ƽԶ��㡣�������������ۿ��ճ�����Ϊ��ۡ�
LONG);
        set("exits",
        ([
          "south" : __DIR__"lingzhi_yuan",
          "west" : __DIR__"xianren_qiao",
                ]));
        create_door("south",([
                                "name" : "Сľ��",
                                "lock" : "lock001",
                                "status" : 3,
                                "id"  : ({ "south","Сľ��","door",}),
                                "other_side_dir" : "north",
                                ]),
                        "north");
        set("outdoors","kongdong");
        setup();
}

void reset()
{
        if( !random( 5) )
        set("objects", ([
                                __DIR__"npc/wuming" : 1,
                ]) );
        ::reset();
}
