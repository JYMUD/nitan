// Room: /d/xiangyang/caodi3.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short", "�ݵ�");
        set("long", @LONG
������������Ĳݵء��ɹű���������������İ���ȫ�����ˣ�
��Ȼ�ɹű�û�������ţ�����ɱ��Χ˿��������
LONG );
        set("outdoors", "xiangyang");
        set("no_clean_up", 0);
        set("exits", ([
                "north"  : __DIR__"southgate2",
                "south"  : "/d/wudang/wdroad5",
                //"west"   : __DIR__"hunanroad1", ȡ�������ﵽ����ɽ��·��
        ]));
        set("coor/x", -7820);
	set("coor/y", -830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}