// xizhaoshan.c
// Date: Nov.1997 by Venus
#include <room.h>
inherit BUNCH_ROOM;
void create()
{
        set("short", "Ϧ��ɽ");
        set("long", @LONG
Ϧ��ɽ�ϱ�ֲ�����ͺ�㡣ÿ��������־�Ⱦ������׳�ۡ�ɽ
����һ�������׷������񻰡����ߴ����еİ�������Ǳ�����������
�������ÿ��Ϧ�����£��������ƣ���Ӱ���������������ʮ��֮һ
�ġ��׷�Ϧ�ա���
LONG);
        set("exits", ([
            "southdown"   : __DIR__"road16",
        ]));
        set("outdoors", "xihu");
        set("no_clean_up", 0);
	set("coor/x", 800);
	set("coor/y", -2080);
	set("coor/z", 10);
	setup();
}
