//Room: /d/dali/paifang.c
//Date: June. 29 1998 by Java

inherit ROOM;

void create()
{
        set("short", "�Ʒ�");
        set("long", @LONG
���Ǵ���ǵ��Ʒ�������һ���Ʒ���д���ĸ���ɫ���֣� ʥ����
�ȡ������ǻʹ���������һ����ʯ��������ڴ�������������ӣ���
�ʹ�������ߣ������᲻�������������糱��
LONG );
        set("outdoors", "dali");
        set("exits", ([
                "east"  : "/d/dali/wangfulu",
                "west"  : "/d/dali/yujie",
                "south" : "/d/dali/taihejiekou",
                "north" : "/d/dali/northgate",
        ]));
        set("objects", ([
                CLASS_D("hu") + "/huyizhi" : 1
        ]));
	set("coor/x", -19130);
	set("coor/y", -6870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}