// This program is a part of NT MudLIB

#include <ansi.h>
inherit ROOM;

void create ()
{
        set ("short",GRN"����"NOR);
        set ("long", @LONG
�������人�ı��š�����ش������ش������ϱ߾�����ͷ��������
���кܶ����˺����ˣ��������ֵúܡ����С��С�����ų��������߹���
�������Լ�����Ʒ���м����ٱ����������������������ˡ�
LONG);

        set("exits", ([
                "south":__DIR__"hzjie1",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5090);
	set("coor/y", -1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}