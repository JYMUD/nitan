inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","����");
        set("long", @LONG
��������ǺȾ����µļ�����һ��Сͤ�ӽ������������룬����
Χ����һЩ�����١�һ��΢�紵�����������ƺ��������Ļ���Ʈ����
��������
LONG );
        set("exits", ([
                "west" : "/d/beijing/hai_dayuan",
        ]));

	set("coor/x", -2800);
	set("coor/y", 7630);
	set("coor/z", 0);
	setup();
}