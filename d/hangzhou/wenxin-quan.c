// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "����Ȫ");
        set("long", @LONG
����Ȫ������ɽ´�Ĺ����������ѩ���´���������ʫ�ƣ���
�е�ɽ�����Ȫһ��ͼ���ҿ����ٳߣ�������ǧ�顣������ͨ����
���Ƶβ��ݡ���Ȼ������Ȫ�����Ĳ������������������ǡ����ġ���
һȪ�����Ĵ�����������������ɽ�����ϵ��ˣ�������������һ
����Ȫ���������ʡ����������ճɾ�����������Ե������ɢ��
LONG );

        set("outdoors", "xihu");
        set("exits", ([
                "east" : "/d/hangzhou/shandao1",
         ]));

        set("objects", ([
                "/d/hangzhou/npc/qinger": 1,
        ]));

	set("coor/x", 760);
	set("coor/y", -1990);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}