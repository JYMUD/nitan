#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�ش���ҩ��");
        set("long", @LONG
�ش���ҩ�����������������������������ҩ�̡��㻹û�߽���
����ŵ�һ��ŨŨ��ҩ����ζ�����Ǵ�ҩ���ϵļ��ٸ�С������ɢ
�������ġ�һλ����ڹ�̨��վ�ţ�����Ц���к��ſ��ˡ�
LONG );
       set("exits", ([
                "west" : "/d/beijing/xi_2",
                "east" : "/d/beijing/liandan_neiting",
        ]));
        set("objects", ([
                "/d/beijing/npc/kid1" : 1,
                "/d/beijing/npc/yaopuhuoji" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7680);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}