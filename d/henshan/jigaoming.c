#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������̨");
        set("long", @LONG
�����Ǹ�������ߴ����������������顸[1��37m������[2��37��0m�����������ڴˣ�
�⼴���༫��(���޼�����)����⼫��(����������)��������������
�ģ���Ի������̨��
LONG );
        set("exits", ([ 
               "northdown"  : __DIR__"sansheng",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 4,
        ]));    

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6950);
	set("coor/y", -5580);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}