#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",  "�����" );
        set("long", @LONG
�����ڱ�����ϣ������������˺��٣�������һ����ΰ��
���ţ��Ǿ���ƽ����������Ĺ�ۡ�ˡ�·��������������Ŵ�
�����Ե�ʮ��Ư������ʱ���м������������߶���
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "south" : __DIR__"jinrilou",
                "north" : __DIR__"wangfu",
        ]));
        set("objects", ([
                "/d/beijing/npc/boy2" : 1,
        ]));
	set("coor/x", -16840);
	set("coor/y", -7200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
       
}