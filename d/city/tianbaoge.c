// This program is a part of NT MudLIB

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "�챦��");
        set("long", @LONG
����ר���з��и����ֻ����鼮�̱������л��в������ѵ�һ����
�䱾����������õ����ϰ徭Ӫ���ƶ����ա��ڴ�֮��������ĳ��ְ�
�������¹�������棬����֪Ϊ���ְ����ˡ�����������ս��˵����£�
����Ŀǰ��û�й���Ա����ֻ���ϰ�������һ���޾���ɵ����ţ�����
�����(shelf) ���߰������һЩ���ᣬ�߶���������һ���������µ�
�о���
LONG );
        set("region", "yangzhou");
        set("exits", ([
                "south" : __DIR__"xidajie3",
        ]));

        set("objects", ([
                __DIR__"npc/bookboss" : 1,
        ]));

        set("no_fight", 1);
        set("no_sleep", 1);
        set("day_shop", 1);
        set("item_desc", ([
                "shelf"  : "����϶������飬��Щ�Ѿ������������á�\n",
        ]));

	set("coor/x", -30);
	set("coor/y", 10);
	set("coor/z", 0);
	setup();
}