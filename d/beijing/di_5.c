#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�������");
        set("long", @LONG
�����Ǳ����ǵذ��ŵ����֡��ֵ�����������������֣�������
�����ﲻ����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ���
�����������ŵ��ӵ������Լ�������ˣ�ŵ���ͯ������һ����æ����
��ʢ�����󡣱����Ǿ���������Ǯׯ���ϱ��ǵذ��ŵ����ֹ㳡��
LONG );
       set("exits", ([
                "north" : "/d/beijing/qianzhuang",
                "south" : "/d/beijing/di_xigc",
                "east" : "/d/beijing/di_dajie1",
                "west" : "/d/beijing/di_4",
        ]));

        set("outdoors", "beijing");
	set("coor/x", -2810);
	set("coor/y", 7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}