#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "�찲�Ź㳡");
        set("long", @LONG
��������찲�Ź㳡����ɫ�ĳ�ǽ������ׯ������֮�У�������
ͨ����ˮ�ž��ǻʹ��Ͻ����ˡ�ԶԶ��ȥ���Ͻ��ǵ������淢�Ե���
ΰ�ߴ�һ�����Ǻ��ƳǶ�����һ����ֱ����ʯ�����ᶫ��������
�Ƕ������ֹ㳡���������������ֹ㳡���ϱ��ǿ��������ĳ����ֹ�
�������Ͼ���������һֱ��������̳�������š�
LONG );
        set("exits", ([
                "south" : "/d/beijing/cagc_s",
                "north" : "/d/beijing/qiao",
               "west" : "/d/beijing/cagc_w",
              "east" : "/d/beijing/cagc_e",
        ]));
        set("objects", ([
                "/d/beijing/npc/maiyi2" : 1,
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/old2" : 1,
                "/d/beijing/npc/kid1" : 1,
                "/clone/npc/walker"  : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7670);
	set("coor/z", 0);
	setup();
}


void init()
{
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/rideto");
}

