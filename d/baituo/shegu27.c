//Cracked by Roath
// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;

void create()
{
        int i;

        set("short", "ɽ��");
        set("long", @LONG
����һ�������εĹ��ȣ������±��ϳ����˱�ֱ�İ������ɼ��
��ľ���ٲ�ֱ�䣬���������´ܣ�ˮ����ɢ��������·�����ʪ�ˡ�
����������Ԩ��ǰ���Ƕ��͵��±ڣ������߹ȵľ�ͷ��û�е�·����
�ˡ�
LONG );

        set("exits", ([
            "south" : __DIR__"shegu26",
        ]));

        i = random (50);

        if( i < 20 )
        set("objects", ([
           // "/clone/drug/lingzhi" : 1,
           "/clone/drug/danggui" : 1,

        ]));

        else if( i < 30 ) set("objects", ([
            __DIR__"obj/branch4" : 1,
            __DIR__"npc/maque" : 1,
        ]));

        else if( i < 40 ) set("objects", ([
            __DIR__"npc/bt_snake" : 2,
        ]));

        else set("objects", ([
            __DIR__"obj/branch1" : 1,
            __DIR__"npc/pu_snake" : 1,
        ]));

        set("cost", 1);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -49980);
        set("coor/y", 20230);
        set("coor/z", 20);
        setup();
}

void init()
{
        set("enter_shegu", 1, this_player());
}