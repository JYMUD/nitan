// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "ɽ��");
        set("long", @LONG
����������һ�����ѵ�ɽ���ϣ����߷�ï����ľɢ������������
�˵���Ϣ��Ϫ���ڹ��������ʣ�ˮ��������á�����������ɽ����ɫ��
��Ӱ���ף���ӳ�ɻ���
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/shandao2",
                "west"  : "/d/hangzhou/wenxin-quan",
                "south" : "/d/hangzhou/quanbian-xiaojing",
        ]));

//        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -1990);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}