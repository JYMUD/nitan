#include <ansi.h>

inherit ROOM;

#define PLACE "cd"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "�����˳ɶ��ֶ�");
        set("long", @LONG
�����������˵ĵĳɶ��ֶ棬�������⼸������ȸ��һ�����
�󵱼�������棬��һ����Ҳ������ֶ����ķ��Ĳ����Ƿֲ����ģ�
�˼�Ķ������ǳ���ư���ӵĽ����ܣ��˳��񶼴����ĺ��塣����
��ǽ�Ϲ��������ƣ�paizi����
LONG );

        set("objects", ([
               __DIR__"npc/boss-hong"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "west" : __DIR__"xym_cdfb",
        ]));

        set("coor/x", -15180);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>