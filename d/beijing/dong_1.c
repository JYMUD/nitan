#include <room.h>
inherit ROOM;

void create()
{
        set("short", "�ض����");
        set("long", @LONG
�����Ǳ����ǵذ��ŵĶ��֡��ֵ�����������������֣�������
�����ﲻ����������ƥ�������С���������й�����ˣ��Ͼ��Ͽ���
�����������ŵ��ӵ������Լ�������ˣ�ŵ���ͯ������һ����æ����
��ʢ�����󡣱����ǵذ��Ŷ��ֵĹ㳡���ϱ߾������ϣ���ʱ�йٱ�
����������ԭ��������Ǿ��ǵ�������������Ĵ������ڵء�������
��������������֡�
LONG );
       set("exits", ([
                "north" : "/d/beijing/di_donggc",
                "east" : "/d/beijing/wang_7",
                "south" : "/d/beijing/dongchang_men",
        ]));
        set("objects", ([
                "/d/beijing/npc/bing2" : 1,
                "/d/beijing/npc/taijian" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2790);
	set("coor/y", 7710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}