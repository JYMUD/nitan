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
                "north" : "/d/beijing/di_dajie2",
                "south" : "/d/beijing/dianmen",
                "east" : "/d/beijing/dong_2",
                "west" : "/d/beijing/di_5",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}