// Code of ShenZhou
// shegu.c �߹�
// maco 7/15/2000

#include <ansi.h>
inherit ROOM;
string look_crack();

void create()
{
        set("short", "�߹�����");
        set("long", @LONG
���ǰ���ɽ�߹��е�һ�����֣��Ӳݴ�������ľ֦��ï�ܣ��İ�
��ɭ����ľ�̸���ڣ���Щ��������ѷ� (crack)������ϸ���������
�����Ǵ�Ƭ�ĵأ����߹�����Σ�յĵش���
LONG );

        set("exits", ([
            "northwest" : __DIR__"shegu31",
            "east" : __DIR__"shegu_maze2",
            "southwest" : __DIR__"shegu23",
        ]));

        set("item_desc", ([
        "crack" : (: look_crack :),
        ]));

        set("objects", ([
            __DIR__"obj/branch"+(1+random(4)) : 1,
        ]));

        set("hide_snake", 1+random(3));
        set("grass", 1);
        set("crack", 1);

        set("cost", 2);
        set("outdoors","baituo");
        set("shegu", 1);
        set("coor/x", -50020);
        set("coor/y", 20210);
        set("coor/z", 20);
        setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "east") {
                if( query("family/family_name", me) == "����ɽ"
                 && !query_temp("shegu/warning_24", me)){
                        set_temp("shegu/warning_24", 1, me);
                        return notify_fail( HIR"�������߹��д��������û�Ļĵأ������ﰵ�Ծ��裬����С�Ľ�����\n"NOR+"��������׼���Ļ������ٴ�ǰ���ɡ�\n");
                }
        }
        return ::valid_leave(me,dir);
}

#include "snake_room.h"