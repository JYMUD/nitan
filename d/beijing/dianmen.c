#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIY"�ذ��Ź㳡"NOR);
        set("long", @LONG
������ǵذ��Ź㳡����ɫ�ĳ�ǽ������ׯ������֮�У�����ͨ
���Ͻ��ǵĵذ��ž��ǳǽ��ˡ�ԶԶ��ȥ���Ͻ��ǵ������淢�Ե���
ΰ�ߴ�һ�����Ǻ��ƳǶ�����һ����ֱ����ʯ�����ᶫ��������
�ǵذ��Ŷ��ֹ㳡�������ǵذ������ֹ㳡���ϱ�ͨ��һ��С�ž���
�ʹ��ı����ˡ�[2��37��0m
LONG );
        set("exits", ([
                "south" : "/d/beijing/hgmen_n",
                "north" : "/d/beijing/di_dajie1",
               "west" : "/d/beijing/di_xigc",
              "east" : "/d/beijing/di_donggc",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing1" : 2,
                "/d/beijing/npc/bing3" : 1,
                "/d/beijing/npc/old2" : 1,
                "/d/beijing/npc/kid1" : 1,
                "/clone/npc/walker"  : 1, 
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7720);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}