#include <ansi.h>

inherit ROOM;

#define PLACE "xy"
#define TYPE  "good"

int sort_by_id(mapping quest1, mapping quest2);

void create()
{
        set("short", "�޼����ܶ�");
        set("long", @LONG
�������޼���Ĵ�����ֻ�������޼����������ǿ���Ҹ߸ߵ���
 ���š���ֻ���Ϻ���ľ���ɵĺ��ң�������֣�д���޼����������֡�
 ľ����������������������֡��䵱����ɽ�����ˣ�Ľ���������ˡ�
 ؤ�������������������Ȩ�Ƶ����Ҳ����Ϊ���������ң���
 �����޼������ƴ�ʢ����཭����Ů�׷�Ľ���������޼���ٲȻһ��
 ���ֵ�һ������ơ�ǽ�Ϲ���һ�������ƣ�paizi���� 
LONG );

        set("objects", ([
               __DIR__"npc/boss-jin"   : 1,
        ]));

        set("no_fight",1);

        set("exits", ([
                "south" : __DIR__"wjb_damen",
        ]));

        set("coor/x", -7780);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
}
#include <bang_good.h>