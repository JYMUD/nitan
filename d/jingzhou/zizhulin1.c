#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "������");
        set("long", @LONG
����ǰͻȻһ���������������һ������������ɵĻ�԰(yua
n)��ǰ������Ʈ�������㣬�������񻷱���˵������ʫ�黭�⡣��
Լ������������Щ���ܡ�
LONG );
        set("outdoors", "jingzhou");

        set("exits", ([
                "north" : __DIR__"zizhulin",
                "enter" : __DIR__"xiaoyuan",
        ]));
        set("item_desc", ([
                "yuan": HIM "\n���￴����һ���ֻ��ĺõط�������Լ��������"
                        "����������\n�Ļ��ܣ��������������ɡ�\n" NOR
        ]) );
        set("coor/x", -7090);
	set("coor/y", -2100);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}