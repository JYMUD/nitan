#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�ذ��Ŵ��");
        set("long", @LONG
�����Ǳ����ǵĵذ��Ŵ�֡��ֵ�����������������֣�������
�����ﲻ����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ���
�����������ŵ��ӵ������Լ�������ˣ�ŵ���ͯ������һ����æ����
��ʢ�����󡣱��߹��ذ��ŵ��ﾩ�ǵĳǽ����ϱ������ֵĵذ��Ź�
����
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_anmen",
                "south" : "/d/beijing/di_dajie1",
        ]));
        set("objects", ([
                "/d/beijing/npc/dipi" : 1,
                "/d/beijing/npc/tiaofu" : 2,
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}