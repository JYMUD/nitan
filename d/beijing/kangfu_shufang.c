#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�������鷿");
        set("long", @LONG
�����ǿ������鷿�������������������ضѷ��źܶ��顣����
���ϻ���һЩ�ҳ�����Ȼ�Ǻܾ�û�ж����ˡ��������ļ���������
��ȴ���Ե�������͸��������ˡ�
LONG );
        set("exits", ([
                "south" : "/d/beijing/kangfu_zoulang2",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}